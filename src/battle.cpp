#include "battle.h"

set_t battle(set_t fighters, std::size_t distance) {
    set_t corps;
    for (auto& attacker: fighters) {
        for (auto& defender: fighters){
            if ((defender != attacker) && (attacker->is_close(defender, distance))) {
                bool success {false};
                success = defender -> accept(attacker);
                if(success) {
                    corps.insert(defender);
                }
            }
        }
    }

    return corps;
}