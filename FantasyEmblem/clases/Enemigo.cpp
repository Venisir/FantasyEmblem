/* 
 * File:   Enemigo.cpp
 * Author: Alberto
 * 
 * Created on 25 de abril de 2015, 12:06
 */

#include "../headers/Enemigo.h"
#include "../headers/Armas.h"
#include "../headers/Objetos.h"
#include "../headers/Cofre.h"
#include "../headers/Unidad.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <string>
#include <cstring>

using namespace std;
using namespace sf;

Enemigo::Enemigo(const char* name, const char* clas, int atributo[],int nivel, int rang, const char* nombreTextu,const char* textuBatalla,const char* textuevadir):Unidad(name, clas, atributo, nivel, rang, nombreTextu, textuBatalla,textuevadir) {

}

Enemigo::~Enemigo() {
}

//borra el ultimo moviemitno que corresponde a la posicion del objetivo
void Enemigo::borraultimo() {
    int *aux= new int[movs.size()-2];
    
    for(int i=0;i<movs.size()-2;i++)
    {
        aux[i]=movimientos[i];
        //cerr << aux[i] << endl;
        //cerr << movs.at(i) << endl;
    }
    
    movimientos=aux;
}

/*
Aliadas* Enemigo::encontrarAliadoMasCercano(Aliadas** aliadas){
    
    int posAliX;
    int posAliY;
    
    int aux = 0;
    
    for(int i=0; i<1; i++){
        posAliX = aliadas[i]->getPosicionCeldaX();
        posAliY = aliadas[i]->getPosicionCeldaY();
        
        
        //Calculo del mas cercano con estrella
    }
    
    return aliadas[aux];
}

void Enemigo::moverseHaciaAliadoMasCercano(Aliadas* aliado){
    
    
}
*/
