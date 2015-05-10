/* 
 * File:   PantallaStart.h
 * Author: Oliver Rull
 *
 * Created on 10 de mayo de 2015, 20:14
 */

#ifndef PANTALLASTART_H
#define	PANTALLASTART_H
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

class PantallaStart: public Estado{
public:
    
    static PantallaStart* Instance();
    /*
    void Pause();
    void Resume();
    */
    //void init();
    void input();
        
protected:
    PantallaStart();
    ~PantallaStart();

private:
    static PantallaStart* pinstance;
    
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

#endif	/* ESTADOPAUSE_H */

