/* 
 * File:   PantallaStart.cpp
 * Author: Oliver Rull
 * 
 * Created on 10 de mayo de 2015, 20:14
 */

#include "../headers/GameOver.h"
#include "../headers/PantallaStart.h"
#include "../headers/Juego.h"
#include "../headers/Escenario.h"
#include "../headers/Estado.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string>

using namespace std;
using namespace sf;


GameOver* GameOver::pinstance = 0;

GameOver* GameOver::Instance () {
    if(pinstance == 0){ //¿Es la primera llamada?
        pinstance = new GameOver(); //Creamos la instancia
    }
    return pinstance; //Retornamos la direccion de la instancia
}


GameOver::GameOver() {
    
    
    
    fondo= new Texture();
    intro = new Sprite();
    
    mainmenu = new SoundBuffer();
    mmselect = new SoundBuffer();
    menusonido = new Sound();
    select = new Sound();
    reloj = new Clock();
    evento = new Event();
    
     init_State();
}



GameOver::~GameOver() {
    
    delete fondo;
    delete intro;
    delete mainmenu;
 
    delete mmselect;
    delete menusonido;

    delete select;  
    
    delete reloj;
    delete evento;
}

void GameOver::init_State() {

    if (!fondo->loadFromFile("resources/gameover.png"))
    {
        std::cerr << "Error cargando la imagen intro.png";
        exit(0);
    }
        
 
        
    
    
    
    intro->setTexture(*fondo);
    intro->setOrigin(0,0);
    intro->setPosition(0,0);
   
  
    aux=0;
   
    //cargar audios
    if (!mainmenu->loadFromFile("resources/gameover.wav")){
        std::cerr << "Error al cargar el archivo de audio";
    }
 
    if (!mmselect->loadFromFile("resources/MainMenu_Select.wav")){
        std::cerr << "Error al cargar el archivo de audio";
    }
    
    
    // Le asignamos el buffer cargado
    menusonido->setBuffer(*mainmenu);
    // establecemos el volumen a 20
    menusonido->setVolume(50);
    //reproducir audio del menu
    menusonido->setLoop(true);
    menusonido->play();
    
 

    select->setBuffer(*mmselect);
    select->setVolume(100);

    
        
}


void GameOver::pararmusica() {
    
    menusonido->stop();
    
}


void GameOver::render_State(){
    Juego::Instance()->getVentana()->clear();
    
    //dibujo el fondo y los sprites guardados en el array menu
    Juego::Instance()->getVentana()->draw(*intro);
    
    Juego::Instance()->getVentana()->display();
}


void GameOver::update_State(){
    if (reloj->getElapsedTime().asSeconds() >= 0.5) {
       
       
        
        
        reloj->restart();
        
        input();
    }
}

void GameOver::input() {
    
    while (Juego::Instance()->getVentana()->pollEvent(*evento)){
        if ((evento->type == Event::Closed)){
            Juego::Instance()->getVentana()->close();
        }
            
        if(evento->type == sf::Event::KeyPressed){
            switch(evento->key.code){
                case sf::Keyboard::A:
                    Juego::Instance()->getVentana()->close();
                break;
                case sf::Keyboard::Escape:
                    Juego::Instance()->getVentana()->close();               
                break;
            }
        }else{
            if(sf::Joystick::isConnected(0)){
                if(evento->type == sf::Event::JoystickButtonPressed){
                    switch(evento->joystickButton.button){
                        case 9:
                            pararmusica();
                            Juego::Instance()->ponerEstadoPantallaInicio(); 
                        break;
                    }
                }
            }
        }
    }
}

