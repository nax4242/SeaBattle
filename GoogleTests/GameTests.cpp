#include "pch.h"
#include "Game.h"
#include <sstream>
#include <iostream>

namespace {
    const std::string valid_user_fleet =
        "1 H 1 A\n"
        "1 H 1 C\n"
        "1 H 1 E\n"
        "1 H 1 G\n"
        "2 H 3 A\n"
        "2 H 3 D\n"
        "2 H 3 G\n"
        "3 V 5 J\n"
        "3 H 7 C\n"
        "4 H 9 A\n";

    const std::string valid_computer_fleet =
        "1 H 1 A\n"
        "1 H 1 C\n"
        "1 H 1 E\n"
        "1 H 1 G\n"
        "2 H 3 A\n"
        "2 H 3 D\n"
        "2 H 3 G\n"
        "3 V 5 J\n"
        "3 H 7 C\n"
        "4 H 9 A\n";

    std::string make_game_input(const std::string& moves = "") {
        return valid_user_fleet + "\n" +
            valid_computer_fleet + "\n" +
            moves;
    }

    std::string run_game_and_restore_input(const std::string& input) {
        std::istringstream input_stream(input);
        std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());

        testing::internal::CaptureStdout();

        try {
            Game().start();
        }
        catch (const std::exception&) {
            const std::string output =
                testing::internal::GetCapturedStdout();

            std::cin.rdbuf(old_cin);
            throw;
        }

        const std::string output =
            testing::internal::GetCapturedStdout();

        std::cin.rdbuf(old_cin);
        return output;
    }
}

TEST(GameTests, DefaultConstructorTest) {
    EXPECT_NO_THROW(Game());
}

TEST(GameTests, StartShowsGameWindowAfterSuccessfulInitializationTest) {
    const std::string input = make_game_input();

    std::istringstream input_stream(input);
    std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());

    testing::internal::CaptureStdout();

    EXPECT_THROW(Game().start(), std::logic_error);

    const std::string output = testing::internal::GetCapturedStdout();

    std::cin.rdbuf(old_cin);

    EXPECT_NE(
        output.find("=== COMPUTER GAME FIELD ==="),
        std::string::npos
    );

    EXPECT_NE(
        output.find("=== YOUR PLAY FIELD ==="),
        std::string::npos
    );

    EXPECT_NE(
        output.find("Ships Left:"),
        std::string::npos
    );
}

TEST(GameTests, UserInitIncompleteFleetThrowsFieldErrorTest) {
    const std::string input =
        "1 H 1 A\n"
        "1 H 1 C\n"
        "1 H 1 E\n"
        "1 H 1 G\n"
        "2 H 3 A\n"
        "2 H 3 D\n"
        "2 H 3 G\n"
        "3 V 5 J\n"
        "3 H 7 C\n"
        "\n";

    std::istringstream input_stream(input);
    std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());

    EXPECT_THROW(Game().start(), std::logic_error);

    std::cin.rdbuf(old_cin);
}

TEST(GameTests, ComputerInitIncompleteFleetThrowsFieldErrorTest) {
    const std::string input =
        valid_user_fleet + "\n" +
        "1 H 1 A\n"
        "1 H 1 C\n"
        "1 H 1 E\n"
        "1 H 1 G\n"
        "2 H 3 A\n"
        "2 H 3 D\n"
        "2 H 3 G\n"
        "3 V 5 J\n"
        "3 H 7 C\n"
        "\n";

    std::istringstream input_stream(input);
    std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());

    EXPECT_THROW(Game().start(), std::logic_error);

    std::cin.rdbuf(old_cin);
}

TEST(GameTests, UserInitInvalidShipThrowsFieldErrorTest) {
    const std::string input =
        valid_user_fleet +
        "\n"
        "\n";

    // Replacing the last valid user line with an invalid ship.
    const std::string invalid_input =
        "1 H 1 A\n"
        "1 H 1 C\n"
        "1 H 1 E\n"
        "1 H 1 G\n"
        "2 H 3 A\n"
        "2 H 3 D\n"
        "2 H 3 G\n"
        "3 V 5 J\n"
        "3 H 7 C\n"
        "5 H 9 A\n"
        "\n";

    std::istringstream input_stream(invalid_input);
    std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());

    try {
        Game().start();
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(
            e.what(),
            "Invalid input: incorrect field"
        );
    }

    std::cin.rdbuf(old_cin);
}

