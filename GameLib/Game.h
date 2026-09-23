#pragma once
#include <string>
#include "Player.h"

class Game {
    Player _user;
    Player _computer;

public:
    Game();

    void start();

private:
    void user_init(std::string);
    void computer_init(std::string);

    State user_move(std::string);
    State computer_move();

    inline bool is_end() const noexcept;
    void show_game_window() const;
};