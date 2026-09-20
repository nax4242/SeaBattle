#include "Ship.h"

Ship::Ship(int size, Position coord, Direction direction) {
	if (size < 1 || size > 4) {
		throw std::logic_error("Invalid input: incorrect ship parameters");
	}

	if (direction == Horizontal && coord.col() + size - 1 > Position::max_col() ||
		direction == Vertical && coord.row() + size - 1 > Position::max_row()) {
		throw std::logic_error("Invalid input: incorrect ship parameters");
	}

	_size = size;
	_coord = coord;
	_direction = direction;
}

Ship::Ship(int size, char direction, int row, char col) {
	if (size < 1 || size > 4) {
		throw std::logic_error("Invalid input: incorrect ship parameters");
	}

	if (direction != 'H' && direction != 'V') {
		throw std::logic_error("Invalid input: incorrect ship parameters");
	}

	col -= 'A' - 1;
	int int_col = static_cast<int>(col);

	if (row < 1 || int_col < 1 || row > Position::max_row() || int_col > Position::max_col()) {
		throw std::logic_error("Invalid input: incorrect ship parameters");
	}

	if (direction == 'H' && int_col + size - 1 > Position::max_col() ||
		direction == 'V' && row + size - 1 > Position::max_row()) {
		throw std::logic_error("Invalid input: incorrect ship parameters");
	}

	_size = size;
	_direction = direction == 'H' ? Horizontal : Vertical;
	_coord = Position(row, int_col);
}

void Ship::rotate() {
	if (_direction == Horizontal && _coord.row() + _size - 1 > Position::max_row() ||
		_direction == Vertical && _coord.col() + _size - 1 > Position::max_col()) {
		throw std::logic_error("Invalid input: incorrect ship parameters");
	}
	
	_direction = _direction == Horizontal ? Vertical : Horizontal;
}