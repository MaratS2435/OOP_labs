#include "battle.h"

set_t battle(set_t fighters, std::size_t distance) {
    std::unordered_map<NpcType, std::shared_ptr<Visitor>> visitors = {
        {DragonType, std::make_shared<DragonVisitor>()},
        {BullType, std::make_shared<BullVisitor>()},
        {FrogType, std::make_shared<FrogVisitor>()}
    };

    set_t corpse;
    for (auto& attacker: fighters) {
        for (auto& defender: fighters){
            if ((defender != attacker) && (attacker->is_close(defender, distance)) && corpse.find(defender) == corpse.end()) {
                bool success {false};
                success = defender -> accept(visitors[attacker -> get_type()], attacker);
                if(success) {
                    corpse.insert(defender);
                }
            }
        }
    }

    return corpse;
}