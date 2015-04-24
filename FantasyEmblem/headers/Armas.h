/* 
 * File:   Armas.h
 * Author: Ricardo
 *
 * Created on 15 de abril de 2015, 9:42
 */

#ifndef ARMAS_H
#define	ARMAS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace sf;


class Armas {
public:
    
    Armas();
    virtual ~Armas();
    
    int getPeso();
    int getPoder();
    int getGolpe();
    int getAlcance();
    int getUsos();
    
    int setUsos();
private:

    
    string* Nombre;
    string* Tipo;
    int* Peso;
    int* Poder;
    int* Golpe;
    int* Alcance;
    int* Usos;
    
    
};

#endif	/* ARMAS_H */

