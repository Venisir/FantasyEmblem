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
#include "../headers/Celda.h"
#include <vector>

#include <iostream>
#include <SFML/Graphics.hpp>

#include <stdio.h>
#include <string>

using namespace std;
using namespace sf;

class Unidad {
public:
    Unidad();
    Unidad(const char* name, const char* clas, int atributo[],int nivel, int rang, const char* nombreTextu, const char* textBatalla);
    ~Unidad();
    
    //METODOS SET
    void setHP(int);
    void setFuerza(int);
    void setMagia(int);
    void setHab(int);
    void setVel(int);
    void setDef(int);
    void setDefm(int);
    
    void cambiaSpriteQuieto();
    void cambiaSprite(int a, int b, int c, int d);
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
    int getRango();
    int getLvl();
    const char* getClase();
    const char* getNombre();

    int getPosicionCeldaX();
    int getPosicionCeldaY();
    
    int getPosicionSpriteX();
    int getPosicionSpriteY();
    
    Sprite getSprite();
    Sprite getSpriteBatalla();
    
    void setPV(int);

    Armas* getArma();
    int getPV();
    
    bool getMueve();
    void setMueve(bool b);
    
    int VelocidadAtaque();
    int Evadir();
    int danyoPropio(Unidad* uni);
    int bonoArmaDanyo(Unidad* uni);
    int bonoArmaGolpe(Unidad* uni);
    int TotalDanyo(Unidad* uni);
    int PosiGolpear(Unidad* uni);
    int PosiGolpearTotal(Unidad* uni);
    int GolpesDoble(Unidad* uni);
    void Atacar(Unidad* uni);

    void Draw();
    void verStats();
    
    void haLlegado();
    bool verSiHaLlegado();
    
    void setHaJugado(bool b);
    bool getHaJugado();
    
    int getDestinoX();
    int getDestinoY();
    
    int* getMovimientos();
    void MovstoInt();
    
    void recorridoA(int destinox, int destinoy);//estrella
    void muestraMovs();
    
    
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
    Sprite* spriteBatalla;
    Texture* textBatalla;
    
    int valorSprite;
    bool siguienteSumar;
    
    bool activo;
    bool mueve;
    int PVactual;
    
    int destinoX;
    int destinoY;
    int direccionDestino;
    
    bool haJugado;
    
    int* movimientos;
    
    vector<Celda*> movs;
    
};

#endif	/* UNIDAD_H */

