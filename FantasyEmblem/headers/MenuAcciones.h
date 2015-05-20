/* 
 * File:   MenuAcciones.h
 * Author: Ricardo
 *
 * Created on 26 de abril de 2015, 12:12
 */

#ifndef MENUACCIONES_H
#define	MENUACCIONES_H

#include "../headers/Juego.h"
#include "../headers/Aliadas.h"
#include "../headers/Enemigo.h"
#include "../headers/Escenario.h"
#include "../headers/Unidad.h"
#include "../headers/Estado.h"
#include "../headers/Mapa.h"
#include "../headers/EstadoBatall.h"
#include "../headers/Cofre.h"
#include "../headers/EstadoObjetos.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string>

class MenuAcciones:public Estado {
public:
    static MenuAcciones* Instance(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice,bool *turno,Objetos** obj, Armas** arm);
    static MenuAcciones* Instance();
    void input();
    void seleccionarMenu();
    
    void teclaArriba();
    void teclaDerecha();
    void teclaIzquierda();
    void teclaAbajo();
    void teclaIntro();
    void reset();
    
protected:
    MenuAcciones();
    MenuAcciones(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice,bool *turno,Objetos** obj, Armas** arm);
    ~MenuAcciones();        
private:
    static MenuAcciones* pinstance;
    void init_State();
    void render_State();
    void update_State();
    
    sf::Texture *texturaMenuNormal;
    sf::Texture *texturaMenuAtaque;
    sf::Texture *texturaMenuCofre;
    sf::Texture *texturaMenuPuerta;
    sf::Texture *texturaDedo;
    sf::Texture *texturaDanyo;
    sf::Texture *texturaObjetos;
    sf::Texture *texturaTurnoEnemigo;
    sf::Sprite *turnoEnemigo;
    sf::Sprite *menu;
    sf::Sprite *cursorDedo;
    sf::Sprite *danyo;
    sf::Sprite *objetos;
    sf::Clock *reloj;
    sf::Clock *reloj2;
    sf::Clock *reloj3;
    sf::Event *evento;
    int cont;
    bool cursorActivo;
    bool *turnoUsu;
    //bool haAtacado;
    int renderAviso;
    Mapa *m;//mapa proveniente del escenario 
    Aliadas **ali;//array de unidades aliadas proveniente del escenario
    Enemigo **enem;//array de unidades enemigas proveniete del escenario
    Cofre **cof;
    Objetos **objeto;
    Armas **arma;
    int *index;//indice de la unidad aliada seleccionada
    int numMenu;//numero de menu que tiene, si tiene el de abrirpuerta, el de abrircofre, el de atacar...
    sf::SoundBuffer* mcursor;
    sf::Sound* cursor;
    
    bool dibujaTurnoEnemigo;
};

#endif	/* MENUACCIONES_H */

