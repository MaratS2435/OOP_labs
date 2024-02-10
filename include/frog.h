#pragma once
#include "npc.h"
#include "dragon.h"
#include "bull.h"
#include "observer.h"

class FrogVisitor : public Visitor {};
class Frog : public NPC
{
    public:
        Frog(std::string name, int x, int y);
        Frog(std::istream &is);

        bool accept(std::shared_ptr<Visitor>& visitor, std::shared_ptr<NPC> attacker) override;
        void print() override;
        void print(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Frog &frog);
};