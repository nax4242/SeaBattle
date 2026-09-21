#include "pch.h"
#include "Position.h"

TEST(PositionTests, DefaultConstructorAlwaysValidTest) {
    for (int i = 0; i < 1000; ++i) {
        Position p;
        EXPECT_GE(p.row(), 1);
        EXPECT_LE(p.row(), 10);
        EXPECT_GE(p.col(), 1);
        EXPECT_LE(p.col(), 10);
    }
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

TEST(PositionTests, BoundaryValuesAcceptedTest) {
    Position pMin(1, 1);
    EXPECT_EQ(pMin.row(), 1);
    EXPECT_EQ(pMin.col(), 1);

    Position pMax(10, 10);
    EXPECT_EQ(pMax.row(), 10);
    EXPECT_EQ(pMax.col(), 10);
}

TEST(PositionTests, IntCharConstructorTest) {
    Position p(4, 'G');
    EXPECT_EQ(p.row(), 4);
    EXPECT_EQ(p.col(), 7);
    EXPECT_EQ(p.char_col(), 'G');
}

TEST(PositionTests, IntCharConstructorLowerCaseTest) {
    Position p(4, 'g');
    EXPECT_EQ(p.col(), 7);
    EXPECT_EQ(p.char_col(), 'G');
}

TEST(PositionTests, IntCharConstructorColumnAtBoundsTest) {
    Position pA(1, 'A');
    EXPECT_EQ(pA.col(), 1);

    Position pJ(1, 'J');
    EXPECT_EQ(pJ.col(), 10);
}

TEST(PositionTests, IntCharConstructorInvalidColumnThrowsTest) {
    EXPECT_THROW(Position(1, 'K'), std::logic_error);
}

TEST(PositionTests, IntCharConstructorInvalidRowThrowsTest) {
    EXPECT_THROW(Position(11, 'A'), std::logic_error);
}

TEST(PositionTests, IntCharConstructorNonLetterThrowsTest) {
    EXPECT_THROW(Position(1, '5'), std::logic_error);
}

TEST(PositionTests, CopyConstructorTest) {
    Position original(4, 6);
    Position copy(original);
    EXPECT_EQ(copy.row(), 4);
    EXPECT_EQ(copy.col(), 6);
}

TEST(PositionTests, ReturnCurrentValuesTest) {
    Position p(6, 9);
    EXPECT_EQ(p.row(), 6);
    EXPECT_EQ(p.col(), 9);
}

TEST(PositionTests, CharColReturnsCorrectLetterTest) {
    Position p(1, 7);
    EXPECT_EQ(p.char_col(), 'G');
}

TEST(PositionTests, CharColFirstColumnTest) {
    Position p(1, 1);
    EXPECT_EQ(p.char_col(), 'A');
}

TEST(PositionTests, CharColLastColumnTest) {
    Position p(1, 10);
    EXPECT_EQ(p.char_col(), 'J');
}

TEST(PositionTests, RowSetterTest) {
    Position p(1, 1);
    p.row(8);
    EXPECT_EQ(p.row(), 8);
}

TEST(PositionTests, RowSetterThrowSmallTest) {
    Position p(1, 1);
    EXPECT_THROW(p.row(0), std::logic_error);
}

TEST(PositionTests, RowSetterThrowBigTest) {
    Position p(1, 1);
    EXPECT_THROW(p.row(11), std::logic_error);
}

TEST(PositionTests, ColIntSetterValidValueTest) {
    Position p(1, 1);
    p.col(8);
    EXPECT_EQ(p.col(), 8);
    EXPECT_EQ(p.char_col(), 'H');
}

TEST(PositionTests, ColIntSetterBoundaryValuesTest) {
    Position p(1, 1);
    p.col(1);
    EXPECT_EQ(p.col(), 1);
    p.col(10);
    EXPECT_EQ(p.col(), 10);
}

TEST(PositionTests, ColIntSetterThrowSmallTest) {
    Position p(1, 1);
    EXPECT_THROW(p.col(0), std::logic_error);
}

TEST(PositionTests, ColIntSetterThrowBigTest) {
    Position p(1, 1);
    EXPECT_THROW(p.col(11), std::logic_error);
}

TEST(PositionTests, ColCharSetterStoresNumericIndexTest) {
    Position p(1, 1);
    p.col('G');
    EXPECT_EQ(p.col(), 7);
    EXPECT_EQ(p.char_col(), 'G');
}

TEST(PositionTests, ColCharSetterLowerCaseTest) {
    Position p(1, 1);
    p.col('c');
    EXPECT_EQ(p.col(), 3);
    EXPECT_EQ(p.char_col(), 'C');
}

TEST(PositionTests, ColCharSetterThrowOutOfRangeTest) {
    Position p(1, 1);
    EXPECT_THROW(p.col('Z'), std::logic_error);
}

TEST(PositionTests, ColCharSetterThrowNonLetterTest) {
    Position p(1, 1);
    EXPECT_THROW(p.col('1'), std::logic_error);
}

TEST(PositionTests, ParseNoSpaceUpperCaseTest) {
    Position p(std::string("7A"));
    EXPECT_EQ(p.row(), 7);
    EXPECT_EQ(p.col(), 1);
}

TEST(PositionTests, ParseWithSpaceUpperCaseTest) {
    Position p(std::string("8 F"));
    EXPECT_EQ(p.row(), 8);
    EXPECT_EQ(p.col(), 6);
}

TEST(PositionTests, ParseNoSpaceLowerCaseTest) {
    Position p(std::string("4e"));
    EXPECT_EQ(p.row(), 4);
    EXPECT_EQ(p.col(), 5);
}

TEST(PositionTests, ParseWithSpaceSingleDigitTest) {
    Position p(std::string("1 A"));
    EXPECT_EQ(p.row(), 1);
    EXPECT_EQ(p.col(), 1);
}

TEST(PositionTests, ParseTwoDigitRowTest) {
    Position p(std::string("10J"));
    EXPECT_EQ(p.row(), 10);
    EXPECT_EQ(p.col(), 10);
}

TEST(PositionTests, ParseEmptyStringThrowsTest) {
    Position p(1, 1);
    EXPECT_THROW(parse("", p), std::logic_error);
}

TEST(PositionTests, ParseNoLetterThrowsTest) {
    EXPECT_THROW(Position(std::string("7")), std::logic_error);
}

TEST(PositionTests, ParseNoDigitThrowsTest) {
    EXPECT_THROW(Position(std::string("A")), std::logic_error);
}

TEST(PositionTests, ParseLetterBeforeDigitThrowsTest) {
    EXPECT_THROW(Position(std::string("A7")), std::logic_error);
}

TEST(PositionTests, ParseTwoLettersThrowsTest) {
    EXPECT_THROW(Position(std::string("7AB")), std::logic_error);
}

TEST(PositionTests, ParseTwoSpacesThrowsTest) {
    EXPECT_THROW(Position(std::string("7  A")), std::logic_error);
}

TEST(PositionTests, ParseTrailingGarbageThrowsTest) {
    EXPECT_THROW(Position(std::string("7A extra")), std::logic_error);
}

TEST(PositionTests, ParseOutOfRangeRowThrowsPositionErrorTest) {
    try {
        Position p(std::string("11A"));
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "Invalid input: incorrect position");
    }
}

TEST(PositionTests, ParseOutOfRangeColThrowsPositionErrorTest) {
    try {
        Position p(std::string("5K"));
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "Invalid input: incorrect position");
    }
}

TEST(PositionTests, ParseZeroRowThrowsPositionErrorTest) {
    EXPECT_THROW(Position(std::string("0A")), std::logic_error);
}