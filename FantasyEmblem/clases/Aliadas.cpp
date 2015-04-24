/* 
 * File:   Aliadas.cpp
 * Author: Constanza
 * 
 * Created on 24 de abril de 2015, 15:22
 */

#include "../headers/Aliadas.h"
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

using namespace std;
using namespace sf;

Aliadas::Aliadas() {
   
}

Aliadas::Aliadas(const Aliadas& orig) {
}

Aliadas::~Aliadas() {
}

bool Aliadas::usarObjeto(Objetos obj){
    bool usada = false; 
    //recorrer inventario y buscar obj
    for(int i=0;i<3;i++){
        if(inventarioObjetos[i].getId() == obj.getId()){
            obj.~Objetos();
            //inventarioObjetos[i];
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
    Armas arma_pasada = cofre.getArma();
    Objetos objeto_pasado = cofre.getObjeto();
    //recorrer inventario en busca objeto tipo llave
    for(int i=0;i<3;i++){
        if(strcmp(inventarioObjetos[i].getTipo(),"llave")==0){
            abierto = true;
            //cambiar sprite
            if(arma_pasada!=NULL){
                for(int j=0;j<3;j++){
                    if((inventarioArmas[j]==NULL) && (meter==false)){
                        inventarioArmas[j] = cofre.getArma();
                        meter=true;
                    }
                }
                if(meter==false){
                    //salta aviso: no puedes coger arma
                }
            }else{
                for(int j=0;j<3;j++){
                    if((inventarioObjetos[j]==NULL) && (meter==false)){
                        inventarioObjetos[j] = objeto_pasado;
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