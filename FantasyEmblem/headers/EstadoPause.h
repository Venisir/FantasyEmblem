/* 
 * File:   EstadoPause.h
 * Author: Alberto
 *
 * Created on 23 de abril de 2015, 16:41
 */

#ifndef ESTADOPAUSE_H
#define	ESTADOPAUSE_H

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

class EstadoPause: public Estado{
public:
    
    static EstadoPause* Instance();
    /*
    void Pause();
    void Resume();
    */
    //void init();
    void input();
        
protected:
    EstadoPause();
    ~EstadoPause();

private:
    static EstadoPause* pinstance;
    
    void init_State();
    void render_State();
    void update_State();
    
    sf::Font* fuente;
    sf::Text* t_textoPause;
    sf::Clock* reloj;
    sf::Event* evento;
};

#endif	/* ESTADOPAUSE_H */

