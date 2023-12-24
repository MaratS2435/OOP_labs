#pragma once
#include "NPC.hpp"
#include "Visitor.hpp"
struct Dragon final: public NPC
{
    Dragon(int x, int y);
    Dragon(std::istream &is);

    void print() override;
    bool accept(std::shared_ptr<NPC> attacker) override;

    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Dragon &dragon);
};