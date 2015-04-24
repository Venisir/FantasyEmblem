/* 
 * File:   Aliadas.cpp
 * Author: Constanza
 * 
 * Created on 24 de abril de 2015, 15:22
 */

#include "../headers/Aliadas.h"

Aliadas::Aliadas() {
}

Aliadas::Aliadas(const Aliadas& orig) {
}

Aliadas::~Aliadas() {
}

bool Aliadas::equiparArma(Armas arma){
    bool equipada = false;
    if(arma!=NULL){
        arma_actual = arma;
    }
    return equipada;
}

bool Aliadas::usarObjeto(Objetos obj){
    bool usada = false; 
    //recorrer inventario y buscar obj
    for(int i=0;i<inventarioObjetos;i++){
        if(inventarioObjetos[i] == obj){
            obj.~Objetos();
            inventarioObjetos[i] = NULL;
        }
    }
    
    return usada;
}

