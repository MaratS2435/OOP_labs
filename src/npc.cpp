#include "bull.hpp"
#include "dragon.hpp"
#include "frog.hpp"

// CONSTRUCTORS

NPC::NPC(NPCType type, std::string name, int x, int y) : type(type), name(name), x(x), y(y), alive(1) {}

NPC::NPC(NPCType type) : type(type), name("NoName"), x(-1), y(-1), alive(1) {}

NPC::NPC() : type(UNKNOWN), name("NoName"), x(-1), y(-1), alive(1) {}

// GET 

int NPC::getX() const{
    return x;
}

int NPC::getY() const{
    return y;
}

std::string NPC::getName() const{
    return name;
}

int NPC::stillAlive(){
    return alive;
}

NPCType NPC::getType() const{
    return type;
}

// SET

void NPC::setName(std::string newName){
    name = newName;
}

void NPC::setType(NPCType newType){
    type = newType;
}

void NPC::setCoords(int new_x, int new_y){
    x = new_x;
    y = new_y;
}

// OPERATORS

std::ostream& operator << (std::ostream &os, const NPC & creature){
    return os << creature.getName() << ' ' << creature.getType() << ' ' << creature.getX() << ' ' << creature.getY();
}

std::istream& operator >> (std::istream &is, NPC & creature){
    std::string name;
    int type;
    int x, y;
    is >> name;
    is >> type;
    is >> x >> y;
    creature.setName(name);
    creature.setType(NPCType(type));
    creature.setCoords(x, y);
    return is;
}

std::istream& operator >> (std::istream &is, std::shared_ptr<NPC>& creature){
    if (!creature){
        std::string name;
        int type;
        int x, y;
        is >> name;
        is >> type;
        is >> x >> y;
        creature = NPC::create_NPC(NPCType(type), name, x, y);
    } else{
        is >> *creature;
    }
    return is;
}

int NPC::operator == (const NPC & other) const{
    if (type != other.getType()){
        return 0;
    }
    if (name != other.getName()){
        return 0;
    }
    if (x != other.getX()){
        return 0;
    }
    if (y != other.getY()){
        return 0;
    }
    return 1;
}

// FACTORY

std::shared_ptr<NPC> NPC::create_NPC(NPCType type, std::string name, int x, int y){
    std::shared_ptr<NPC> res;
    switch (type){
    case BULL:
        res = std::make_shared<Bull>(x, y, name);
        break;
    case DRAGON:
        res = std::make_shared<Dragon>(x, y, name);
        break;
    case FROG:
        res = std::make_shared<Frog>(x, y, name);
        break;
    default:
        break;
    }
    return res;
}

// OBSERVER METHODS

void NPC::addobserver(Observer * observer){
    observers.insert(observer);
}

void NPC::removeobserver(Observer * observer){
    observers.erase(observer);
}


void NPC::notify(std::string killerName){
    alive = 0;
    for(auto observer : observers){
        observer->update(killerName, this);
    }
}

// OBSERVER REALISATION

TextObserver::TextObserver(std::set<std::shared_ptr<NPC>>& creatures){
    for(auto creature : creatures){
        creature->addobserver(this);
    }
}

FileObserver::FileObserver(std::set<std::shared_ptr<NPC>>& creatures, std::string nameFile){
    file.open(nameFile.c_str());
    for(auto creature : creatures){
        creature->addobserver(this);
    }
}

FileObserver::~FileObserver(){
    file.close();
}


void TextObserver::update(std::string killerName, NPC * deadman){
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << deadman->getName() << " ("; 
    switch (deadman->getType()){
        case BULL:
            std::cout << "Bull) was killed by " << killerName << " (Dragon)" << std::endl;  
            break;
        case FROG:
            std::cout << "Frog) was killed by " << killerName << " (Bull)" << std::endl;
            break;
        default:
            break;
    }
    std::cout << "------------------------------------------------" << std::endl;
}

