#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <cmath>
#include "Cell.hpp"
#include "Astar.hpp"
#include "Dijkstra.h"
using namespace sf;
using namespace std;


void draw(RectangleShape & cell, RenderWindow& window, Map::Grid<> & Grid, int totalVisited) {
    // Draw the grid
    for (int i = 0; i < Size::COLS; ++i)
    {
        for (int j = 0; j < Size::ROWS; ++j)
        {   
            switch(Grid[i][j].type){
                case Type::START:
                    cell.setFillColor(sf::Color::Red);
                    break;
                case Type::EMPTY:
                    cell.setFillColor(sf::Color::White);
                    break;
                case Type::GOAL:
                    cell.setFillColor(sf::Color::Green);
                    break;
                case Type::VISITED:
                    cell.setFillColor(sf::Color::Cyan);
                    break;
            }
            cell.setPosition(i * Size::CELL_SIZE, j * Size::CELL_SIZE);
            window.draw(cell);
        }
    }
    
}

int main()
{   
    

    // Create the SFML window
    RenderWindow window(VideoMode(Size::WIDTH, Size::HEIGHT), "Path Finding", sf::Style::Titlebar | sf::Style::Close);
    window.setSize(Vector2u(Size::WIDTH, Size::HEIGHT));

    Map::Grid<> Grid = {};

    vector<Cell> openSet = {};
    vector<Cell> closeSet = {};

    // Initialize the grid with zeros
    for (int i = 0; i < Size::COLS; ++i)
    {
        for (int j = 0; j < Size::ROWS; ++j)
        {
            Grid[i][j] = Cell();
        }
    }
    
    Cell start = Grid[0][0];
    Cell end = Grid[Size::COLS-1][Size::ROWS-1];
    
    openSet.push_back(start);

    int totalVisited = 0;

    // set the cell sizes
    RectangleShape cell(sf::Vector2f(Size::CELL_SIZE, Size::CELL_SIZE));
    cell.setOutlineThickness(1.0f);                   
    cell.setOutlineColor(sf::Color::Black);           
    int x = 0;
    int y = 0;

    Dijkstra test;
    // Main loop
    // Main loop
    // Set the update rate to 60 times per second
    sf::Clock clock;
    sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
    sf::Time elapsedTime = sf::Time::Zero;
    // Process events
    Event event;

    bool startSet = false;
    bool goalSet = false;

    
    while (window.isOpen())
    {



        // Accumulate the elapsed time
        elapsedTime += clock.restart();

        // Update the game logic only when enough time has passed
        while (elapsedTime >= timePerFrame)
        {   
            while (window.pollEvent(event))
            {   
                switch (event.type)
                {
                case Event::Closed:
                    window.close();
                    break;
                case Event::MouseButtonPressed:
                    if (startSet == false || goalSet == false){
                        if (event.mouseButton.button == Mouse::Left){
                            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                            int col = std::ceil(mousePos.x / Size::CELL_SIZE);
                            int row = std::ceil(mousePos.y / Size::CELL_SIZE);
                            if(startSet == false){
                                Grid[col][row].type = Type::START;
                                startSet = true;
                            }else if (goalSet == false){
                                Grid[col][row].type = Type::GOAL;
                                goalSet = true;
                            }
                        }
                    }
                    break;
                }
                
            }





            // // Clear the window
            
            // cout << totalVisited << endl;

            // if (totalVisited < 2304)
            //     test.updateMap(Grid, totalVisited);
            
            window.clear();

            draw(cell, window, Grid, totalVisited);

            // // Display the updated window
            window.display();

            // // Decrease the elapsed time
            // elapsedTime -= timePerFrame;
        }
    }

    return 0;
}