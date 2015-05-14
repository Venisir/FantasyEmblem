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
    Aliadas(const char* name, const char* clas, int atributo[],int nivel, int rang, const char* nombreTextu, int experien);
    virtual ~Aliadas();    
     
    void subirNivel();
     
    void guardamovimiento(int n);
    void recorre();
    int* getRecorrido();
    Armas** getArmas();
    Objetos** getObjetos();
    bool usarObjeto(Objetos* obj);
    bool abrirCofre(Cofre* cofre);
    bool equiparArma(Armas* arma);
    void abrirPuerta(Mapa* mapa);
    int getExp();
    void hayPuerta(Mapa* mapa);
     
private:
    int experiencia;
    Objetos* inventarioObjetos[3];
    Armas* inventarioArmas[3];
     
    int* recorrido;
    int ultimo_mov;//ultimo paso hecho
    int pasos;//contador de los pasos realizados
    Sprite* spriteCofreAbierto;
    Texture* texturaCofreAbierto;
    Sprite *spriteAvisoInventArmas, *spriteAvisoInventObjetos, *spriteAvisoLlaveCofre, *spriteAvisoLlavePuerta;
    Texture *texturaAvisoInventarioArmas, *texturaAvisoInventarioObjetos,*texturaAvisoLlaveCofre,*texturaAvisoLlavePuerta;
};
 
#endif  /* ALIADAS_H */
