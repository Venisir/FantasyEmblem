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
    
}

void Juego::init(){
    //sta->setEstado(0);
}

void Juego::update(){
    states.back()->update();
}

void Juego::render(){
    states.back()->render();
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