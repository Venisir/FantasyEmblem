/* 
 * File:   EstadoObjetos.h
 * Author: Oliver Rull
 *
 * Created on 12 de mayo de 2015, 17:38
 */

#ifndef ESTADOOBJETOS_H
#define	ESTADOOBJETOS_H

#include "../headers/Juego.h"
#include "../headers/Aliadas.h"
#include "../headers/Enemigo.h"
#include "../headers/Escenario.h"
#include "../headers/Unidad.h"
#include "../headers/Estado.h"
#include "../headers/Mapa.h"
#include "../headers/EstadoBatall.h"
#include "../headers/Cofre.h"
#include "../headers/MenuAcciones.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string>

using namespace std;
using namespace sf;

class EstadoObjetos:public Estado {
public:
    static EstadoObjetos* Instance(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice,bool *turno,Objetos** obj, Armas** arm);
    static EstadoObjetos* Instance();
    void input();
    void mostrarItems();
    int getSeleccionada();
    void reset();
    
protected:
    EstadoObjetos();
    EstadoObjetos(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice,bool *turno,Objetos** obj, Armas** arm);
    ~EstadoObjetos();        
private:
    static EstadoObjetos* pinstance;
    void init_State();
    void render_State();
    void update_State();

     sf::Sprite *objeto1;
    sf::Sprite *objeto2;
    sf::Sprite *objeto3;
    //sf::Sprite *arma;
    sf::Font* fuente;
    sf::Texture *texturaMenu1;
    sf::Texture *texturaMenu;
    sf::Texture *texturaDedo;
    sf::Sprite *menu;
    sf::Sprite *menu1;
    sf::Sprite *cursorDedo;
    sf::Clock *reloj;
    sf::Clock *reloj2;
    sf::Event *evento;
    sf::Text** stats;
    sf::Text* stats1;
    int cont;
    bool cursorActivo;
    bool *turnoUsu;
    Mapa *m;//mapa proveniente del escenario 
    Aliadas **ali;//array de unidades aliadas proveniente del escenario
    Enemigo **enem;//array de unidades enemigas proveniete del escenario
    Cofre **cof;
    Objetos **objeto;
    Armas ** arma;
    int *index;//indice de la unidad aliada seleccionada
    int seleccionada;
    
    sf::Sprite** objetos;
};

#endif	