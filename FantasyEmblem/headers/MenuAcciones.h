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

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string>


class MenuAcciones:public Estado {
public:
    static MenuAcciones* Instance();
    void input();
    
protected:
    MenuAcciones();
    //MenuAcciones(Mapa* map, Aliadas* al, Enemigo* ene, int indice);
    ~MenuAcciones();        
private:
    static MenuAcciones* pinstance;
    void init_state();
    void render_state();
    void update_state();
    
    
    sf::Texture *texturaMenu;
    sf::Texture *texturaDedo;
    sf::Texture *texturaDanyo;
    sf::Texture *texturaObjetos;
    sf::Sprite *menu;
    sf::Sprite *cursorDedo;
    sf::Sprite *danyo;
    sf::Sprite *objetos;
    sf::Clock *reloj;
    sf::Event *evento;
    Mapa* m;//mapa proveniente del escenario 
    Aliadas* ali;//array de unidades aliadas proveniente del escenario
    Enemigo* enem;//array de unidades enemigas proveniete del escenario
    int index;//indice de la unidad aliada seleccionada  
};

#endif	/* MENUACCIONES_H */

