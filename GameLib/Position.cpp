#include "Position.h"

Position::Position(int row, int col) {
	if (row < 1 || row > _max_row) {
		throw std::logic_error("Invalid input: incorrect position");
	}

	if (col < 1 || col > _max_col) {
		throw std::logic_error("Invalid input: incorrect position");
	}

	_row = row;
	_col = col;
}

Position::Position(const Position& other) : _row(other._row), _col(other._col) {}

Position::Position(std::string str) : Position(parse(str)) {}

std::string to_string(const Position& other) noexcept {
	return "(" + std::to_string(other._row) + ", " + std::to_string(other._col) + ")";
}

Position parse(const std::string& str) {
	int start_index = 1, length = 0;
	int values[2];

	if (str[0] != '(') {
		throw std::logic_error("Invalid input: incorrect string format");
	}

	for (int count = 0; count < 2; count++) {
		if (str[start_index] == '-') {
			length++;
		}

		if (!std::isdigit(static_cast<int>(str[start_index + length]))) {
			throw std::logic_error("Invalid input: incorrect string format");
		}

		while (start_index + length < str.size() && std::isdigit(static_cast<int>(str[start_index + length]))) {
			length++;
		}

		values[count] = std::stoi(str.substr(start_index, length));
		start_index += length;
		length = 0;

		if (count == 0) {
			if (str[start_index++] != ',') throw std::logic_error("Invalid input: incorrect string format");
			if (str[start_index++] != ' ') throw std::logic_error("Invalid input: incorrect string format");
		}
	}

	if (start_index >= str.size() || str[start_index] != ')') {
		throw std::logic_error("Invalid input: incorrect string format");
	}

	if (start_index + 1 != str.size()) {
		throw std::logic_error("Invalid input: incorrect string format");
	}

	return Position(values[0], values[1]);
}