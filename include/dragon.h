#pragma once

#include "npc.h"
#include "bull.h"
#include "frog.h"

class Dragon : public NPC 
{
    public:
        Dragon(int x, int y);
        Dragon(std::istream& is);
        virtual ~Dragon() = default;

        int getDistMove() override;
        int getDistFight() override;

        bool accept(std::shared_ptr<NPC> visitor) override;
        bool visit(std::shared_ptr<Bull> monster) override;

        void print() override;
        void print(std::ostream &os) override;

    protected:
        int dist_move = 50;
        int dist_fight = 30;
};