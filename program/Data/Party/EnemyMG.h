#pragma once
#include <vector>
#include <memory>
#include "../Enemy/Factory/EnemyFactory.h"
#include "../Character/CharacterBase.h"

class EnemyMG {
private:
    std::vector<std::unique_ptr<Character>> enemies;
    EnemyFactory factory;

public:
    void SpawnWave(const std::vector<std::string>& ids) {
        enemies.clear();
        for (const auto& id : ids) {
            enemies.push_back(factory.CreateEnemy(id));
        }
    }

    std::vector<Character*> GetActiveEnemies() {
        std::vector<Character*> actives;
        for (auto& e : enemies) if (e->IsLife()) actives.push_back(e.get());
        return actives;
    }
};