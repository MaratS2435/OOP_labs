#include "factory.h"


std::shared_ptr<NPC> Create(NpcType type, std::string name, int x, int y) {
    std::shared_ptr<NPC> hero;
    switch (type) {
        case DragonType:
            hero = std::make_shared<Dragon>(name, x, y);
            break;
        case BullType:
            hero = std::make_shared<Bull>(name, x, y);
            break;
        case FrogType:
            hero = std::make_shared<Frog>(name, x, y);
            break;
    }
    return hero;
}

std::shared_ptr<NPC> Create(std::istream& stream) {
    std::shared_ptr<NPC> hero;
    int type;
    stream >> type;
    switch(type) {
        case DragonType:
            hero = std::make_shared<Dragon>(stream);
            break;
        case BullType:
            hero = std::make_shared<Bull>(stream);
            break;
        case FrogType:
            hero = std::make_shared<Frog>(stream);
            break;
    }
    return hero;
}

std::string randname() {
    std::map<int,std::string> name;
        name.insert({0, "Oleg"});
        name.insert({1, "Vova"});
        name.insert({2, "Dima"});
        name.insert({3, "Misha"});
        name.insert({4, "Kolya"});

    return name[std::rand() % 5];
}