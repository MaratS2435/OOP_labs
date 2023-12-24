#include "dragon.hpp"
#include "bull.hpp"
#include "frog.hpp"

Dragon::Dragon(int x, int y, std::string name) : NPC(DRAGON, name, x, y) {}

Dragon::Dragon() : NPC(DRAGON) {}

Dragon::~Dragon() {}

void Dragon::whoami(){
        std::cout << "Dragon" << '\n';
}

void Dragon::defend(std::shared_ptr<NPC> attacker){
        attacker->attack(this);
}

void Dragon::attack(Dragon* defender){ }

void Dragon::attack(Frog* defender){ }

void Dragon::attack(Bull * defender){
        defender->notify(getName());
}