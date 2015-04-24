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


Objetos::Objetos(string nom,string tip, int uso, int alcan, string descrip, bool cai) {
    Nombre=nom;
    Tipo=tip;
    Usos=uso;
    Alcance=alcan;
    Descripcion=descrip;
    Caido=cai;
}



Objetos::~Objetos() {
}

Objetos::getUsos(){
    return Usos;
}

Objetos::getAlcance(){
    return Alcance;
}

Objetos::setUsos(int us) {
    Usos=Usos-us;
}

Objetos::getTipo(){
    return Tipo;
}

Objetos::getId(){
    return id;
}