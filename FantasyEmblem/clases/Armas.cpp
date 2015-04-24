/* 
 * File:   Armas.cpp
 * Author: Ricardo
 * 
 * Created on 15 de abril de 2015, 9:42
 */

#include "../headers/Armas.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace sf;


Armas::Armas(string nom, string tip, int pes, int pod, int golp, int alcan, int usos ) {
    if(nom!=NULL && tip!=NULL){
        Nombre=nom;
        Tipo=tip;
    }
    Peso=pes;
    Poder=pod;
    Golpe=golp;
    Alcance=alcan;
    Usos=usos;
    
}


Armas::~Armas() {
}

Armas::getPeso(){
    return Peso;
}

Armas::getPoder(){
    return Poder;
}

Armas::getGolpe(){
    return Golpe;
}

Armas::getAlcance(){
    return Alcance;    
}

Armas::getUsos(){
    return Usos;
}

Armas::setUsos(int uso){
    Usos=Usos-uso;
}