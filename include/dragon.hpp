#pragma once

#include "npc.hpp"

class Dragon : public NPC{
public:
    Dragon(int x, int y, std::string name);
    Dragon();
    void whoami();
    ~Dragon();
    void defend(std::shared_ptr<NPC> attacker) override;
    void attack(Dragon* defender) override;
    void attack(Frog* defender) override;
    void attack(Bull * defender) override;
};