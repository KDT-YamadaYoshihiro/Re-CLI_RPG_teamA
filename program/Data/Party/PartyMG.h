#pragma once
#include <vector>
#include <memory>

#define PARTY_MAX 4
class Character;

class PartyMG {
private:
    std::vector<std::unique_ptr<Character>> members;
    //共通ポイント
    int sharedSP = 3; 

public:
    // キャラの追加
    void AddMember(std::unique_ptr<Character> chara) { members.push_back(std::move(chara)); }

    // 生存しているメンバーのリストを返す
    std::vector<Character*> GetActiveMembers() {
        std::vector<Character*> actives;
        for (auto& m : members) if (m->IsLife()) actives.push_back(m.get());
        return actives;
    }

    int GetSP() const { return sharedSP; }
    void UseSP(int cost) { sharedSP -= cost; }
};