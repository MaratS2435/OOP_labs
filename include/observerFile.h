#pragma once

#include "observer.h"

class ObserverFile : public Observer
{
    public :
        void update(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender) override;
};
