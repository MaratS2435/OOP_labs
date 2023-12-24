#include "bull.hpp"
#include "dragon.hpp"
#include "frog.hpp"

Bull::Bull(int x, int y, std::string name) : NPC(BULL, name, x, y) {}

Bull::Bull() : NPC(BULL) {}

Bull::~Bull() {}

void Bull::whoami(){
        std::cout << "Bull" << '\n';
}

void Bull::defend(std::shared_ptr<NPC> attacker){
        attacker->attack(this);
}

void Bull::attack(Dragon* defender){
        notify(defender->getName());
}

void Bull::attack(Frog* defender){
        defender->notify(getName());
}

void Bull::attack(Bull * defender){ }