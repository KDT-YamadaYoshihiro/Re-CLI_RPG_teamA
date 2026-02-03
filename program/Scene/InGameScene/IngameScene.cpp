#include "InGameScene.h"
#include "System/TextView/TextView.h"
#include "SceneManager/SceneManager.h"
#include "Scene/TitleScene/TitleScene.h"
#include "Data/Player/Factory/PlayerFactory.h"
#include "Data/Enemy/Factory/EnemyFactory.h"
#include "Scene/EndingScene/EndingScene.h"

/// <summary>
/// 初期化
/// </summary>
InGameScene::InGameScene()
	:m_currentPhase(GamePhase::MAP_SELECT)
{
	// 乱数初期化
	srand(static_cast<unsigned int>(time(nullptr)));
}

InGameScene::~InGameScene()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <returns></returns>
bool InGameScene::Init()
{
	m_map = std::make_unique<Map>();

	if (!m_map)
	{
		TextView::Instance().Add("Ingame/m_map : nullptr");
		return false;
	}

	PlayerFactory pFactory;
	m_party.AddMember(pFactory.CreatePlayer("hero"));
	m_party.AddMember(pFactory.CreatePlayer("mage"));
	m_party.AddMember(pFactory.CreatePlayer("ninja"));
	m_party.AddMember(pFactory.CreatePlayer("cleric"));

	m_battle = std::make_unique<BattleSystem>(m_party, m_enemy);
	if (!m_battle)
	{
		TextView::Instance().Add("Ingame/m_battle : nulptr");
		return false;
	}

	auto& itemMgr = ItemManager::Instance();
	// 代表者（誰の所持品か。現在は共有イベント等のため先頭キャラをオーナーとする）
	Character* owner = m_party.GetActiveMembers()[0]; // 先頭キャラ取得

	// 低級ポーションを5つ追加
	ItemFactory::Instance().OnCreate();
	int potionID = static_cast<int>(ItemIdType::LowerPotion);
	int potionID2 = static_cast<int>(ItemIdType::MiddlePotion);
	for (int i = 0; i < 5; ++i)
	{
		itemMgr.AddItem(potionID, *owner);
		itemMgr.AddItem(potionID2, *owner);
	}

	m_shop = std::make_unique<ShopSystem>(*owner, ItemManager::Instance());
	if (!m_shop)
	{
		TextView::Instance().Add("Ingame/m_shop : nullptr");
		return false;
	}

	return true;
}

/// <summary>
/// 更新
/// </summary>
void InGameScene::Update()
{
	// ダンジョン踏破時
	if (m_map->GetIsCleared())
	{
		TextView::Instance().Reset();
		SceneManager::Instance().ChangeScene<EndingScene>();
	}

	switch (m_currentPhase)
	{
	case GamePhase::MAP_SELECT:					// マップ探索
	{
		// 内部で入力待ちループが走るため、戻ってきたときは選択済み
		SceneType nextScene = m_map->SelectScene();

		// 選択されたシーンに応じてフェーズを切り替える
		if (nextScene == SceneType::BATTLE || nextScene == SceneType::BOSS) {
			// --- バトル開始前の準備 ---

			// 1. 以前の敵情報をクリア (EnemyMGにClear関数が必要)
			m_enemy.Clear();

			// SkillPointをリセット
			m_party.SetSP(2);

			// 2. 敵を生成 (EnemyDataBaseにあるIDを指定)

			std::vector<std::string> enemyIds;
			if (nextScene == SceneType::BOSS)
			{
				// ボス
				enemyIds.push_back("boss");
				m_enemy.SpawnWave(enemyIds);
			}
			else {		
				// ボス以外
				enemyIds = EnemyEntity(m_enemy.drop_gold,m_map->Get_current_floor());
				m_enemy.SpawnWave(enemyIds);
			}

			// 3. バトルシステムを新規作成して開始
			m_battle = std::make_unique<BattleSystem>(m_party, m_enemy);

			m_currentPhase = GamePhase::BATTLE;
		}
		else if (nextScene == SceneType::SHOP) {
			inShop = true;
			m_currentPhase = GamePhase::SHOP;
		}

		break;
	}
	case GamePhase::BATTLE:						// バトル処理
	{
		if (m_battle) {
			m_battle->Update();

			// バトルが終了したかチェック
			if (m_battle->IsFinished()) {
				if (KeyInput::Instance().ChechKey(KeyInput::SPACE)) {
					if (m_battle->IsVictory()) {
						// 勝利ならマップへ戻る
						m_battle.reset();
						m_currentPhase = GamePhase::MAP_SELECT;
					}
					else {
						// 敗北ならゲームオーバー（またはタイトル）へ
						 SceneManager::Instance().ChangeScene<TitleScene>();
					}
				}
			}
		}
		 break;
	}
	case GamePhase::SHOP:
	{
		if (!m_shop) {
			m_shop = std::make_unique<ShopSystem>(*m_party.GetActiveMembers()[0], ItemManager::Instance());
			inShop = true; // ショップ開始
		}

		if (inShop)
		{
			m_shop->Update();

			// ショップ側でESCが押される等して IsExit() が true になったら終了処理
			if (m_shop->IsExit())
			{
				inShop = false;
				m_shop.reset(); // ここでリセット
				m_currentPhase = GamePhase::MAP_SELECT; // ここでフェーズを戻す
			}
		}
		break;
	}
	case GamePhase::GAMEOVER:
	{
		// 終了処理

		break;
	}
	case GamePhase::CLEAR:
	{
		break;
	}
	default:
		break;
	}

}

/// <summary>
/// 描画
/// </summary>
void InGameScene::Render()
{
	switch (m_currentPhase)
	{
	case GamePhase::MAP_SELECT:
		m_map->DrawInfo();
		break;
	case GamePhase::BATTLE:
		if(m_battle) m_battle->Render(m_enemy.drop_gold);
		break;
	}

	TextView::Instance().RenderFrame();

}


/// <summary>
/// 
/// </summary>
/// <param name="nextScene"></param>
void InGameScene::PhaseTransition(SceneType nextScene)
{
	switch (nextScene)
	{
	case SceneType::BATTLE: m_currentPhase = GamePhase::BATTLE; break;
	case SceneType::SHOP:   m_currentPhase = GamePhase::SHOP;   break;
	case SceneType::BOSS:   m_currentPhase = GamePhase::BATTLE; break; // ボスもバトルフェーズへ
	default:                m_currentPhase = GamePhase::MAP_SELECT; break;
	}
}

std::vector<std::string> InGameScene::EnemyEntity(int& money,int floor)
{
	std::vector<std::string> ids;

	// 1. 出現候補の敵IDリスト (EnemyDataBaseに登録されているIDである必要があります)
	// ここに "goblin" や "bat" などを自由に追加してください
	std::vector<std::string> enemyPool = {
		"slime",
		"goblin",
		"bat"
	};

	// 2. 出現数を決定 (例: 1体 ～ 3体)
	// rand() % 3 で 0~2 になるので +1 して 1~3
	int count = (rand() % 3) + 1;
	money = 0;

	// 3. ランダムに抽出してリストに追加
	for (int i = 0; i < count; ++i)
	{
		// poolのサイズで剰余を取ってインデックスを決める
		int index = rand() % enemyPool.size();
		ids.push_back(enemyPool[index]);
		//int enemy_drop_money = std::stoi(ids[count]) * 10;
		money += 10 * (floor + 1);
	}


	return ids;
}

