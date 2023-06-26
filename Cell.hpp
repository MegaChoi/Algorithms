#ifndef CELL
#define CELL
#include <array>
#include <climits>


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

enum Algo{
	ASTAR,
	DIJKSTRA,
	NONE,
};


class Cell {
public:
    Type type = EMPTY;
    int row;
    int col;

	// g value
    double distance = INT_MAX;

	// h value 
	double hValue = 0;

	// f value
	double fValue = 0;


	Cell * prev = nullptr;

    Cell() {}

    void set(int x, int y) {
        col = x;
        row = y;
    }
};

namespace Map {
	template <typename cell = Cell>
	using Grid = array<array<cell, Size::ROWS>, Size::COLS>;
}
#endif // !CELL