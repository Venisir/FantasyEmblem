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
#include "../headers/Mapa.h"

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

Aliadas::Aliadas() {

}


Aliadas::Aliadas(const char* name, const char* clas, int atributo[],int nivel, int rang, const char* nombreTextu, int experien):Unidad(name, clas, atributo, nivel, rang, nombreTextu) {
    experiencia = experien;
    
    recorrido=new int[rango];
    ultimo_mov=0;   
}

Aliadas::~Aliadas() {
}

bool Aliadas::equiparArma(Armas* arma){
    bool equipada = false;
    if(arma!=NULL)
        arma_actual = arma;
    return equipada;
}
bool Aliadas::usarObjeto(Objetos* obj){
    bool usada = false; 
    //recorrer inventario y buscar obj
    for(int i=0;i<3;i++){
        if(inventarioObjetos[i]->getId() == obj->getId()){
            obj->~Objetos();
            delete inventarioObjetos[i];
            usada = true;
        }
    }    
    return usada;
}


 void Aliadas::subirNivel(){
    lvl++;
}

bool Aliadas::abrirCofre(Cofre* cofre){
    bool abierto = false;
    bool meter = false;
    //recorrer inventario en busca objeto tipo llave
    for(int i=0;i<3;i++){
        if(strcmp(inventarioObjetos[i]->getTipo(),"llaveCofre")== 0){
            abierto = true;
            //cambiar sprite
            string s = "niveles/Tilev1.png";
    
            if (!texturaCofreAbierto->loadFromFile(s))
            {
                std::cerr << "Error cargando la imagen textura de la unidad";
                exit(0);
            }
            spriteCofreAbierto->setTexture(*texturaCofreAbierto);
            spriteCofreAbierto->setTextureRect(IntRect(8*16, 1*16, 16, 16));
            
            if(cofre->getArma() != NULL){
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

void Aliadas::abrirPuerta(Mapa* mapa){
    for(int i=0;i<3;i++){
        if(strcmp(inventarioObjetos[i]->getTipo(),"llavePuerta")== 0){            
          mapa->quitarPuerta(); 
        }
    }
}

 void Aliadas::guardamovimiento(int n){
    int negativo=n*(-1);
    //si el ultimo introducido es el negativo del que se va a introducir..
    if(ultimo_mov<rango)
    {
        if(negativo==recorrido[ultimo_mov-1])
        {
            ultimo_mov--;
        }
        else
        {
            recorrido[ultimo_mov]=n;
            ultimo_mov++;
        }
    }
    else if(ultimo_mov==rango)
    {
        if(negativo==recorrido[ultimo_mov-1])
        {
            ultimo_mov--;
        } 
    }
}
 
 void Aliadas::recorre()
 {
     for(int i=0;i<ultimo_mov;i++)
     {
         switch(recorrido[i])
         {
             case 1:
                 moverDerecha(); 
                 std::cerr << recorrido[i] << " ";
                break;
             case 2:
                 moverArriba();
                 std::cerr << recorrido[i] << " ";
                break;
             case -1:
                 moverIzquierda();
                 std::cerr << recorrido[i] << " ";
                break;
             case -2:
                 moverAbajo();
                 std::cerr << recorrido[i] << " ";
                break; 
         }
//        hayPuerta();
     }
     recorrido=new int[rango];
     ultimo_mov=0;
     std::cerr << endl;
 }
 
 void Aliadas::hayPuerta(Mapa* mapa){
     bool puerta = false;     
     //derecha
     if(mapa->getPuerta(spriteUnidad->getPosition().y,spriteUnidad->getPosition().x+16) == true){
         puerta = true;
         cout<<"Hay puerta a la derecha"<<endl;
     //izquierda
     }else if(mapa->getPuerta(spriteUnidad->getPosition().y,spriteUnidad->getPosition().x-16) == true){
          puerta = true;
          cout<<"Hay puerta a la izquierda"<<endl;
     //arriba
     }else if(mapa->getPuerta(spriteUnidad->getPosition().y+16,spriteUnidad->getPosition().x) == true){
          puerta = true;
          cout<<"Hay puerta arriba"<<endl;
     //abajo
     }else if(mapa->getPuerta(spriteUnidad->getPosition().y-16,spriteUnidad->getPosition().x) == true){
          puerta = true;
          cout<<"Hay puerta abajo"<<endl;
     }     
     if(puerta==true)
        abrirPuerta(mapa);
 }