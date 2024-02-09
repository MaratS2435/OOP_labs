#pragma once

#include "npc.h"
#include "dragon.h"
#include "frog.h"

class Bull : public NPC
{
    public:
        Bull(int x, int y);
        Bull(std::istream& is);
        virtual ~Bull() = default;

        int getDistMove() override;
        int getDistFight() override;

        bool accept(std::shared_ptr<NPC> visitor) override;
        bool visit(std::shared_ptr<Frog> monster) override;

        void print() override;
        void print(std::ostream &os) override;

    protected:
        int dist_move = 30;
        int dist_fight = 10;
};
