#pragma once
#include "orc.h"
#include "squirrel.h"
#include "bear.h"

class Factory {
    public:
        virtual std::shared_ptr<NPC> create(int x, int y) = 0;
        ~Factory() = default;
};

class OrcFactory : public Factory {
    public:
        std::shared_ptr<NPC> create(int x, int y) override;
};

class BearFactory : public Factory {
    public:
        std::shared_ptr<NPC> create(int x, int y) override;
};

class SquirrelFactory : public Factory {
    public:
        std::shared_ptr<NPC> create(int x, int y) override;
};

