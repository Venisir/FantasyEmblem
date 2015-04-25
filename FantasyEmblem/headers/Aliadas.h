/* 
 * File:   Aliadas.h
 * Author: Constanza
 *
 * Created on 24 de abril de 2015, 15:22
 */

#ifndef ALIADAS_H
#define	ALIADAS_H

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

class Aliadas : public Unidad {
public:
    Aliadas(const char* name, const char* clas, int atributo[],int nivel, int rang, const char* nombreTextu, int experien);
    virtual ~Aliadas();    
    //bool usarObjeto(Objetos obj);
    void subirNivel();
    //bool abrirCofre(Cofre cofre);
    
private:
    int experiencia;
    //Objetos* inventarioObjetos[3];
    Armas* inventarioArmas[3];
    
};

#endif	/* ALIADAS_H */

