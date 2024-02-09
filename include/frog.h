#ifndef Frog_H
#define Frog_H

#include "npc.h"
#include "dragon.h"
#include "bull.h"

class Frog : public NPC
{
    public:
        Frog(int x, int y);
        Frog(std::istream& is);
        virtual ~Frog() = default;

        int getDistMove() override;
        int getDistFight() override;

        void print() override;
        void print(std::ostream &os) override;

        bool accept(std::shared_ptr<NPC> visitor) override;      

    protected:
        int dist_move = 1;
        int dist_fight = 10;
};

#endif