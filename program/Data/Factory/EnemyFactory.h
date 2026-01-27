#pragma once
#include <memory>
#include <string>

class Character;

class EnemyFactory {
public:
	std::unique_ptr<Character>
	CreateEnemy(const std::string& enemyId);
};