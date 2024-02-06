#include "dragon.h"
#include "bull.h"
#include "frog.h"

Dragon::Dragon(int x, int y) : NPC(DragonType, x, y) {}
Dragon::Dragon(std::istream &is) : NPC(DragonType, is) {}

void Dragon::print() {
    std::cout << *this;
}

void Dragon::print(std::ostream &os) {
    os << *this;
}

bool Dragon::visit(std::shared_ptr<Bull> other) 
{
    fight_notify(other);
    return true;
}

bool Dragon::accept(std::shared_ptr<NPC> visitor) 
{
    std::shared_ptr<Dragon> self = std::dynamic_pointer_cast<Dragon>(shared_from_this());
    if (!self) {
         throw std::runtime_error("dynamic_pointer_cast failed");
    }
    return visitor -> visit(self);
}

std::ostream &operator<<(std::ostream &os, Dragon &dragon)
{
    os << "dragon: " << *static_cast<NPC *>(&dragon) << std::endl;
    return os;
}