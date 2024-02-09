#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <set>
#include <memory>
#include <mutex>
#include <sstream>
#include <thread>
#include <shared_mutex>
#include <chrono>
#include <queue>
#include <optional>
#include <array>

#define fileOutput "log.txt"
#define STOP 30

using namespace std::chrono_literals;

extern std::shared_mutex print_mutex;

enum NpcType 
{
    Unknown = 0,
    DragonType = 1, // дракон
    BullType = 2, // бык
    FrogType = 3 // жаба
};

class Observer;

class ObserverConsole;
class ObserverFile;


class NPC;

class Dragon;
class Bull;
class Frog;