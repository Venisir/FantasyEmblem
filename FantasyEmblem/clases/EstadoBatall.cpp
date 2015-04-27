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
    perso1= new Texture();
    per1= new Sprite();
    perso2= new Texture();
    per2= new Sprite();
    
    
    init_State();
}



EstadoBatall::~EstadoBatall() {
    
    delete fondoBata;
    delete reloj;
    delete evento;
    delete batalla;
    delete pinstance;
    delete perso1;
    delete per1;
    delete perso2;
    delete per2;
}

void EstadoBatall::init_State(){
    
    string s ="resources/fondoBatalla.png";
    if (!fondoBata->loadFromFile(s))
    {
        std::cerr << "Error cargando la imagen fondoBatalla.png";
        exit(0);
    }
    
    if (!perso1->loadFromFile("resources/ike.png"))
    {
        std::cerr << "Error cargando la imagen ike.png";
        exit(0);
    }
    if (!perso2->loadFromFile("resources/ike.png"))
    {
        std::cerr << "Error cargando la imagen ike.png";
        exit(0);
    }
    
    batalla->setTexture(*fondoBata);
    batalla->setOrigin(0,0);
    batalla->setPosition(0,0);
  
    contPer1i = 0;
    contPer1j = 0;
    per1->setTexture(*perso1);
    
    
    per1->setTextureRect(IntRect(0,0,248,160));
    per1->setScale(1.5,1.5);
    per1->setPosition(90,25);
    
    per2->setTexture(*perso2);
    per2->setTextureRect(IntRect(0,0,248,160));
    per2->setScale(1.5,-1.5);
    per2->setPosition(0,25);
    
}

void EstadoBatall::render_State(){
    Juego::Instance()->getVentana()->clear();
    
    Juego::Instance()->getVentana()->draw(*batalla);
    Juego::Instance()->getVentana()->draw(*per1);
    Juego::Instance()->getVentana()->draw(*per2);
    Juego::Instance()->getVentana()->display();
}


void EstadoBatall::update_State(){
    if (reloj->getElapsedTime().asSeconds() >= 0.1) {
        cerr << contPer1i << "  " << contPer1j << endl;
        per1->setTextureRect(IntRect(contPer1i*248,contPer1j*160,248,160));
        if(contPer1i==7){
            contPer1i=0;
            contPer1j++;
        }
        contPer1i++;
        
        if(contPer1i==7 && contPer1j== 5){
            contPer1i = 0;
            contPer1j = 0;
            Juego::Instance()->ponerEstadoEscenario();
        }
        
        
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