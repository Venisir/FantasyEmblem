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
    bool meter = false;
    //recorrer inventario en busca objeto tipo llave
    for(int i=0;i<3;i++){
        if(strcmp(inventarioObjetos[i] -> getTipo(),"llave")==0){
            abierto = true;
            //cambiar sprite
            if(cofre -> getArma()!=NULL){
                for(int j=0;j<3;j++){
                    if((inventarioArmas[j]==NULL) && (meter==false)){
                        inventarioArmas[j] = cofre->getArma();
                        meter=true;
                    }
                }
                if(meter==false){
                    //salta aviso: no puedes coger arma
                }
            }else{
                for(int j=0;j<3;j++){
                    if((inventarioObjetos[j]==NULL) && (meter==false)){
                        inventarioObjetos[j] = cofre->getObjeto();
                        meter=true;
                    }
                }
                if(meter==false){
                    //salta aviso: no puedes coger objeto
                }
            }
            
        } 
    }   
    return abierto;
}