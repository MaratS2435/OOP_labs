#pragma once

#include "npc.hpp"

class Bull : public NPC{
public:
    Bull(int x, int y, std::string name);
    Bull();
    void whoami();
    ~Bull();
    void defend(std::shared_ptr<NPC> attacker) override;
    void attack(Dragon * defender) override;
    void attack(Bull * defender) override;
    void attack(Frog * defender) override;
};