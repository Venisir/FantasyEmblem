/* 
 * File:   Creditos.h
 * Author: Oliver Rull
 *
 * Created on 19 de mayo de 2015, 19:21
 */

#ifndef CREDITOS_H
#define	CREDITOS_H

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

class Creditos: public Estado{
public:
    
    static Creditos* Instance();
    void input();
        
protected:
    Creditos();
    ~Creditos();

private:
    static Creditos* pinstance;
    
    void init_State();
    void render_State();
    void update_State();
    
    sf::Font* fuente;
    sf::Text* t_textoPause;
    sf::Text* t_textoPause2;
    sf::Text* t_textoPause3;
    sf::Text* t_textoPause4;
    sf::Clock* reloj;
    sf::Event* evento;
    sf::Texture* per1;
    sf::Sprite* sprite1;
    sf::Texture* per2;
    sf::Sprite* sprite2;
    sf::Texture* per3;
    sf::Sprite* sprite3;
    sf::Texture* per4;
    sf::Sprite* sprite4;
    int cont;
    int cont1i;
    int cont1j;
    int cont2i;
    int cont2j;
    int cont3i;
    int cont3j;
    int cont4i;
    int cont4j;
    sf::SoundBuffer* pause_close;
    sf::Sound* cpause;
    
    sf::Time time1;
};

#endif	/* ESTADOPAUSE_H */

