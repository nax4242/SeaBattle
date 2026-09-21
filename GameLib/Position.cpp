#include "Position.h"

Position::Position() {
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<int> row_dist(1, _max_row);
	std::uniform_int_distribution<int> col_dist(1, _max_col);

	_row = row_dist(gen);
	_col = col_dist(gen);
}

Position::Position(int row, int col) {
	if (is_collision(row)) {
		throw std::logic_error("Invalid input: incorrect position");
	}

	if (is_collision(static_cast<char>(col + 'A' - 1))) {
		throw std::logic_error("Invalid input: incorrect position");
	}

	_row = row;
	_col = col;
}

Position::Position(int row, char col) {
	if (is_collision(row)) {
		throw std::logic_error("Invalid input: incorrect position");
	}

	if (is_collision(col)) {
		throw std::logic_error("Invalid input: incorrect position");
	}

	_row = row;
	_col = std::toupper(col) - 'A' + 1;
}

Position::Position(const Position& other) : _row(other._row), _col(other._col) {}

Position::Position(std::string str) {
	parse(str, *this);
}

void parse(const std::string& str, Position& pos) {
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

	int row_value = std::stoi(str.substr(digits_start, digits_end - digits_start));

	if (digits_end < str.size() && str[digits_end] == ' ') {
		digits_end++;
	}

	if (digits_end >= str.size() || !std::isalpha(str[digits_end])) {
		throw std::logic_error("Invalid input: incorrect string format");
	}
	char col_char = str[digits_end];
	digits_end++;

	if (digits_end != str.size()) {
		throw std::logic_error("Invalid input: incorrect string format");
	}

	pos = Position(row_value, col_char);
}