/* 
 * File:   Enemigo.h
 * Author: Alberto
 *
 * Created on 25 de abril de 2015, 12:06
 */

#ifndef ENEMIGO_H
#define	ENEMIGO_H

#include "../headers/Unidad.h"
#include "../headers/Cofre.h"
#include "../headers/Armas.h"
#include "../headers/Objetos.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string>

using namespace std;
using namespace sf;

class Enemigo : public Unidad {
public:
    Enemigo();
    Enemigo(const char* name, const char* clas, int atributo[],int nivel, int rang, const char* nombreTextu,const char* textuBatalla,const char* textuevadir);
    ~Enemigo();
    
    //Aliadas* encontrarAliadoMasCercano(Aliadas** aliadas);
    //void moverseHaciaAliadoMasCercano(Aliadas* aliado);
    
private:
    Armas* arma;
};

#endif	/* ENEMIGO_H */

