/* 
 * File:   Aliadas.h
 * Author: Constanza
 *
 * Created on 24 de abril de 2015, 15:22
 */
 
#ifndef ALIADAS_H
#define ALIADAS_H
 
#include "../headers/Unidad.h"
#include "../headers/Cofre.h"
#include "../headers/Armas.h"
#include "../headers/Objetos.h"
#include "../headers/Mapa.h"
 
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string>
 
using namespace std;
using namespace sf;
 
class Aliadas : public Unidad {
public:
    Aliadas();
    Aliadas(const char* name, const char* clas, int atributo[],int nivel, int rang, const char* nombreTextu,const char* textuBatalla , int experien);
    virtual ~Aliadas();    
     
    void subirNivel();
     
    void guardamovimiento(int n);
    void recorre();
    int* getRecorrido();
    Armas** getArmas();
    Objetos** getObjetos();
    Sprite* dameQuePinte();
    bool usarObjeto(Objetos* obj);
    bool abrirCofre(Cofre* cofre);
    bool equiparArma(Armas* arma);
    bool abrirPuerta(Mapa* mapa);
    
    int getExp();
    
    bool hayCofre(Mapa* mapa);
    bool hayPuerta(Mapa* mapa);
    
    int hayEnemigosCercanos(Enemigo** enemigos);
    int hayCofresCercanos(Mapa* m);
    int hayPuertasCercanas(Mapa* m);
     
private:
    int experiencia;
    Objetos** inventarioObjetos;
    Armas** inventarioArmas;
    
    int* recorrido;
    int ultimo_mov;//ultimo paso hecho
    int pasos;//contador de los pasos realizados
    Sprite *spriteAviso;
    Texture *texturaAvisoInventarioArmas, *texturaAvisoInventarioObjetos,*texturaAvisoLlaveCofre,*texturaAvisoLlavePuerta;
};
 
#endif  /* ALIADAS_H */
