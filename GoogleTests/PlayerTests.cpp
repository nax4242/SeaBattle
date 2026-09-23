#include "pch.h"
#include "Player.h"

TEST(PlayerTests, DefaultConstructorCreatesPlayerNotReadyTest) {
    Player player;

    EXPECT_FALSE(player.check_ready());
}

TEST(PlayerTests, DefaultConstructorPlayerIsLosingTest) {
    Player player;

    EXPECT_TRUE(player.check_lose());
}

TEST(PlayerTests, SetSingleDeckShipTest) {
    Player player;

    player.set_ship(Ship(1, Position(1, 1), Horizontal));

    EXPECT_FALSE(player.check_ready());
    EXPECT_FALSE(player.check_lose());
}

TEST(PlayerTests, SetTwoDeckShipTest) {
    Player player;

    player.set_ship(Ship(2, Position(1, 1), Horizontal));

    EXPECT_FALSE(player.check_ready());
    EXPECT_FALSE(player.check_lose());
}

TEST(PlayerTests, SetThreeDeckShipTest) {
    Player player;

    player.set_ship(Ship(3, Position(1, 1), Horizontal));

    EXPECT_FALSE(player.check_ready());
    EXPECT_FALSE(player.check_lose());
}

TEST(PlayerTests, SetFourDeckShipTest) {
    Player player;

    player.set_ship(Ship(4, Position(1, 1), Horizontal));

    EXPECT_FALSE(player.check_ready());
    EXPECT_FALSE(player.check_lose());
}

TEST(PlayerTests, MaximumSingleDeckShipsAcceptedTest) {
    Player player;

    player.set_ship(Ship(1, Position(1, 1), Horizontal));
    player.set_ship(Ship(1, Position(1, 3), Horizontal));
    player.set_ship(Ship(1, Position(1, 5), Horizontal));
    player.set_ship(Ship(1, Position(1, 7), Horizontal));

    EXPECT_FALSE(player.check_ready());
    EXPECT_FALSE(player.check_lose());
}

TEST(PlayerTests, ExtraSingleDeckShipThrowsFieldErrorTest) {
    Player player;

    player.set_ship(Ship(1, Position(1, 1), Horizontal));
    player.set_ship(Ship(1, Position(1, 3), Horizontal));
    player.set_ship(Ship(1, Position(1, 5), Horizontal));
    player.set_ship(Ship(1, Position(1, 7), Horizontal));

    try {
        player.set_ship(Ship(1, Position(1, 10), Horizontal));
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "Invalid input: incorrect field");
    }
}

TEST(PlayerTests, ExtraTwoDeckShipThrowsFieldErrorTest) {
    Player player;

    player.set_ship(Ship(2, Position(1, 1), Horizontal));
    player.set_ship(Ship(2, Position(3, 1), Horizontal));
    player.set_ship(Ship(2, Position(5, 1), Horizontal));

    try {
        player.set_ship(Ship(2, Position(7, 1), Horizontal));
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "Invalid input: incorrect field");
    }
}

TEST(PlayerTests, ExtraThreeDeckShipThrowsFieldErrorTest) {
    Player player;

    player.set_ship(Ship(3, Position(1, 1), Horizontal));
    player.set_ship(Ship(3, Position(3, 1), Horizontal));

    try {
        player.set_ship(Ship(3, Position(5, 1), Horizontal));
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "Invalid input: incorrect field");
    }
}

TEST(PlayerTests, ExtraFourDeckShipThrowsFieldErrorTest) {
    Player player;

    player.set_ship(Ship(4, Position(1, 1), Horizontal));

    try {
        player.set_ship(Ship(4, Position(3, 1), Horizontal));
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "Invalid input: incorrect field");
    }
}

