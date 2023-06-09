#ifndef CELL
#define CELL
#include <array>

using namespace std;

namespace Size{
	const int CELL_SIZE = 20;
	const int COLS = 64;
	const int ROWS = 36;
	const int HEIGHT = 720;
	const int WIDTH = 1280;
}
enum Type{
	START,
	WALL,
	VISITED,
	EMPTY,
	GOAL,
	PATH
};



class Cell{
public:
	Type type = EMPTY;
	double distance = 0;
	Cell() {};
};

namespace Map {
	template <typename cell = Cell>
	using Grid = array<array<cell, Size::ROWS>, Size::COLS>;
}
#endif // !CELL