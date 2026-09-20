#pragma once
#include <string>
#include <stdexcept>

class Position {
	static const int _max_col = 10;
	static const int _max_row = 10;

	int _row;
	int _col;

public:
	Position(int = 1, int = 1);
	Position(const Position&);
	Position(std::string);

	inline int row() const noexcept;
	inline int col() const noexcept;
	inline static int max_row() noexcept;
	inline static int max_col() noexcept;

	inline void row(int);
	inline void col(int);

	friend std::string to_string(const Position&) noexcept;
	friend Position parse(const std::string&);
};

inline int Position::row() const noexcept {
	return _row;
}
inline int Position::col() const noexcept {
	return _col;
}
inline void Position::row(int row) {
	if (row < 1 || row > _max_row) {
		throw std::logic_error("Invalid input: incorrect position");
	}

	_row = row;
}
inline void Position::col(int col) {
	if (col < 1 || col > _max_col) {
		throw std::logic_error("Invalid input: incorrect position");
	}

	_col = col;
}
inline int Position::max_row() noexcept {
	return _max_row;
}
inline int Position::max_col() noexcept {
	return _max_col;
}

Position parse(const std::string&);