#pragma once

#include "npc.h"
#include "dragon.h"
#include "bull.h"
#include "frog.h"

std::shared_ptr<NPC> Create(NpcType type, int x, int y);

std::shared_ptr<NPC> Create(std::istream& stream);