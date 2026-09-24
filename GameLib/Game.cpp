#include "Game.h"
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>

Game::Game() : _user(), _computer() {}

void Game::user_init(const std::string& input) {
    std::istringstream input_stream(input);
    std::string line;

    try {
        while (std::getline(input_stream, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }

            if (line.empty()) {
                continue;
            }

            _user.set_ship(Ship(line));
        }
    }
    catch (const std::exception&) {
        throw std::logic_error("Invalid input: incorrect field");
    }

    if (!_user.check_ready()) {
        throw std::logic_error("Invalid input: incorrect field");
    }
}

void Game::computer_init(const std::string& input) {
    std::istringstream input_stream(input);
    std::string line;

    try {
        while (std::getline(input_stream, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }

            if (line.empty()) {
                continue;
            }

            _computer.set_ship(Ship(line));
        }
    }
    catch (const std::exception&) {
        throw std::logic_error("Invalid input: incorrect field");
    }

    if (!_computer.check_ready()) {
        throw std::logic_error("Invalid input: incorrect field");
    }
}

State Game::user_move(const std::string& input) {
    Position position(1, 1);

    try {
        parse(input, position);
    }
    catch (const std::exception&) {
        throw std::logic_error("Invalid input: incorrect move");
    }

    return _computer.set_action(position.row(), position.char_col());
}

State Game::computer_move() {
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_int_distribution<int> row_distribution(1, Position::max_row());
    std::uniform_int_distribution<int> col_distribution(1, Position::max_col());

    while (true) {
        int row = row_distribution(generator);
        char col = static_cast<char>('A' + col_distribution(generator) - 1);

        try {
            return _user.set_action(row, col);
        }
        catch (const std::logic_error&) {}
    }
}

void Game::show_game_window(bool show_computer_ships) const noexcept {
    std::cout << "=== COMPUTER GAME FIELD ===\n\n";
    _computer.show_field(!show_computer_ships);

    std::cout << "\n\n=== YOUR PLAY FIELD ===\n\n";
    _user.show_field(false);
    std::cout << '\n';
}

void Game::start() {
    std::string input;
    std::string user_ships;
    std::string computer_ships;

    std::cout << "Enter your ships using the format `1 h 4 c`, \
where `1` is the size (1–4), `h` (or `v`) is the ship's orientation (horizontal or vertical), \
and `4 c` represents the coordinates on the grid (1...10 and a...j). \
You need to place: 4 ships of length 1, 3 ships of length 2, 2 ships of length 3, and 1 ship of length 4.\n";

    while (std::getline(std::cin, input) && !input.empty()) {
        if (!user_ships.empty()) {
            user_ships += '\n';
        }

        user_ships += input;
    }

    user_init(user_ships);

    std::cout << "Enter computer ships using the format `1 h 4 c`, \
where `1` is the size (1–4), `h` (or `v`) is the ship's orientation (horizontal or vertical), \
and `4 c` represents the coordinates on the grid (1–10 and a–j). \
You need to place: 4 ships of length 1, 3 ships of length 2, 2 ships of length 3, and 1 ship of length 4.\n";

    while (std::getline(std::cin, input) && !input.empty()) {
        if (!computer_ships.empty()) {
            computer_ships += '\n';
        }

        computer_ships += input;
    }

    computer_init(computer_ships);

    system("cls");
    show_game_window();

    while (!is_end()) {
        State state;

        do {
            std::getline(std::cin, input);

            state = user_move(input);

            system("cls");
            show_game_window();

        } while (state == Hit && !is_end());

        if (is_end()) {
            break;
        }

        do {
            state = computer_move();

            system("cls");
            show_game_window();

        } while (state == Hit && !is_end());
    }

    system("cls");
    show_game_window(true);

    if (_computer.check_lose()) {
        std::cout << "USER WIN!\n";
    }
    else {
        std::cout << "COMPUTER WIN!\n";
    }
}