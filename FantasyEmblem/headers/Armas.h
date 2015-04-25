/* 
 * File:   Armas.h
 * Author: Ricardo
 *
 * Created on 15 de abril de 2015, 9:42
 */

#ifndef ARMAS_H
#define	ARMAS_H

//#include "../headers/Unidad.h"
//#include "../headers/Aliadas.h"
#include "../headers/Cofre.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace sf;


class Armas {
public:
    
    Armas(const char* nom, const char* tip, int pes, int pod, int golp, int alcan, int usos);
    virtual ~Armas();
    
    const char* getNombre();
    const char* getTipo();
    int getPeso();
    int getPoder();
    int getGolpe();
    int getAlcance();
    int getUsos();
    
    void setUsos(int uso);
    
private:

    
    const char* Nombre;
    const char* Tipo;
    int Peso;
    int Poder;
    int Golpe;
    int Alcance;
    int Usos;
    
    
};

#endif	/* ARMAS_H */

