#include "pch.h"
#include "Ship.h"
#include "flags.h"

#ifdef SHIP_TESTS

TEST(ShipTests, InitConstructorTest) {
    Ship s(3, Position(4, 3), Horizontal);
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.direction(), Horizontal);
    EXPECT_EQ(s.row(), 4);
    EXPECT_EQ(s.col(), 3);
}

TEST(ShipTests, InitConstructorVerticalTest) {
    Ship s(2, Position(5, 5), Vertical);
    EXPECT_EQ(s.direction(), Vertical);
}

TEST(ShipTests, PartialConstructorNoLongerCompilesNote) {
    SUCCEED();
}

TEST(ShipTests, CharConstructorMatchesExampleFromTaskTest) {
    Ship s(3, 'H', 4, 'C');
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.direction(), Horizontal);
    EXPECT_EQ(s.row(), 4);
    EXPECT_EQ(s.col(), 3);
}

TEST(ShipTests, CharConstructorVerticalTest) {
    Ship s(2, 'V', 3, 'B');
    EXPECT_EQ(s.direction(), Vertical);
    EXPECT_EQ(s.row(), 3);
    EXPECT_EQ(s.col(), 2);
}

TEST(ShipTests, CharConstructorLowerCaseDirectionTest) {
    Ship s(1, 'h', 2, 'H');
    EXPECT_EQ(s.direction(), Horizontal);
    EXPECT_EQ(s.row(), 2);
    EXPECT_EQ(s.col(), 8);
}

TEST(ShipTests, CharConstructorLowerCaseColumnTest) {
    Ship s(1, 'H', 1, 'a');
    EXPECT_EQ(s.col(), 1);
}

TEST(ShipTests, CharConstructorColumnALowerBoundTest) {
    Ship s(1, 'H', 1, 'A');
    EXPECT_EQ(s.col(), 1);
}

TEST(ShipTests, CharConstructorColumnJUpperBoundTest) {
    Ship s(1, 'H', 1, 'J');
    EXPECT_EQ(s.col(), 10);
}

TEST(ShipTests, CharConstructorInvalidDirectionThrowsTest) {
    EXPECT_THROW(Ship(2, 'X', 1, 'A'), std::logic_error);
}

TEST(ShipTests, CharConstructorInvalidColumnThrowsTest) {
    EXPECT_THROW(Ship(2, 'H', 1, 'Z'), std::logic_error);
}

TEST(ShipTests, CharConstructorInvalidRowThrowsTest) {
    EXPECT_THROW(Ship(2, 'H', 11, 'A'), std::logic_error);
}

TEST(ShipTests, SizeTooSmallThrowsTest) {
    EXPECT_THROW(Ship(0, Position(1, 1), Horizontal), std::logic_error);
}

TEST(ShipTests, SizeTooBigThrowsTest) {
    EXPECT_THROW(Ship(5, Position(1, 1), Horizontal), std::logic_error);
}

TEST(ShipTests, SizeMaxAllowedTest) {
    Ship s(4, Position(1, 1), Horizontal);
    EXPECT_EQ(s.size(), 4);
}

TEST(ShipTests, SizeMinAllowedTest) {
    Ship s(1, Position(1, 1), Horizontal);
    EXPECT_EQ(s.size(), 1);
}

TEST(ShipTests, HorizontalOutOfBoundsThrowsTest) {
    EXPECT_THROW(Ship(3, Position(1, 9), Horizontal), std::logic_error);
}

TEST(ShipTests, HorizontalExactlyFitsTest) {
    Ship s(3, Position(1, 8), Horizontal);
    EXPECT_EQ(s.col(), 8);
}

TEST(ShipTests, VerticalOutOfBoundsThrowsTest) {
    EXPECT_THROW(Ship(3, Position(9, 1), Vertical), std::logic_error);
}

TEST(ShipTests, VerticalExactlyFitsTest) {
    Ship s(3, Position(8, 1), Vertical);
    EXPECT_EQ(s.row(), 8);
}

TEST(ShipTests, HorizontalIgnoresRowOverflowTest) {
    Ship s(2, Position(10, 1), Horizontal);
    EXPECT_EQ(s.row(), 10);
}

TEST(ShipTests, VerticalIgnoresColOverflowTest) {
    Ship s(2, Position(1, 10), Vertical);
    EXPECT_EQ(s.col(), 10);
}

