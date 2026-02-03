#pragma once
#include "Scene/SceneBase/SceneBase.h"
#include "Map/Map.h"
#include "Shop/ShopSysytem.h"
#include "Battale/BattleSystem.h"
#include "Data/Character/CharacterBase.h"
#include "Item/ItemManager/ItemManager.h"
#include <memory>

// ゲーム本編の進行状態
enum class GamePhase
{
    MAP_SELECT,  // マップ移動先選択
    BATTLE,      // 戦闘中
    SHOP,        // ショップ
    GAMEOVER,    // ゲームオーバー
    CLEAR        // ゲームクリア
};

class InGameScene : public SceneBase
{
private:
    // 進行状態
    GamePhase m_currentPhase;
    // 共有実態
    PartyMG m_party;
    EnemyMG m_enemy;

    // 各システム
    std::unique_ptr<Map> m_map;                 // 探索シーン
    std::unique_ptr<ShopSystem> m_shop;         // ショップ
    std::unique_ptr<BattleSystem> m_battle;    // バトル

    bool inShop = true;

public:
	InGameScene();
	~InGameScene();

	bool Init() override;
	void Update() override;
	void Render() override;

private:

    /// <summary>
    ///　次のシーン
    /// </summary>
    /// <param name="nextScene"></param>
    void PhaseTransition(SceneType nextScene);

    /// <summary>
    /// ランダムな敵のIDリストを生成する
    /// </summary>
    std::vector<std::string> EnemyEntity(int& money,int floor);

};