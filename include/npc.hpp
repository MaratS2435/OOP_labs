#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <set>
#include <fstream>
#include <random>
#include <ctime>

enum NPCType{
    UNKNOWN,
    FROG,
    BULL,
    DRAGON
};

class NPC;
class Dragon;
class Bull;
class Frog;

class Observer{
public:
    virtual void update(std::string killerName, NPC * deadman) = 0;
};

class TextObserver : public Observer{
public:
    TextObserver(std::set<std::shared_ptr<NPC>>& creatures);
    void update(std::string killerName, NPC* deadman) override;
};

class FileObserver : public Observer{
    std::ofstream file;
public:
    FileObserver(std::set<std::shared_ptr<NPC>>& creatures, std::string nameFile);
    void update(std::string killerName, NPC* deadman) override;
    ~FileObserver();
};

class NPC{
    int x;
    int y;
    int alive;
    NPCType type;   
    std::string name;
    std::set<Observer *> observers;
public:
    // TIPICAL CLASS METHODS
    NPCType getType() const;
    std::string getName() const;
    int getX() const;
    int getY() const;
    void setCoords(int new_x, int new_y);
    void setName(std::string newName);
    void setType(NPCType newType);
    NPC(NPCType type, std::string name, int x, int y);
    NPC(NPCType type);
    NPC();
    ~NPC() = default;
    int stillAlive();
    virtual void whoami() = 0;
    void print(std::ostream& os);
    int operator == (const NPC & other) const;
    //FACTORY FUNCTION
    static std::shared_ptr<NPC> create_NPC(NPCType type, std::string name, int x, int y); 
    //OBSERVER METHODS
    void addobserver(Observer * observer);
    void removeobserver(Observer * observer);
    void notify(std::string killerName);
    //VISITOR METHODS
    virtual void defend(std::shared_ptr<NPC> attacker) = 0;
    virtual void attack(Dragon* defender) = 0;
    virtual void attack(Bull* defender) = 0;
    virtual void attack(Frog* defender) = 0;
    //FIGHT METHODS
    int isClose(std::shared_ptr<NPC> enemy, int distance);
};

// INPUT/OUTPUT OVERLOADS
std::ostream& operator << (std::ostream &os, const NPC & creature);
std::istream& operator >> (std::istream &is, NPC & creature);
std::istream& operator >> (std::istream &is, std::shared_ptr<NPC>& creature);

// CREATURE FUNCTIONS
void generateCoords(std::shared_ptr<NPC> creature, int field[501][501]);
void generateCreatures(std::set<std::shared_ptr<NPC>>& creatures, int quantity, int field[501][501]);
void loadCreatures(std::set<std::shared_ptr<NPC>>& creatures, std::string filename, int field[501][501]);
void saveCreatures(std::set<std::shared_ptr<NPC>>& creatures, std::string filename);

// FIGHT!!!
std::set<std::shared_ptr<NPC>> fight(std::set<std::shared_ptr<NPC>>& creatures, int distance, int field[501][501]);