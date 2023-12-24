#pragma once
#include <queue>
#include <shared_mutex>
#include "fstream"
#include "ctime"
#include <algorithm>
#include <chrono>
#include <thread>
#include <optional>
#include "npc.h"
#include "bear.h"
#include "squirrel.h"
#include "orc.h"

using namespace std::chrono_literals;
#define ESPILON 0.001

using namespace std::chrono_literals;



namespace Commands {
    const int LOSE = 0;
    const int WIN = 1;
    const int BATTLE_END = 3;
    const int BATTLE_START = 2;
}

struct ObserverBattlefield;

class Battlefield {
    friend class FightManager;
    public:
        Battlefield();

        friend std::ostream &operator<<(std::ostream &os, Battlefield &btf);

        void attachObs(std::shared_ptr<ObserverBattlefield> observer);
        void detachObs(std::shared_ptr<ObserverBattlefield> observer);
        void notify(int win);

        void fillRandomly(size_t seed, size_t orcs, size_t squrrels, size_t bears);
        void placeHero(std::shared_ptr<NPC> npc);
        void removeHero(std::shared_ptr<NPC> npc);
        void removeDeadmen();

        std::list<std::shared_ptr<NPC>> npc();
        void battle();
    private:
        std::pair<int, int> _size;
        std::list<std::shared_ptr<NPC>> _npcList;
        std::list<std::shared_ptr<ObserverBattlefield>> _observers;
};

struct FightMMA {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class FightManager {
    
    private:
        std::queue<FightMMA> _events;
        std::shared_mutex _mtx;
    public:
        FightManager() = default;
        static FightManager & get();
        void push_event(FightMMA && event);
        void operator()();
};

struct ObserverBattlefield: public std::enable_shared_from_this<ObserverBattlefield> {
    virtual void battleStart(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> _npcList) = 0;
    virtual void fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) = 0;
    virtual void battleEnd(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> _npcList) = 0;
};

class ObserverBattlefieldOstream : public ObserverBattlefield {
    public:
        void battleStart(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> _npcList) override;
        void fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override;
        void battleEnd(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> _npcList) override;
};

class ObserverBattlefieldFile : public ObserverBattlefield {
    public:
        ObserverBattlefieldFile();
        ~ObserverBattlefieldFile();
        void battleStart(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> _npcList) override;
        void fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override;
        void battleEnd(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> _npcList) override;
    private:
        std::ofstream file;
};