TEST(PlayerTests, CollidingShipDoesNotIncreaseShipCountTest) {
    Player player;

    player.set_ship(Ship(1, Position(1, 1), Horizontal));

    try {
        player.set_ship(Ship(1, Position(1, 2), Horizontal));
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "Invalid input: incorrect field");
    }

    player.set_ship(Ship(1, Position(1, 3), Horizontal));
    player.set_ship(Ship(1, Position(1, 5), Horizontal));
    player.set_ship(Ship(1, Position(1, 7), Horizontal));

    EXPECT_FALSE(player.check_lose());
}

TEST(PlayerTests, SetActionMissedReturnsMissedTest) {
    Player player;
    player.set_ship(Ship(2, Position(4, 4), Horizontal));

    EXPECT_EQ(player.set_action(5, 'E'), Missed);
    EXPECT_FALSE(player.check_lose());
}

TEST(PlayerTests, SetActionHitReturnsHitTest) {
    Player player;
    player.set_ship(Ship(2, Position(4, 4), Horizontal));

    EXPECT_EQ(player.set_action(4, 'D'), Hit);
    EXPECT_FALSE(player.check_lose());
}

TEST(PlayerTests, SetActionDestroySingleDeckShipUpdatesLoseTest) {
    Player player;
    player.set_ship(Ship(1, Position(4, 4), Horizontal));

    EXPECT_EQ(player.set_action(4, 'D'), BoatDestroyed);
    EXPECT_TRUE(player.check_lose());
}

TEST(PlayerTests, SetActionDestroyTwoDeckShipUpdatesShipsCountTest) {
    Player player;
    player.set_ship(Ship(2, Position(4, 4), Horizontal));

    EXPECT_EQ(player.set_action(4, 'D'), Hit);
    EXPECT_FALSE(player.check_lose());

    EXPECT_EQ(player.set_action(4, 'E'), DestroyersDestroyed);
    EXPECT_TRUE(player.check_lose());
}

TEST(PlayerTests, SetActionDestroyThreeDeckShipUpdatesShipsCountTest) {
    Player player;
    player.set_ship(Ship(3, Position(4, 4), Horizontal));

    EXPECT_EQ(player.set_action(4, 'D'), Hit);
    EXPECT_EQ(player.set_action(4, 'E'), Hit);
    EXPECT_EQ(player.set_action(4, 'F'), CruisersDestroyed);
    EXPECT_TRUE(player.check_lose());
}

TEST(PlayerTests, SetActionDestroyFourDeckShipUpdatesShipsCountTest) {
    Player player;
    player.set_ship(Ship(4, Position(4, 4), Horizontal));

    EXPECT_EQ(player.set_action(4, 'D'), Hit);
    EXPECT_EQ(player.set_action(4, 'E'), Hit);
    EXPECT_EQ(player.set_action(4, 'F'), Hit);
    EXPECT_EQ(player.set_action(4, 'G'), BattleshipDestroyed);
    EXPECT_TRUE(player.check_lose());
}

TEST(PlayerTests, CheckReadyReturnsFalseForIncompleteFleetTest) {
    Player player;

    player.set_ship(Ship(1, Position(1, 1), Horizontal));
    player.set_ship(Ship(1, Position(1, 3), Horizontal));
    player.set_ship(Ship(1, Position(1, 5), Horizontal));
    player.set_ship(Ship(1, Position(1, 7), Horizontal));

    player.set_ship(Ship(2, Position(3, 1), Horizontal));
    player.set_ship(Ship(2, Position(3, 4), Horizontal));
    player.set_ship(Ship(2, Position(3, 7), Horizontal));

    EXPECT_FALSE(player.check_ready());
}

TEST(PlayerTests, CheckReadyReturnsTrueForCompleteFleetTest) {
    Player player;

    player.set_ship(Ship(1, Position(1, 1), Horizontal));
    player.set_ship(Ship(1, Position(1, 3), Horizontal));
    player.set_ship(Ship(1, Position(1, 5), Horizontal));
    player.set_ship(Ship(1, Position(1, 7), Horizontal));

    player.set_ship(Ship(2, Position(3, 1), Horizontal));
    player.set_ship(Ship(2, Position(3, 4), Horizontal));
    player.set_ship(Ship(2, Position(3, 7), Horizontal));

    player.set_ship(Ship(3, Position(5, 1), Horizontal));
    player.set_ship(Ship(3, Position(5, 5), Horizontal));

    player.set_ship(Ship(4, Position(7, 1), Horizontal));

    EXPECT_TRUE(player.check_ready());
    EXPECT_FALSE(player.check_lose());
}

