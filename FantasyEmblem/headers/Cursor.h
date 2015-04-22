/* 
 * File:   Cursor.h
 * Author: Alberto
 *
 * Created on 15 de abril de 2015, 9:43
 */

#ifndef CURSOR_H
#define	CURSOR_H

//#include "tinyxml2.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string>

//using namespace tinyxml2;
using namespace std;
using namespace sf;

class Cursor {
    
public:
    Cursor(sf::RenderWindow* v);
    Cursor(const Cursor& orig);
    ~Cursor();
    void init();
    void render();
    void update();
    void input();
    void cambiaSpriteCursorMano();
    void cambiaSpriteCursorSeleccionar();
private:    
    sf::Texture* texturaSeleccionar;
    sf::Texture* texturaMano;
    sf::Sprite* spriteCursor;
    sf::Clock* reloj;
    sf::Event* evento;
    
    float contadorUpdate;
    
    //Temporal
    sf::RenderWindow* ventana;
};

#endif	/* CURSOR_H */

