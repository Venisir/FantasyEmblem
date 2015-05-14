/* 
 * File:   Celda.cpp
 * Author: Ricardo
 * 
 * Created on 11 de mayo de 2015, 18:31
 */

#include "../headers/Celda.h"

Celda::Celda() {
}

Celda::Celda(sf::Vector2i pos,int g,int f,int h, Celda*  father)
{
    coordenadas=pos;
    this->g=g;
    this->f=f;
    this->h=h;
    padre=father;
}

Celda::~Celda() {
}

Celda::Celda(sf::Vector2i pos, int g, int f, int h) 
{
    coordenadas=pos;
    this->f=f;
    this->g=g;
    this->h=h;
    padre=NULL;
}


int Celda::getF()
{
    return f;
}

int Celda::getG()
{
    return g;
}

int Celda::getH() 
{
    return h;
}

sf::Vector2i Celda::getCoordenadas() 
{
    return coordenadas;
}

Celda* Celda::getPadre() 
{
    return padre;
}

void Celda::setCoordenadas(int x, int y) 
{
    coordenadas.x=x;
    coordenadas.y=y;
}

void Celda::setF(int x) 
{
    f=x;
}

void Celda::setG(int x) 
{
    g=x;
}

void Celda::setH(int x) 
{
    h=x;
}

void Celda::setPadre(Celda* father) 
{
    padre=father;
}











