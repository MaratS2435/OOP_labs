#include <gtest/gtest.h>
#include <cstring>
#include "npc.h"
#include "dragon.h"
#include "bull.h"
#include "frog.h"
#include "observer.h"
#include "factory.h"
#include "battle.h"


TEST(Test_Dragon, Constructor) {
    Dragon dragon(1, 1);
    EXPECT_TRUE(dragon.get_type() == DragonType and dragon.get_x() == 1 and dragon.get_y() == 1);
}

TEST(Test_Dragon, FightBull)
{
    std::shared_ptr<Dragon> dragon = std::make_shared<Dragon>(1, 1);
    std::shared_ptr<Bull> bull = std::make_shared<Bull>(1, 2);

    
    EXPECT_TRUE(bull -> accept(dragon) == true);
}

TEST(Test_Dragon, FightDragonFrog){
    std::shared_ptr<Dragon> dragon1 = std::make_shared<Dragon>(1, 1);
    std::shared_ptr<Dragon> dragon2 = std::make_shared<Dragon>(1, 2);
    std::shared_ptr<Frog> frog = std::make_shared<Frog>(2, 1);
    ASSERT_EQ(dragon2 -> accept(dragon1), false);
    ASSERT_EQ(frog -> accept(dragon1), false);
}

TEST(Test_Bull, Constr)
{
    Bull bull(1, 1);
    EXPECT_TRUE(bull.get_type() == BullType and bull.get_x() == 1 and bull.get_y() == 1);
}

TEST(Test_Bull, FightFrog)
{
    std::shared_ptr<Bull> bull = std::make_shared<Bull>(1, 2);
    std::shared_ptr<Frog> frog = std::make_shared<Frog>(2, 1);
    EXPECT_TRUE(frog -> accept(bull) == true);
}

TEST(Test_Bull, FightDragonBull) {
    std::shared_ptr<Bull> bull1 = std::make_shared<Bull>(1, 2);
    std::shared_ptr<Bull> bull2 = std::make_shared<Bull>(1, 3);
    std::shared_ptr<Dragon> dragon = std::make_shared<Dragon>(1, 1);

    EXPECT_TRUE(bull2 -> accept(bull1) == false and dragon -> accept(bull1) == false);
}

TEST(Test_Frog, Constr) {
    Frog frog(1, 1);
    EXPECT_TRUE(frog.get_type() == FrogType and frog.get_x() == 1 and frog.get_y() == 1);
}

TEST(Test_Frog, FightAll) {
    std::shared_ptr<Frog> frog1 = std::make_shared<Frog>(0, 1);
    std::shared_ptr<Frog> frog2 = std::make_shared<Frog>(2, 1);
    std::shared_ptr<Bull> bull = std::make_shared<Bull>(1, 2);
    std::shared_ptr<Dragon> dragon = std::make_shared<Dragon>(1, 1);
    EXPECT_TRUE(frog2 -> accept(frog1) == false and
                bull -> accept(frog1) == false and
                dragon -> accept(frog1) == false);
}

TEST(Test_NPC, Distance) {
    std::shared_ptr<Frog> frog1 = std::make_shared<Frog>(0, 1);
    std::shared_ptr<Frog> frog2 = std::make_shared<Frog>(1, 1);
    std::size_t distance = 5;
    EXPECT_TRUE(frog1 -> is_close(frog2, distance));
}

TEST(Test_NPC, InsertObservers) {
    std::shared_ptr<Bull> bull = std::make_shared<Bull>(1, 2);
    std::shared_ptr<Frog> frog = std::make_shared<Frog>(2, 1);
    ObserverConsole observer;
    std::shared_ptr observer1 = std::make_shared<ObserverConsole>(observer);
    bull -> subscribe(observer1);
    frog -> subscribe(observer1);
    EXPECT_TRUE(frog -> accept(bull) == true);
}

TEST(Test_Factory, CreateNPC) {
    std::shared_ptr<NPC> dragon = Create(DragonType, 1, 1);
    EXPECT_TRUE(dragon -> get_type() == DragonType and dragon -> get_x() == 1 and dragon -> get_y() == 1);
}


TEST(Test_Fight, FightDragonWithBull) {
    std::shared_ptr<Bull> bull = std::make_shared<Bull>(1, 2);
    std::shared_ptr<Dragon> dragon = std::make_shared<Dragon>(1, 1);
    std::set<std::shared_ptr<NPC>> monsters {dragon, bull};
    std::set<std::shared_ptr<NPC>> corpse {bull};
    

    std::set<std::shared_ptr<NPC>> dead_list = battle(monsters, 10);
    ASSERT_EQ(corpse, dead_list);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}