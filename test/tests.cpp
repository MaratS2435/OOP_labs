#include <gtest/gtest.h>
#include <vector>
#include "battlefield.h"

// TEST(FactoryTest, TEST_01) {
//     std::shared_ptr<BearFactory> fB = std::make_shared<BearFactory>();
//     std::shared_ptr<NPC> bear = fB->create(10,20);
//     ASSERT_TRUE(bear->type() == BEAR && bear->coords().first == 10 && bear->coords().second == 20);
// }

// TEST(FactoryTest, TEST_02) {
//     std::shared_ptr<Factory> fB = std::make_shared<OrcFactory>();
//     std::shared_ptr<NPC> orc = fB->create(10,20);
//     ASSERT_TRUE(orc->type() == ORC && orc->coords().first == 10 && orc->coords().second == 20);
// }

// TEST(FactoryTest, TEST_03) {
//     std::shared_ptr<Factory> fB = std::make_shared<SquirrelFactory>();
//     std::shared_ptr<NPC> squirrel = fB->create(10,20);
//     ASSERT_TRUE(squirrel->type() == SQUIRREL && squirrel->coords().first == 10 && squirrel->coords().second == 20);
// }

// TEST(BattleCheck, TEST_01) {
//     std::shared_ptr<Factory> fB = std::make_shared<SquirrelFactory>();
//     std::shared_ptr<NPC> squirrel = fB->create(10,20);
//     std::shared_ptr<Factory> fO = std::make_shared<OrcFactory>();
//     std::shared_ptr<NPC> orc = fO->create(10,20);
//     ASSERT_TRUE(!squirrel->accept(orc));
// }

// TEST(BattleCheck, TEST_02) {
//     std::shared_ptr<Factory> fB = std::make_shared<SquirrelFactory>();
//     std::shared_ptr<NPC> squirrel = fB->create(10,20);
//     std::shared_ptr<Factory> fO = std::make_shared<OrcFactory>();
//     std::shared_ptr<NPC> orc = fO->create(10,20);
//     ASSERT_TRUE(!squirrel->accept(orc) && !orc->accept(squirrel));
// }

// TEST(BattleCheck, TEST_03) {
//     std::shared_ptr<Factory> fB = std::make_shared<SquirrelFactory>();
//     std::shared_ptr<NPC> squirrel = fB->create(10,20);
//     std::shared_ptr<Factory> fO = std::make_shared<BearFactory>();
//     std::shared_ptr<NPC> bear = fO->create(10,20);
//     std::cout << bear->accept(squirrel) << ' ' << !squirrel->accept(bear) << std::endl;
//     ASSERT_TRUE(bear->accept(squirrel) && !squirrel->accept(bear));
// }

// TEST(BattleCheck, TEST_04) {
//     std::shared_ptr<Factory> fB = std::make_shared<OrcFactory>();
//     std::shared_ptr<NPC> orc = fB->create(10,20);
//     std::shared_ptr<Factory> fO = std::make_shared<BearFactory>();
//     std::shared_ptr<NPC> bear = fO->create(10,20);
//     ASSERT_TRUE(!bear->accept(orc) && orc->accept(bear));
// }

// TEST(Kill, TEST_01) {
//     std::shared_ptr<Factory> fB = std::make_shared<OrcFactory>();
//     std::shared_ptr<NPC> orc = fB->create(10,20);
//     std::shared_ptr<Factory> fO = std::make_shared<BearFactory>();
//     std::shared_ptr<NPC> bear = fO->create(10,20);
//     std::shared_ptr<Factory> fS = std::make_shared<SquirrelFactory>();
//     std::shared_ptr<NPC> squirrel = fS->create(10,20);
//     orc->kill(); bear->kill(); squirrel->kill();
//     ASSERT_TRUE(!orc->is_alive() && !bear->is_alive() && !squirrel->is_alive());
// }

