#pragma once
#include "npc.h"
#include "Visitor.hpp"

struct WanderingKnight : public NPC
{
    WanderingKnight(int x, int y);
    WanderingKnight(std::istream &is);
    void print() override;
    void save(std::ostream &os) override;
    bool accept(std::shared_ptr<NPC> attacker) override;
    friend std::ostream &operator<<(std::ostream &os, WanderingKnight &WanderingKnight);
};
