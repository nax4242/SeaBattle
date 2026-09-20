#pragma once
#include "Position.h"

enum Direction { Horizontal, Vertical };

class Ship {
	int _size;
	Position _coord;
	Direction _direction;

public:
	Ship(int, Position, Direction = Horizontal);
	Ship(int, char, int, char);
	Ship() = delete;
	Ship(const Ship&) = delete;

	inline int size() const noexcept;
	inline Direction direction() const noexcept;
	inline int row() const noexcept;
	inline int col() const noexcept;

	void rotate();

private:
	bool is_collision() const noexcept;
};