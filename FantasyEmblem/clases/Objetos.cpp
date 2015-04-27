/* 
 * File:   Objetos.cpp
 * Author: Ricardo
 * 
 * Created on 15 de abril de 2015, 9:42
 */

#include "../headers/Objetos.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace sf;

Objetos::Objetos(){
    
}

Objetos::Objetos(const char* nom,const char* tip, int uso, int alcan, const char* descrip, bool cai) {
    Nombre=nom;
    Tipo=tip;
    Usos=uso;
    Alcance=alcan;
    Descripcion=descrip;
    Caido=cai;
}

Objetos::~Objetos() {
}

int Objetos::getUsos(){
    return Usos;
}

int Objetos::getAlcance(){
    return Alcance;
}

void Objetos::setUsos(int us) {
    Usos=Usos-us;
}

const char* Objetos::getTipo(){
    return Tipo;
}

int Objetos::getId(){
    return id;
}
