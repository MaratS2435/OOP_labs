#include <gtest/gtest.h>
#include "npc.cpp"
#include "dragon.cpp"
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

TEST(MOVE, MoveDragon){
    std::shared_ptr<NPC> dragon = std::make_shared<Dragon>(10, 15);
    const int MAX_X{100};
    const int MAX_Y{100};
    const int DISTANCE_MOVE_DRAGON{50};
    dragon->move(DISTANCE_MOVE_DRAGON, DISTANCE_MOVE_DRAGON, MAX_X, MAX_Y);
    auto [x, y] = dragon->position();
    ASSERT_EQ(x, 60);

}

TEST(MOVE, MovePrincess){
    std::shared_ptr<NPC> princess = std::make_shared<Princess>(10, 15);
    const int MAX_X{100};
    const int MAX_Y{100};
    const int DISTANCE_MOVE_PRINCESS{1};
    princess->move(DISTANCE_MOVE_PRINCESS, DISTANCE_MOVE_PRINCESS, MAX_X, MAX_Y);
    auto [x, y] = princess->position();
    ASSERT_EQ(x, 11);
}

TEST(MOVE, MoveKnight){
    std::shared_ptr<NPC> knight = std::make_shared<WanderingKnight>(10, 15);
    const int MAX_X{100};
    const int MAX_Y{100};
    const int DISTANCE_MOVE_KNIGHT{30};

    knight->move(DISTANCE_MOVE_KNIGHT, DISTANCE_MOVE_KNIGHT, MAX_X, MAX_Y);
    auto [x, y] = knight->position();
    ASSERT_EQ(x, 40);

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
