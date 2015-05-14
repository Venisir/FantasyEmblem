/* 
 * File:   EstadoBatall.h
 * Author: Oliver Rull
 *
 * Created on 27 de abril de 2015, 17:15
 */

#ifndef ESTADOBATALL_H
#define	ESTADOBATALL_H

#include "../headers/Juego.h"
#include "../headers/Escenario.h"
#include "../headers/Estado.h"
#include "../headers/EstadoBatall.h"
#include "../headers/Aliadas.h"
#include "../headers/Enemigo.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string>

using namespace std;
using namespace sf;

class EstadoBatall: public Estado {
public:
    static EstadoBatall* Instance();
    void input();
    
protected: 
    
    EstadoBatall();
    ~EstadoBatall();
    
    
    static EstadoBatall* pinstance;
    
    void init_State();
    void render_State();
    void update_State();
    
    
    
private:
    int contPer1i;
    int contPer1j;
    
    sf::Clock* reloj;
    sf::Event* evento;
    sf::Texture* fondoBata;
    sf::Sprite* batalla;
    sf::Texture* perso1;
    sf::Sprite* per1;
    sf::Texture* perso2;
    sf::Sprite* per2;
};

#endif	/* ESTADOBATALL_H */

