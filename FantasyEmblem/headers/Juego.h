/* 
 * File:   Juego.h
 * Author: Alberto, Ricardo
 *
 * Created on 15 de abril de 2015, 9:43
 */

#ifndef JUEGO_H
#define	JUEGO_H

#include "../headers/EstadoBatallaEnemigo.h"
#include "../headers/Escenario.h"
#include "../headers/MenuPrincipal.h"
#include "../headers/EstadoPause.h"
#include "../headers/Estado.h"
#include "../headers/Juego.h"
#include "../headers/Mapa.h"
#include "../headers/Aliadas.h"
#include "../headers/Enemigo.h"
#include "../headers/EstadoBatall.h"
#include "../headers/PantallaStart.h"
#include "../headers/EstadoConversacion.h"
#include "../headers/ObjetoSeleccionado.h"
#include "../headers/EstadoPer.h"
#include "../headers/EstadoSumarExp.h"
#include "../headers/GameOver.h"
#include "../headers/SubirNivel.h"

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
    void renderText();
    sf::View getView();
    void setView(sf::View v);
    
    void init();
    void render();
    void update();
    void input();
    
    void ponerEstadoMenuPrincipal();
    void ponerEstadoEscenario();
    void ponerEstadoPause();
    void ponerEstadoUnidadSeleccionada();
    void ponerEstadoMenuAcciones(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice, bool *turno, Objetos** obj, Armas** arm);
    void ponerEstadoBatalla(Aliadas* ali, Enemigo* ene);

    void ponerEstadoConversacion(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice, bool *turno, Objetos** obj, Armas** arm);
    void ponerEstadoPantallaInicio();
    void ponerEstadoObjetos(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice, bool *turno, Objetos** obj, Armas** arm);
    void ponerEstadoObjetosSeleccionado(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice, bool *turno, Objetos** obj, Armas** arm);
    void ponerEstadoPersonaje(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice, bool *turno, Aliadas* alis, Objetos** obj, Armas** arm);
    
    void ponerEstadoBatallaEnemigo(Aliadas* ali, Enemigo* ene);
    void ponerEstadoGameOver();
    void ponerEstadoSumaExp(Aliadas* ali, Enemigo* ene, int i);
    void ponerEstadoSubirNivel(Aliadas* ali, Enemigo* ene);
    
    void reiniciarEstadoEscenario();
    
protected:
    Juego();
    virtual ~Juego();
    
private:
    static Juego* pinstance;
    
    //Pila de estados
    vector<Estado*> states;
    
    RenderWindow* ventana;
    
    sf::Clock* reloj;
    sf::Clock* reloj_fps;
    sf::Font* fuente;
    sf::View view;
    
    float fps;
    float c_time;
};

#endif	/* JUEGO_H */

