#include "Player.h"

const int Player::_max_ships_counts[4] = { 4, 3, 2, 1 };

Player::Player() : _gamefield(), _ships_counts{ 0, 0, 0, 0 } {}

void Player::set_ship(const Ship& ship) {
    int size = ship.size() - 1;

    if (_ships_counts[size] >= _max_ships_counts[size]) {
        throw std::logic_error("Invalid input: incorrect field");
    }

    _gamefield.set(ship);
    _ships_counts[size]++;
}

State Player::set_action(int human_row, char human_col) {
    State state = _gamefield.set(human_row, human_col);

    switch (state) {
    case BoatDestroyed:
        _ships_counts[0]--;
        break;

    case DestroyersDestroyed:
        _ships_counts[1]--;
        break;

    case CruisersDestroyed:
        _ships_counts[2]--;
        break;

    case BattleshipDestroyed:
        _ships_counts[3]--;
        break;

    default:
        break;
    }

    return state;
}

void Player::show_field(bool hide_ships) const noexcept {
    std::cout << to_string(_gamefield, !hide_ships) << "\n\n";
    std::cout << "Ships Left:\n";
    std::cout << "* - " << _ships_counts[0]
              << " ** - " << _ships_counts[1]
              << " *** - " << _ships_counts[2]
              << " **** - " << _ships_counts[3];
}