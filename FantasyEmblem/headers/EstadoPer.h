/* 
 * File:   EstadoPer.h
 * Author: Oliver Rull
 *
 * Created on 13 de mayo de 2015, 9:31
 */

#ifndef ESTADOPER_H
#define	ESTADOPER_H

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
#include "../headers/EstadoObjetos.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string>

using namespace std;
using namespace sf;

class EstadoPer:public Estado {
public:
    static EstadoPer* Instance(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice,bool *turno);
    void input();
    void mostrarDatos();
    void mostrarStats();
    
protected:
    EstadoPer();
    EstadoPer(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice,bool *turno);
    ~EstadoPer();        
private:
    static EstadoPer* pinstance;
    void init_State();
    void render_State();
    void update_State();
    
    sf::Texture *texturaMenu;
    sf::Font* fuente;
    sf::Text* t_stats;
    sf::Text* level;
    sf::Text* vida;
    sf::Text* clase;
    sf::Text* stats;
    sf::Text* stats1;

    sf::Sprite *menu;
    sf::Clock *reloj;
    sf::Clock *reloj2;
    sf::Event *evento;
    int cont;
    bool *turnoUsu;
    Mapa *m;//mapa proveniente del escenario 
    Aliadas **ali;//array de unidades aliadas proveniente del escenario
    Enemigo **enem;//array de unidades enemigas proveniete del escenario
    Cofre **cof;
    int *index;//indice de la unidad aliada seleccionada
};

#endif	



