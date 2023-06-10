#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <cmath>
#include "Cell.hpp"
#include "Astar.hpp"
#include "Dijkstra.h"
#include <fstream>
#include <iostream>
using namespace sf;
using namespace std;



void draw(RectangleShape & cell, RenderWindow& window, Map::Grid<> & Grid, int goalFound) {
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
                case Type::WALL:
                    cell.setFillColor(sf::Color::Black);
                    break;
                case Type::PATH:
                    cell.setFillColor(sf::Color::Yellow);
                    break;
            }
            cell.setPosition(i * Size::CELL_SIZE, j * Size::CELL_SIZE);
            window.draw(cell);
        }
    }
    
}

// void distance(Map::Grid<> & Grid, int x, int y){
//     for (int i = 0; i < Size::COLS; ++i){
//         for (int j = 0; j < Size::ROWS; ++j){
//             Grid[i][j].distance = sqrt(pow((x - i),2) + pow((y - j),2));
//         }
//     }
// }

int main()
{   
    

    // Create the SFML window
    RenderWindow window(VideoMode(Size::WIDTH, Size::HEIGHT), "Path Finding", sf::Style::Titlebar | sf::Style::Close);
    window.setSize(Vector2u(Size::WIDTH, Size::HEIGHT));

    // Init grid
    Map::Grid<> Grid = {};


    // Init all cells with distance of INFINITE
    for (int i = 0; i < Size::COLS; ++i)
    {
        for (int j = 0; j < Size::ROWS; ++j)
        {
            Grid[i][j] = Cell();
            Grid[i][j].set(i,j);
        }
    }
    
    

    bool goalFound = false;

    // set the cell sizes
    RectangleShape cell(sf::Vector2f(Size::CELL_SIZE, Size::CELL_SIZE));
    cell.setOutlineThickness(1.0f);                   
    cell.setOutlineColor(sf::Color::Black);           
    int x = 0;
    int y = 0;

    Dijkstra test;

    // Set the update rate to 60 times per second
    sf::Clock clock;
    sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
    sf::Time elapsedTime = sf::Time::Zero;
    // Process events
    Event event;

    bool startSet = false;
    bool goalSet = false;
    bool search = false;

    sf::Vector2i startCell(0, 0);
    sf::Vector2i goalCell(0, 0);
    
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
                                    Grid[col][row].distance = 0;
                                    startSet = true;
                                    test.setStartCell(Grid[col][row]);
                                    
                                }else if (goalSet == false){
                                    Grid[col][row].type = Type::GOAL;
                                    // distance(Grid, col, row);
                                    goalSet = true;
                                }
                            }
                        }
                        break;
                    case Event::MouseMoved:
                        if (startSet && goalSet && !search){
                            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                                // cout << mousePos.x << " " << mousePos.y << std::endl;
                                int col = std::ceil(mousePos.x / Size::CELL_SIZE);
                                int row = std::ceil(mousePos.y / Size::CELL_SIZE);

                                if(Grid[col][row].type != Type::START && Grid[col][row].type != Type::GOAL)
                                    Grid[col][row].type = Type::WALL;
                            }
                        }
                        break;
                    case Event::KeyPressed:
                        if (event.key.code == Keyboard::Space){
                            search = true;
                        }
                        break;
                }
                
            }



            // start algorithms after start and goal cells are set
            if(startSet && goalSet && search){
                if (goalFound == false){
                    test.updateMap(Grid, goalFound);
                    // cout << goalFound << endl;
                }
            }

            
            window.clear();

            draw(cell, window, Grid, goalFound);

            // // Display the updated window
            window.display();

            // // Decrease the elapsed time
            elapsedTime -= timePerFrame;

            // Window is closed, terminate the program
            if (!window.isOpen()) {
                break;
            }
        }
    }

    return 0;
}