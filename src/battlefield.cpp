#include "battlefield.h"

std::mutex print_mutex;

std::unordered_map<TypeNPC, std::shared_ptr<Visitor>> visitors = {
    {BEAR, std::make_shared<VisitorBear>()},
    {SQUIRREL, std::make_shared<VisitorSquirrel>()},
    {ORC, std::make_shared<VisitorOrc>()}
};

std::ostream &operator << (std::ostream &os, Battlefield &btf) {
    os << "This is a battlefield" << std::endl;
    os << "There are " << btf._npcList.size() << " fighters." << std::endl;
    for (auto npc: btf._npcList) {
        os << *npc;
    }
    return os;
}

Battlefield::Battlefield() : _size(BTF_SIZE,BTF_SIZE), _npcList(), _observers() {}

void Battlefield::attachObs(std::shared_ptr<ObserverBattlefield> obs) {
    _observers.push_back(obs);
}

void Battlefield::detachObs(std::shared_ptr<ObserverBattlefield> obs) {
    if (!_observers.remove(obs)) {
        throw std::logic_error("Observer not in observer list");
    }
}

void Battlefield::fillRandomly(size_t seed, size_t orcs, size_t squirrels, size_t bears) {
    srand(seed);
    std::shared_ptr<Factory> factoryB = std::make_shared<BearFactory>();
    std::shared_ptr<Factory> factoryO = std::make_shared<OrcFactory>();
    std::shared_ptr<Factory> factoryS = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> orcNPC;
    std::shared_ptr<NPC> squirrelNPC;
    std::shared_ptr<NPC> bearNPC;
    size_t c_sq = 0, c_b = 0, c_o = 0;
    while(c_b < bears || c_sq < squirrels || c_o < orcs) {
        switch (rand() % 3 + 1) {
            case BEAR:
                if (c_b < bears) {
                    bearNPC = factoryB->create(rand() % (BTF_SIZE - 1), rand() % (BTF_SIZE - 1));
                    this->placeHero(bearNPC);
                    c_b++;
                }
                break;
            case SQUIRREL:
                if (c_sq < squirrels) {
                    squirrelNPC = factoryS->create(rand() % (BTF_SIZE - 1), rand() % (BTF_SIZE - 1));
                    this->placeHero(squirrelNPC);
                    c_sq++;
                }
                break;
            case ORC:
                if (c_o < orcs) {
                    orcNPC = factoryO->create(rand() % (BTF_SIZE - 1), rand() % (BTF_SIZE - 1));
                    this->placeHero(orcNPC);
                    c_o++;
                }
                break;
            default:
                break;
        }
    }
}

void Battlefield::notify(int cmd) {
    switch (cmd) {
        case Commands::BATTLE_START:
            for (auto obs: _observers) {
                obs->battleStart(this->_size, this->_npcList);
            }
            break;
        case Commands::BATTLE_END:
            for (auto obs: _observers) {
                obs->battleEnd(this->_size, this->_npcList);
            }
            break;
        default:
            throw std::logic_error("Unknown notify");
        }
}

void Battlefield::placeHero(std::shared_ptr<NPC> npc) {
    if (npc->coords().first < BTF_SIZE && npc->coords().first < BTF_SIZE) _npcList.push_back(npc);
}

void Battlefield::removeDeadmen() {
    _npcList.erase(std::remove_if(_npcList.begin(), _npcList.end(), [](std::shared_ptr<NPC> npc) {return !npc->is_alive(); }), _npcList.end());
}

void Battlefield::removeHero(std::shared_ptr<NPC> npc) {
    if (!_npcList.remove(npc)) {
        throw std::logic_error("NPC not on battlefield");
    }
}

std::list<std::shared_ptr<NPC>> Battlefield::npc() {
    return _npcList;
}

