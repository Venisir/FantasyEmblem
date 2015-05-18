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
#include "../headers/Armas.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string>

using namespace std;
using namespace sf;

class EstadoBatall: public Estado {
public:
    static EstadoBatall* Instance(Aliadas* ali, Enemigo* ene);
    void input();
    void paramusica();
    void playmusica();
    
protected: 
    
    EstadoBatall();
    EstadoBatall(Aliadas* ali, Enemigo* ene);
    ~EstadoBatall();
    
    
    static EstadoBatall* pinstance;
    
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

