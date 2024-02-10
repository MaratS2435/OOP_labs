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

std::string randname(int x) {
    switch (x)
    {
    case 1:
        return "Oleg";
        break;
    case 2:
        return "Vova";
        break;
    case 3:
        return "Dima";
        break;
    case 4:
        return "Misha";
        break;
    case 5:
        return "Kolya";
        break;
    
    default:
        return "Noname";
        break;
    }
}