/* 
 * File:   EstadoSumarExp.h
 * Author: Oliver Rull
 *
 * Created on 16 de mayo de 2015, 17:11
 */

#ifndef ESTADOSUMAREXP_H
#define	ESTADOSUMAREXP_H


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

class EstadoSumarExp: public Estado {
public:
    static EstadoSumarExp* Instance(Aliadas* ali, Enemigo* ene, int i);
    void input();
    
protected: 
    
    EstadoSumarExp();
    EstadoSumarExp(Aliadas* ali, Enemigo* ene, int i);
    ~EstadoSumarExp();
    
    
    static EstadoSumarExp* pinstance;
    
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
    float aux;
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
    sf::Texture* marco;
    sf::Texture* barra;
    sf::Sprite* marcoExp;
    sf::Sprite* barraExp;
    sf::Font* fuente;
    sf::Text* stats;
    sf::Text* stats2;
    sf::Text* nombres;
    sf::Text* armas;
    sf::Text* vidas;
    sf::Text* exp2;
    Aliadas* alia; 
    Enemigo* enem;
    int exp;
    bool suma;
    int cont;
};

#endif	/* ESTADOBATALL_H */


