#pragma once
#include <string>

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

	inline void row(int);
	inline void col(int);

	friend std::string to_string(const Position&) noexcept;
	friend Position parse(const std::string&);
};