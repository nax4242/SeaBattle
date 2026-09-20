#include "pch.h"
#include "Ship.h"

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

TEST(ShipTests, PartialConstructorDefaultsToHorizontalTest) {
    Ship s(3, Position(4, 3));
    EXPECT_EQ(s.direction(), Horizontal);
    EXPECT_EQ(s.row(), 4);
    EXPECT_EQ(s.col(), 3);
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
}

TEST(ShipTests, RotateDoesNotChangeStateOnThrowTest) {
    Ship s(4, Position(9, 1), Horizontal);
    EXPECT_THROW(s.rotate(), std::logic_error);
    EXPECT_EQ(s.direction(), Horizontal);
    EXPECT_EQ(s.size(), 4);
    EXPECT_EQ(s.row(), 9);
    EXPECT_EQ(s.col(), 1);
}