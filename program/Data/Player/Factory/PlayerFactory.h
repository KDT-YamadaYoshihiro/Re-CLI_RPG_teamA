#pragma once
#include <memory>
#include <string>

class Character;

// ファクトリクラス
class PlayerFactory
{
public:
	std::unique_ptr<Character>
		CreatePlayer(const std::string& playerID);
};