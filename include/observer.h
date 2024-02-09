#pragma once

#include "declaration.h"
#include "npc.h"

class Observer
{
    public :
        virtual void update(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender) = 0;
};