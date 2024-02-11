#include "npc.h"

std::shared_mutex print_mutex;

NPC::NPC(NpcType _type, int _x, int _y) : type(_type), x(_x), y(_y), alive(true) {}

NPC::NPC(NpcType _type, std::istream& is) : type(_type), alive(true)
{
    is >> x >> y;
}

std::string NPC::getType()
{
    //std::lock_guard<std::mutex> lck(mtx);
    switch (type)
    {
    case 1 :
        return "DragonType";
        break;
    case 2 :
        return "BullType";
        break;
    case 3 :
        return "FrogType";
        break;
    default:
        return "Unknown";
        break;
    }
}

int NPC::getIntType()
{
    //std::lock_guard<std::mutex> lck(mtx);
    return type;
}

bool NPC::isAlive()
{
    //std::lock_guard<std::mutex> lck(mtx);
    return alive;
}

void NPC::must_die()
{
    //std::lock_guard<std::mutex> lck(mtx);
    alive = false;
}

bool NPC::isClose(const std::shared_ptr<NPC> &other)
{
    auto [other_x, other_y] = other->position();
    float dist = this->distance(other);

    //std::lock_guard<std::mutex> lck(mtx);
    if (dist <= this->getDistFight())
        return true;
    else
        return false;
}

std::pair <int, int> NPC::position()
{
    //std::lock_guard<std::mutex> lck(mtx);
    return std::pair <int, int> {x, y};
}

float NPC::distance(const std::shared_ptr<NPC> &other)
{
    //std::lock_guard<std::mutex> lck(mtx);
    return sqrt(pow((x - other->x), 2) + pow((y - other->y), 2));
}

void NPC::move(int shift_x, int shift_y, int max_x, int max_y)
{
    //std::lock_guard<std::mutex> lck(mtx);
    if ((x + shift_x >= 0) && (x + shift_x <= max_x))
        x += shift_x;
    if ((y + shift_y >= 0) && (y + shift_y <= max_y))
        y += shift_y;
}


bool NPC::win()
{
    int attack = std::rand() % 6;
    int defend = std::rand() % 6;
    if (attack > defend) return true;
    return false;
}

bool NPC::visit(std::shared_ptr<Dragon> monster) 
{
    return false;
}

bool NPC::visit(std::shared_ptr<Bull> monster) 
{
    return false;
}

bool NPC::visit(std::shared_ptr<Frog> monster) 
{
    return false;
}

std::size_t NPC::countObservers() const
{
    return observers.size();
}

void NPC::subscribe(std::shared_ptr<Observer> observer)
{
    observers.insert(observer);
}

void NPC::unsubscribe(std::shared_ptr<Observer> observer)
{
    //std::lock_guard<std::shared_mutex> lck(print_mutex);
    std::cout << observers.size() << std::endl;
    observers.erase(observer);
    std::cout << observers.size() << std::endl;
}

void NPC::notify(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender) const
{
    for (auto observer : observers) {
        observer->update(attacker, defender);
    }
}

std::ostream &operator<<(std::ostream &os, NPC &npc) 
{
    os << "Type : " << npc.getType() << ", x : " << npc.x << ", y : " << npc.y << std::endl;
    return os;
}