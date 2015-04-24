/* 
 * File:   Enemigos.h
 * Author: Constanza
 *
 * Created on 24 de abril de 2015, 15:22
 */

#ifndef ENEMIGOS_H
#define	ENEMIGOS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string>

using namespace std;
using namespace sf;

class Enemigos:public Unidad{
public:
    Enemigos();
    Enemigos(const Enemigos& orig);
    virtual ~Enemigos();
    
private:
    int experiencia_dada;
    Objetos drop;
};

#endif	/* ENEMIGOS_H */

