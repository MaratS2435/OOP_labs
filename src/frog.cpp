#include "frog.hpp"
#include "dragon.hpp"
#include "bull.hpp"

Frog::Frog(int x, int y, std::string name) : NPC(FROG, name, x, y) {}

Frog::Frog() : NPC(FROG) {}

Frog::~Frog() {}

void Frog::whoami(){
        std::cout << "Frog" << '\n';
}

void Frog::defend(std::shared_ptr<NPC> attacker){
        attacker->attack(this);
}

void Frog::attack(Dragon* defender){ }

void Frog::attack(Frog* defender){ }

void Frog::attack(Bull * defender){
        notify(defender->getName());
}