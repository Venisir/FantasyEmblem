/* 
 * File:   Cofre.cpp
 * Author: Constanza
 * 
 * Created on 24 de abril de 2015, 17:01
 */

#include "../headers/Cofre.h"
#include "../headers/Armas.h"
#include "../headers/Objetos.h"
#include "../headers/Juego.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace sf;

Cofre::Cofre() {
    
}

Cofre::Cofre(int posX, int posY, Armas* arma, Objetos* obj) {
    x = posX;
    y = posY;
    dropArma = arma;
    dropObjeto = obj;
    abierto = false;
    
    spriteCofre = new Sprite();
    texturaCofre = new Texture();
    
    string s = "niveles/Tilev1.png";
    
    if (!texturaCofre->loadFromFile(s))
    {
        std::cerr << "Error cargando la imagen textura de la unidad";
        exit(0);
    }
    
    spriteCofre->setTexture(*texturaCofre);
    spriteCofre->setTextureRect(IntRect(8*16, 0*16, 16, 16));
}

Cofre::~Cofre() {
}

Armas* Cofre::getArma(){
    return dropArma;
}

Objetos* Cofre::getObjeto(){
    return dropObjeto;
}

void Cofre::Draw(){
    Juego::Instance()->getVentana()->draw(*spriteCofre);
}

void Cofre::setPosition(int i, int j){
    spriteCofre->setPosition(i,j);
}

void Cofre::cambiaTexturaAbierto(){
    //cerr << "Le cambia la textura desde cofre.cpp" << endl;
    spriteCofre->setTextureRect(IntRect(8*16, 1*16, 16, 16));
    
}

int Cofre::getPosicionSpriteX() {
    return spriteCofre->getPosition().x;
}

int Cofre::getPosicionSpriteY() {
    return spriteCofre->getPosition().y;
}