TEST(GameTests, ComputerInitCollidingShipsThrowsFieldErrorTest) {
    const std::string input =
        valid_user_fleet +
        "\n"
        "1 H 1 A\n"
        "1 H 1 B\n"
        "\n";

    std::istringstream input_stream(input);
    std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());

    try {
        Game().start();
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(
            e.what(),
            "Invalid input: incorrect field"
        );
    }

    std::cin.rdbuf(old_cin);
}

TEST(GameTests, UserMoveHitRedrawsGameWindowTest) {
    const std::string input = make_game_input("1 A\n");

    std::istringstream input_stream(input);
    std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());

    testing::internal::CaptureStdout();

    EXPECT_THROW(Game().start(), std::logic_error);

    const std::string output = testing::internal::GetCapturedStdout();

    std::cin.rdbuf(old_cin);

    const std::string window_title =
        "=== COMPUTER GAME FIELD ===";

    size_t first = output.find(window_title);
    ASSERT_NE(first, std::string::npos);

    size_t second = output.find(
        window_title,
        first + window_title.size()
    );

    EXPECT_NE(second, std::string::npos);
}

TEST(GameTests, UserHitAllowsAnotherMoveTest) {
    const std::string input =
        make_game_input(
            "1 A\n"
            "1 C\n"
        );

    std::istringstream input_stream(input);
    std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());

    testing::internal::CaptureStdout();

    EXPECT_THROW(Game().start(), std::logic_error);

    const std::string output = testing::internal::GetCapturedStdout();

    std::cin.rdbuf(old_cin);

    const std::string window_title =
        "=== COMPUTER GAME FIELD ===";

    size_t first = output.find(window_title);
    ASSERT_NE(first, std::string::npos);

    size_t second = output.find(
        window_title,
        first + window_title.size()
    );
    ASSERT_NE(second, std::string::npos);

    size_t third = output.find(
        window_title,
        second + window_title.size()
    );
    EXPECT_NE(third, std::string::npos);
}

TEST(GameTests, InvalidUserMoveThrowsMoveErrorTest) {
    const std::string input = make_game_input("11 A\n");

    std::istringstream input_stream(input);
    std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());

    try {
        Game().start();
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(
            e.what(),
            "Invalid input: incorrect move"
        );
    }

    std::cin.rdbuf(old_cin);
}

TEST(GameTests, InvalidUserColumnThrowsMoveErrorTest) {
    const std::string input = make_game_input("1 K\n");

    std::istringstream input_stream(input);
    std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());

    try {
        Game().start();
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(
            e.what(),
            "Invalid input: incorrect move"
        );
    }

    std::cin.rdbuf(old_cin);
}

TEST(GameTests, LowerCaseUserMoveIsAcceptedTest) {
    const std::string input = make_game_input("1 a\n");

    std::istringstream input_stream(input);
    std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());

    testing::internal::CaptureStdout();

    EXPECT_THROW(Game().start(), std::logic_error);

    const std::string output = testing::internal::GetCapturedStdout();

    std::cin.rdbuf(old_cin);

    EXPECT_NE(
        output.find("=== COMPUTER GAME FIELD ==="),
        std::string::npos
    );
}

TEST(GameTests, UserMoveOnAlreadyShotCellThrowsMoveErrorTest) {
    const std::string input =
        make_game_input(
            "10 J\n"
            "10 J\n"
        );

    std::istringstream input_stream(input);
    std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());

    try {
        Game().start();
        FAIL() << "Ожидалось исключение";
    }
    catch (const std::logic_error& e) {
        EXPECT_STREQ(
            e.what(),
            "Invalid input: incorrect move"
        );
    }

    std::cin.rdbuf(old_cin);
}
