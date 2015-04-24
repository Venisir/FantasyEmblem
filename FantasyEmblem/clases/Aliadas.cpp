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
    if(arma!= NULL){
        arma_actual = arma;
        equipada = true;
    }
    return equipada;
}

bool Aliadas::usarObjeto(Objetos obj){
    bool usada = false; 
    //recorrer inventario y buscar obj
    for(int i=0;i<3;i++){
        if(inventarioObjetos[i] == obj){
            obj.~Objetos();
            inventarioObjetos[i] = NULL;
            usada = true;
        }
    }    
    return usada;
}

void Aliadas::subirNivel(){
    lvl++;
}

bool Aliadas::abrirCofre(Cofre cofre){
    bool abierto = false;
    //recorrer inventario en busca objeto tipo llave
    for(int i=0;i<3;i++){
        if(inventarioObjetos[i].getTipo().strcmp("llave")){
            abierto = true;
            //cambiar sprite
        } 
    }   
    return abierto;
}



