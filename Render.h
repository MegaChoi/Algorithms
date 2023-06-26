#ifndef RENDER_H
#define RENDER_H
#include <SFML/Graphics.hpp>
#include "Cell.hpp"
using namespace sf;
using namespace std;

class Render {
public:
    static void draw(RectangleShape & cell, RenderWindow& window, Map::Grid<> & Grid);
};
#endif