#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <cmath>
#include "Cell.hpp"
#include "Astar.h"
#include "Dijkstra.h"
#include "Render.h"
#include <fstream>
#include <iostream>
using namespace sf;
using namespace std;

#define MAX_OPS 2

class Menu{
public:
    Menu();
    ~Menu();
    void MoveUp();
    void MoveDown();
    void draw(RenderWindow& window);
    Algo getOption();

private:
    int selected;
    Font font;
    Text Options[MAX_OPS];
};

#endif