#include "npc.h"
#include "observer.h"

NPC::NPC(NpcType t, std::string name, int _x, int _y) : type(t), _name(name), x(_x), y(_y) {}
NPC::NPC(NpcType t, std::istream &is) : type(t)
{
    is >> _name;
    is >> x;
    is >> y;
}

std::string NPC::get_name() const{
    return _name;
}

int NPC::get_x() const {
    return x;
}
int NPC::get_y() const{
    return y;
}

NpcType NPC::get_type() const{
    return type;
}

void NPC::subscribe(std::shared_ptr<Observer> observer)
{
   observers.push_back(observer);
}

void NPC::fight_notify(const std::shared_ptr<NPC> defender)
{
    for (auto &o : observers)
        o->update(shared_from_this(), defender);
}

bool NPC::is_close(const std::shared_ptr<NPC> &other, std::size_t distance) const
{
    if (std::pow(x - other->x, 2) + std::pow(y - other->y, 2) <= std::pow(distance, 2))
        return true;
    else
        return false;
}

bool Visitor::visit(const std::shared_ptr<Dragon>& other) {
    return false;
}

bool Visitor::visit(const std::shared_ptr<Bull>& other) {
    return false;
}

bool Visitor::visit(const std::shared_ptr<Frog>& other) {
    return false;
}

std::ostream &operator<<(std::ostream &os, NPC &npc)
{
    os << "{x:" << npc.x << ", y:" << npc.y << "} ";
    return os;
}