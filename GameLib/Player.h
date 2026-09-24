#pragma once
#include "GameField.h"

class Player {
    static const int _max_ships_counts[4];

    GameField _gamefield;
    int _ships_counts[4];

public:
    Player();

    void set_ship(const Ship&);
    State set_action(int, char);

    void show_field(bool = false) const noexcept;

    inline bool check_lose() const noexcept;
    inline bool check_ready() const noexcept;
};

inline bool Player::check_lose() const noexcept {
    return _ships_counts[0] == 0 &&
           _ships_counts[1] == 0 &&
           _ships_counts[2] == 0 &&
           _ships_counts[3] == 0;
}

inline bool Player::check_ready() const noexcept {
    return _ships_counts[0] == _max_ships_counts[0] &&
           _ships_counts[1] == _max_ships_counts[1] &&
           _ships_counts[2] == _max_ships_counts[2] &&
           _ships_counts[3] == _max_ships_counts[3];
}