/* 
 * File:   Escenario.cpp
 * Author: Ricardo
 * 
 * Created on 15 de abril de 2015, 9:41
 */


//#include "tinyxml2.h"
#include "../headers/Escenario.h"
#include "../headers/Estado.h"
#include "../headers/Juego.h"

#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

//using namespace tinyxml2;
using namespace std;
using namespace sf;

Escenario* Escenario::pinstance = 0;

Escenario* Escenario::Instance () {
    if(pinstance == 0){ //¿Es la primera llamada?
        pinstance = new Escenario(); //Creamos la instancia
    }
    return pinstance; //Retornamos la direccion de la instancia
}

Escenario::Escenario() {
    //Realizar inicializaciones necesarias de la instancia
    //ventana->create(sf::VideoMode(480,320), "Fantasy Emblem");
    texturaSeleccionar = new Texture();
    texturaMano = new Texture();
    spriteCursor = new Sprite();
    reloj = new Clock();
    evento = new Event();
    
    init_State();
}

Escenario::~Escenario() {
    /*if(pinstance != NULL)*/ 
    delete texturaSeleccionar;
    delete texturaMano;
    delete spriteCursor;
    delete reloj;
    delete evento;
    //delete ventana;
    delete pinstance;
}

void Escenario::init_State(){
    
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
    
    spriteCursor->setPosition(0,0);
    
    cambiaSpriteCursorSeleccionar();
}

void Escenario::cambiaSpriteCursorSeleccionar() {
    spriteCursor->setTexture(*texturaSeleccionar);
}

void Escenario::cambiaSpriteCursorMano() {
    spriteCursor->setTexture(*texturaMano);
}

void Escenario::render_State(){
    Juego::Instance()->getVentana()->clear();
    Juego::Instance()->getVentana()->draw(*spriteCursor);
    Juego::Instance()->getVentana()->display();
}


void Escenario::update_State(){
    if (reloj->getElapsedTime().asMilliseconds() >= 100) {
        reloj->restart();
        
        input();
    }
}

void Escenario::input() {
    
    while (Juego::Instance()->getVentana()->pollEvent(*evento)){
        if ((evento->type == Event::Closed)){
            Juego::Instance()->getVentana()->close();
        }
            
        if(evento->type == sf::Event::KeyPressed){
            switch(evento->key.code){
                case sf::Keyboard::Down:
                    if(spriteCursor->getPosition().y<320-16)
                        spriteCursor->move(0,16);     
                    std::cerr << spriteCursor->getPosition().y <<endl;
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
                    if(spriteCursor->getPosition().x<480-16)
                        spriteCursor->move(16,0);       
                    std::cerr << spriteCursor->getPosition().x <<endl;
                break;
                case sf::Keyboard::Numpad1:
                    cambiaSpriteCursorSeleccionar();             
                break;
                case sf::Keyboard::Numpad2:
                    cambiaSpriteCursorMano();               
                break;
                case sf::Keyboard::Numpad8:
                    Juego::Instance()->ponerEstadoMenuPrincipal();              
                break;
                case sf::Keyboard::Numpad9:
                    Juego::Instance()->ponerEstadoPause();              
                break;
                case sf::Keyboard::Return:
                                  
                break;
                
                case sf::Keyboard::Escape:
                    Juego::Instance()->getVentana()->close();               
                break;
            }
        }
    }
}