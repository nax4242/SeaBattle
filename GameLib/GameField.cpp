#include "GameField.h"

GameField::GameField() : _n(Position::max_row()), _m(Position::max_col()) {
	_field = new char*[_n];

	for (int i = 0; i < _n; i++) {
		_field[i] = new char[_m];

        for (int j = 0; j < _m; j++) {
            _field[i][j] = ' ';
        }
	}
}

GameField::~GameField() {
	for (int i = 0; i < _n; i++) {
		delete[]_field[i];
	}

	delete[]_field;
}

void GameField::set(const Ship& ship) {
    if (is_collision(*this, ship)) {
        throw std::logic_error("Invalid input: incorrect field");
    }

    int field_start_row = ship.row() - 1;
    int field_start_col = ship.col() - 1;

    int field_end_row = ship.direction() == Horizontal ? field_start_row : field_start_row + ship.size() - 1;
    int field_end_col = ship.direction() == Horizontal ? field_start_col + ship.size() - 1 : field_start_col;

    for (int i = field_start_row; i <= field_end_row; i++) {
        for (int j = field_start_col; j <= field_end_col; j++) {
            _field[i][j] = '*';
        }
    }
}

State GameField::set(int row, char col) {
    if (is_collision(row) || is_collision(col)) {
        throw std::logic_error("Invalid input: incorrect move");
    }

    Position position(row, col);

    int real_row = position.row() - 1;
    int real_col = position.col() - 1;

    if (_field[real_row][real_col] == 'X' || _field[real_row][real_col] == '.') {
        throw std::logic_error("Invalid input: incorrect move");
    }

    if (_field[real_row][real_col] == ' ') {
        _field[real_row][real_col] = '.';
        return Missed;
    }

    int destroyed_size = check_destroy(real_row, real_col);
    _field[real_row][real_col] = 'X';

    switch (destroyed_size) {
    case 1:
        return BoatDestroyed;

    case 2:
        return DestroyersDestroyed;

    case 3:
        return CruisersDestroyed;

    case 4:
        return BattleshipDestroyed;

    default:
        return Hit;
    }
}

int GameField::check_destroy(int real_row, int real_col) const noexcept {
    if (_field[real_row][real_col] != '*') {
        return 0;
    }

    int size = 1;
    bool destroyed = true;

    for (int real_current_col = real_col - 1; real_current_col >= 0 && (_field[real_row][real_current_col] == '*' || _field[real_row][real_current_col] == 'X'); real_current_col--) {
        if (_field[real_row][real_current_col] == '*') {
            destroyed = false;
        }

        size++;
    }
    
    for (int real_current_col = real_col + 1; real_current_col < _m && (_field[real_row][real_current_col] == '*' || _field[real_row][real_current_col] == 'X'); real_current_col++) {
        if (_field[real_row][real_current_col] == '*') {
            destroyed = false;
        }

        size++;
    }

    for (int real_current_row = real_row - 1; real_current_row >= 0 && (_field[real_current_row][real_col] == '*' || _field[real_current_row][real_col] == 'X'); real_current_row--) {
        if (_field[real_current_row][real_col] == '*') {
            destroyed = false;
        }

        size++;
    }

    for (int real_current_row = real_row + 1; real_current_row < _n && (_field[real_current_row][real_col] == '*' || _field[real_current_row][real_col] == 'X'); real_current_row++) {
        if (_field[real_current_row][real_col] == '*') {
            destroyed = false;
        }

        size++;
    }

    return destroyed ? size : 0;

}

std::string to_string(const GameField& game_field, bool show_ships) noexcept {
    std::string result;

    result += "  |";
    for (int i = 0; i < game_field._m; i++) {
        result += static_cast<char>('A' + i);
        if (i + 1 < game_field._m) {
            result += ' ';
        }
    }
    result += "|\n";

    result += "  +";
    for (int i = 0; i < game_field._m * 2 - 1; i++) {
        result += "-";
    }
    result += "+\n";

    for (int real_row = 0; real_row < game_field._n; real_row++) {
        int human_row = real_row + 1;

        result += std::to_string(human_row);
        if (human_row < 10) {
            result += " |";
        }
        else {
            result += '|';
        }

        for (int real_col = 0; real_col < game_field._m; real_col++) {
            char cell = game_field._field[real_row][real_col];

            if (!show_ships && cell == '*') {
                cell = ' ';
            }

            result += cell;
            result += '|';
        }

        result += '\n';
    }

    result += "  +";
    for (int i = 0; i < game_field._m * 2 - 1; i++) {
        result += "-";
    }
    result += "+";

    return result;
}

bool is_collision(const GameField& game_field, const Ship& ship) noexcept {
    int real_start_row = ship.row() - 1;
    int real_start_col = ship.col() - 1;
    bool is_vertical = ship.direction() == Vertical;

    for (int diff = 0; diff < ship.size(); diff++) {
        int real_current_row = real_start_row + (is_vertical ? diff : 0);
        int real_current_col = real_start_col + (is_vertical ? 0 : diff);

        for (int d_row = -1; d_row <= 1; d_row++) {
            for (int d_col = -1; d_col <= 1; d_col++) {
                int real_check_row = real_current_row + d_row;
                int real_check_col = real_current_col + d_col;

                if (real_check_row >= 0 && real_check_row < game_field._n &&
                    real_check_col >= 0 && real_check_col < game_field._m &&
                    (game_field._field[real_check_row][real_check_col] == '*' ||
                     game_field._field[real_check_row][real_check_col] == 'X')) {
                    return true;
                }
            }
        }
    }

    return false;
}