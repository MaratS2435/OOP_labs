#include "WanderingKnight.h"
#include "Princess.h"
#include "dragon.h"
WanderingKnight::WanderingKnight(int x, int y) : NPC(WanderingKnightType, x, y) {}
WanderingKnight::WanderingKnight(std::istream &is) : NPC(WanderingKnightType, is) {}

void WanderingKnight::print()
{
    std::cout << *this;
}

bool WanderingKnight::accept(const std::shared_ptr<NPC> attacker) {
    std::shared_ptr<Visitor> attacker_visitor = VisitorFactory::CreateVisitor(attacker->get_type());
    std::shared_ptr<WanderingKnight> defender = std::dynamic_pointer_cast<WanderingKnight>(std::const_pointer_cast<NPC>(shared_from_this()));
    bool result = attacker_visitor->visit(defender);
    attacker->fight_notify(defender, result);
    return result;
}

void WanderingKnight::save(std::ostream &os)
{
    os << WanderingKnightType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, WanderingKnight &WanderingKnight)
{
    os << "WanderingKnight: " << *static_cast<NPC *>(&WanderingKnight) << std::endl;
    return os;
}
