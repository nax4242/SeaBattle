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
};

inline int Ship::size() const noexcept {
	return _size;
}
inline Direction Ship::direction() const noexcept {
	return _direction;
}
inline int Ship::row() const noexcept {
	return _coord.row();
}
inline int Ship::col() const noexcept {
	return _coord.col();
}