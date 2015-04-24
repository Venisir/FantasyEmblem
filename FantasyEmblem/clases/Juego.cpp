/* 
 * File:   Juego.cpp
 * Author: Alberto, Ricardo
 * 
 * Created on 15 de abril de 2015, 9:43
 */
#include "../headers/Escenario.h"
#include "../headers/MenuPrincipal.h"
#include "../headers/EstadoPause.h"
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

Juego* Juego::pinstance = 0;

Juego* Juego::Instance () {
    if(pinstance == 0){ //¿Es la primera llamada?
        //pinstance = new Juego; //Creamos la instancia
        pinstance = new Juego(); //Creamos la instancia
    }
    return pinstance; //Retornamos la direccion de la instancia
}

Juego::Juego() {
    //Realizar inicializaciones necesarias de la instancia
    
    reloj = new sf::Clock();
    reloj_fps = new sf::Clock();
    fuente = new sf::Font();
    fuente->loadFromFile("resources/font.ttf");
    
    ponerEstadoMenuPrincipal();
    
    //ponerEstadoEscenario();
}
/*
Juego::Juego(const Juego& orig) {
}
*/

Juego::~Juego() {
    /*if(pinstance != NULL)*/ 
    delete pinstance;
    delete reloj;
    delete reloj_fps;
    delete fuente;
}

void Juego::init(){
    //sta->setEstado(0);
}

void Juego::update(){
    
    if (reloj->getElapsedTime().asMilliseconds() >= 100) {
        reloj->restart();
        states.back()->update();
    }
    
}

void Juego::render(){
    
    c_time = reloj_fps->restart().asSeconds();
    fps = (float) 1 / c_time;
    
    states.back()->render();
   
}

void Juego::renderText() {
    
    std::stringstream ss_fps;
    ss_fps << "FPS: "<<fps;
    std::string s_fps = ss_fps.str();
    sf::Text t_fps(s_fps,*fuente,12);
    
    t_fps.setColor(sf::Color::Black);
    
    t_fps.setPosition(0,0);
    
    ventana->draw(t_fps);
}

RenderWindow* Juego::getVentana(){
    return ventana;
}

void Juego::setVentana(RenderWindow* v){
    ventana = v;
}

void Juego::ponerEstadoMenuPrincipal(){
    states.push_back(MenuPrincipal::Instance());
    //states.back()->init();
}

void Juego::ponerEstadoEscenario(){
    states.push_back(Escenario::Instance());
    //states.back()->init();
}

void Juego::ponerEstadoPause(){
    states.push_back(EstadoPause::Instance());
    //states.back()->init();
}


/*
void Juego::input() 
{
	// let the state handle events
	states.back()->HandleEvents(this);
}

void Juego::update() 
{
	// let the state update the game
	states.back()->Update(this);
}

void Juego::render() 
{
	// let the state draw the screen
	states.back()->Render(this);
}
*/