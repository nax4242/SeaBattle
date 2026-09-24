#pragma once
#include <string>
#include <iostream>
#include "Ship.h"

enum State { Missed, BoatDestroyed, DestroyersDestroyed, CruisersDestroyed, BattleshipDestroyed, Hit };

class GameField {
	char** _field;
	const int _n;
	const int _m;

public:
	GameField();
	~GameField();

	void set(const Ship&);
	State set(int, char);

	friend std::string to_string(const GameField&, bool) noexcept;

private:
	int check_destroy(int, int) const noexcept;
	friend bool is_collision(const GameField&, const Ship&) noexcept;
};

std::string to_string(const GameField&, bool = false) noexcept;
bool is_collision(const GameField&, const Ship&) noexcept;