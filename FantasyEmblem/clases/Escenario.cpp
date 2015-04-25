/* 
 * File:   Escenario.cpp
 * Author: Ricardo
 * 
 * Created on 15 de abril de 2015, 9:41
 */


//#include "tinyxml2.h"
#include "../headers/Aliadas.h"
#include "../headers/Enemigo.h"
#include "../headers/Escenario.h"
#include "../headers/Estado.h"
#include "../headers/Juego.h"
#include "../headers/Mapa.h"

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
    texturaCursor = new Texture();
    spriteCursor = new Sprite();
    reloj = new Clock();
    relojCursor = new Clock();
    evento = new Event();
    mapa = new Mapa();
    
    int atri[] = { 11, 22, 33, 44, 55, 66, 77};
    
    aliadas[0] = new Aliadas("Alberto", "Espadachin", atri, 8, 9, "Mapa_espadachin_azul.png", 0);
    enemigos[0] = new Enemigo("AlbertoMalo", "Guerrero", atri, 8, 9, "Mapa_espadachin_rojo.png");
    
    aliadas[0]->setPosition(176,176);
    enemigos[0]->setPosition(208,176);
    
    init_State();
}

Escenario::~Escenario() {
    /*if(pinstance != NULL)*/ 
    delete texturaCursor;
    delete spriteCursor;
    delete reloj;
    delete relojCursor;
    delete evento;
    //delete ventana;
    delete pinstance;
    delete mapa;
    delete aliadas[0];
}

void Escenario::init_State(){
    
    if (!texturaCursor-> loadFromFile("resources/cursores.png"))
    {
        std::cerr << "Error cargando la imagen cursores.png";
        exit(0);
    }
    /*
    if (!texturaMano-> loadFromFile("resources/cursor_1.png"))
    {
        std::cerr << "Error cargando la imagen cursor_1.png";
        exit(0);
    }
    */
    
    spriteCursor->setTexture(*texturaCursor);
    spriteCursor->setTextureRect(IntRect(0, 0, 16, 16));
    
    spriteCursor->setPosition(0,0);
    
    cambiaSpriteCursorSeleccionar();
    
    cursorActivo = 0;
    varCursor = 0;
}

void Escenario::cambiaSpriteCursorSeleccionar() {
    varCursor = 0;
    spriteCursor->setTextureRect(IntRect(0, 0, 16, 16));
    cursorActivo = 0;
}

void Escenario::cambiaSpriteCursorMano() {
    varCursor = 1;
    spriteCursor->setTextureRect(IntRect(0, 16, 16, 16));
    cursorActivo = 16;
}

void Escenario::render_State(){
    
    Juego::Instance()->getVentana()->clear();
    
    mapa->Draw();
    
    aliadas[0]->Draw();
    enemigos[0]->Draw();
    
    Juego::Instance()->getVentana()->draw(*spriteCursor);
    
    Juego::Instance()->renderText();
    
    Juego::Instance()->getVentana()->display();
}

void Escenario::update_State(){
    
    if (relojCursor->getElapsedTime().asSeconds() >= 0.5) {
        
        aliadas[0]->cambiaSpriteQuieto();
        enemigos[0]->cambiaSpriteQuieto();
        
        if(varCursor == 0){
            spriteCursor->setTextureRect(IntRect(cursorActivo, 0, 16, 16));
            cursorActivo = abs(cursorActivo-16);
        }else{
            spriteCursor->setTextureRect(IntRect(cursorActivo, 16, 16, 16));
            cursorActivo = abs(cursorActivo-16);
        }
        relojCursor->restart();
    }
    
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
                        std::cerr << "Cursor en: (" << spriteCursor->getPosition().x << ", " << spriteCursor->getPosition().y << ")" <<endl;
                break;
                case sf::Keyboard::Up:
                    if(spriteCursor->getPosition().y>=16)
                        spriteCursor->move(0,-16);       
                        std::cerr << "Cursor en: (" << spriteCursor->getPosition().x << ", " << spriteCursor->getPosition().y << ")" <<endl;      
                break;
                case sf::Keyboard::Left:
                    if(spriteCursor->getPosition().x>=16)
                        spriteCursor->move(-16,0);              
                        std::cerr << "Cursor en: (" << spriteCursor->getPosition().x << ", " << spriteCursor->getPosition().y << ")" <<endl;
                break;
                case sf::Keyboard::Right:
                    if(spriteCursor->getPosition().x<480-16)
                        spriteCursor->move(16,0);       
                        std::cerr << "Cursor en: (" << spriteCursor->getPosition().x << ", " << spriteCursor->getPosition().y << ")" <<endl;
                break;
                case sf::Keyboard::Numpad1:
                    cambiaSpriteCursorSeleccionar();             
                break;
                
                case sf::Keyboard::Numpad2:
                    cambiaSpriteCursorMano();               
                break;
                
                case sf::Keyboard::Numpad3:
                    aliadas[0]->verStats();
                break;
                
                case sf::Keyboard::Numpad4:
                    cerr<< "Posicion CELDA unidad: (" << aliadas[0]->getPosicionCeldaX() << ", " << aliadas[0]->getPosicionCeldaY() << ")" << endl;
                    cerr<< "Posicion PIXEL unidad: (" << aliadas[0]->getPosicionSpriteX() << ", " << aliadas[0]->getPosicionSpriteY() << ")" << endl;
                break;
                
                case sf::Keyboard::Numpad5:
                    
                break;
                
                case sf::Keyboard::Numpad6:
                    
                break;
                
                case sf::Keyboard::Numpad7:
                    
                break;
                
                case sf::Keyboard::Numpad8:
                    Juego::Instance()->ponerEstadoMenuPrincipal();              
                break;
                case sf::Keyboard::Numpad9:
                    Juego::Instance()->ponerEstadoPause();              
                break;
                
                case sf::Keyboard::Return:
                    if(varCursor == 0){
                        if(spriteCursor->getPosition().x == aliadas[0]->getPosicionSpriteX() &&
                            spriteCursor->getPosition().y == aliadas[0]->getPosicionSpriteY()){
                            
                            aliadas[0]->verStats();
                            cambiaSpriteCursorMano();
                            

                        }
                        if(spriteCursor->getPosition().x == enemigos[0]->getPosicionSpriteX() &&
                            spriteCursor->getPosition().y == enemigos[0]->getPosicionSpriteY()){
                            
                            enemigos[0]->verStats();
                            cambiaSpriteCursorMano();

                        }
                    }else{
                        //if(spriteCursor->getPosition().x == aliadas[0]->getPosicionCeldaX() &&
                        //    spriteCursor->getPosition().y == aliadas[0]->getPosicionCeldaY()){

                            cambiaSpriteCursorSeleccionar();

                        //}
                    }
                break;
                
                case sf::Keyboard::A:
                    aliadas[0]->moverIzquierda();
                break;
                
                case sf::Keyboard::W:
                    aliadas[0]->moverArriba();
                break;
                
                case sf::Keyboard::S:
                    aliadas[0]->moverAbajo();
                break;
                
                case sf::Keyboard::D:
                    aliadas[0]->moverDerecha();
                break;
                
                case sf::Keyboard::Escape:
                    Juego::Instance()->getVentana()->close();               
                break;
            }
        }
    }
}