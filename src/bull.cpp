#include "bull.h"
#include "frog.h"
#include "dragon.h"

Bull::Bull(int x, int y) : NPC(BullType, x, y) {}
Bull::Bull(std::istream &is) : NPC(BullType, is) {}

void Bull::print() {
    std::cout << *this;
}

void Bull::print(std::ostream &os) {
    os << *this;
}

bool Bull::accept(std::shared_ptr<NPC> visitor) {
    std::shared_ptr<Bull> self = std::dynamic_pointer_cast<Bull>(shared_from_this());
    if (!self) {
         throw std::runtime_error("dynamic_pointer_cast failed");
    }
    return visitor -> visit(self);
}

bool Bull::visit(std::shared_ptr<Frog> other)
{
    fight_notify(other);
    return true;
}

std::ostream &operator<<(std::ostream &os, Bull &bull)
{
    os << "bull: " << *static_cast<NPC *>(&bull) << std::endl;
    return os;
}