/* 
 * File:   Cofre.h
 * Author: Constanza
 *
 * Created on 24 de abril de 2015, 17:01
 */

#ifndef COFRE_H
#define	COFRE_H

#include "../headers/Armas.h"
#include "../headers/Objetos.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string>

using namespace std;
using namespace sf;

class Cofre {
public:
    Cofre();
    Cofre(int posX, int posY, Armas* arma, Objetos* obj);
    virtual ~Cofre(); 
    Armas* getArma();
    Objetos* getObjeto();
    void Draw();
    void setPosition(int i, int j);
    void cambiaTexturaAbierto();
    
    int getPosicionSpriteX();
    int getPosicionSpriteY();
    
private:
    int x;
    int y;
    bool abierto;
    Armas* dropArma;
    Objetos* dropObjeto;
    
    Sprite* spriteCofre;
    Texture* texturaCofre;
};

#endif	/* COFRE_H */

