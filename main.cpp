#include <cstdlib>
#include <ctime>
#include <cstring>
#include "npc.h"
#include "dragon.h"
#include "bull.h"
#include "frog.h"
#include "observer.h"
#include "factory.h"
#include "battle.h"

// save array to file
void save(const set_t &array, const std::string &filename)
{
    std::ofstream fs(filename);
    fs << array.size() << std::endl;
    for (auto &n : array)
        fs << n -> get_type() << std::endl << n -> get_x() << std::endl << n -> get_y() << std::endl;
    fs.flush();
    fs.close();
}

set_t load(const std::string &filename)
{
    set_t result;
    std::ifstream is(filename);
    if (is.good() && is.is_open())
    {
        int count;
        if (is >> count && count > 0) {
            for (int i = 0; i < count; ++i)
                result.insert(Create(is));
        } 
        else
        {
            if (count == 0)
                std::cerr << "Error: File is empty." << std::endl;
            else
                std::cerr << "Error: Failed to read count from file." << std::endl;
        }
        is.close();
    }
    else
        std::cerr << "Error: Something wrong in load" << std::endl;
    return result;
}

// print to screen
std::ostream &operator<<(std::ostream &os, const set_t &array)
{
    for (auto &n : array)
        os << *n;
    return os;
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    set_t array; // монстры
    std::size_t distance;
    int choice;

    std::cout << "1 - Generate" << std::endl;
    std::cout << "2 - Load" << std::endl;
    std::cout << "Your choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        std::cout << "Generating ..." << std::endl;
        for (std::size_t i = 0; i < 10; ++i)
        array.insert(Create(NpcType(std::rand() % 3 + 1),
                             std::rand() % 501,
                             std::rand() % 501));
        break;
    
    case 2:
        std::cout << "Loading ..." << std::endl;
        array = load("npc.txt");
        break;
    }

    std::cout << std::endl;
    std::cout << "1 - FIGHT!" << std::endl;
    std::cout << "2 - Save" << std::endl;
    std::cout << "Your choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case 1:

        break;
    
    case 2:
        std::cout << "Saving ..." << std::endl;
        save(array, "npc.txt");
        break;
    }

    std::cout << "Enter the distance: ";
    std::cin >> distance;

    

    ObserverConsole observer1;
    ObserverFile observer2;
    std::shared_ptr observer11 = std::make_shared<ObserverConsole>(observer1);
    std::shared_ptr observer22 = std::make_shared<ObserverFile>(observer2);

    for (auto& f: array) {
        f -> print();
        f -> subscribe(observer11);
        f -> subscribe(observer22);
    }
    std::cout << std::endl;

    int announce = std::rand() % 5 + 1;
    switch (announce)
    {
    case 1:
        std::cout << "Good day for a swell battle!" << std::endl;
        break;
    
    case 2:
        std::cout << "This match will get red hot!" << std::endl;
        break;

    case 3:
        std::cout << "Here's a real high-class bout!" << std::endl;
        break;

    case 4:
        std::cout << "A great slam and then some!" << std::endl;
        break;

    case 5:
        std::cout << "A brawl is surely brewing!" << std::endl;
        break;

    }

    std::cout << std::endl;
    std::cout << "And begin!" << std::endl ;

        auto dead_list = battle(array, distance);
        for (auto &d : dead_list)
            array.erase(d);
        std::cout << "Fight stats ----------" << std::endl
                  << "distance: " << distance << std::endl
                  << "killed: " << dead_list.size() << std::endl
                  << std::endl << std::endl;


    std::cout << "Survivors:" << std::endl;
    for (auto& f: array) {
        f -> print();
    }

    return 0;
}