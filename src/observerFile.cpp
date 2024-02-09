#include "observerFile.h"

void ObserverFile::update(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender)
{
    std::ofstream file("log.txt", std::ios_base::app);
    file << "Murder..." << std::endl;
    attacker -> print(file);
    file << "killed" << std::endl;
    defender -> print(file);
    file << std::endl;
}
