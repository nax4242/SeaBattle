#include "pch.h"
#include "GameField.h"

TEST(GameFieldTests, DefaultConstructorCreatesEmptyFieldTest) {
    GameField field;

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
        "  +-------------------+";

    EXPECT_EQ(to_string(field), expected);
}

TEST(GameFieldTests, SetHorizontalShipTest) {
    GameField field;
    Ship ship(3, Position(4, 3), Horizontal);

    field.set(ship);

    EXPECT_EQ(to_string(field, true),
        "  |A B C D E F G H I J|\n"
        "  +-------------------+\n"
        "1 | | | | | | | | | | |\n"
        "2 | | | | | | | | | | |\n"
        "3 | | | | | | | | | | |\n"
        "4 | | |*|*|*| | | | | |\n"
        "5 | | | | | | | | | | |\n"
        "6 | | | | | | | | | | |\n"
        "7 | | | | | | | | | | |\n"
        "8 | | | | | | | | | | |\n"
        "9 | | | | | | | | | | |\n"
        "10| | | | | | | | | | |\n"
        "  +-------------------+");
}

TEST(GameFieldTests, SetVerticalShipTest) {
    GameField field;
    Ship ship(3, Position(3, 7), Vertical);

    field.set(ship);

    EXPECT_EQ(to_string(field, true),
        "  |A B C D E F G H I J|\n"
        "  +-------------------+\n"
        "1 | | | | | | | | | | |\n"
        "2 | | | | | | | | | | |\n"
        "3 | | | | | | |*| | | |\n"
        "4 | | | | | | |*| | | |\n"
        "5 | | | | | | |*| | | |\n"
        "6 | | | | | | | | | | |\n"
        "7 | | | | | | | | | | |\n"
        "8 | | | | | | | | | | |\n"
        "9 | | | | | | | | | | |\n"
        "10| | | | | | | | | | |\n"
        "  +-------------------+");
}

TEST(GameFieldTests, ToStringHidesShipsByDefaultTest) {
    GameField field;
    field.set(Ship(2, Position(1, 1), Horizontal));

    const std::string hidden = to_string(field);
    const std::string shown = to_string(field, true);

    EXPECT_EQ(hidden.find('*'), std::string::npos);
    EXPECT_NE(shown.find('*'), std::string::npos);
}

TEST(GameFieldTests, ToStringKeepsHitsAndMissesWhenShipsAreHiddenTest) {
    GameField field;
    field.set(Ship(2, Position(2, 2), Horizontal));

    EXPECT_EQ(field.set(1, 'A'), Missed);
    EXPECT_EQ(field.set(2, 'B'), Hit);

    const std::string hidden = to_string(field);
    EXPECT_NE(hidden.find("1 |.|"), std::string::npos);
    EXPECT_NE(hidden.find("2 | |X|"), std::string::npos);
    EXPECT_EQ(hidden.find('*'), std::string::npos);
}

TEST(GameFieldTests, CollisionWithOverlappingHorizontalShipTest) {
    GameField field;
    field.set(Ship(3, Position(4, 3), Horizontal));

    EXPECT_TRUE(is_collision(field, Ship(2, Position(4, 4), Horizontal)));
}

TEST(GameFieldTests, CollisionWithOverlappingVerticalShipTest) {
    GameField field;
    field.set(Ship(3, Position(3, 5), Vertical));

    EXPECT_TRUE(is_collision(field, Ship(2, Position(4, 5), Vertical)));
}

TEST(GameFieldTests, CollisionWithHorizontalNeighbourTest) {
    GameField field;
    field.set(Ship(2, Position(3, 3), Horizontal));

    EXPECT_TRUE(is_collision(field, Ship(1, Position(3, 5), Horizontal)));
}

TEST(GameFieldTests, CollisionWithVerticalNeighbourTest) {
    GameField field;
    field.set(Ship(2, Position(3, 3), Horizontal));

    EXPECT_TRUE(is_collision(field, Ship(1, Position(4, 3), Horizontal)));
}

TEST(GameFieldTests, CollisionWithDiagonalNeighbourTest) {
    GameField field;
    field.set(Ship(1, Position(4, 4), Horizontal));

    EXPECT_TRUE(is_collision(field, Ship(1, Position(5, 5), Horizontal)));
}

TEST(GameFieldTests, CollisionWithAlreadyHitShipCellTest) {
    GameField field;
    field.set(Ship(1, Position(4, 4), Horizontal));
    EXPECT_EQ(field.set(4, 'D'), BoatDestroyed);

    EXPECT_TRUE(is_collision(field, Ship(1, Position(4, 5), Horizontal)));
    EXPECT_TRUE(is_collision(field, Ship(1, Position(5, 5), Horizontal)));
}

TEST(GameFieldTests, ShipSeparatedByOneCellIsAcceptedTest) {
    GameField field;
    field.set(Ship(2, Position(3, 3), Horizontal));

    EXPECT_FALSE(is_collision(field, Ship(1, Position(3, 6), Horizontal)));
    EXPECT_FALSE(is_collision(field, Ship(1, Position(5, 3), Horizontal)));
    EXPECT_FALSE(is_collision(field, Ship(1, Position(5, 5), Horizontal)));
}

