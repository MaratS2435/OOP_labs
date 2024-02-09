#include "factory.h"

std::shared_ptr<NPC> factory(NpcType type, int x, int y)
{
    switch (type)
    {
        case DragonType :
            return std::make_shared<Dragon>(x, y);
            break;
        case BullType :
            return std::make_shared<Bull>(x, y);
            break;
        case FrogType :
            return std::make_shared<Frog>(x, y);
            break;
        default:
            std::cout << "unexpected type : " << type << std::endl;
            break;
    }
    return nullptr;
}

std::shared_ptr<NPC> factory(std::istream &is)
{
    int type;
    is >> type;
    switch (type)
    {
        case DragonType :
            return std::make_shared<Dragon>(is);
            break;
        case BullType :
            return std::make_shared<Bull>(is);
            break;
        case FrogType :
            return std::make_shared<Frog>(is);
            break;
        default:
            std::cout << "unexpected type : " << type << std::endl;
            break;
    }
    return nullptr;
}