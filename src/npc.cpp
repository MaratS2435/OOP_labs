#include "npc.h"

std::mutex PRmutex;

int throw_dice() {
    return rand() % 6 + 1;
}

NPC::NPC() : _coords{0,0} {}

NPC::NPC(TypeNPC type, const std::pair<int,int> &coords, const int &attackRange, const int &movementRange) : 
    _coords{coords}, _type{type}, alive{true}, _rangeAttack{attackRange}, _rangeMove{movementRange} {}

NPC::NPC(TypeNPC type, const int &x, const int &y, const int &attackRange, const int &movementRange) : 
    _coords{x,y}, _type(type), alive(true), _rangeAttack{attackRange}, _rangeMove{movementRange} {}

TypeNPC NPC::type() const{
    return this->_type;
}

std::pair<int,int> NPC::coords() const{
    std::lock_guard<std::mutex> lck(mtx);
    return this->_coords;
}

void NPC::save(std::ofstream &ofs) {
    ofs << this->_coords.first << ' ' << this->_coords.second << ' ' << this->type();
}

int NPC::attack_range() const {
    return _rangeAttack;
}

void NPC::load(std::ifstream &ifs) {
    int x,y,type;
    ifs >> x;
    ifs >> y;
    ifs >> type;
    _coords.first = x;
    _coords.second = y;
    _type = TypeNPC(type);
    alive = true;
}

bool NPC::is_alive() const{
    std::lock_guard<std::mutex> lck(mtx);
    return this->alive;
}

void NPC::move(const int& moveX, const int& moveY) {
    std::lock_guard<std::mutex> lck(mtx);
    if ((_coords.first + moveX >= 0) && (_coords.first + moveX <= BTF_SIZE)) {
        _coords.first += moveX;
    }

    if ((_coords.second + moveY >= 0) && (_coords.second + moveY <= BTF_SIZE)) {
        _coords.second += moveY;
    }
}

void NPC::kill(){
    std::lock_guard<std::mutex> lck(mtx);
    this->alive = false;
}

void NPC::attachObs(std::shared_ptr<ObserverNPC> obs) {
    _observers.push_back(obs);
}

double NPC::distance(const std::shared_ptr<NPC> other) const{
    std::lock_guard<std::mutex> lck(mtx);
    return pow((pow(_coords.first - other->_coords.first, 2) + pow(_coords.second - other->_coords.second, 2)), 0.5);
}

int NPC::move_range() const{
    return _rangeMove;
}

std::ostream &operator<<(std::ostream &os, NPC &npc) {
    switch (npc._type) {
        case ORC:
            os << "Orc: ";
            break;
        case SQUIRREL:
            os << "Squirrel: ";
            break;
        case BEAR:
            os << "Bear: ";
            break;
        default:
            throw std::logic_error("Unknown NPC type");
            break;
        }
    os << "{x = " << npc._coords.first << ", y = " << npc._coords.second << "} ";
    if (npc.alive) {
        os << "alive" << std::endl;
    } else {
        os << "dead" << std::endl;
    }
    return os;
}

void NPC::notify(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win, int diceA, int diceD, int rangeAttack, double dist) {
    for (auto obs: _observers) {
        obs->fight(attacker, defender, win, diceA, diceD, rangeAttack, dist);
    }
}

void ObserverOstream::fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win, int diceA, int diceD, int rangeAttack, double dist) {
    std::lock_guard<std::mutex> lck(PRmutex);
    std::cout << "With dice attacker = " << diceA << '\t' << "With dice defender = " << diceD << std::endl;
    std::cout << "With attacker attack range = " << rangeAttack << '\t' << "With distance = " << dist << std::endl;
    if (win) {
        std::cout << std::endl << "Murder --------" << std::endl;
        std::cout << "Attacker: " << *attacker << "Defender: " << *defender << std::endl;
    } else {
        std::cout << std::endl << "Failed attack attempt --------" << std::endl;
        std::cout << "Attacker: " << *attacker << "Defender: " << *defender << std::endl;
    }
}

ObserverFile::ObserverFile() {
    const time_t tm = time(nullptr);
    file.open("../log/log.txt");
}

ObserverFile::~ObserverFile() {
    file.close();
}

void ObserverFile::fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win, int diceA, int diceD, int rangeAttack, double dist) {
    file << "With dice attacker = " << diceA << '\t' << "With dice defender = " << diceD << std::endl;
    file << "With attacker attack range = " << rangeAttack << '\t' << "With distance = " << dist << std::endl;
    if (win) {
        file << '\n' << "Murder --------" << '\n';
        file << "Attacker: " << *attacker << "Defender: " << *defender << '\n';
    } else {
        file << '\n' << "Failed attack attempt --------" << '\n';
        file << "Attacker: " << *attacker << "Defender: " << *defender << '\n';
    }
}