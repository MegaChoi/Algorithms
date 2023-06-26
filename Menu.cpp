#include "Menu.h"

Menu::Menu(){
    if(!font.loadFromFile("Texture/futura.ttf")){
        cout << "no font loaded" << endl;
    }
    Options[0].setFont(font);
    Options[0].setFillColor(Color::White);
    Options[0].setString("Astar");
    Options[0].setCharacterSize(70);
    Options[0].setPosition(400,200);

    Options[1].setFont(font);
    Options[1].setFillColor(Color::White);
    Options[1].setString("Dijkstra");
    Options[1].setCharacterSize(70);
    Options[1].setPosition(400,300);


    selected = -1;
}

Menu::~Menu(){}


void Menu::draw(RenderWindow& window){
    for (Text option : Options){
        window.draw(option);
    }
}

Algo Menu::getOption(){
    if(selected == 0){
        return ASTAR;
    }else if (selected == 1){
        return DIJKSTRA;
    }else{
        return NONE;
    }
}

void Menu::MoveUp(){
    if(selected - 1 >= 0){
        Options[selected].setFillColor(Color::White);
        selected--;
        if(selected == -1)
            selected = 2;
        Options[selected].setFillColor(Color::Blue);
    }
}

void Menu::MoveDown(){
    if(selected + 1 <= MAX_OPS){
        Options[selected].setFillColor(Color::White);
        selected++;
        if(selected == MAX_OPS)
            selected = 0;
        Options[selected].setFillColor(Color::Blue);
    }
}