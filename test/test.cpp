#include "bull.hpp"
#include "dragon.hpp"
#include "frog.hpp"
#include <gtest/gtest.h>

TEST(Fight_tests, Frog_vs_Frog){
    std::shared_ptr<NPC> frog1 = NPC::create_NPC(FROG, "JABA", 1, 1);
    std::shared_ptr<NPC> frog2 = NPC::create_NPC(FROG, "LYAGUSHKA", 1, 1);
    frog1->defend(frog2);
    ASSERT_EQ(frog1->stillAlive(), 1);
    ASSERT_EQ(frog1->stillAlive(), 1);
}

TEST(Fight_tests, Frog_vs_Bull){
    std::shared_ptr<NPC> frog = NPC::create_NPC(FROG, "JABA", 1, 1);
    std::shared_ptr<NPC> bull = NPC::create_NPC(BULL, "BULLISHE", 1, 1);
    frog->defend(bull);
    ASSERT_EQ(frog->stillAlive(), 0);
    ASSERT_EQ(bull->stillAlive(), 1);
}

TEST(Fight_tests, Frog_vs_Dragon){
    std::shared_ptr<NPC> frog = NPC::create_NPC(FROG, "JABA", 1, 1);
    std::shared_ptr<NPC> dragon = NPC::create_NPC(DRAGON, "ALDUIN", 1, 1);
    frog->defend(dragon);
    ASSERT_EQ(frog->stillAlive(), 1);
    ASSERT_EQ(dragon->stillAlive(), 1);
}

TEST(Fight_tests, Bull_vs_Bull){
    std::shared_ptr<NPC> bull1 = NPC::create_NPC(BULL, "BULLSHIT", 1, 1);
    std::shared_ptr<NPC> bull2 = NPC::create_NPC(BULL, "BULLISHE", 1, 1);
    bull1->defend(bull2);
    ASSERT_EQ(bull1->stillAlive(), 1);
    ASSERT_EQ(bull2->stillAlive(), 1);
}

TEST(Fight_tests, Dragon_vs_Bull){
    std::shared_ptr<NPC> dragon = NPC::create_NPC(DRAGON, "ALDUIN", 1, 1);
    std::shared_ptr<NPC> bull = NPC::create_NPC(BULL, "BULLISHE", 1, 1);
    bull->defend(dragon);
    ASSERT_EQ(bull->stillAlive(), 0);
    ASSERT_EQ(dragon->stillAlive(), 1);
}

TEST(Fight_tests, Dragon_vs_Dragon){
    std::shared_ptr<NPC> dragon1 = NPC::create_NPC(DRAGON, "PARTUNAX", 1, 1);
    std::shared_ptr<NPC> dragon2 = NPC::create_NPC(DRAGON, "ALDUIN", 1, 1);
    dragon2->defend(dragon1);
    ASSERT_EQ(dragon1->stillAlive(), 1);
    ASSERT_EQ(dragon2->stillAlive(), 1);
}

TEST(Fight_tests, Bull_attack_Dragon){
    std::shared_ptr<NPC> dragon = NPC::create_NPC(DRAGON, "ALDUIN", 1, 1);
    std::shared_ptr<NPC> bull = NPC::create_NPC(BULL, "BULLISHE", 1, 1);
    dragon->defend(bull);
    ASSERT_EQ(bull->stillAlive(), 0);
    ASSERT_EQ(dragon->stillAlive(), 1);
}

TEST(Fight_tests, Frog_attack_Bull){
    std::shared_ptr<NPC> frog = NPC::create_NPC(FROG, "JABA", 1, 1);
    std::shared_ptr<NPC> bull = NPC::create_NPC(BULL, "BULLISHE", 1, 1);
    bull->defend(frog);
    ASSERT_EQ(frog->stillAlive(), 0);
    ASSERT_EQ(bull->stillAlive(), 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}