#pragma once
#include <string>
#include <stdexcept>
#include <random>

class Position {
	static constexpr int _max_col = 10;
	static const int _max_row = 10;

	int _row;
	int _col;

public:
	Position();
	Position(int, int);
	Position(int, char);
	Position(const Position&);
	Position(std::string);

	inline int row() const noexcept;
	inline int col() const noexcept;
	inline char char_col() const noexcept;

	inline void row(int);
	inline void col(int);
	inline void col(char);

	inline static int max_row() noexcept;
	inline static int max_col() noexcept;

private:
	friend void parse(const std::string&, Position&);
	friend bool is_collision(int) noexcept;
	friend bool is_collision(char) noexcept;
};

inline bool is_collision(int row) noexcept {
	return row < 1 || row > Position::_max_row;
}
inline bool is_collision(char col) noexcept {
	col = std::toupper(col) - 'A' + 1;
	return col < 1 || col > Position::_max_col;
}

inline int Position::row() const noexcept {
	return _row;
}
inline int Position::col() const noexcept {
	return _col;
}
inline char Position::char_col() const noexcept {
	return static_cast<char>(_col + 'A' - 1);
}

inline void Position::row(int row) {
	if (is_collision(row)) {
		throw std::logic_error("Invalid input: incorrect position");
	}

	_row = row;
}
inline void Position::col(int col) {
	if (is_collision(static_cast<char>(col + 'A' - 1))) {
		throw std::logic_error("Invalid input: incorrect position");
	}

	_col = col;
}
inline void Position::col(char col) {
	if (is_collision(col)) {
		throw std::logic_error("Invalid input: incorrect position");
	}

	_col = std::toupper(col) - 'A' + 1;
}

inline int Position::max_row() noexcept {
	return _max_row;
}
inline int Position::max_col() noexcept {
	return _max_col;
}

void parse(const std::string&, Position&);