void Battlefield::battle() {
    bool stop = false;
    std::thread fightThread(std::ref(FightManager::get()));
    this->notify(Commands::BATTLE_START);
    std::thread moveThread([this, &stop]() {
        auto start = std::chrono::system_clock::now();
        while (true) {
            if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start).count() > 30) {
                break;
            }
            for (auto attacker : _npcList) {
                bool success1;
                for (auto defender : _npcList) {
                    if (attacker != defender && attacker->attack_range() > defender->distance(attacker) && defender->is_alive() && attacker->is_alive()) {
                        FightManager::get().push_event({defender, attacker});
                    }
                }
            }
            for (auto npc: _npcList) {
                if (npc->is_alive()) {
                    int moveX = -npc->move_range() + std::rand() % (2 * npc->move_range());
                    int moveY = -npc->move_range() + std::rand() % (2 * npc->move_range());
                    npc->move(moveX, moveY);
                }
            }
            std::this_thread::sleep_for(50ms);
        }
        stop = true;
    });
    auto start = std::chrono::system_clock::now();
    while (true) {
        if (stop) {
            break;
        }
        const int grid{20}, step_x{BTF_SIZE / grid}, step_y{BTF_SIZE / grid}, size = (grid + 1) * (grid + 1); 
        {
            std::array<char, size> fields{0};
            for (std::shared_ptr<NPC> npc : _npcList) {
                auto [x, y] = npc->coords();
                int i = x / step_x;
                int j = y / step_y;
                if (i + grid * j > size) {
                    std::cout << i << ' ' << j << ' ' <<  i + j *grid << ' '<< size << std::endl;
                    throw std::logic_error("Problems with scale");
                }
                if (npc->is_alive())
                {
                    switch (npc->type())
                    {
                    case TypeNPC::BEAR:
                        fields[i + grid * j] = 'B';
                        break;
                    case TypeNPC::ORC:
                        fields[i + grid * j] = 'O';
                        break;
                    case TypeNPC::SQUIRREL:
                        fields[i + grid * j] = 'S';
                        break;

                    default:
                        break;
                    }
                }
                else
                    fields[i + grid * j] = '#';
            }

            std::lock_guard<std::mutex> lck(print_mutex);
            for (int j = 0; j < grid + 1; ++j)
            {
                for (int i = 0; i < grid + 1; ++i)
                {
                    char c = fields[i + j * grid];
                    if (c != 0)
                        std::cout << "[" << c << "]";
                    else
                        std::cout << "[ ]";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            std::this_thread::sleep_for(1000ms);
        }
    };
    fightThread.join();
    moveThread.join();
    this->notify(Commands::BATTLE_END);
}

void ObserverBattlefieldOstream::battleStart(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> npcList) {
    std::cout << std::endl << "-------- Battle started --------" << std::endl;
    std::cout << "There are " << npcList.size() << " fighters." << std::endl;
    for (auto npc: npcList) {
        std::cout << *npc;
    }
    std::cout << std::endl;
}
void ObserverBattlefieldOstream::battleEnd(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> npcList) {
    std::cout << std::endl << "-------- Battle ended --------" << std::endl;
    std::cout << "There was " << npcList.size() << " fighters." << std::endl;
    for (auto npc: npcList) {
        std::cout << *npc;
    }
    std::cout << std::endl;
}

void ObserverBattlefieldOstream::fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) {
    if (win) {
        std::cout << std::endl << "Murder --------" << std::endl;
        std::cout << "Attacker: " << *attacker << "Defender: " << *defender << std::endl;
    } else {
        std::cout << std::endl << "Failed attack attempt --------" << std::endl;
        std::cout << "Attacker: " << *attacker << "Defender: " << *defender << std::endl;
    }
}

ObserverBattlefieldFile::ObserverBattlefieldFile() {
    const time_t tm = time(nullptr);
    file.open("../log/log.txt");
}

ObserverBattlefieldFile::~ObserverBattlefieldFile() {
    file.close();
}

void ObserverBattlefieldFile::fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) {
    if (win) {
        file << '\n' << "Murder --------" << '\n';
        file << "Attacker: " << *attacker << "Defender: " << *defender << '\n';
    } else {
        file << '\n' << "Failed attack attempt --------" << '\n';
        file << "Attacker: " << *attacker << "Defender: " << *defender << '\n';
    }
}

void ObserverBattlefieldFile::battleStart(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> npcList) {
    file << std::endl << "-------- Battle started --------" << std::endl;
    file << "There are " << npcList.size() << " fighters." << std::endl;
    for (auto npc: npcList) {
        file << *npc;
    }
    file << std::endl;
}

void ObserverBattlefieldFile::battleEnd(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> npcList) {
    file << std::endl << "-------- Battle ended --------" << std::endl;
    file << "There was " << npcList.size() << " fighters." << std::endl;
    for (auto npc: npcList) {
        file << *npc;
    }
    file << std::endl;
}

FightManager & FightManager::get() {
    static FightManager inst;
    
    return inst;
}

void FightManager::push_event(FightMMA && event) {
    std::lock_guard<std::shared_mutex> lock(_mtx);
    _events.push(event);
}

void FightManager::operator()() {
    auto start = std::chrono::system_clock::now();
    while(true) {
        if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start).count() > 31) {
            break;
        }
        std::optional<FightMMA> event;
        {
            std::lock_guard<std::shared_mutex> lock(_mtx);
            if (!_events.empty()) {
                event = _events.back();
                _events.pop();
            }
        }
        
        if (event) {
            if (event->attacker->is_alive()) {
                if (event->defender->is_alive()) {  
                    event->defender->accept(visitors[event->attacker->type()], event->attacker);
                }
            }
        } else {
            std::this_thread::sleep_for(100ms);
        }  
    }
}