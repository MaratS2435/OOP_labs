#pragma once

#include "npc.h"
#include "dragon.h"
#include "bull.h"
#include "frog.h"

std::shared_ptr<NPC> factory(std::istream &is);
std::shared_ptr<NPC> factory(NpcType type, int x, int y);