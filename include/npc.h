#pragma once

#include <iostream>
#include <memory>
#include <cstring>
#include <string>
#include <random>
#include <fstream>
#include <set>
#include <math.h>
#include <map>
#include <unordered_map>

// type for npcs
class NPC;
class Dragon;
class Bull;
class Frog;
class Observer;
class ObserverConsole;
class ObserverFile;
using set_t = std::set<std::shared_ptr<NPC>>;

enum NpcType
{
    Unknown = 0,
    DragonType = 1,
    BullType = 2,
    FrogType = 3
};

struct Visitor {
    virtual bool visit(const std::shared_ptr<Dragon>&);
    virtual bool visit(const std::shared_ptr<Bull>&);
    virtual bool visit(const std::shared_ptr<Frog>&);
};

class NPC : public std::enable_shared_from_this<NPC>
{
    private:
        NpcType type;
        std::string _name;
        int x{0};
        int y{0};
        std::vector<std::shared_ptr<Observer>> observers;

    public:

        NPC(NpcType t, std::string name, int _x, int _y);
        NPC(NpcType t, std::istream &is);
        ~NPC() = default;

        int get_x() const;
        int get_y() const;
        NpcType get_type() const;
        std::string get_name() const;
        void subscribe(std::shared_ptr<Observer> observer);
        void fight_notify(const std::shared_ptr<NPC> defender);
        virtual bool is_close(const std::shared_ptr<NPC> &other, std::size_t distance) const;
        virtual void print() = 0;
        virtual void print(std::ostream &os) = 0;

        virtual bool accept(std::shared_ptr<Visitor>& visitor, std::shared_ptr<NPC> attacker) = 0;

    friend std::ostream &operator<<(std::ostream &os, NPC &npc);
};