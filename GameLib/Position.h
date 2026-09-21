#pragma once
#include <string>
#include <stdexcept>

class Position {
	static const int _max_col = 10;
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
	inline int char_col() const noexcept;

	inline static int max_row() noexcept;
	inline static int max_col() noexcept;

	inline void row(int);
	inline void col(int);
	inline void col(char);

	friend void parse(const std::string&, Position&);
	
private:
	inline bool is_collision(int) const noexcept;
	inline bool is_collision(char) const noexcept;
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