void FileObserver::update(std::string killerName, NPC * deadman){
    file << "------------------------------------------------\n";
    file << deadman->getName() << " ("; 
    switch (deadman->getType()){
        case BULL:
            file << "Bull) was killed by " << killerName << " (Dragon)\n"; 
            break;
        case FROG:
            file << "Frog) was killed by " << killerName << " (Bull)\n";
            break;
        default:
            break;
    }
    file << "------------------------------------------------\n";
}

// WORKING WITH NPC

void generateCoords(std::shared_ptr<NPC> creature, int field[501][501]){
    int x = std::rand() % 501, y = std::rand() % 501;
    while(field[x][y]){
        x = std::rand() % 501;
        y = std::rand() % 501;
    }
    field[x][y] = 1;
    creature->setCoords(x, y);
}

void generateCreatures(std::set<std::shared_ptr<NPC>>& creatures, int quantity, int field[501][501]){
    std::srand(std::time(nullptr));
    std::ifstream namesFile;
    const char * pathToNameFile = getenv("PATH_TO_NAMES_FILE");
    namesFile.open(pathToNameFile);
    std::string name;
    std::shared_ptr<NPC> newCreature;
    for (int i = 0; i < quantity; i++){
        namesFile >> name;
        newCreature = NPC::create_NPC(NPCType(std::rand() % 3 + 1), name, 0, 0);
        generateCoords(newCreature, field);
        creatures.insert(newCreature);
    }
    namesFile.close();
}


void loadCreatures(std::set<std::shared_ptr<NPC>>& creatures, std::string filename, int field[501][501]){
    std::ifstream file;
    file.open(filename);
    std::shared_ptr<std::shared_ptr<NPC>> creature = std::make_shared<std::shared_ptr<NPC>>();
    int creaturesNum;
    file >> creaturesNum;
    for(int i = 0; i < creaturesNum; i++){
        file >> *creature;
        if (!field[(*creature)->getX()][(*creature)->getY()]){
            creatures.insert(*creature);    
            field[(*creature)->getX()][(*creature)->getY()] = 1;
        }
        *creature = nullptr;
    }
    file.close();
}


void saveCreatures(std::set<std::shared_ptr<NPC>>& creatures, std::string filename){
    std::ofstream file;
    file.open(filename);
    file << creatures.size() << '\n';
    for (auto creature : creatures){
        file << *creature << '\n';
    }
    file.close();
}

// OTHER METHODS

int NPC::isClose(std::shared_ptr<NPC> enemy, int distance){
    if ((abs(this->getX() - enemy->getX()) <= distance) and (abs(this->getY() - enemy->getY()) <= distance)){
        return 1;
    }
    return 0;
}

void NPC::print(std::ostream& os){
    os << "------------------------------------------------" << '\n';
    os << "Name: " << getName() << '\n';
    os << "Type: ";
    switch (getType()){
        case FROG:
            os << "frog" << '\n';
            break;
        case BULL:
            os << "bull" << '\n';
            break;
        case DRAGON:
            os << "dragon" << '\n';
            break;
        default:
            break;
    }
    os << "Coords: (" << getX() << ", " << getY() << ")\n";
    os << "------------------------------------------------" << '\n';
}

//FIGHT!!!

std::set<std::shared_ptr<NPC>> fight(std::set<std::shared_ptr<NPC>>& creatures, int distance, int field[501][501]){
    std::set<std::shared_ptr<NPC>> deadlist; 
    for (auto attacker : creatures){
        for (auto defender : creatures){
            if((attacker->getName() != defender->getName()) and attacker->stillAlive() and defender->stillAlive() and attacker->isClose(defender, distance)){
                defender->defend(attacker);
            }
        }
    }
    for(auto creature : creatures){
        if (!creature->stillAlive()){
            deadlist.insert(creature);
            field[creature->getX()][creature->getY()] = 0;
        }
    }
    return deadlist;
}