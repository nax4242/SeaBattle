#include "Ship.h"

Ship::Ship(int size, Position position, Direction direction) {
	if (size < _min_size || size > _max_size) {
		throw std::logic_error("Invalid input: incorrect ship parameters");
	}

	if (direction != Horizontal && direction != Vertical) {
		throw std::logic_error("Invalid input: incorrect ship");
	}

	if (is_collision(size, position, direction)) {
		throw std::logic_error("Invalid input: incorrect ship");
	}

	_size = size;
	_position = position;
	_direction = direction;
}

Ship::Ship(int size, char direction, int row, char col) {
	if (size < _min_size || size > _max_size) {
		throw std::logic_error("Invalid input: incorrect ship parameters");
	}

	char dir_upper = static_cast<char>(std::toupper(direction));
	if (dir_upper != 'H' && dir_upper != 'V') {
		throw std::logic_error("Invalid input: incorrect ship parameters");
	}
	Direction dir = (dir_upper == 'H') ? Horizontal : Vertical;

	if (is_collision(row) || is_collision(col)) {
		throw std::logic_error("Invalid input: incorrect ship");
	}
	Position position(row, col);

	if (is_collision(size, position, dir)) {
		throw std::logic_error("Invalid input: incorrect ship");
	}

	_size = size;
	_position = position;
	_direction = dir;
}

Ship::Ship(const std::string& str) {
	parse(str, *this);
}

void parse(const std::string& str, Ship& ship) {
	size_t digits_end = 0;
	size_t digits_start = digits_end;

	if (digits_end < str.size() && str[digits_end] == '-') {
		digits_end++;
	}
	if (digits_end >= str.size() || !std::isdigit(str[digits_end])) {
		throw std::logic_error("Invalid input: incorrect string format");
	}
	while (digits_end < str.size() && std::isdigit(str[digits_end])) {
		digits_end++;
	}
	int size_value = std::stoi(str.substr(digits_start, digits_end - digits_start));

	if (digits_end >= str.size() || str[digits_end] != ' ') {
		throw std::logic_error("Invalid input: incorrect string format");
	}
	digits_end++;

	if (digits_end >= str.size() || !std::isalpha(str[digits_end])) {
		throw std::logic_error("Invalid input: incorrect string format");
	}
	char dir_upper = static_cast<char>(std::toupper(str[digits_end]));
	digits_end++;
	if (dir_upper != 'H' && dir_upper != 'V') {
		throw std::logic_error("Invalid input: incorrect string format");
	}
	Direction dir = (dir_upper == 'H') ? Horizontal : Vertical;

	if (digits_end >= str.size() || str[digits_end] != ' ') {
		throw std::logic_error("Invalid input: incorrect string format");
	}
	digits_end++;

	Position position(1, 1);
	parse(str.substr(digits_end), position);

	ship = Ship(size_value, position, dir);
}

bool is_collision(int size, Position position, Direction direction) noexcept {
	if (direction == Horizontal) {
		return position.col() + size - 1 > Position::max_col();
	}
	else {
		return position.row() + size - 1 > Position::max_col();
	}
}