TEST(PlayerTests, CheckReadyRemainsTrueAfterHitTest) {
    Player player;

    player.set_ship(Ship(1, Position(1, 1), Horizontal));
    player.set_ship(Ship(1, Position(1, 3), Horizontal));
    player.set_ship(Ship(1, Position(1, 5), Horizontal));
    player.set_ship(Ship(1, Position(1, 7), Horizontal));

    player.set_ship(Ship(2, Position(3, 1), Horizontal));
    player.set_ship(Ship(2, Position(3, 4), Horizontal));
    player.set_ship(Ship(2, Position(3, 7), Horizontal));

    player.set_ship(Ship(3, Position(5, 1), Horizontal));
    player.set_ship(Ship(3, Position(5, 5), Horizontal));

    player.set_ship(Ship(4, Position(7, 1), Horizontal));

    EXPECT_TRUE(player.check_ready());

    EXPECT_EQ(player.set_action(1, 'A'), BoatDestroyed);

    EXPECT_FALSE(player.check_ready());
    EXPECT_FALSE(player.check_lose());
}

TEST(PlayerTests, ShowFieldShowsShipsByDefaultTest) {
    Player player;
    player.set_ship(Ship(1, Position(1, 1), Horizontal));

    testing::internal::CaptureStdout();
    player.show_field();
    const std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("*"), std::string::npos);
    EXPECT_NE(output.find("Ships Left:\n* - 1 ** - 0 *** - 0 **** - 0"), std::string::npos);
}

TEST(PlayerTests, ShowFieldHidesShipsWhenRequestedTest) {
    Player player;
    player.set_ship(Ship(1, Position(1, 1), Horizontal));

    testing::internal::CaptureStdout();
    player.show_field(true);
    const std::string output = testing::internal::GetCapturedStdout();

    const std::string ships_left = "Ships Left:\n";

    const size_t ships_left_pos = output.find(ships_left);

    ASSERT_NE(ships_left_pos, std::string::npos);

    const std::string field = output.substr(0, ships_left_pos);

    EXPECT_EQ(field.find('*'), std::string::npos);

    EXPECT_NE(
        output.find("Ships Left:\n* - 1 ** - 0 *** - 0 **** - 0"),
        std::string::npos
    );
}

TEST(PlayerTests, ShowFieldPrintsFieldWithExactFormattingTest) {
    Player player;

    testing::internal::CaptureStdout();
    player.show_field();
    const std::string output = testing::internal::GetCapturedStdout();

    const std::string expected =
        "  |A B C D E F G H I J|\n"
        "  +-------------------+\n"
        "1 | | | | | | | | | | |\n"
        "2 | | | | | | | | | | |\n"
        "3 | | | | | | | | | | |\n"
        "4 | | | | | | | | | | |\n"
        "5 | | | | | | | | | | |\n"
        "6 | | | | | | | | | | |\n"
        "7 | | | | | | | | | | |\n"
        "8 | | | | | | | | | | |\n"
        "9 | | | | | | | | | | |\n"
        "10| | | | | | | | | | |\n"
        "  +-------------------+\n\n"
        "Ships Left:\n"
        "* - 0 ** - 0 *** - 0 **** - 0";

    EXPECT_EQ(output, expected);
}

TEST(PlayerTests, ShowFieldAfterActionDisplaysMissTest) {
    Player player;

    player.set_action(5, 'E');

    testing::internal::CaptureStdout();
    player.show_field(true);
    const std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("5 | | | | |.| | | | | |"), std::string::npos);
}
