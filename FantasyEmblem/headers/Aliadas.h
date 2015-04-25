/* 
 * File:   Aliadas.h
 * Author: Constanza
 *
 * Created on 24 de abril de 2015, 15:22
 */

#ifndef ALIADAS_H
#define	ALIADAS_H

#include "../headers/Unidad.h"
#include "../headers/Cofre.h"
#include "../headers/Armas.h"
#include "../headers/Objetos.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string>

using namespace std;
using namespace sf;

class Aliadas : public Unidad {
public:
    Aliadas(const char* name, const char* clas, int atributo[],int nivel, int rang, const char* nombreTextu, int experien);
    virtual ~Aliadas();    
    
    void subirNivel();
    
    void guardamovimiento(int n);
    void recorre();
    
    bool usarObjeto(Objetos* obj);
    bool abrirCofre(Cofre* cofre);
    bool equiparArma(Armas* arma);
    
private:
    int experiencia;
    Objetos* inventarioObjetos[3];
    Armas* inventarioArmas[3];
    
    int* recorrido;
    int ultimo_mov;//ultimo paso hecho
    int pasos;//contador de los pasos realizados
    
};

#endif	/* ALIADAS_H */

