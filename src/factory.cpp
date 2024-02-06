#include "factory.h"

std::shared_ptr<NPC> Create(NpcType type, int x, int y) {
    std::shared_ptr<NPC> hero;
    switch (type) {
        case DragonType:
            hero = std::make_shared<Dragon>(x, y);
            break;
        case BullType:
            hero = std::make_shared<Bull>(x, y);
            break;
        case FrogType:
            hero = std::make_shared<Frog>(x, y);
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