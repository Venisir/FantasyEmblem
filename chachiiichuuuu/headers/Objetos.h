/* 
 * File:   Objetos.h
 * Author: Ricardo
 *
 * Created on 15 de abril de 2015, 9:42
 */

#ifndef OBJETOS_H
#define	OBJETOS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace sf;

class Objetos {
public:
    Objetos();
    Objetos(const char* nom,const char* tip, int uso, int alcan, const char* descrip, bool cai, const char* fotico);
    virtual ~Objetos();
    
    const char* getNombre();
    void setNombre(const char* nom);
    Sprite getSprite();
    int getId();
    int getUsos();
    int getAlcance();
    const char* getTipo();
    void setUsos( int uso);
    
private:
    int id;
    const char* Nombre;
    const char* Tipo;
    int Usos;
    int Alcance;
    const char* Descripcion;
    bool Caido;
    const char* foto;
    sf::Texture* textObjeto;
    sf::Sprite* spriteObjeto;
    
};

#endif	/* OBJETOS_H */

