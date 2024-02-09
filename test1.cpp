#include <gtest/gtest.h>
#include "declaration.h"
#include "npc.h"
#include "dragon.h"
#include "bull.h"
#include "frog.h"
#include "factory.h"
#include "observerConsole.h"
#include "observerFile.h"

TEST(Test_Dragon, Constr)
{
    Dragon Dragon{1, 1};
    EXPECT_TRUE(Dragon.getType() == "DragonType");
}

TEST(Test_Dragon, FightDragon)
{
    std::shared_ptr<Dragon> Dragon1 = std::make_shared<Dragon>(1, 1);
    std::shared_ptr<Dragon> Dragon2 = std::make_shared<Dragon>(1, 2);
    EXPECT_TRUE(Dragon1->accept(Dragon2) == false && Dragon2->accept(Dragon1) == false);
}

TEST(Test_Dragon, FightBull)
{
    std::shared_ptr<Dragon> dragon = std::make_shared<Dragon>(1, 1);
    std::shared_ptr<Bull> bull = std::make_shared<Bull>(1, 2);
    EXPECT_TRUE(bull->accept(dragon) == true);
}

TEST(Test_Dragon, FightFrog)
{
    std::shared_ptr<Dragon> dragon = std::make_shared<Dragon>(1, 1);
    std::shared_ptr<Frog> frog = std::make_shared<Frog>(1, 2);
    EXPECT_TRUE(frog->accept(dragon) == false);
}

TEST(Test_Bull, Constr)
{
    std::shared_ptr<Bull> bull = std::make_shared<Bull>(1, 2);
    EXPECT_TRUE(bull->getType() == "BullType");
}

TEST(Test_Bull, FightBull)
{

    std::shared_ptr<Bull> Bull1 = std::make_shared<Bull>(1, 1);
    std::shared_ptr<Bull> Bull2 = std::make_shared<Bull>(1, 2);
    EXPECT_TRUE(Bull1->accept(Bull2) == false && Bull2->accept(Bull1) == false);
}

TEST(Test_Bull, FightDragon)
{
    std::shared_ptr<Bull> bull = std::make_shared<Bull>(1, 1);
    std::shared_ptr<Dragon> dragon = std::make_shared<Dragon>(1, 2);
    EXPECT_TRUE(dragon->accept(bull) == false);
}

TEST(Test_Bull, FightFrog)
{
    std::shared_ptr<Bull> bull = std::make_shared<Bull>(1, 1);
    std::shared_ptr<Frog> frog = std::make_shared<Frog>(1, 2);
    EXPECT_TRUE(frog->accept(bull) == true);
}

TEST(Test_Frog, Constr)
{
    std::shared_ptr<Frog> frog = std::make_shared<Frog>(1, 1);
    EXPECT_TRUE(frog->getType() == "FrogType");
}

TEST(Test_Frog, FightFrog)
{
    std::shared_ptr<Frog> frog1 = std::make_shared<Frog>(1, 1);
    std::shared_ptr<Frog> frog2 = std::make_shared<Frog>(1, 2);
    EXPECT_TRUE(frog1->accept(frog2) == false && frog2->accept(frog1) == false);
}

TEST(Test_Frog, FightDragon)
{
    std::shared_ptr<Frog> frog = std::make_shared<Frog>(1, 1);
    std::shared_ptr<Dragon> dragon = std::make_shared<Dragon>(1, 2);
    EXPECT_TRUE(dragon->accept(frog) == false);
}

TEST(Test_Frog, FightBull)
{
    std::shared_ptr<Frog> frog = std::make_shared<Frog>(1, 1);
    std::shared_ptr<Bull> bull = std::make_shared<Bull>(1, 2);
    EXPECT_TRUE(bull->accept(frog) == false);
}

TEST(Test_NPC, Distance)
{
    std::shared_ptr<Frog> Frog1 = std::make_shared<Frog>(1, 1);
    std::shared_ptr<Frog> Frog2 = std::make_shared<Frog>(4, 5);
    float distance = 5.0;
    EXPECT_TRUE(Frog1->distance(Frog2) == distance);
}

TEST(Test_NPC, Alive)
{
    std::shared_ptr<Frog> frog = std::make_shared<Frog>(1, 1);
    EXPECT_TRUE(frog->isAlive() == true);
    frog->must_die();
    EXPECT_TRUE(frog->isAlive() == false);
}

TEST(Test_NPC, InsertObservers)
{
    Frog frog{1, 1};
    ObserverConsole observer;
    frog.subscribe(std::make_shared<ObserverConsole>(observer));
    EXPECT_TRUE(frog.countObservers() == 1);
}

TEST(Test_NPC, EraseObservers)
{
    Frog frog{1, 1};
    ObserverFile observer;
    std::shared_ptr observer1 = std::make_shared<ObserverFile>(observer);
    frog.subscribe(observer1);
    frog.unsubscribe(observer1);
    EXPECT_TRUE(frog.countObservers() == 0);
}

TEST(Test_NPC, Print)
{
    Frog frog{1, 1};

    std::ostringstream coutstream;
    std::streambuf *coutbuf = std::cout.rdbuf(coutstream.rdbuf());

    std::cout << frog;

    std::cout.rdbuf(coutbuf);

    std::string s = "Type : FrogType, x : 1, y : 1\n";

    EXPECT_TRUE(s == coutstream.str());
}

TEST(Test_Factory, CreateNPC)
{
    std::shared_ptr<NPC> obj = factory(NpcType(1), 1, 1);
    EXPECT_TRUE(obj->getType() == "DragonType");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}