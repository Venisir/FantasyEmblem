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

Objetos::Objetos(const char* nom,const char* tip, int uso, int alcan, const char* descrip, bool cai, const char* fotico) {
    Nombre=nom;
    Tipo=tip;
    Usos=uso;
    Alcance=alcan;
    Descripcion=descrip;
    Caido=cai;
    foto=fotico;
            
    spriteObjeto= new Sprite();
    textObjeto= new Texture();
            
    string s1 = string(fotico);
    string s = "resources/"+s1;
    
    if (!textObjeto->loadFromFile(s))
    {
        std::cerr << "Error cargando la imagen textura del arma";
        exit(0);
    }
    
    spriteObjeto->setTexture(*textObjeto);
}

Objetos::~Objetos() {
    
    delete spriteObjeto;
    delete textObjeto;
    delete Nombre;
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

const char* Objetos::getNombre(){
    return Nombre;
}

void Objetos::setNombre(const char* nom){
    Nombre = nom;
}
Sprite Objetos::getSprite(){
    return *spriteObjeto;
}