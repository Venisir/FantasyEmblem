
#ifndef CELDA_H
#define	CELDA_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
class Celda {
public:
    Celda();
    Celda(sf::Vector2i pos,int g,int f, int h,Celda* father);
    Celda(sf::Vector2i pos,int g,int f, int h);
    ~Celda();
    Celda* getPadre();
    int getG();
    int getF();
    int getH();
    sf::Vector2i getCoordenadas();
    void setPadre(Celda* father);
    void setG(int x);
    void setF(int x);
    void setH(int x);
    void setCoordenadas(int x,int y);
    
private:
    sf::Vector2i coordenadas;
    int g;
    int h;
    int f;
    Celda* padre;    
};

#endif	/* CELDA_H */

