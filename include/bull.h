#pragma once
#include "npc.h"
#include "dragon.h"
#include "frog.h"
#include "observer.h"


class Bull : public NPC
{
    public:
        Bull(std::string name, int x, int y);
        Bull(std::istream &is);

        bool accept(std::shared_ptr<NPC> visitor) override;
        bool visit(std::shared_ptr<Frog> other) override;
        void print() override;
        void print(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Bull &bull);
};