#pragma once
#include "Data/Party/PartyMG.h"
#include "Data/Party/EnemyMG.h"
#include "BattaleClc.h"
#include "System/KeyInput/KeyInput.h"
#include "System/TextView/TextView.h"
#include "Item/ItemManager/ItemManager.h"
#include <memory>

// 選択の進行状況
enum class SelectStep {
    SELECT_ACTION, // 通常かスキルか
    SELECT_SKILL_TYPE, // スキルの種類（1, 2, 3）
    SELECT_ITEM,        // アイテム選択
    SELECT_TARGET  // 対象選択
};

class BattleSystem {
private:
    PartyMG* m_party;
    EnemyMG* m_enemy;
    BattaleClc calc;

    // 誰の行動かの確認
    bool m_actionCheck = false;
    Character* m_actionUnit = nullptr;

    // 選択用カーソル
    SelectStep m_select = SelectStep::SELECT_ACTION;
    // 0: 通常攻撃, 1: スキル
    int m_actionType = 0; 
    // 1:単体, 2:全体, 3:回復
    int m_skillType = 0;   
    // 攻撃対象
    int m_target = 0; 
    // アイテム選択用
    int m_itemIndex = 0;  
    // 行動記録
    std::string m_actionLog = "戦闘開始！"; 
    // SP表示用
	std::string m_spLog = "";

    // --- 追加：勝敗判定用フラグ ---
    bool m_isFinished = false; // バトルが終了したか
    bool m_isVictory = false;  // プレイヤーが勝利したか

public:

    explicit BattleSystem(PartyMG & partyRef, EnemyMG & enemyRef)
         : m_party(&partyRef), m_enemy(&enemyRef) 
    {}

    void Update() {

        CheckBattleEnd();

        if (m_isFinished)
        {
            return;
        }

        if (!m_actionCheck) {
            // 全キャラの生存確認
            std::vector<Character*> all = m_party->GetActiveMembers();
            std::vector<Character*> enemies = m_enemy->GetActiveEnemies();
            all.insert(all.end(), enemies.begin(), enemies.end());

            // 誰かが10000に達するまでAPを増加させ続ける
            while (!m_actionCheck) {
                for (auto* chara : all) {
                    //calc.AddSpeed(chara->SetActionPoint(), chara->GetState().speed, chara->GetState().actionValue);
                    chara->SetActionPoint(calc.AddSpeed(chara->GetState().actionPoint, chara->GetState().speed));
                    if (chara->GetState().actionPoint >= 1000) {
                        m_actionCheck = true;
                        m_actionUnit = chara;
                    }
                    // SP表示の更新
                    m_spLog = "";
                    for (int i = 0; i < 3; ++i) {
                        if (i < m_party->GetSP()) {
                            m_spLog += "● ";
                        }
                        else {
                            m_spLog += "○ ";
                        }
                    }

                    break;
                }
            }
        }
        else {
            // コマンド選択中
            SelectSkill();
        }
    }

