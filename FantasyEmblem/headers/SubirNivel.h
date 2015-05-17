/* 
 * File:   SubirNivel.h
 * Author: Oliver Rull
 *
 * Created on 17 de mayo de 2015, 11:19
 */

#ifndef SUBIRNIVEL_H
#define	SUBIRNIVEL_H

#include "../headers/Juego.h"
#include "../headers/Escenario.h"
#include "../headers/EstadoSumarExp.h"
#include "../headers/Estado.h"
#include "../headers/EstadoBatall.h"
#include "../headers/Aliadas.h"
#include "../headers/Enemigo.h"
#include "../headers/Armas.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string>

using namespace std;
using namespace sf;

class SubirNivel: public Estado {
public:
    static SubirNivel* Instance(Aliadas* ali, Enemigo* ene);
    void input();
    
protected: 
    
    SubirNivel();
    SubirNivel(Aliadas* ali, Enemigo* ene);
    ~SubirNivel();
    
    
    static SubirNivel* pinstance;
    
    void init_State();
    void render_State();
    void update_State();
    void mostrarDats();
    
    
private:
    int contPer1i;
    int contPer1j;
    int contPer2i;
    int contPer2j;
    
    bool atacado;
    bool atacado2;
    bool turno2;
    bool reini;
    bool atacar2;
    int aux1;
    int aux2;
    int aux3;
    int aux4;
    int aux5;
    int aux6;
    int aux7;
    sf::Clock* reloj;
    sf::Event* evento;
    sf::Texture* fondoBata;
    sf::Sprite* batalla;
    sf::Texture* perso1;
    sf::Sprite* per1;
    sf::Texture* perso2;
    sf::Sprite* per2;
    sf::Texture* marco;
    sf::Texture* barra;
    sf::Sprite* marcoExp;
    sf::Sprite* barraExp;
    sf::Font* fuente;
    sf::Text* stats;
    sf::Text* stats2;
    sf::Text* stats4;
    sf::Text* stats3;
    sf::Text* clase;
    sf::Text* nombres;
    sf::Text* armas;
    sf::Text* vidas;
    sf::Text* exp2;
    sf::Texture* mas;
    sf::Sprite* mas1;
    sf::SoundBuffer* level;
    sf::Sound* level1;
    sf::SoundBuffer* up;
    sf::Sound* up1;
    Aliadas* alia; 
    Enemigo* enem;
    int exp;
    bool suma;
    int cont;
};


#endif	/* SUBIRNIVEL_H */

