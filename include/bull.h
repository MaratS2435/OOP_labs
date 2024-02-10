#pragma once
#include "npc.h"
#include "dragon.h"
#include "frog.h"
#include "observer.h"

class BullVisitor : public Visitor {
    bool visit(const std::shared_ptr<Frog>& other) override;
};

class Bull : public NPC
{
    public:
        Bull(std::string name, int x, int y);
        Bull(std::istream &is);

        bool accept(std::shared_ptr<Visitor>& visitor, std::shared_ptr<NPC> attacker) override;
        void print() override;
        void print(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Bull &bull);
};