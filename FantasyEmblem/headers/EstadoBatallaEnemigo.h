/* 
 * File:   EstadoBatallaEnemigo.h
 * Author: Oliver Rull
 *
 * Created on 16 de mayo de 2015, 16:47
 */

#ifndef ESTADOBATALLAENEMIGO_H
#define	ESTADOBATALLAENEMIGO_H

#include "../headers/Juego.h"
#include "../headers/Escenario.h"
#include "../headers/Estado.h"
//#include "../headers/EstadoBatall.h"
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

class EstadoBatallaEnemigo: public Estado {
public:
    static EstadoBatallaEnemigo* Instance(Aliadas* ali, Enemigo* ene);
    void input();
    
protected: 
    
    EstadoBatallaEnemigo();
    EstadoBatallaEnemigo(Aliadas* ali, Enemigo* ene);
    ~EstadoBatallaEnemigo();
    
    
    static EstadoBatallaEnemigo* pinstance;
    
    void init_State();
    void render_State();
    void update_State();
    void mostrarDats();
    
    
private:
    int contPer1i;
    int contPer1j;
    int contPer2i;
    int contPer2j;
    int contPer2evai;
    int contPer2evaj;
    bool eva1;
    bool eva2;
    bool atacado;
    bool atacado2;
    bool turno2;
    bool reini;
    bool atacar2;
    int aux;
    int aux2;
    int aux3;
    sf::Clock* reloj;
    sf::Event* evento;
    sf::Texture* fondoBata;
    sf::Sprite* batalla;
    sf::Texture* perso1;
    sf::Sprite* per1;
    sf::Texture* perso2;
    sf::Sprite* per2;
    sf::Sprite* per1eva;
    sf::Sprite* per2eva;
    sf::Font* fuente;
    sf::Text* stats;
    sf::Text* stats2;
    sf::Text* nombres;
    sf::Text* armas;
    sf::Text* vidas;
    sf::SoundBuffer* batasonido;
    sf::Sound* batasonido1;
    Aliadas* alia; 
    Enemigo* enem;
};

#endif	/* ESTADOBATALL_H */

