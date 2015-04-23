/* 
 * File:   Juego.h
 * Author: Alberto, Ricardo
 *
 * Created on 15 de abril de 2015, 9:43
 */

#ifndef JUEGO_H
#define	JUEGO_H

#include "../headers/Escenario.h"
#include "../headers/Estado.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string>
#include <vector>

//using namespace tinyxml2;
using namespace std;
using namespace sf;

class Juego {
    
public:
    static Juego* Instance();
    
    RenderWindow* getVentana();
    void setVentana(RenderWindow* v);
    
    void init();
    void render();
    void update();
    void input();
    
    void ponerEstadoMenuPrincipal();
    void ponerEstadoEscenario();
    void ponerEstadoPause();
    
protected:
    Juego();
    virtual ~Juego();
    
private:
    static Juego* pinstance;
    
    //Pila de estados
    
    vector<Estado*> states;
    
    RenderWindow* ventana;
    
};

#endif	/* JUEGO_H */

