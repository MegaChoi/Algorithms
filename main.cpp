#include "Menu.h"




int main()
{   
    
    //------------------------------------------------- SET UP----------------------------------------------
    // Create the SFML window
    RenderWindow window(VideoMode(Size::WIDTH, Size::HEIGHT), "Path Finding", sf::Style::Titlebar | sf::Style::Close);
    window.setSize(Vector2u(Size::WIDTH, Size::HEIGHT));


    // // Init the grid map
    // Map::Grid<> Grid = {};
    // // Init all cells with distance of INFINITE
    // for (int i = 0; i < Size::COLS; ++i)
    // {
    //     for (int j = 0; j < Size::ROWS; ++j)
    //     {
    //         Grid[i][j] = Cell();
    //         Grid[i][j].set(i,j);
    //     }
    // }

    // // lamda function to set all cells to EMPTY 
    // auto clearMap = [&]() ->void{
    //     for (int i = 0; i < Size::COLS; ++i)
    //     {
    //         for (int j = 0; j < Size::ROWS; ++j)
    //         {
    //             Grid[i][j].type = EMPTY;
    //         }
    //     }
    // };

    // Main menu
    Menu menu;

    // SFML Process events
    Event event;

    // Set the cell dimensions
    RectangleShape cell(sf::Vector2f(Size::CELL_SIZE, Size::CELL_SIZE));
    cell.setOutlineThickness(1.0f);                   
    cell.setOutlineColor(sf::Color::Black);           
    int x = 0;
    int y = 0;


    // Algorithm object pointer
    Algorithm * algorithm = new Astar();

    // Set the update rate to 60 times per second
    sf::Clock clock;
    sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
    sf::Time elapsedTime = sf::Time::Zero;

    // boolean variables
    bool goalFound = false;
    bool algoSet = false;
    bool startSet = false;
    bool goalSet = false;
    bool search = false;


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
                                    algorithm->setStartCell(col,row); 
                                    startSet = true;
                                }else if (goalSet == false){
                                    algorithm->setGoalCell(col,row);
                                    goalSet = true;
                                }
                            }
                        }
                        break;
                    case Event::MouseMoved:
                        if (startSet && goalSet && !search){
                            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                                int col = std::ceil(mousePos.x / Size::CELL_SIZE);
                                int row = std::ceil(mousePos.y / Size::CELL_SIZE);
                                algorithm->setWall(col,row);
                            }
                        }
                        break;
                    case Event::KeyPressed:
                        // start searching
                        if (event.key.code == Keyboard::Space){
                            search = true;
                        }
                        // reset the grid to EMTPY
                        else if (event.key.code == Keyboard::R){
                            algorithm->reset();
                            startSet = false;
                            goalSet = false;
                            goalFound = false;
                            search = false;
                        } 
                        // chnage the algorithm
                        else if (event.key.code == Keyboard::Up){
                            menu.MoveUp();
                        }else if (event.key.code == Keyboard::Down){
                            menu.MoveDown();
                        }
                        // selecte the algorithm
                        else if (event.key.code == Keyboard::Enter){
                            Algo selectedAlgo = menu.getOption();
                            if(selectedAlgo == ASTAR){
                                algorithm = new Astar();
                                algoSet = true;
                            }else if(selectedAlgo == DIJKSTRA){
                                algorithm = new Dijkstra();
                                algoSet = true;
                            }
                        }else if (event.key.code == Keyboard::E){
                            algoSet = false;
                            goalFound = false;
                            startSet = false;
                            goalSet = false;
                            search = false;
                        }
                        break;
                }
                
            }

            window.clear();

            // start algorithms after start and goal cells are set
            if(algoSet){
                if(startSet && goalSet && search && !goalFound){
                    algorithm->updateMap(goalFound);
                }
                algorithm->render(cell, window);
            }else{
                menu.draw(window);
            }
            
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