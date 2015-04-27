/* 
 * File:   EstadoBatall.cpp
 * Author: Oliver Rull
 * 
 * Created on 27 de abril de 2015, 17:15
 */

#include "../headers/EstadoBatall.h"
#include "../headers/Estado.h"
#include "../headers/Juego.h"
#include "../headers/Aliadas.h"
#include "../headers/Enemigo.h"

#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

//using namespace tinyxml2;
using namespace std;
using namespace sf;


EstadoBatall* EstadoBatall::pinstance = 0;

EstadoBatall* EstadoBatall::Instance () {
    if(pinstance == 0){ //¿Es la primera llamada?
        pinstance = new EstadoBatall(); //Creamos la instancia
    }
    return pinstance; //Retornamos la direccion de la instancia
}


EstadoBatall::EstadoBatall() {
    
    reloj = new Clock();
    evento = new Event();
    fondoBata = new Texture();
    batalla = new Sprite();
}



EstadoBatall::~EstadoBatall() {
    
    delete fondoBata;
    delete reloj;
    delete evento;
    delete batalla;
    delete pinstance;
    
}

void EstadoBatall::init_State(){
    
    if (!fondoBata->loadFromFile("resources/fondoBatalla.png"))
    {
        std::cerr << "Error cargando la imagen fondoBatalla.png";
        exit(0);
    }
    
    batalla->setTexture(*fondoBata);

}

void EstadoBatall::render_State(){
    Juego::Instance()->getVentana()->clear();
    Juego::Instance()->getVentana()->draw(*batalla);
    Juego::Instance()->getVentana()->display();
}


void EstadoBatall::update_State(){
    if (reloj->getElapsedTime().asMilliseconds() >= 100) {
        reloj->restart();
        
        input();
    }
}

void EstadoBatall::input() {
    
    while (Juego::Instance()->getVentana()->pollEvent(*evento)){
        if ((evento->type == Event::Closed)){
            Juego::Instance()->getVentana()->close();
        }
            
        if(evento->type == sf::Event::KeyPressed){
            switch(evento->key.code){
                case sf::Keyboard::B:
                    Juego::Instance()->ponerEstadoEscenario();              
                break;
                case sf::Keyboard::Escape:
                    Juego::Instance()->getVentana()->close();               
                break;
            }
        }
    }
}