    void SelectSkill() {
        if (!m_actionUnit) return;

        if (m_actionUnit->GetFaction() == Faction::Player) {
            std::vector<Character*> enemyList = m_enemy->GetActiveEnemies();
            std::vector<Character*> partyList = m_party->GetActiveMembers();

            switch (m_select) {
            case SelectStep::SELECT_ACTION:
                // 0:通常, 1:スキル, 2:アイテム
                if (KeyInput::Instance().ChechKey(KeyInput::LEFT)) { m_actionType = (m_actionType + 2) % 3; }
                if (KeyInput::Instance().ChechKey(KeyInput::RIGHT)) { m_actionType = (m_actionType + 1) % 3; }

                if (KeyInput::Instance().ChechKey(KeyInput::ENTER)) {
                    // --- 修正：選択したアクションによって次のステップを分岐させる ---
                    if (m_actionType == 0)      m_select = SelectStep::SELECT_TARGET , m_party->UseSP(-1);     // 通常攻撃
                    else if (m_actionType == 1 and m_party->GetSP() > 0) m_select = SelectStep::SELECT_SKILL_TYPE, m_party->UseSP(1); // スキル
                    else if (m_actionType == 2) m_select = SelectStep::SELECT_ITEM;       // アイテム
                }
                break;

            case SelectStep::SELECT_SKILL_TYPE:
                if (KeyInput::Instance().ChechKey(KeyInput::LEFT)) m_skillType = (m_skillType + 2) % 3;
                if (KeyInput::Instance().ChechKey(KeyInput::RIGHT)) m_skillType = (m_skillType + 1) % 3;

                if (KeyInput::Instance().ChechKey(KeyInput::ENTER)) {
                    if (m_skillType == 1) { // 全体攻撃
                        ExecuteSkill(1, nullptr);
                        FinishTurn();
                    }
                    else {
                        m_select = SelectStep::SELECT_TARGET;
                    }
                }
                break;

            case SelectStep::SELECT_ITEM:
            {
                auto items = ItemManager::Instance().GetAllItems();
                if (items.empty()) {
                    m_actionLog = "アイテムを持っていません！";
                    m_select = SelectStep::SELECT_ACTION; // キャンセルして戻す
                    return;
                }
                // アイテム選択の上下移動
                if (KeyInput::Instance().ChechKey(KeyInput::UP)) m_itemIndex = (m_itemIndex + (int)items.size() - 1) % (int)items.size();
                if (KeyInput::Instance().ChechKey(KeyInput::DOWN)) m_itemIndex = (m_itemIndex + 1) % (int)items.size();

                if (KeyInput::Instance().ChechKey(KeyInput::ENTER)) {
                    m_select = SelectStep::SELECT_TARGET; // アイテムを決めたら対象選択へ
                }
            }
            break;

            case SelectStep::SELECT_TARGET:
                // ターゲットリストの決定（アイテムも味方ターゲットにする場合）
                bool targetFriend = (m_actionType == 2) || (m_actionType == 1 && m_skillType == 2);
                std::vector<Character*>* currentTargets = targetFriend ? &partyList : &enemyList;

                if (currentTargets->empty()) { m_select = SelectStep::SELECT_ACTION; return; }

                if (KeyInput::Instance().ChechKey(KeyInput::RIGHT)) m_target = (m_target + 1) % (int)currentTargets->size();
                if (KeyInput::Instance().ChechKey(KeyInput::LEFT)) m_target = (m_target + (int)currentTargets->size() - 1) % (int)currentTargets->size();

                if (KeyInput::Instance().ChechKey(KeyInput::ENTER)) {
                    if (m_actionType == 0) ExecuteNormalAttack((*currentTargets)[m_target]);
                    else if (m_actionType == 1) ExecuteSkill(m_skillType, (*currentTargets)[m_target]);
                    else if (m_actionType == 2) ExecuteUseItem((*currentTargets)[m_target]);
                    FinishTurn();
                }
                break;
            }
        }
        else {
            ExecuteEnemyAI();
        }
    }


    void ExecuteUseItem(Character* target) {
        auto items = ItemManager::Instance().GetAllItems();
        auto it = items.begin();
        std::advance(it, m_itemIndex);
        int itemID = it->first;

        m_actionLog = m_actionUnit->GetState().name + " は " + it->second.item->GetData().name + " を使った！";
        ItemManager::Instance().UseItem(itemID, *target);
    }

    // 通常攻撃の実行
    void ExecuteNormalAttack(Character* target) {
        if (!m_actionUnit || !target) return;

        // 物理ダメージ計算
        int damage = calc.ClcDamage(m_actionUnit->GetState().ATK, target->GetState().DEF);

        target->TakeDamage(damage); // ダメージ適用
        m_actionLog = m_actionUnit->GetState().name + " の攻撃！ " + target->GetState().name + " に " + std::to_string(damage) + " のダメージ！";
    }

