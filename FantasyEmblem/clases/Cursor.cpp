/* 
 * File:   Cursor.cpp
 * Author: Alberto
 * 
 * Created on 15 de abril de 2015, 9:43
 */

//#include "tinyxml2.h"
#include "../headers/Cursor.h"
#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

//using namespace tinyxml2;
using namespace std;
using namespace sf;

Cursor::Cursor(RenderWindow *v) {
    ventana = v;
    texturaSeleccionar = new Texture();
    texturaMano = new Texture();
    spriteCursor = new Sprite();
    reloj = new Clock();
    evento = new Event();
}

Cursor::Cursor(const Cursor& orig) {
}

Cursor::~Cursor() {
    delete texturaSeleccionar;
    delete texturaMano;
    delete spriteCursor;
    delete reloj;
    delete evento;
    delete ventana;
}

void Cursor::init() {
    
    //ventana->setSize(sf::Vector2u(960, 640));
    
    if (!texturaSeleccionar-> loadFromFile("resources/cursor.png"))
    {
        std::cerr << "Error cargando la imagen cursor.png";
        exit(0);
    }
    
    if (!texturaMano-> loadFromFile("resources/mano.png"))
    {
        std::cerr << "Error cargando la imagen mano.png";
        exit(0);
    }
    contadorUpdate = 0;
    
    spriteCursor->setPosition(0,0);
    
    cambiaSpriteCursorSeleccionar();
}

void Cursor::render() {
    ventana->clear();
    ventana->draw(*spriteCursor);
    ventana->display();
}

void Cursor::update() {
    if (reloj->getElapsedTime().asMilliseconds() >= 100) {
        reloj->restart();
        
        input();
        
        contadorUpdate++;
    }
}

void Cursor::cambiaSpriteCursorSeleccionar() {
    spriteCursor->setTexture(*texturaSeleccionar);
}

void Cursor::cambiaSpriteCursorMano() {
    spriteCursor->setTexture(*texturaMano);
}

void Cursor::input() {
    
    while (ventana->pollEvent(*evento)){
        if ((evento->type == Event::Closed)){
            ventana->close();
        }
            
        if(evento->type == sf::Event::KeyPressed){
            switch(evento->key.code){
                case sf::Keyboard::Down:
                    if(spriteCursor->getPosition().y<=320-16)
                        spriteCursor->move(0,16);     
                break;
                case sf::Keyboard::Up:
                    if(spriteCursor->getPosition().y>=16)
                        spriteCursor->move(0,-16);              
                break;
                case sf::Keyboard::Left:
                    if(spriteCursor->getPosition().x>=16)
                        spriteCursor->move(-16,0);              
                break;
                case sf::Keyboard::Right:
                    if(spriteCursor->getPosition().x<=480-16)
                        spriteCursor->move(16,0);       
                break;
                case sf::Keyboard::Numpad1:
                    cambiaSpriteCursorSeleccionar();             
                break;
                case sf::Keyboard::Numpad2:
                    cambiaSpriteCursorMano();               
                break;
                case sf::Keyboard::Escape:
                    ventana->close();               
                break;
            }
        }
    }
}