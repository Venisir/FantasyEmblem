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
    Unidad();
    Unidad(const Unidad& orig);
    virtual ~Unidad();
    
    //METODOS SET
    void setHP(int hp);
    void setFuerza(int f);
    void setMagia(int m);
    void setHab(int h);
    void setVel(int v);
    void setDef(int d);
    void setDefm(int dm);
    void setExp();
    
    //METODOS GET
    int getHP();
    int getFuerza();
    int getMagia();
    int getHab();
    int getVel();
    int getDef();
    int getDefm();
    int getExp();
    
    
protected:
    //Nombre
    string nombre;
    //Clase
    string clase;
    //Arma
    Armas arma_actual;
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
    bool activo;
    
    
};

#endif	/* UNIDAD_H */

