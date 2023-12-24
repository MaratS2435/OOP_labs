#include "NPC.hpp"
#include "Dragon.hpp"
#include "WanderingKnight.hpp"
#include "Princess.hpp"
#pragma once
// Текстовый наблюдатель
class TextObserver : public IFightObserver {
private:
    TextObserver() {}
public:
    static std::shared_ptr<IFightObserver> get() {
        static TextObserver instance;
        return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver *) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            std::cout << std::endl
                      << "Убийство --------" << std::endl;
            attacker->print();
            defender->print();
        }
    }
};