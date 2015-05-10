/* 
 * File:   Escenario.h
 * Author: Ricardo
 *
 * Created on 15 de abril de 2015, 9:41
 */

#ifndef ESCENARIO_H
#define	ESCENARIO_H

#include "../headers/Juego.h"
#include "../headers/Aliadas.h"
#include "../headers/Enemigo.h"
#include "../headers/Escenario.h"
#include "../headers/Unidad.h"
#include "../headers/Estado.h"
#include "../headers/Mapa.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string>

//using namespace tinyxml2;
using namespace std;
using namespace sf;

class Escenario: public Estado{
public:
    
    static Escenario* Instance();
    /*
    void Pause();
    void Resume();
    */
    //void init();
    void input();
    
    void cambiaSpriteCursorMano();
    void cambiaSpriteCursorSeleccionar();
    void mostrarCuadriculaUnidad(int xx, int yy, int rangoUnidad, int color);
    void quitarCuadriculaUnidad(int xx, int yy, int rangoUnidad);
    bool hayunidad();
    void mostrarStats(int numUnidad, int tipo);
    void setEnemigo(Enemigo* malo);
    void empiezaturnoIA();
    void volverMenuAcciones();
    
protected:
    Escenario();
    ~Escenario();

private:
    static Escenario* pinstance;
    
    void init_State();
    void render_State();
    void update_State();
    
    sf::Texture* texturaCursor;
    sf::Texture* texturaMenuStats;
    sf::Sprite* spriteMenuStats;
    sf::Sprite* spriteCursor;
    sf::Clock* reloj;
    sf::Clock* relojCursor;
    sf::Clock* reloj2;
    sf::Event* evento;
    sf::Font* fuente;
    sf::Text* t_stats;
    
    Mapa* mapa;
    //Aliadas* unidadWena;
    
    int cursorActivo;
    int varCursor;
    int *unidad_sel;
    bool *turnoUsu;
    
    int turnoEnemigo;
    int fasesEnemigo;
    
    bool tieneQueMostrarStats;
        
    Aliadas** aliadas;//aray de unidades aliadas (posiblemente esten en mapa)
    Enemigo** enemigos;//array de unidades enemigas
    Cofre** cofres;
};

#endif	/* ESCENARIO_H */

