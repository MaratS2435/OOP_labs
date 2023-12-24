#include "bull.hpp"
#include "dragon.hpp"
#include "frog.hpp"

void printLine(){
    std::cout << "------------------------------------------------\n"; 
}

void FightInterface(std::set<std::shared_ptr<NPC>>& creatures, int field[501][501]){
    int distance;
    char createSL;
    std::cout << "Set the attack distance (0 <= distance <= 500): ";
            std::cin >> distance;
            printLine();
            printLine();
            std::cout << "Fight mode activating...\n";
            TextObserver textObserver(creatures);
            FileObserver fileObserver(creatures, "log.txt");
            std::cout << "Fight mode on.\n";
            printLine();
            std::set<std::shared_ptr<NPC>> deadlist = fight(creatures, distance, field);
            for(auto deadman : deadlist){
                creatures.erase(deadman);
            }
            printLine();
            std::cout << "Fight mode off.\n";
            std::cout << "Want to create survivors list? (y/n): \n";
            std::cin >> createSL;
            if (createSL == 'y'){
                std::cout << "Creating survivors list...\n";
                saveCreatures(creatures, "SurvivorsList.txt");
                std::cout << "Survivors list created!\n";
            }
}

void Interface(){
    std::set<std::shared_ptr<NPC>> creatures;
    int field[501][501];
    for (int i = 0; i < 501; i++){
        for (int j = 0; j < 501; j++){
            field[i][j] = 0;
        }    
    }

    char input;
    int emptyField = 1;
    int programRunning = 1;
    int distance;
    char createSL;
    int quantity;

    printLine();
    std::cout << "Welcome to the Balagur Fate 3 Dangeon Editor! Enter 'h' for help.\n";
    printLine();
    while(programRunning){
        printLine();
        std::cout << "> ";
        std::cin >> input;
        printLine();
        printLine();
        switch (input){
            case 'h':
                std::cout << "Editor capabilities:\n";
                std::cout << "h - help.\n";
                std::cout << "f - switch on fight mode.\n";
                std::cout << "g - generate new random creatures.\n";
                std::cout << "l - load creatures from save.\n";
                std::cout << "p - print all characters.\n";
                std::cout << "q - quit\n";
                break;
            case 'f':
                if (emptyField){
                    std::cout << "Field is empty!\n";
                    break;
                }
                FightInterface(creatures, field);
                break;
            case 'g':
                std::cout << "Enter characters quantity: ";
                std::cin >> quantity;
                std::cout << "Generating NPC...\n";
                generateCreatures(creatures, quantity, field);
                std::cout << "Generated NPC: " << quantity << ".\n";
                emptyField = 0;
                break;
            case 'l':
                std::cout << "WARNING! If the coordinates of a saved creature coincide with the coordinates of a creature on the field, it will not be loaded.\n";
                std::cout << "Loading...\n";
                loadCreatures(creatures, "saved_creatures.txt", field);
                std::cout << "Save loaded!\n";
                emptyField = 0;
                break;
            case 'p':
                std::cout << creatures.size() << " creatures on field!\n";
                printLine();
                for (auto creature : creatures){
                    creature->print(std::cout);
                }
                printLine();
                std::cout << "You can fight them!\n";
                break;
            case 'q':
                std::cout << "See you later!\n";
                programRunning = 0;
                break;
            default:
                std::cout << "Invalid input!\n";
                break;
        }
        printLine();
    }
}

int main(){
    Interface();
    return 0;
}