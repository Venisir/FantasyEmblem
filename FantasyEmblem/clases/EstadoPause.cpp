/* 
 * File:   EstadoPause.cpp
 * Author: Alberto
 * 
 * Created on 23 de abril de 2015, 16:41
 */

//#include "tinyxml2.h"
#include "../headers/EstadoPause.h"
#include "../headers/Estado.h"
#include "../headers/Juego.h"

#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

//using namespace tinyxml2;
using namespace std;
using namespace sf;

EstadoPause* EstadoPause::pinstance = 0;

EstadoPause* EstadoPause::Instance () {
    if(pinstance == 0){ //¿Es la primera llamada?
        pinstance = new EstadoPause(); //Creamos la instancia
    }
    return pinstance; //Retornamos la direccion de la instancia
}

EstadoPause::EstadoPause() {
    //Realizar inicializaciones necesarias de la instancia
    fuente = new sf::Font();
    t_textoPause = new Text();
    reloj = new Clock();
    evento = new Event();
    
    pause_close = new SoundBuffer();
    cpause = new Sound();
    init_State();
}

EstadoPause::~EstadoPause() {
    /*if(pinstance != NULL)*/ 
    delete fuente;
    delete t_textoPause;
    delete reloj;
    delete evento;
    
    delete pinstance;
    delete pause_close;
    delete cpause;
}

void EstadoPause::init_State(){
    
    fuente->loadFromFile("resources/font.ttf");
    
    std::stringstream ss_textoPause;
    ss_textoPause << "PAUSE";
    std::string s_textoPause = ss_textoPause.str();
    
    //sf::Text t_textoPause(s_textoPause,*fuente,20);
    
    t_textoPause->setFont(*fuente);
    t_textoPause->setCharacterSize(20);
    t_textoPause->setString(s_textoPause);
    t_textoPause->setColor(sf::Color::White);
    
    //Centrar el texto
    sf::FloatRect textRect = t_textoPause->getLocalBounds();
    t_textoPause->setOrigin(textRect.left + textRect.width/2.0f,
                  textRect.top  + textRect.height/2.0f);
    t_textoPause->setPosition(sf::Vector2f(480/2.0f,320/2.0f));

    
    
    if (!pause_close->loadFromFile("resources/PauseMenu_Close.wav")){
        std::cerr << "Error al cargar el archivo de audio";
    }
    
    cpause->setBuffer(*pause_close);
    cpause->setVolume(80);

}

void EstadoPause::render_State(){
    Juego::Instance()->getVentana()->clear();
    Juego::Instance()->getVentana()->draw(*t_textoPause);
    Juego::Instance()->getVentana()->display();
}


void EstadoPause::update_State(){
    if (reloj->getElapsedTime().asMilliseconds() >= 100) {
        reloj->restart();
        
        input();
    }
}

void EstadoPause::input() {
    
    while (Juego::Instance()->getVentana()->pollEvent(*evento)){
        if ((evento->type == Event::Closed)){
            Juego::Instance()->getVentana()->close();
        }
            
        if(evento->type == sf::Event::KeyPressed){
            switch(evento->key.code){
                case sf::Keyboard::Numpad9:
                    cpause->play();
                    Escenario::Instance()->playmusic();
                    Juego::Instance()->ponerEstadoEscenario();              
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
                            cpause->play();
                            Escenario::Instance()->playmusic();
                            Juego::Instance()->ponerEstadoEscenario();    
                        break;
                    }
                }
            }
        }
    }
}