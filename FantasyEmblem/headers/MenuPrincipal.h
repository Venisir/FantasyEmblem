/* 
 * File:   MenuPrincipal.h
 * Author: Constanza y Andrea
 *
 * Created on 25 de marzo de 2015, 9:57
 */

#ifndef MENUPRINCIPAL_H
#define	MENUPRINCIPAL_H

#include "../headers/Juego.h"
#include "../headers/Escenario.h"
#include "../headers/Estado.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string>

using namespace std;
using namespace sf;

#define MAX_NUM_SPRITE 3
#define MAX_NUM_TEXT 3

class MenuPrincipal: public Estado{
public:
    
    static MenuPrincipal* Instance();
    void input();
    
    void cambiaSpriteCursorMano();
    void cambiaSpriteCursorSeleccionar();
    
    void MoveUp();
    void MoveDown();
    void Intro();
    void Exit();
    int getSelectedItemIndex();
    
protected:
    MenuPrincipal();
    ~MenuPrincipal();        
private:    
    
    static MenuPrincipal* pinstance;
    
    void init_State();
    void render_State();
    void update_State();
    
    int selectedItemIndex;
    
    sf::Texture* fondo_menu;
    sf::Texture* botn1;
    sf::Texture* botn2;
    sf::Texture* botn3;
    sf::Texture* texturas[MAX_NUM_TEXT];
    sf::Texture* textura_fond;
    sf::Sprite* menu[MAX_NUM_SPRITE];
    sf::Sprite* fondo;
    sf::Time time1;
    sf::SoundBuffer* mainmenu;
    sf::SoundBuffer* mmcursor;
    sf::SoundBuffer* mmselect;
    sf::Sound* menusonido;
    sf::Sound* cursor;
    sf::Sound* select;
    
    sf::Clock* reloj;
    sf::Event* evento;
};

#endif	/* MENUPRINCIPAL_H */
