/* 
 * File:   Unidad.h
 * Author: Beatriz
 *
 * Created on 15 de abril de 2015, 9:40
 */

#ifndef UNIDAD_H
#define	UNIDAD_H
#include "../headers/Armas.h"
#include "../headers/Objetos.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string>

using namespace std;

class Unidad {
public:
    Unidad(const char* name, const char* clas, int atributo[],int nivel, int rang, const char* nombreTextu);
    virtual ~Unidad();
    
    //METODOS SET
    void setHP(int);
    void setFuerza(int);
    void setMagia(int);
    void setHab(int);
    void setVel(int);
    void setDef(int);
    void setDefm(int);
    
    void cambiaSpriteQuieto();
    void setPosition(int i, int j);
    
    void moverArriba();
    void moverAbajo();
    void moverIzquierda();
    void moverDerecha();

    //METODOS GET
    int getHP();
    int getFuerza();
    int getMagia();
    int getHab();
    int getVel();
    int getDef();
    int getDefm();
    int getExp();
    
    int getPosicionCeldaX();
    int getPosicionCeldaY();
    
    int getPosicionSpriteX();
    int getPosicionSpriteY();
    
    void Draw();
    
    void verStats();
    
protected:
    //Nombre
    const char* nombre;
    //Clase
    const char* clase;
    //Arma
    Armas* arma_actual;
    //------------------------------Atributos-----------------------------------
    //Posicion 0 - Vida de la unidad
    //Posicion 1 - Fuerza 
    //Posicion 2 - Magia
    //Posicion 3 - Habilidad
    //Posicion 4 - Velocidad
    //Posicion 5 - Defensa
    //Posicion 6 - Defensa magica
    int atributos[7];
    //Nivel
    int lvl;
    //Movimiento de la unidad
    int rango;
    //Sprite de la unidad
    Sprite* spriteUnidad;
    Texture* texturaUnidad;
    
    int valorSprite;
    bool siguienteSumar;
    
    bool activo;
    
    
};

#endif	/* UNIDAD_H */

