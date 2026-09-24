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
    void user_init(const std::string&);
    void computer_init(const std::string&);

    State user_move(const std::string&);
    State computer_move();

    inline bool is_end() const noexcept;
    void show_game_window(bool = false) const noexcept;
};

inline bool Game::is_end() const noexcept {
    return _user.check_lose() || _computer.check_lose();
}