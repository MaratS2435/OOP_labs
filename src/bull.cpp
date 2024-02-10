#include "bull.h"
#include "frog.h"
#include "dragon.h"

Bull::Bull(std::string name, int x, int y) : NPC(BullType, name, x, y) {}
Bull::Bull(std::istream &is) : NPC(BullType, is) {}

void Bull::print() {
    std::cout << *this;
}

void Bull::print(std::ostream &os) {
    os << *this;
}

bool Bull::accept(std::shared_ptr<Visitor>& visitor, std::shared_ptr<NPC> attacker) {
    std::shared_ptr<Bull> self = std::dynamic_pointer_cast<Bull>(shared_from_this());
    if (!self) {
         throw std::runtime_error("dynamic_pointer_cast failed");
    }
    if (visitor -> visit(self)) 
        attacker -> fight_notify(self);
    return visitor -> visit(self);
}

bool BullVisitor::visit(const std::shared_ptr<Frog>& other)
{
    return true;
}

std::ostream &operator<<(std::ostream &os, Bull &bull)
{
    os << "bull " << bull.get_name() << ": " << *static_cast<NPC *>(&bull) << std::endl;
    return os;
}