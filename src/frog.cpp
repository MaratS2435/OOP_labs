#include "frog.h"

Frog::Frog(int x, int y) : NPC(FrogType, x, y) {}

Frog::Frog(std::istream& is) : NPC(FrogType, is) {}

int Frog::getDistMove()
{
    return dist_move;
}

int Frog::getDistFight()
{
    return dist_fight;
}

bool Frog::accept(std::shared_ptr<NPC> visitor) 
{
    return visitor->visit(std::shared_ptr<Frog>(this,[](Frog*){}));
}

void Frog::print() {
    std::cout << *this;
}

void Frog::print(std::ostream &os) {
    os << *this;
}
