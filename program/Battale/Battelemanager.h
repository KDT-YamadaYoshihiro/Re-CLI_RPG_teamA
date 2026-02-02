#pragma once
#include "../Data/Party/PartyMG.h"
#include "../Data/Party/EnemyMG.h"
#include "BattaleClc.h"
#include "../System/KeyInput/KeyInput.h"
#include "../System/TextView/TextView.h"
#include <memory>

// 選択の進行状況
enum class SelectStep {
    SELECT_ACTION, // 通常かスキルか
    SELECT_SKILL_TYPE, // スキルの種類（1, 2, 3）
    SELECT_TARGET  // 対象選択
};

class BattleManager {
private:
    PartyMG* party;
    EnemyMG* enemy;
    BattaleClc calc;

    // 誰の行動かの確認
    bool actioncheck = false;
    Character* actionUnit = nullptr;

    // 選択用カーソル
    SelectStep select = SelectStep::SELECT_ACTION;
    // 0: 通常攻撃, 1: スキル
    int actionType = 0; 
    // 1:単体, 2:全体, 3:回復
    int skillType = 0;   
    // 攻撃対象
    int target = 0; 
    // 行動記録
    std::string actionLog = "戦闘開始！"; 

public:

    explicit BattleManager(PartyMG & partyRef, EnemyMG & enemyRef)
         : party(&partyRef), enemy(&enemyRef) 
    {}

    void Update() {
        // 全生存キャラクターを1つのリストに集める
        std::vector<Character*> all = party->GetActiveMembers();
        std::vector<Character*> enemies = enemy->GetActiveEnemies();
        all.insert(all.end(), enemies.begin(), enemies.end());

        // 全員の行動地が10000を超えてないか確認する
        for (auto* chara : all) {
            if (chara->GetState().actionPoint >= 10000) {
                actioncheck = true;
                actionUnit = chara;
            }
        }

        // 超えている奴がいないなら
        if (!actioncheck) {
            for (auto* chara : all) {
                calc.AddSpeed(chara->GetState().actionPoint, chara->GetState().speed, chara->GetState().actionValue);
            }
        }
        else {
            SelectSkill();
        }
    }

    void SelectSkill() {
        if (!actionUnit) return;

        // 味方なら
        if (actionUnit->GetFaction() == Faction::Player) {
            // 生存している対象リストを取得
            std::vector<Character*> enemyList = enemy->GetActiveEnemies();
            std::vector<Character*> partyList = party->GetActiveMembers();

            switch (select) {
            case SelectStep::SELECT_ACTION:
                // 入力処理
                if (KeyInput::Instance().ChechKey(KeyInput::LEFT)) { actionType = 0; }
                if (KeyInput::Instance().ChechKey(KeyInput::RIGHT)) { actionType = 1; }

                if (KeyInput::Instance().ChechKey(KeyInput::ENTER)) {
                    if (actionType == 0) {
                        select = SelectStep::SELECT_TARGET; // 通常攻撃はすぐ対象選択へ
                    }
                    else {
                        select = SelectStep::SELECT_SKILL_TYPE; // スキルは詳細選択へ
                    }
                }
                break;
            case SelectStep::SELECT_SKILL_TYPE:
                // 1:単体, 2:全体, 3:回復 の選択
                if (KeyInput::Instance().ChechKey(KeyInput::LEFT)) skillType = (skillType + 2) % 3;
                if (KeyInput::Instance().ChechKey(KeyInput::RIGHT)) skillType = (skillType + 1) % 3;

                if (KeyInput::Instance().ChechKey(KeyInput::ENTER)) {
                    if (skillType == 1) { // 2:全体攻撃
                        ExecuteSkill(1, nullptr); // 対象選択不要
                        FinishTurn();
                    }
                    else {
                        select = SelectStep::SELECT_TARGET; // 1:単体攻撃 or 3:回復 は対象選択へ
                    }
                }
                break;
            case SelectStep::SELECT_TARGET:
                // 対象リストの取得（スキル3なら味方、それ以外なら敵）
                std::vector<Character*>* currentTargets = (actionType == 1 && skillType == 2) ? &partyList : &enemyList;

                // 範囲外アクセス対策
                if (currentTargets->empty()) {
                    target = 0;
                    return;
                }

                if (KeyInput::Instance().ChechKey(KeyInput::UP)) {
                    //target++;
                    //int maxIndex = static_cast<int>(currentTargets->size()) - 1;
                    target = (target + 1) % static_cast<int>(currentTargets->size());
                }
                if (KeyInput::Instance().ChechKey(KeyInput::DOWN)) {
                    //target--;
                    //if (target < 0) target = 0;
                    target = (target + static_cast<int>(currentTargets->size()) - 1) % static_cast<int>(currentTargets->size());
                }

                if (KeyInput::Instance().ChechKey(KeyInput::ENTER)) {
                    if (actionType == 0) ExecuteNormalAttack((*currentTargets)[target]);
                    else ExecuteSkill(skillType, (*currentTargets)[target]);
                    FinishTurn();
                }
                break;
            }
        }
        else {
            ExecuteEnemyAI();
        }
    }
    
    // 通常攻撃の実行
    void ExecuteNormalAttack(Character* target) {
        if (!actionUnit || !target) return;

        // 物理ダメージ計算
        int damage = calc.ClcDamage(actionUnit->GetState().ATK, target->GetState().DEF);

        target->TakeDamage(damage); // ダメージ適用
        actionLog = actionUnit->GetState().name + " の攻撃！ " + target->GetState().name + " に " + std::to_string(damage) + " のダメージ！";
    }

