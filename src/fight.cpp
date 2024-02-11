#include "fight.h"

FightManager::FightManager(std::mutex* _mtx) {
    mtx = _mtx;
}

FightManager & FightManager::get(std::mutex* _mtx)
{
    static FightManager instance(_mtx);
    return instance;
}

void FightManager::add_event(FightEvent &&event)
{
    //std::lock_guard<std::shared_mutex> lock(datamtx);
    events.push(event);
}

void FightManager::operator()()
{
    time_t start_time = time(0);

    while (time(0) - start_time <= STOP + 1)
    {   
            if (!events.empty())
            {
                std::lock_guard<std::mutex> lock(*mtx);
                while (!events.empty()) {
                    std::optional<FightEvent> event;
                    event = events.back();
                    events.pop();
                    if (event->attacker->isAlive())     // no zombie fighting!
                        if (event->defender->isAlive()) // already dead!
                            if (event->defender->accept(event->attacker)) 
                                event->defender->must_die();
                }
            }
        std::this_thread::sleep_for(10ms);
    }
}