// TEST(Distance, TEST_01) {
//     std::shared_ptr<Factory> fB = std::make_shared<OrcFactory>();
//     std::shared_ptr<NPC> orc = fB->create(10,20);
//     std::shared_ptr<Factory> fO = std::make_shared<BearFactory>();
//     std::shared_ptr<NPC> bear = fO->create(10,20);
//     std::shared_ptr<Factory> fS = std::make_shared<SquirrelFactory>();
//     std::shared_ptr<NPC> squirrel = fS->create(30,20);
//     ASSERT_TRUE(fabs(squirrel->distance(bear) - 20) < ESPILON);
// }

// TEST(Distance, TEST_02) {
//     std::shared_ptr<Factory> fB = std::make_shared<OrcFactory>();
//     std::shared_ptr<NPC> orc = fB->create(10,20);
//     std::shared_ptr<Factory> fO = std::make_shared<BearFactory>();
//     std::shared_ptr<NPC> bear = fO->create(10,20);
//     std::shared_ptr<Factory> fS = std::make_shared<SquirrelFactory>();
//     std::shared_ptr<NPC> squirrel = fS->create(-30,-20);
//     ASSERT_TRUE(fabs(squirrel->distance(bear) - 56.568) < ESPILON);
// }

// TEST(BattlefieldTEST, TEST_01) {
//     std::shared_ptr<Factory> fB = std::make_shared<OrcFactory>();
//     std::shared_ptr<NPC> orc = fB->create(10,20);
//     std::shared_ptr<Factory> fO = std::make_shared<BearFactory>();
//     std::shared_ptr<NPC> bear = fO->create(10,20);
//     std::shared_ptr<Factory> fS = std::make_shared<SquirrelFactory>();
//     std::shared_ptr<NPC> squirrel = fS->create(-30,-20);
//     std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
//     btf->placeHero(orc);
//     btf->placeHero(bear);
//     btf->placeHero(squirrel);
//     ASSERT_TRUE(btf->npc().size() == 3);
// }

// TEST(BattlefieldTEST, TEST_02) {
//     std::shared_ptr<Factory> fB = std::make_shared<OrcFactory>();
//     std::shared_ptr<NPC> orc = fB->create(10,20);
//     std::shared_ptr<Factory> fO = std::make_shared<BearFactory>();
//     std::shared_ptr<NPC> bear = fO->create(10,20);
//     std::shared_ptr<Factory> fS = std::make_shared<SquirrelFactory>();
//     std::shared_ptr<NPC> squirrel = fS->create(10,20);
//     std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
//     btf->placeHero(orc);
//     btf->placeHero(bear);
//     btf->placeHero(squirrel);
//     ASSERT_NO_THROW(btf->battle(1,2));
// }

// TEST(BattlefieldTEST, TEST_03) {
//     std::shared_ptr<Factory> fB = std::make_shared<OrcFactory>();
//     std::shared_ptr<NPC> orc = fB->create(10,20);
//     std::shared_ptr<Factory> fO = std::make_shared<BearFactory>();
//     std::shared_ptr<NPC> bear = fO->create(10,20);
//     std::shared_ptr<Factory> fS = std::make_shared<SquirrelFactory>();
//     std::shared_ptr<NPC> squirrel = fS->create(10,20);
//     std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
//     btf->placeHero(orc);
//     btf->placeHero(bear);
//     btf->placeHero(squirrel);
//     btf->battle(1,2);
//     btf->removeDeadmen();
//     ASSERT_TRUE(btf->npc().size() == 2);
// }

// TEST(BattlefieldTEST, TEST_04) {
//     std::shared_ptr<Factory> fB = std::make_shared<OrcFactory>();
//     std::shared_ptr<NPC> orc = fB->create(10,20);
//     std::shared_ptr<Factory> fO = std::make_shared<BearFactory>();
//     std::shared_ptr<NPC> bear = fO->create(10,20);
//     std::shared_ptr<Factory> fS = std::make_shared<SquirrelFactory>();
//     std::shared_ptr<NPC> squirrel = fS->create(10,20);
//     std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
//     btf->fillRandomly(1,10,10,10);
//     ASSERT_TRUE(btf->npc().size()==30);
// }


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}