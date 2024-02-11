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
        //std::shared_mutex datamtx;
        std::mutex* mtx;

        FightManager(std::mutex* _mtx);

    public:
        static FightManager &get(std::mutex* _mtx);

        void add_event(FightEvent &&event);

        void operator()();
};