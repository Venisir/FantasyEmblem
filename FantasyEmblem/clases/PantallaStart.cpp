/* 
 * File:   PantallaStart.cpp
 * Author: Oliver Rull
 * 
 * Created on 10 de mayo de 2015, 20:14
 */

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


PantallaStart* PantallaStart::pinstance = 0;

PantallaStart* PantallaStart::Instance () {
    if(pinstance == 0){ //¿Es la primera llamada?
        pinstance = new PantallaStart(); //Creamos la instancia
    }
    return pinstance; //Retornamos la direccion de la instancia
}


PantallaStart::PantallaStart() {
    
    
    boto= new Texture();
    fondo= new Texture();
    intro = new Sprite();
    start= new Sprite();
    mainmenu = new SoundBuffer();
    mmselect = new SoundBuffer();
    menusonido = new Sound();
    select = new Sound();
    reloj = new Clock();
    evento = new Event();
    
     init_State();
}



PantallaStart::~PantallaStart() {
    
    delete fondo;
    delete boto;
    delete start;
    delete intro;
    delete mainmenu;
 
    delete mmselect;
    delete menusonido;

    delete select;  
    
    delete reloj;
    delete evento;
}

void PantallaStart::init_State() {

    if (!fondo->loadFromFile("resources/intro.png"))
    {
        std::cerr << "Error cargando la imagen intro.png";
        exit(0);
    }
        
    if (!boto->loadFromFile("resources/start.png"))
    {
        std::cerr << "Error cargando la imagen start.png";
        exit(0);
    }
        
    
    
    
    intro->setTexture(*fondo);
    intro->setOrigin(0,0);
    intro->setPosition(0,0);
   
    start->setTexture(*boto);
    
    start->setPosition(200,200);
   
    aux=0;
   
    //cargar audios
    if (!mainmenu->loadFromFile("resources/menu.wav")){
        std::cerr << "Error al cargar el archivo de audio";
    }
 
    if (!mmselect->loadFromFile("resources/MainMenu_Select.wav")){
        std::cerr << "Error al cargar el archivo de audio";
    }
    
    
    // Le asignamos el buffer cargado
    menusonido->setBuffer(*mainmenu);
    // establecemos el volumen a 20
    menusonido->setVolume(30);
    //reproducir audio del menu
    menusonido->setLoop(true);
    menusonido->play();
    
 

    select->setBuffer(*mmselect);
    select->setVolume(100);

    
        
}


void PantallaStart::pararmusica() {
    
    menusonido->stop();
    
}
void PantallaStart::playmusic() {
    
    menusonido->play();
    
}

void PantallaStart::render_State(){
    Juego::Instance()->getVentana()->clear();
    
    //dibujo el fondo y los sprites guardados en el array menu
    Juego::Instance()->getVentana()->draw(*intro);
    Juego::Instance()->getVentana()->draw(*start);
    Juego::Instance()->getVentana()->display();
}


void PantallaStart::update_State(){
    if (reloj->getElapsedTime().asSeconds() >= 0.5) {
       
        if(aux==0){
            start->setScale(0,0);
            aux=1;
        }else if(aux==1){
            start->setScale(1,1);
            aux=0;
        }
        
        
        reloj->restart();
        
        input();
    }
}

void PantallaStart::input() {
    
    while (Juego::Instance()->getVentana()->pollEvent(*evento)){
        if ((evento->type == Event::Closed)){
            Juego::Instance()->getVentana()->close();
        }
            
        if(evento->type == sf::Event::KeyPressed){
            switch(evento->key.code){
                case sf::Keyboard::Return:
                    Juego::Instance()->ponerEstadoMenuPrincipal();              
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
                            Juego::Instance()->ponerEstadoMenuPrincipal(); 
                        break;
                    }
                }
            }
        }
    }
}