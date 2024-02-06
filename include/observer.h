#pragma once

#include "npc.h"

class Observer {
    public:
        virtual void update(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender) = 0;
};

class ObserverConsole : public Observer {
    public:
        void update(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender) override {
            std::cout << "Murder..." << std::endl;
            attacker -> print();
            std::cout << "killed" << std::endl;
            defender -> print();
            std::cout << std::endl;
        }
};

class ObserverFile : public Observer {
    public:
        void update(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender) override {
            std::ofstream file("log.txt", std::ios_base::app);
            file << "Murder..." << std::endl;
            attacker -> print(file);
            file << "killed" << std::endl;
            defender -> print(file);
            file << std::endl;
        }
};