    // スキルの使用
    void ExecuteSkill(int type, Character* target) {
        // チェック
        if (!m_actionUnit)
        {
            return;
        }
        if ((type == 0 || type == 2) && !target)
        {
            return;
        }

        int damage = 0;
        int avrg_damage = 0;
        switch (type) {
        case 0: // 単体ダメージ
            damage = calc.ClcMGCDamage(m_actionUnit->GetState().INT, target->GetState().MND);
            target->TakeDamage(damage);
            m_actionLog = m_actionUnit->GetState().name + " のスキル！ " + target->GetState().name + " に " + std::to_string(damage) + " のダメージ！";
            break;

        case 1: // 全体攻撃
        {
            for (auto* e : m_enemy->GetActiveEnemies()) {
                damage = calc.ClcMGCDamage(m_actionUnit->GetState().INT, e->GetState().MND) / 2;
                e->TakeDamage(damage);
                avrg_damage = (avrg_damage + damage) / 2;
            }
            m_actionLog = m_actionUnit->GetState().name + " のスキル！ " + " 全体 に " + std::to_string(damage) + " のダメージ！";
            break;
        }
        case 2: // 味方回復
        {
            int healVal = m_actionUnit->GetState().INT;
            target->Heal(healVal);
            m_actionLog = m_actionUnit->GetState().name + " のスキル！ " + target->GetState().name + " に " + std::to_string(healVal) + " を回復！";
            break;
        }
        }
    }

    void ExecuteEnemyAI() {
        // ターゲットのリストを取得
        std::vector<Character*> targetList = m_party->GetActiveMembers();

        // 空ならターン終了/勝敗処理へ分岐
        if (targetList.empty()) {
            FinishTurn();
            return;
        }

        // ターゲットを決定
        Character* targetUnit = targetList[rand() % targetList.size()];

        // 通常攻撃を実行
        // 物理ダメージ計算（敵のATK vs 味方のDEF）
        int damage = calc.ClcDamage(m_actionUnit->GetState().ATK, targetUnit->GetState().DEF);

        // ダメージの適用
        targetUnit->TakeDamage(damage);

        // ターン終了処理
        FinishTurn();
    }

    // 行動の終了
    void FinishTurn() {
        Status& s = const_cast<Status&>(m_actionUnit->GetState());
        s.actionPoint = 0;
        m_select = SelectStep::SELECT_ACTION;
        m_actionCheck = false;
        m_actionUnit = nullptr;
        m_actionType = 0;
        m_skillType = 0;
        m_target = 0;
        m_itemIndex = 0;
    }

    void Render(int money) {
        // 描画の初期化
        TextView::Instance().Add("====BATTLE====\n");

        // 味方の描画
        TextView::Instance().Add("【 味方 】");
        for (auto* unit : m_party->GetActiveMembers()) {
            std::string line = unit->GetState().name +
                " HP : " + std::to_string(unit->GetState().hp) +
                " / " + std::to_string(unit->GetState().MaxHP);
            TextView::Instance().Add(line);
        }
        TextView::Instance().Add("--------------------------------\n");
        
        // 敵の描画
        TextView::Instance().Add("【 敵 】");
        auto enemies = m_enemy->GetActiveEnemies();
        for (int i = 0; i < enemies.size(); ++i) {
            std::string line = enemies[i]->GetState().name +
                " HP : " + std::to_string(enemies[i]->GetState().hp) +
                " / " + std::to_string(enemies[i]->GetState().MaxHP);
            TextView::Instance().Add(line);
        }
        TextView::Instance().Add("--------------------------------\n");

        // 戦闘のログの描画
        TextView::Instance().Add("【 ログ 】");
        TextView::Instance().Add(m_actionLog); 

        TextView::Instance().Add("--------------------------------\n");

        // 現在のSPを表示　ある分は●、無い分は○で表示
		TextView::Instance().Add("【 SP 】 ");
        TextView::Instance().Add(m_spLog);

        TextView::Instance().Add("--------------------------------\n");


        // 終了時は結果を表示、進行中はコマンドを表示
        if (m_isFinished) {
            TextView::Instance().Add(m_isVictory ? "敵が " + std::to_string(money) + "ゴールドを落とした。 \n" : "");
            TextView::Instance().Add(m_isVictory ? "[勝利！ Spaceでマップへ]" : "[敗北... Spaceでタイトルへ]");
        }
        else {
            DrawCommand(); // 既存の描画ロジック
        }
    }