TEST(GameFieldTests, SetRejectsCollidingShipTest) {
    GameField field;
    field.set(Ship(3, Position(4, 3), Horizontal));

    try {
        field.set(Ship(2, Position(5, 5), Horizontal));
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "Invalid input: incorrect field");
    }
}

TEST(GameFieldTests, ShipExactlyFitsRightBoundaryTest) {
    GameField field;
    field.set(Ship(3, Position(1, 8), Horizontal));

    EXPECT_NE(to_string(field, true).find("1 | | | | | | | |*|*|*|"), std::string::npos);
}

TEST(GameFieldTests, ShipExactlyFitsBottomBoundaryTest) {
    GameField field;
    field.set(Ship(3, Position(8, 1), Vertical));

    EXPECT_NE(to_string(field, true).find("8 |*|"), std::string::npos);
    EXPECT_NE(to_string(field, true).find("9 |*|"), std::string::npos);
    EXPECT_NE(to_string(field, true).find("10|*|"), std::string::npos);
}

TEST(GameFieldTests, MissedMoveReturnsMissedTest) {
    GameField field;

    EXPECT_EQ(field.set(5, 'E'), Missed);
    EXPECT_NE(to_string(field).find("5 | | | | |."), std::string::npos);
}

TEST(GameFieldTests, FirstHitOnSingleDeckBoatReturnsBoatDestroyedTest) {
    GameField field;
    field.set(Ship(1, Position(4, 4), Horizontal));

    EXPECT_EQ(field.set(4, 'D'), BoatDestroyed);
}

TEST(GameFieldTests, FirstHitOnDestroyerReturnsHitTest) {
    GameField field;
    field.set(Ship(2, Position(4, 4), Horizontal));

    EXPECT_EQ(field.set(4, 'D'), Hit);
}

TEST(GameFieldTests, SecondHitOnDestroyerReturnsDestroyersDestroyedTest) {
    GameField field;
    field.set(Ship(2, Position(4, 4), Horizontal));

    EXPECT_EQ(field.set(4, 'D'), Hit);
    EXPECT_EQ(field.set(4, 'E'), DestroyersDestroyed);
}

TEST(GameFieldTests, CruiserIsDestroyedOnlyAfterAllThreeHitsTest) {
    GameField field;
    field.set(Ship(3, Position(4, 4), Horizontal));

    EXPECT_EQ(field.set(4, 'D'), Hit);
    EXPECT_EQ(field.set(4, 'E'), Hit);
    EXPECT_EQ(field.set(4, 'F'), CruisersDestroyed);
}

TEST(GameFieldTests, BattleshipIsDestroyedOnlyAfterAllFourHitsTest) {
    GameField field;
    field.set(Ship(4, Position(4, 4), Horizontal));

    EXPECT_EQ(field.set(4, 'D'), Hit);
    EXPECT_EQ(field.set(4, 'E'), Hit);
    EXPECT_EQ(field.set(4, 'F'), Hit);
    EXPECT_EQ(field.set(4, 'G'), BattleshipDestroyed);
}

TEST(GameFieldTests, VerticalDestroyerIsDestroyedTest) {
    GameField field;
    field.set(Ship(2, Position(4, 4), Vertical));

    EXPECT_EQ(field.set(4, 'D'), Hit);
    EXPECT_EQ(field.set(5, 'D'), DestroyersDestroyed);
}

TEST(GameFieldTests, AlreadyShotHitCellThrowsMoveErrorTest) {
    GameField field;
    field.set(Ship(1, Position(4, 4), Horizontal));

    EXPECT_EQ(field.set(4, 'D'), BoatDestroyed);
    try {
        field.set(4, 'D');
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "Invalid input: incorrect move");
    }
}

TEST(GameFieldTests, AlreadyShotMissCellThrowsMoveErrorTest) {
    GameField field;

    EXPECT_EQ(field.set(4, 'D'), Missed);
    try {
        field.set(4, 'D');
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "Invalid input: incorrect move");
    }
}

TEST(GameFieldTests, RowTooSmallThrowsMoveErrorTest) {
    GameField field;

    try {
        field.set(0, 'A');
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "Invalid input: incorrect move");
    }
}

TEST(GameFieldTests, RowTooBigThrowsMoveErrorTest) {
    GameField field;

    try {
        field.set(11, 'A');
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "Invalid input: incorrect move");
    }
}

TEST(GameFieldTests, ColumnTooSmallThrowsMoveErrorTest) {
    GameField field;

    try {
        field.set(1, '@');
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "Invalid input: incorrect move");
    }
}

TEST(GameFieldTests, ColumnTooBigThrowsMoveErrorTest) {
    GameField field;

    try {
        field.set(1, 'K');
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "Invalid input: incorrect move");
    }
}

TEST(GameFieldTests, LowerCaseColumnIsAcceptedTest) {
    GameField field;
    field.set(Ship(1, Position(4, 4), Horizontal));

    EXPECT_EQ(field.set(4, 'd'), BoatDestroyed);
}