    // スキルの使用
    void ExecuteSkill(int type, Character* target) {
        // チェック
        if (!actionUnit)
        {
            return;
        }
        if ((type == 0 || type == 2) && !target)
        {
            return;
        }

        int damage = 0;
        switch (type) {
        case 0: // 単体ダメージ
            damage = calc.ClcMGCDamage(actionUnit->GetState().INT, target->GetState().MND);
            target->TakeDamage(damage);
            actionLog = actionUnit->GetState().name + " のスキル！ " + target->GetState().name + " に " + std::to_string(damage) + " のダメージ！";
            break;

        case 1: // 全体攻撃
            int avrg_damage = 0;
            for (auto* e : enemy->GetActiveEnemies()) {
                damage = calc.ClcMGCDamage(actionUnit->GetState().INT, e->GetState().MND) / 2;
                e->TakeDamage(damage);
                avrg_damage = (avrg_damage + damage) / 2;
            }
            actionLog = actionUnit->GetState().name + " のスキル！ " + " 全体 に " + std::to_string(damage) + " のダメージ！";
            break;

        case 2: // 味方回復
            int healVal = actionUnit->GetState().INT;
            target->Heal(healVal);
            actionLog = actionUnit->GetState().name + " のスキル！ " + target->GetState().name + " に " + std::to_string(healVal) + " を回復！";
            break;
        }
    }

    void ExecuteEnemyAI() {
        // ターゲットのリストを取得
        std::vector<Character*> targetList = party->GetActiveMembers();

        // 空ならターン終了/勝敗処理へ分岐
        if (targetList.empty()) {
            FinishTurn();
            return;
        }

        // ターゲットを決定
        Character* targetUnit = targetList[rand() % targetList.size()];

        // 通常攻撃を実行
        // 物理ダメージ計算（敵のATK vs 味方のDEF）
        int damage = calc.ClcDamage(actionUnit->GetState().ATK, targetUnit->GetState().DEF);

        // ダメージの適用
        targetUnit->TakeDamage(damage);

        // ターン終了処理
        FinishTurn();
    }

    // 行動の終了
    void FinishTurn() {
        Status& s = const_cast<Status&>(actionUnit->GetState());
        s.actionPoint = 0;
        select = SelectStep::SELECT_ACTION;
        actioncheck = false;
        actionUnit = nullptr;
    }


    void Render() {
        // 描画の初期化
        TextView::Instance().Reset();

        // 味方の描画
        TextView::Instance().Add("【 味方 】");
        for (auto* unit : party->GetActiveMembers()) {
            std::string line = unit->GetState().name +
                " HP : " + std::to_string(unit->GetState().hp) +
                " / " + std::to_string(unit->GetState().MaxHP);
            TextView::Instance().Add(line);
        }
        TextView::Instance().Add("--------------------------------");
        
        // 敵の描画
        TextView::Instance().Add("【 敵 】");
        auto enemies = enemy->GetActiveEnemies();
        for (int i = 0; i < enemies.size(); ++i) {
            std::string line = enemies[i]->GetState().name +
                " HP : " + std::to_string(enemies[i]->GetState().hp) +
                " / " + std::to_string(enemies[i]->GetState().MaxHP);
            TextView::Instance().Add(line);
        }
        TextView::Instance().Add("--------------------------------");

        // 戦闘のログの描画
        TextView::Instance().Add("【 ログ 】");
        TextView::Instance().Add(actionLog); 

        TextView::Instance().Add("--------------------------------");

        // 選択の描画
        TextView::Instance().Add("【 選択 】");
        if (actioncheck && actionUnit->GetFaction() == Faction::Player) {
            std::string selectingText = "";

            switch (select) {
            case SelectStep::SELECT_ACTION:
                selectingText = "行動を選択中: ";
                selectingText += (actionType == 0) ? "?[通常攻撃]" : "  通常攻撃";
                selectingText += (actionType == 1) ? "  ?[スキル]" : "    スキル";
                break;

            case SelectStep::SELECT_SKILL_TYPE:
                selectingText = "スキルを選択中: ";
                if (skillType == 0) selectingText += "?[単体]";
                else if (skillType == 1) selectingText += "?[全体]";
                else if (skillType == 2) selectingText += "?[回復]";
                break;

            case SelectStep::SELECT_TARGET:
                selectingText = "対象を選択中: ";
                // 現在のターゲットの名前を取得して表示
                std::vector<Character*> enemyList = enemy->GetActiveEnemies();
                std::vector<Character*> partyList = party->GetActiveMembers();
                std::vector<Character*>* currentTargets = (actionType == 1 && skillType == 2) ? &partyList : &enemyList;

                if (!currentTargets->empty()) {
                    selectingText += "?[" + (*currentTargets)[target]->GetState().name + "]";
                }
                break;
            }
            TextView::Instance().Add(selectingText);
        }
        else if (actioncheck && actionUnit->GetFaction() == Faction::Enemy) {
            TextView::Instance().Add("敵が思考中...");
        }
        else {
            TextView::Instance().Add("待機中...");
        }
        TextView::Instance().Add("--------------------------------");

        TextView::Instance().RenderFrame();
    }
};