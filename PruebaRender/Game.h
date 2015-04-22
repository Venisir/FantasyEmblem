/* 
 * File:   Game.h
 * Author: Alberto
 *
 * Created on 25 de marzo de 2015, 9:35
 */

#ifndef GAME_H
#define	GAME_H

#include "tinyxml2.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string>

using namespace tinyxml2;
using namespace std;
using namespace sf;

class Game {
public:
    Game(sf::RenderWindow* v);
    Game(const Game& orig);
   ~Game();
    void init();
    void render();
    void update();
    void run();
    void input();
    
private:
    sf::RenderWindow* ventana;
    sf::Event* evento;
    sf::Clock* reloj;
    sf::Clock* relojUpdate;
    sf::Clock* reloj_fps;
    sf::Font* fuente;
    sf::Text* t_fps;
    sf::Text* t_fps2;
    
    float fps;
    float contadorUpdate;
    float timeUpdate;
    
    int state;
};

#endif	/* GAME_H */

