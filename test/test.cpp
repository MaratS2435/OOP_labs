#include <gtest/gtest.h>
#include <cstring>
#include "npc.h"
#include "dragon.h"
#include "bull.h"
#include "frog.h"
#include "observer.h"
#include "factory.h"
#include "battle.h"

std::unordered_map<NpcType, std::shared_ptr<Visitor>> visitors = {
        {DragonType, std::make_shared<DragonVisitor>()},
        {BullType, std::make_shared<BullVisitor>()},
        {FrogType, std::make_shared<FrogVisitor>()}
};


TEST(Test_Dragon, Constructor) {
    std::string name {"default"};
    Dragon dragon(name, 1, 1);
    EXPECT_TRUE(dragon.get_name() == name && dragon.get_type() == DragonType and dragon.get_x() == 1 and dragon.get_y() == 1);
}

TEST(Test_Dragon, FightBull)
{
    std::string name {"default"};
    std::shared_ptr<Dragon> dragon = std::make_shared<Dragon>(name, 1, 1);
    std::shared_ptr<Bull> bull = std::make_shared<Bull>(name, 1, 2);

    
    EXPECT_TRUE(bull -> accept(visitors[dragon -> get_type()], dragon) == true);
}

TEST(Test_Dragon, FightDragonFrog){
    std::string name {"default"};
    std::shared_ptr<Dragon> dragon1 = std::make_shared<Dragon>(name, 1, 1);
    std::shared_ptr<Dragon> dragon2 = std::make_shared<Dragon>(name, 1, 2);
    std::shared_ptr<Frog> frog = std::make_shared<Frog>(name, 2, 1);
    ASSERT_EQ(dragon2 -> accept(visitors[dragon1 -> get_type()], dragon1), false);
    ASSERT_EQ(frog -> accept(visitors[dragon1 -> get_type()], dragon1), false);
}

TEST(Test_Bull, Constr)
{
    std::string name {"default"};
    Bull bull(name, 1, 1);
    EXPECT_TRUE(bull.get_name() == name && bull.get_type() == BullType and bull.get_x() == 1 and bull.get_y() == 1);
}

TEST(Test_Bull, FightFrog)
{
    std::string name {"default"};
    std::shared_ptr<Bull> bull = std::make_shared<Bull>(name, 1, 2);
    std::shared_ptr<Frog> frog = std::make_shared<Frog>(name, 2, 1);
    EXPECT_TRUE(frog -> accept(visitors[bull -> get_type()], bull) == true);
}

TEST(Test_Bull, FightDragonBull) {
    std::string name {"default"};
    std::shared_ptr<Bull> bull1 = std::make_shared<Bull>(name, 1, 2);
    std::shared_ptr<Bull> bull2 = std::make_shared<Bull>(name, 1, 3);
    std::shared_ptr<Dragon> dragon = std::make_shared<Dragon>(name, 1, 1);

    EXPECT_TRUE(bull2 -> accept(visitors[bull1 -> get_type()], bull1) == false and dragon -> accept(visitors[bull1 -> get_type()], bull1) == false);
}

TEST(Test_Frog, Constr) {
    std::string name {"default"};
    Frog frog(name, 1, 1);
    EXPECT_TRUE(frog.get_name() == name && frog.get_type() == FrogType and frog.get_x() == 1 and frog.get_y() == 1);
}

TEST(Test_Frog, FightAll) {
    std::string name {"default"};
    std::shared_ptr<Frog> frog1 = std::make_shared<Frog>(name, 0, 1);
    std::shared_ptr<Frog> frog2 = std::make_shared<Frog>(name, 2, 1);
    std::shared_ptr<Bull> bull = std::make_shared<Bull>(name, 1, 2);
    std::shared_ptr<Dragon> dragon = std::make_shared<Dragon>(name, 1, 1);
    EXPECT_TRUE(frog2 -> accept(visitors[frog1 -> get_type()], frog1) == false and
                bull -> accept(visitors[frog1 -> get_type()], frog1) == false and
                dragon -> accept(visitors[frog1 -> get_type()], frog1) == false);
}

TEST(Test_NPC, Distance) {
    std::string name {"default"};
    std::shared_ptr<Frog> frog1 = std::make_shared<Frog>(name, 0, 1);
    std::shared_ptr<Frog> frog2 = std::make_shared<Frog>(name, 1, 1);
    std::size_t distance = 5;
    EXPECT_TRUE(frog1 -> is_close(frog2, distance));
}

TEST(Test_NPC, InsertObservers) {
    std::string name {"default"};
    std::shared_ptr<Bull> bull = std::make_shared<Bull>(name, 1, 2);
    std::shared_ptr<Frog> frog = std::make_shared<Frog>(name, 2, 1);
    ObserverConsole observer;
    std::shared_ptr observer1 = std::make_shared<ObserverConsole>(observer);
    bull -> subscribe(observer1);
    frog -> subscribe(observer1);
    EXPECT_TRUE(frog -> accept(visitors[bull -> get_type()], bull) == true);
}

TEST(Test_Factory, CreateNPC) {
    std::string name {"default"};
    std::shared_ptr<NPC> dragon = Create(DragonType, name,  1, 1);
    EXPECT_TRUE(dragon -> get_name() == name && dragon -> get_type() == DragonType and dragon -> get_x() == 1 and dragon -> get_y() == 1);
}


TEST(Test_Fight, FightDragonWithBull) {
    std::string name {"default"};
    std::shared_ptr<Bull> bull = std::make_shared<Bull>(name, 1, 2);
    std::shared_ptr<Dragon> dragon = std::make_shared<Dragon>(name, 1, 1);
    std::set<std::shared_ptr<NPC>> monsters {dragon, bull};
    std::set<std::shared_ptr<NPC>> corpse {bull};
    

    std::set<std::shared_ptr<NPC>> dead_list = battle(monsters, 10);
    ASSERT_EQ(corpse, dead_list);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}