TEST(ShipTests, IsCollisionDirectTest) {
    EXPECT_FALSE(is_collision(3, Position(1, 8), Horizontal));
    EXPECT_TRUE(is_collision(3, Position(1, 9), Horizontal));
    EXPECT_FALSE(is_collision(3, Position(8, 1), Vertical));
    EXPECT_TRUE(is_collision(3, Position(9, 1), Vertical));
}

TEST(ShipTests, PositionGetterTest) {
    Ship s(2, Position(6, 5), Horizontal);
    Position p = s.position();
    EXPECT_EQ(p.row(), 6);
    EXPECT_EQ(p.col(), 5);
}

TEST(ShipTests, SizeSetterValidTest) {
    Ship s(1, Position(1, 1), Horizontal);
    s.size(4);
    EXPECT_EQ(s.size(), 4);
}

TEST(ShipTests, SizeSetterThrowOutOfRangeTest) {
    Ship s(1, Position(1, 1), Horizontal);
    EXPECT_THROW(s.size(0), std::logic_error);
    EXPECT_THROW(s.size(5), std::logic_error);
}

TEST(ShipTests, SizeSetterThrowWhenDoesNotFitTest) {
    Ship s(1, Position(1, 8), Horizontal);
    EXPECT_THROW(s.size(4), std::logic_error);
    EXPECT_EQ(s.size(), 1);
}

TEST(ShipTests, RowSetterValidTest) {
    Ship s(2, Position(1, 1), Horizontal);
    s.row(8);
    EXPECT_EQ(s.row(), 8);
}

TEST(ShipTests, RowSetterThrowOutOfFieldTest) {
    Ship s(2, Position(1, 1), Horizontal);
    EXPECT_THROW(s.row(0), std::logic_error);
    EXPECT_THROW(s.row(11), std::logic_error);
}

TEST(ShipTests, RowSetterThrowWhenDoesNotFitVerticalTest) {
    Ship s(4, Position(7, 1), Vertical);
    EXPECT_THROW(s.row(8), std::logic_error);
    EXPECT_EQ(s.row(), 7);
}

TEST(ShipTests, ColIntSetterValidTest) {
    Ship s(2, Position(1, 1), Horizontal);
    s.col(8);
    EXPECT_EQ(s.col(), 8);
}

TEST(ShipTests, ColIntSetterThrowOutOfFieldTest) {
    Ship s(2, Position(1, 1), Horizontal);
    EXPECT_THROW(s.col(0), std::logic_error);
    EXPECT_THROW(s.col(11), std::logic_error);
}

TEST(ShipTests, ColIntSetterThrowWhenDoesNotFitTest) {
    Ship s(4, Position(1, 1), Horizontal);
    EXPECT_THROW(s.col(8), std::logic_error);
    EXPECT_EQ(s.col(), 1);
}

TEST(ShipTests, ColCharSetterValidTest) {
    Ship s(2, Position(1, 1), Horizontal);
    s.col('H');
    EXPECT_EQ(s.col(), 8);
}

TEST(ShipTests, ColCharSetterLowerCaseTest) {
    Ship s(2, Position(1, 1), Horizontal);
    s.col('h');
    EXPECT_EQ(s.col(), 8);
}

TEST(ShipTests, ColCharSetterThrowOutOfFieldTest) {
    Ship s(2, Position(1, 1), Horizontal);
    EXPECT_THROW(s.col('Z'), std::logic_error);
}

TEST(ShipTests, DirectionEnumSetterTest) {
    Ship s(2, Position(1, 1), Horizontal);
    s.direction(Vertical);
    EXPECT_EQ(s.direction(), Vertical);
}

TEST(ShipTests, DirectionEnumSetterThrowWhenDoesNotFitTest) {
    Ship s(4, Position(9, 1), Horizontal);
    EXPECT_THROW(s.direction(Vertical), std::logic_error);
    EXPECT_EQ(s.direction(), Horizontal);
}

TEST(ShipTests, DirectionCharSetterTest) {
    Ship s(2, Position(1, 1), Horizontal);
    s.direction('V');
    EXPECT_EQ(s.direction(), Vertical);
}

TEST(ShipTests, DirectionCharSetterLowerCaseTest) {
    Ship s(2, Position(1, 1), Horizontal);
    s.direction('v');
    EXPECT_EQ(s.direction(), Vertical);
}

TEST(ShipTests, DirectionCharSetterInvalidLetterThrowsTest) {
    Ship s(2, Position(1, 1), Horizontal);
    EXPECT_THROW(s.direction('X'), std::logic_error);
    EXPECT_EQ(s.direction(), Horizontal);
}

