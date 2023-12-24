#include "orc.h"

Orc::Orc(const int &x, const int &y) : NPC{ORC, x, y, RangeMove::ATTACK_RANGE_ORC, RangeMove::MOVE_RANGE_ORC} {}

int Orc::accept(const std::shared_ptr<Visitor>& attacker_visitor, const std::shared_ptr<NPC>& attacker) {
    std::shared_ptr<const NPC> npc_const_ptr = shared_from_this();
    std::shared_ptr<NPC> npc_ptr = std::const_pointer_cast<NPC>(npc_const_ptr);
    std::shared_ptr<Orc> defender = std::dynamic_pointer_cast<Orc>(npc_ptr);
    int diceA = throw_dice();
    int diceD = throw_dice();
    if (attacker_visitor->visit(defender)) {
        if (diceA >= diceD) {
            this->notify(attacker, defender, true, diceA, diceD, _rangeAttack, attacker->distance(defender));
            this->kill();
            return true;
        }
    }
    // this->notify(attacker, defender, false, diceA, diceD, _rangeAttack, attacker->distance(defender));
    return false;
}

bool VisitorOrc::visit(const std::shared_ptr<Bear> defender) {
    return true;
}
bool VisitorOrc::visit(const std::shared_ptr<Orc> defender) {
    return true;
}
bool VisitorOrc::visit(const std::shared_ptr<Squirrel> defender) {
    return false;
}

std::shared_ptr<NPC> OrcFactory::create(int x, int y) {
    std::shared_ptr<NPC> result = std::make_shared<Orc>(x, y);
    std::shared_ptr<ObserverOstream> obsO = std::make_shared<ObserverOstream>();
    std::shared_ptr<ObserverFile> obsF = std::make_shared<ObserverFile>();
    result->attachObs(obsO);
    result->attachObs(obsF);
    return result;
}

std::shared_ptr<NPC> OrcFactory::create(std::istream &is) {
    std::pair<int,int> tmp;
    is >> tmp.first; is >> tmp.second;
    std::shared_ptr<NPC> result = std::make_shared<Orc>(tmp.first, tmp.second);
    std::shared_ptr<ObserverOstream> obsO = std::make_shared<ObserverOstream>();
    std::shared_ptr<ObserverFile> obsF = std::make_shared<ObserverFile>();
    result->attachObs(obsO);
    result->attachObs(obsF);
    return result;
}

std::shared_ptr<NPC> OrcFactory::create(std::ifstream &ifs) {
    int x; int y; int type;
    ifs >> x; ifs >> y; ifs >> type;
    std::shared_ptr<NPC> result = std::make_shared<Orc>(x,y);
    std::shared_ptr<ObserverOstream> obsO = std::make_shared<ObserverOstream>();
    std::shared_ptr<ObserverFile> obsF = std::make_shared<ObserverFile>();
    result->attachObs(obsO);
    result->attachObs(obsF);
    return result;
}