#include <gtest/gtest.h>
#include "NPC.cpp"
#include "Dragon.cpp"
#include "WanderingKnight.cpp"
#include "Princess.cpp"

TEST(AcceptTest, DragonAttackKnight) {
    std::shared_ptr<NPC> dragon = std::make_shared<Dragon>(10, 15);
    std::shared_ptr<NPC> knight = std::make_shared<WanderingKnight>(7, 15);
    bool success = dragon->accept(knight);
    ASSERT_TRUE(success);
}

TEST(AcceptTest, KnightAttackDragon) {
    std::shared_ptr<NPC> dragon = std::make_shared<Dragon>(10, 15);
    std::shared_ptr<NPC> knight = std::make_shared<WanderingKnight>(7, 15);
    bool success = knight->accept(dragon);
    ASSERT_FALSE(success);
}

TEST(AcceptTest, KnightAttackPrincess) {
    std::shared_ptr<NPC> princess = std::make_shared<Princess>(10, 15);
    std::shared_ptr<NPC> knight = std::make_shared<WanderingKnight>(7, 15);
    bool success = princess->accept(knight);
    ASSERT_FALSE(success);
}

TEST(AcceptTest, PrincessAttackKnight) {
    std::shared_ptr<NPC> princess = std::make_shared<Princess>(10, 15);
    std::shared_ptr<NPC> knight = std::make_shared<WanderingKnight>(7, 15);
    bool success = knight->accept(princess);
    ASSERT_FALSE(success);
}

TEST(AcceptTest, PrincessAttackDragon) {
    std::shared_ptr<NPC> dragon = std::make_shared<Dragon>(10, 15);
    std::shared_ptr<NPC> princess = std::make_shared<Princess>(7, 15);
    bool success = dragon->accept(princess);
    ASSERT_FALSE(success);
}

TEST(AcceptTest, DragonAttackPrincess) {
    std::shared_ptr<NPC> dragon = std::make_shared<Dragon>(10, 15);
    std::shared_ptr<NPC> princess = std::make_shared<Princess>(7, 15);
    bool success = princess->accept(dragon);
    ASSERT_TRUE(success);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
