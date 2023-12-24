#include "NPC.hpp"
#include "Dragon.hpp"
#include "WanderingKnight.hpp"
#include "Princess.hpp"
#include "FightObserver.hpp"
#pragma once

// Фабрики -----------------------------------
std::shared_ptr<NPC> factory(std::istream &is) {
    std::shared_ptr<NPC> result;
    int type{0};
    if (is >> type) {
        switch (type) {
            case DragonType:
                result = std::make_shared<Dragon>(is);
                break;
            case WanderingKnightType:
                result = std::make_shared<WanderingKnight>(is);
                break;
            case PrincessType:
                result = std::make_shared<Princess>(is);
                break;
        }
    } else
        std::cerr << "unexpected NPC type:" << type << std::endl;

    if (result)
        result->subscribe(TextObserver::get());

    return result;
}


std::shared_ptr<NPC> factory(NpcType type, int x, int y) {
    std::shared_ptr<NPC> result;
    switch (type) {
        case DragonType:
            result = std::make_shared<Dragon>(x, y);
            break;
        case WanderingKnightType:
            result = std::make_shared<WanderingKnight>(x, y);
            break;
        case PrincessType:
            result = std::make_shared<Princess>(x, y);
            break;
        default:
            break;
    }
    if (result)
        result->subscribe(TextObserver::get());

    return result;
}

// Сохранение массива в файл
void save(const set_t &array, const std::string &filename) {
    std::ofstream fs(filename);
    fs << array.size() << std::endl;
    for (auto &n : array)
        n->save(fs);
    fs.flush();
    fs.close();
}

set_t load(const std::string &filename) {
    set_t result;
    std::ifstream is(filename);
    if (is.good() && is.is_open()) {
        int count;
        is >> count;
        for (int i = 0; i < count; ++i)
            result.insert(factory(is));
        is.close();
    } else
        std::cerr << "Ошибка: " << std::strerror(errno) << std::endl;
    return result;
}
