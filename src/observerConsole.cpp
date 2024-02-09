#include "observerConsole.h"

void ObserverConsole::update(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender)
{
    std::lock_guard<std::shared_mutex> lck(print_mutex);
    std::cout << "Murder..." << std::endl;
    attacker -> print();
    std::cout << "killed" << std::endl;
    defender -> print();
    std::cout << std::endl;
}