    // --- 追加：アクセサ ---
    bool IsFinished() const { return m_isFinished; }
    bool IsVictory() const { return m_isVictory; }

private:

    // --- 追加：勝敗判定ロジック ---
    void CheckBattleEnd()
    {
        // プレイヤー全滅チェック
        if (m_party->GetActiveMembers().empty()) {
            m_isFinished = true;
            m_isVictory = false;
        }
        // 敵全滅チェック
        else if (m_enemy->GetActiveEnemies().empty()) {
            m_isFinished = true;
            m_isVictory = true;
        }
    }

    // SelectStep
    void DrawCommand() {
        TextView::Instance().Add("【 選択 】");
        if (m_actionCheck && m_actionUnit && m_actionUnit->GetFaction() == Faction::Player) {
            std::string selectingText = "";
            switch (m_select) {
            case SelectStep::SELECT_ACTION:
                selectingText = m_actionUnit->GetState().name +  " が 行動を選択中: ";
                selectingText += (m_actionType == 0) ? "●[通常攻撃] " : "  通常攻撃 ";
                selectingText += (m_actionType == 1) ? "●[スキル] " : "  スキル ";
                selectingText += (m_actionType == 2) ? "●[アイテム]" : "  アイテム"; // ★追加
                break;

            case SelectStep::SELECT_SKILL_TYPE:
                selectingText = "スキルを選択中: ";
                selectingText += (m_skillType == 0) ? "●[単体]" : "  単体 ";
                selectingText += (m_skillType == 1) ? "●[全体]" : "  全体 ";
                selectingText += (m_skillType == 2) ? "●[回復]" : "  回復 ";
                break;

            case SelectStep::SELECT_ITEM: // ★追加アイテムリストの表示
            {
                auto items = ItemManager::Instance().GetAllItems();
                if (items.empty()) {
                    selectingText = "アイテムがありません！";
                }
                else {

                    int currentIndex = 0; // ループの回数をカウント

                    for (auto it = items.begin(); it != items.end(); ++it) {
                        std::string line = "";

                        // 現在のループ回数が、選択中のインデックスと一致するか判定
                        if (currentIndex == m_itemIndex) {
                            // 選択中の行
                            line = "・[" + it->second.item->GetData().name + " x" + std::to_string(it->second.count)  + "]";
                        }
                        else {
                            // 選択されていない行（頭にスペースを入れて揃えると綺麗です）
                            line = "  " + it->second.item->GetData().name + " x" + std::to_string(it->second.count);
                        }

                        // 1行ずつTextViewに追加して描画する
                        TextView::Instance().Add(line);

                        currentIndex++;
                    }
                }
            }
            break;

            case SelectStep::SELECT_TARGET:
                selectingText = "対象を選択中: ";
                std::vector<Character*> enemyList = m_enemy->GetActiveEnemies();
                std::vector<Character*> partyList = m_party->GetActiveMembers();
                // アイテム(Type:2)または回復スキル(Type:1, Skill:2)なら味方を選択
                bool isFriendTarget = (m_actionType == 2) || (m_actionType == 1 && m_skillType == 2);
                std::vector<Character*>* currentTargets = isFriendTarget ? &partyList : &enemyList;

                for (int list = 0; list < currentTargets->size(); list++) {
                    if (list == m_target) 
                    {
                        selectingText += "●[" + (*currentTargets)[list]->GetState().name + "]  ";
                    }
                    else 
                    {
                        selectingText += (*currentTargets)[list]->GetState().name + "  ";
                    }
                }

                break;
            }
            TextView::Instance().Add(selectingText);
        }
        else if (m_actionCheck && m_actionUnit && m_actionUnit->GetFaction() == Faction::Enemy) {
            TextView::Instance().Add("敵が思考中...");
        }
        else {
            TextView::Instance().Add("待機中..."); // AP計算が止まっているとここから動かない
        }
    }
};