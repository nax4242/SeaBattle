#pragma once
#include "Position.h"

enum Direction { Horizontal, Vertical };

class Ship {
	static constexpr int _min_size = 1;
	static constexpr int _max_size = 4;

	int _size;
	Position _position;
	Direction _direction;

public:
	Ship(int, Position, Direction);
	Ship(int, char, int, char);
	Ship(std::string str);

	Ship() = delete;
	Ship(const Ship&) = delete;

	inline int size() const noexcept;
	inline int row() const noexcept;
	inline int col() const noexcept;
	inline Position position() const noexcept;
	inline Direction direction() const noexcept;

	inline void size(int size);
	inline void row(int row);
	inline void col(int col);
	inline void col(char col);
	inline void direction(Direction direction);
	inline void direction(char direction);
	inline void position(Position position);

	void rotate();

private:
	friend void parse(const std::string&, Ship&);
	friend bool is_collision(int, Position, Direction) noexcept;
};

bool is_collision(int, Position, Direction) noexcept;

inline int Ship::size() const noexcept {
	return _size;
}
inline int Ship::row() const noexcept {
	return _position.row();
}
inline int Ship::col() const noexcept {
	return _position.col();
}
inline Position Ship::position() const noexcept {
	return _position;
}
inline Direction Ship::direction() const noexcept {
	return _direction;
}

inline void Ship::size(int size) {
	if (size < _min_size || size > _max_size) {
		throw std::logic_error("Invalid input: incorrect ship");
	}

	if (is_collision(size, _position, _direction)) {
		throw std::logic_error("Invalid input: incorrect ship");
	}

	_size = size;
}
inline void Ship::row(int row) {
	if (is_collision(row)) {
		throw std::logic_error("Invalid input: incorrect ship");
	}

	Position new_position(_position);
	new_position.row(row);

	if (is_collision(_size, new_position, _direction)) {
		throw std::logic_error("Invalid input: incorrect ship");
	}

	_position = new_position;
}
inline void Ship::col(int col) {
	if (is_collision(static_cast<char>(col + 'A' - 1))) {
		throw std::logic_error("Invalid input: incorrect ship");
	}

	Position new_position(_position);
	new_position.col(col);

	if (is_collision(_size, new_position, _direction)) {
		throw std::logic_error("Invalid input: incorrect ship");
	}

	_position = new_position;
}
inline void Ship::col(char col) {
	if (is_collision(col)) {
		throw std::logic_error("Invalid input: incorrect ship");
	}

	Position new_position(_position);
	new_position.col(col);

	if (is_collision(_size, new_position, _direction)) {
		throw std::logic_error("Invalid input: incorrect ship");
	}

	_position = new_position;
}
inline void Ship::direction(Direction direction) {
	if (is_collision(_size, _position, direction)) {
		throw std::logic_error("Invalid input: incorrect ship");
	}

	_direction = direction;
}
inline void Ship::direction(char direction) {
	char dir_upper = static_cast<char>(std::toupper(direction));
	if (dir_upper != 'H' && dir_upper != 'V') {
		throw std::logic_error("Invalid input: incorrect ship");
	}
	Direction dir = (dir_upper == 'H') ? Horizontal : Vertical;

	if (is_collision(_size, _position, dir)) {
		throw std::logic_error("Invalid input: incorrect ship");
	}

	_direction = dir;
}
inline void Ship::position(Position new_position) {
	if (is_collision(_size, new_position, _direction)) {
		throw std::logic_error("Invalid input: incorrect ship");
	}

	_position = new_position;
}