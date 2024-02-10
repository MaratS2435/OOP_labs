#pragma once

#include "npc.h"
#include "dragon.h"
#include "bull.h"
#include "frog.h"

std::string randname(int x);

std::shared_ptr<NPC> Create(NpcType type, std::string name, int x, int y);

std::shared_ptr<NPC> Create(std::istream& stream);