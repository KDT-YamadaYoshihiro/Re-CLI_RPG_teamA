#pragma once
#include <vector>
#include <memory>
#include "Data/Enemy/Factory/EnemyFactory.h"
#include "Data/Character/CharacterBase.h"

class EnemyMG {
private:
    std::vector<std::unique_ptr<Character>> enemies;
    EnemyFactory factory;

public:

    // 落とすお金
    int drop_gold;

    void SpawnWave(const std::vector<std::string>& ids) {
        enemies.clear();
        for (const auto& id : ids) {
            // 失敗時の処理
            if (auto enemyUnit = factory.CreateEnemy(id)) {
                enemies.push_back(std::move(enemyUnit));
            }
        }
    }

    std::vector<Character*> GetActiveEnemies() {
        std::vector<Character*> actives;
        for (auto& e : enemies) if (e->IsLife()) actives.push_back(e.get());
        return actives;
    }

    // エネミーリストのリセット
    void Clear()
    {
        enemies.clear();
    }
};