TEST(ShipTests, PositionSetterValidTest) {
    Ship s(2, Position(1, 1), Horizontal);
    s.position(Position(5, 5));
    EXPECT_EQ(s.row(), 5);
    EXPECT_EQ(s.col(), 5);
}

TEST(ShipTests, PositionSetterThrowWhenDoesNotFitTest) {
    Ship s(4, Position(1, 1), Horizontal);
    EXPECT_THROW(s.position(Position(1, 9)), std::logic_error);
    EXPECT_EQ(s.col(), 1);
}

TEST(ShipTests, RotateHorizontalToVerticalTest) {
    Ship s(2, Position(1, 1), Horizontal);
    s.rotate();
    EXPECT_EQ(s.direction(), Vertical);
}

TEST(ShipTests, RotateVerticalToHorizontalTest) {
    Ship s(2, Position(1, 1), Vertical);
    s.rotate();
    EXPECT_EQ(s.direction(), Horizontal);
}

TEST(ShipTests, RotateTwiceReturnsToOriginalTest) {
    Ship s(2, Position(1, 1), Horizontal);
    s.rotate();
    s.rotate();
    EXPECT_EQ(s.direction(), Horizontal);
}

TEST(ShipTests, RotateThrowsWhenDoesNotFitTest) {
    Ship s(4, Position(9, 1), Horizontal);
    EXPECT_THROW(s.rotate(), std::logic_error);
    EXPECT_EQ(s.direction(), Horizontal);
}

TEST(ShipTests, ParseExampleOneTest) {
    Ship s(std::string("1 H 4 B"));
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.direction(), Horizontal);
    EXPECT_EQ(s.row(), 4);
    EXPECT_EQ(s.col(), 2);
}

TEST(ShipTests, ParseExampleTwoNoInnerSpaceTest) {
    Ship s(std::string("1 H 10F"));
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.direction(), Horizontal);
    EXPECT_EQ(s.row(), 10);
    EXPECT_EQ(s.col(), 6);
}

TEST(ShipTests, ParseExampleThreeLowerCaseColumnTest) {
    Ship s(std::string("3 H 10a"));
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.row(), 10);
    EXPECT_EQ(s.col(), 1);
}

TEST(ShipTests, ParseExampleFourLowerCaseDirectionTest) {
    Ship s(std::string("1 h 2H"));
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.direction(), Horizontal);
    EXPECT_EQ(s.row(), 2);
    EXPECT_EQ(s.col(), 8);
}

TEST(ShipTests, ParseVerticalDirectionTest) {
    Ship s(std::string("2 V 3 B"));
    EXPECT_EQ(s.direction(), Vertical);
}

TEST(ShipTests, ParseEmptyStringThrowsTest) {
    EXPECT_THROW(Ship(std::string("")), std::logic_error);
}

TEST(ShipTests, ParseMissingDirectionThrowsTest) {
    EXPECT_THROW(Ship(std::string("1 4B")), std::logic_error);
}

TEST(ShipTests, ParseInvalidDirectionLetterThrowsTest) {
    EXPECT_THROW(Ship(std::string("1 X 4B")), std::logic_error);
}

TEST(ShipTests, ParseMissingSpaceAfterSizeThrowsTest) {
    EXPECT_THROW(Ship(std::string("1H4B")), std::logic_error);
}

TEST(ShipTests, ParseMissingPositionThrowsTest) {
    EXPECT_THROW(Ship(std::string("1 H")), std::logic_error);
}

TEST(ShipTests, ParseMalformedPositionThrowsTest) {
    EXPECT_THROW(Ship(std::string("1 H ZZ")), std::logic_error);
}

TEST(ShipTests, ParseTrailingGarbageThrowsTest) {
    EXPECT_THROW(Ship(std::string("1 H 4B extra")), std::logic_error);
}

TEST(ShipTests, ParseOutOfRangeSizeThrowsShipErrorTest) {
    try {
        Ship s(std::string("5 H 1A"));
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "Invalid input: incorrect ship parameters");
    }
}

TEST(ShipTests, ParseOutOfRangePositionThrowsShipErrorTest) {
    try {
        Ship s(std::string("1 H 11A"));
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "Invalid input: incorrect position");
    }
}

TEST(ShipTests, ParseDoesNotFitFieldThrowsShipErrorTest) {
    try {
        Ship s(std::string("3 H 1I"));
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "Invalid input: incorrect ship");
    }
}

#endif