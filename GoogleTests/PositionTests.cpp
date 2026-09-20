#include "pch.h"
#include "Position.h"

TEST(PositionTests, DefaultConstructorTest) {
    Position p;
    EXPECT_EQ(p.row(), 1);
    EXPECT_EQ(p.col(), 1);
}

TEST(PositionTests, InitConstructorTest) {
    Position p(3, 7);
    EXPECT_EQ(p.row(), 3);
    EXPECT_EQ(p.col(), 7);
}

TEST(PositionTests, RowTooSmallThrowsTest) {
    EXPECT_THROW(Position(0, 5), std::logic_error);
}

TEST(PositionTests, RowTooBigThrowsTest) {
    EXPECT_THROW(Position(12, 5), std::logic_error);
}

TEST(PositionTests, ColTooSmallThrowsTest) {
    EXPECT_THROW(Position(2, 0), std::logic_error);
}

TEST(PositionTests, ColTooBigThrowsTest) {
    EXPECT_THROW(Position(2, 12), std::logic_error);
}

TEST(PositionTests, CopyConstructorTest) {
    Position original(4, 6);
    Position copy(original);
    EXPECT_EQ(copy.row(), 4);
    EXPECT_EQ(copy.col(), 6);
}

TEST(PositionTests, StringConstructorTest) {
    Position p(std::string("(3, 5)"));
    EXPECT_EQ(p.row(), 3);
    EXPECT_EQ(p.col(), 5);
}

TEST(PositionTests, ReturnCurrentValues) {
    Position p(6, 9);
    EXPECT_EQ(p.row(), 6);
    EXPECT_EQ(p.col(), 9);
}

TEST(PositionTests, RowSeterTest) {
    Position p;
    p.row(8);
    EXPECT_EQ(p.row(), 8);
}

TEST(PositionTests, ColSeterTest) {
    Position p;
    p.col(8);
    EXPECT_EQ(p.col(), 8);
}

TEST(PositionTests, RowSeterThrowSmallTest) {
    Position p;
    EXPECT_THROW(p.row(0), std::logic_error);
}

TEST(PositionTests, RowSeterThrowBigTest) {
    Position p;
    EXPECT_THROW(p.row(11), std::logic_error);
}

TEST(PositionTests, ColSeterThrowSmallTest) {
    Position p;
    EXPECT_THROW(p.col(0), std::logic_error);
}

TEST(PositionTests, ColSeterThrowBigTest) {
    Position p;
    EXPECT_THROW(p.col(11), std::logic_error);
}

TEST(PositionTests, ToStringTest) {
    Position p(3, 5);
    EXPECT_EQ(to_string(p), "(3, 5)");
}

TEST(PositionTests, ToStringDoubleDigitTest) {
    Position p(10, 10);
    EXPECT_EQ(to_string(p), "(10, 10)");
}

TEST(PositionTests, ParseTest) {
    Position p = parse("(3, 5)");
    EXPECT_EQ(p.row(), 3);
    EXPECT_EQ(p.col(), 5);
}

TEST(PositionTests, ParseDoubleDigitTest) {
    Position p = parse("(10, 10)");
    EXPECT_EQ(p.row(), 10);
    EXPECT_EQ(p.col(), 10);
}

TEST(PositionTests, ParseThrowTest1) {
    EXPECT_THROW(parse(""), std::logic_error);
}

TEST(PositionTests, ParseInvalidFormatThrowTest2) {
    EXPECT_THROW(parse("3, 5)"), std::logic_error);
}

TEST(PositionTests, ParseInvalidFormatThrowTest3) {
    EXPECT_THROW(parse("(3, 5"), std::logic_error);
}

TEST(PositionTests, ParseInvalidFormatThrowTest4) {
    EXPECT_THROW(parse("(3 5)"), std::logic_error);
}

TEST(PositionTests, ParseInvalidFormatThrowTest5) {
    EXPECT_THROW(parse("(3,5)"), std::logic_error);
}

TEST(PositionTests, ParseInvalidFormatThrowTest6) {
    EXPECT_THROW(parse("(3, 5) abc"), std::logic_error);
}

TEST(PositionTests, ParseInvalidFormatThrowTest7) {
    EXPECT_THROW(parse("(a, b)"), std::logic_error);
}

TEST(PositionTests, ParseInvalidFormatThrowTest8) {
    EXPECT_THROW(parse("(-, 5)"), std::logic_error);
}

TEST(PositionTests, ParseOutOfRangeTest1) {
    EXPECT_THROW(parse("(11, 5)"), std::logic_error);
}

TEST(PositionTests, ParseOutOfRangeTest2) {
    EXPECT_THROW(parse("(5, 0)"), std::logic_error);
}

TEST(PositionTests, ParseOutOfRangeTest3) {
    EXPECT_THROW(parse("(-3, 5)"), std::logic_error);
}