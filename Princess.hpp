#pragma once
#include "NPC.hpp"

struct Princess final: public NPC
{
    Princess(int x, int y);
    Princess(std::istream &is);

    void print() override;
    void save(std::ostream &os) override;
    bool accept(std::shared_ptr<NPC> attacker) override;
    friend std::ostream &operator<<(std::ostream &os, Princess &knight);
};