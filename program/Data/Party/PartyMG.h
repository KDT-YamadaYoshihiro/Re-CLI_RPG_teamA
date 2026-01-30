#pragma once
#include <vector>
#include <memory>

#define PARTY_MAX 4
class Character;

class PartyMG
{
private:
public:
	void Init();
	const std::vector<std::unique_ptr<Character>>& GetParty() const;
};