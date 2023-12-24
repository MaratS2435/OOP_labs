#pragma once

#include "npc.hpp"

class Frog : public NPC{
public:
    Frog(int x, int y, std::string name);
    Frog();
    void whoami();
    ~Frog();
    void defend(std::shared_ptr<NPC> attacker) override;
    void attack(Dragon* defender) override;
    void attack(Frog* defender) override;
    void attack(Bull * defender) override;
};