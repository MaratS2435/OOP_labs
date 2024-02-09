#include "../include/bull.h"

Bull::Bull(int x, int y) : NPC(BullType, x, y) {}

Bull::Bull(std::istream& is) : NPC(BullType, is) {}

int Bull::getDistMove()
{
    return dist_move;
}

int Bull::getDistFight()
{
    return dist_fight;
}

bool Bull::accept(std::shared_ptr<NPC> visitor) 
{
    return visitor->visit(std::shared_ptr<Bull>(this,[](Bull*){}));
}

bool Bull::visit(std::shared_ptr<Frog> monster) 
{
    if (win()) 
    {
        notify(std::shared_ptr<Bull>(this,[](Bull*){}), monster);
        return true;
    }
    return false;
}

void Bull::print() {
    std::cout << *this;
}

void Bull::print(std::ostream &os) {
    os << *this;
}