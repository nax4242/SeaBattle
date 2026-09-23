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

    void show_field(bool = false) const;

    inline bool check_lose() const noexcept;
    inline bool check_ready() const noexcept;
};
