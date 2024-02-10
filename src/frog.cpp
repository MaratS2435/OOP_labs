#include "frog.h"
#include "dragon.h"
#include "bull.h"

Frog::Frog(std::string name, int x, int y) : NPC(FrogType, name, x, y) {}
Frog::Frog(std::istream &is) : NPC(FrogType, is) {}

void Frog::print() {
    std::cout << *this;
}

void Frog::print(std::ostream &os) {
    os << *this;
}

bool Frog::accept(std::shared_ptr<NPC> visitor)
{
    std::shared_ptr<Frog> self = std::dynamic_pointer_cast<Frog>(shared_from_this());
    if (!self) {
         throw std::runtime_error("dynamic_pointer_cast failed");
    }
    return visitor -> visit(self);
}

std::ostream &operator<<(std::ostream &os, Frog &frog)
{
    os << "frog " << frog.get_name() << ": " << *static_cast<NPC *>(&frog) << std::endl;
    return os;
}