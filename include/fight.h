#pragma once

#include "declaration.h"
#include "npc.h"

struct FightEvent
{
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class FightManager
{
    private:
        std::queue<FightEvent> events;
        std::shared_mutex mtx;

        FightManager() {};

    public:
        static FightManager &get();

        void add_event(FightEvent &&event);

        void operator()();
};