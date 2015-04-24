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
    virtual ~Objetos();
    
    int getUsos();
    int getAlcance();
    
    int setUsos();
    
private:
    
    string* Nombre;
    string* Tipo;
    int* Usos;
    int* Alcance;
    string* Descripcion;
    bool* Caido;
    
};

#endif	/* OBJETOS_H */

