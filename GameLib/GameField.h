#pragma once
#include <string>

class GameField {
	char** _field;
	const int _n;
	const int _m;

public:
	GameField(char** = nullptr, int = 10, int = 10);
	GameField(int, int);
	GameField(const GameField&);

	~GameField();

	inline void set(int, int);
	inline char get(int, int) const;

	friend std::string to_string(GameField) noexcept;
};