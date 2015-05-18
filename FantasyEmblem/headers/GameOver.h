/* 
 * File:   GameOver.h
 * Author: Oliver Rull
 *
 * Created on 17 de mayo de 2015, 10:09
 */

#ifndef GAMEOVER_H
#define	GAMEOVER_H

#include "../headers/Juego.h"
#include "../headers/Escenario.h"
#include "../headers/Estado.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string>

//using namespace tinyxml2;
using namespace std;
using namespace sf;

class GameOver: public Estado{
public:
    
    static GameOver* Instance();
    void input();
    void pararmusica();
    
protected:
    GameOver();
    ~GameOver();

private:
    static GameOver* pinstance;
    
    void init_State();
    void render_State();
    void update_State();
    
    int aux;
    
    sf::Clock* reloj;
    sf::Event* evento;
    sf::Texture* fondo;
    sf::Texture* boto;
    sf::Sprite* intro;
    sf::Sprite* start;
    
    sf::SoundBuffer* mainmenu;
    sf::SoundBuffer* mmselect;
    sf::Sound* menusonido;
    sf::Sound* select;

};


#endif	/* GAMEOVER_H */

