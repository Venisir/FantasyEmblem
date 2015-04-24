/* 
 * File:   Cofre.cpp
 * Author: Constanza
 * 
 * Created on 24 de abril de 2015, 17:01
 */

#include "../headers/Cofre.h"

Cofre::Cofre(int posX, int posY, Armas arma, Objetos obj) {
    x = posX;
    y = posY;
    dropArma = arma;
    dropObjeto = obj;
    abierto = false;
}

Cofre::Cofre(const Cofre& orig) {
}

Cofre::~Cofre() {
}

Cofre::getArma(){
    return dropArma;
}

Cofre::getObjeto(){
    return dropObjeto;
}

