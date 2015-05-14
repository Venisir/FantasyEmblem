/* 
 * File:   Aliadas.cpp
 * Author: Constanza
 * 
 * Created on 24 de abril de 2015, 15:22
 */
 
#include "../headers/Aliadas.h"
#include "../headers/Enemigo.h"
#include "../headers/Armas.h"
#include "../headers/Objetos.h"
#include "../headers/Cofre.h"
#include "../headers/Unidad.h"
#include "../headers/Mapa.h"
#include "../headers/Juego.h"
 
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
    
    inventarioObjetos=new Objetos*[3];
    inventarioArmas=new Armas*[3];
    
    for(int i=0; i<3; i++){
        inventarioObjetos[i]=NULL;
        inventarioArmas[i]=NULL;
    }
    spriteCofreAbierto = new Sprite(); 
    spriteAvisoInventArmas = new Sprite();
    spriteAvisoInventObjetos = new Sprite();
    spriteAvisoLlaveCofre = new Sprite();
    spriteAvisoLlavePuerta = new Sprite();
    texturaCofreAbierto = new Texture();
    texturaAvisoInventarioArmas = new Texture();
    texturaAvisoInventarioObjetos = new Texture();
    texturaAvisoLlaveCofre = new Texture();
    texturaAvisoLlavePuerta = new Texture();
    
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
        if(inventarioObjetos[i]!=NULL){
            if(strcmp(inventarioObjetos[i]->getTipo(),"llaveCofre")== 0){
                abierto = true;
                //cambiar sprite
                string s = "niveles/Tilev1.png";

                if (!texturaCofreAbierto->loadFromFile(s))
                {
                    std::cerr << "Error cargando la imagen textura del cofre abierto";
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
                        string s_armas = "resources/avisoarmas.png";

                        if (!texturaAvisoInventarioArmas->loadFromFile(s_armas))
                        {
                            std::cerr << "Error cargando la imagen textura del aviso de inventario lleno de armas";
                            exit(0);
                        }
                        spriteAvisoInventArmas->setTexture(*texturaAvisoInventarioArmas);
                       //spriteAvisoInventArmas->setPosition(170,170);
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
                        string s_objetos = "resources/avisoobjetos.png";

                        if (!texturaAvisoInventarioObjetos->loadFromFile(s_objetos))
                        {
                            std::cerr << "Error cargando la imagen textura del aviso de inventario lleno de objetos";
                            exit(0);
                        }
                        spriteAvisoInventObjetos->setTexture(*texturaAvisoInventarioObjetos);
                        //spriteAvisoInventObjetos->setPosition(200,200);
                    }
                }

            }else{
                string noLlave = "resources/avisollavecofre.png";

                if (!texturaAvisoLlaveCofre->loadFromFile(noLlave))
                {
                    std::cerr << "Error cargando la imagen textura del aviso de no hay llave de cofre";
                    exit(0);
                }
                spriteAvisoLlaveCofre->setTexture(*texturaAvisoLlaveCofre);
            } 
        }
    }   
    return abierto;
}
 

void Aliadas::abrirPuerta(Mapa* mapa){
    bool llave=false;
    cout<<"entra a abrirPuerta"<<endl;
    for(int i=0;i<3 && llave==false;i++){
        
        if(inventarioObjetos[i]!=NULL){
            if(strcmp(inventarioObjetos[i]->getTipo(),"llavePuerta")== 0){  
                string s_armas = "resources/avisoarmas.png";

                if (!texturaAvisoInventarioArmas->loadFromFile(s_armas))
                {
                    std::cerr << "Error cargando la imagen textura del aviso de inventario lleno de armas";
                    exit(0);
                }
                spriteAvisoInventArmas->setTexture(*texturaAvisoInventarioArmas);
                cout<<"abro la puerta"<<endl;
                llave=true;
            }
        }
    }
    
    if(!llave){
        
        string noLlave = "resources/avisollavepuerta.png";

        if (!texturaAvisoLlavePuerta->loadFromFile(noLlave))
        {
            std::cerr << "Error cargando la imagen textura del aviso de no hay llave de cofre";
            exit(0);
        }
        cout<<"p1"<<endl;
        spriteAvisoLlavePuerta->setTexture(*texturaAvisoLlavePuerta);
        spriteAvisoLlavePuerta->setOrigin(0,0);
        spriteAvisoLlavePuerta->setPosition(170,0);
        Juego :: Instance()->getVentana()->draw(*spriteAvisoLlavePuerta);
        cout<<"p3"<<endl;
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
  
int* Aliadas::getRecorrido(){
    return recorrido;
}
  
void Aliadas::recorre()
{
    //for(int i=0;i<ultimo_mov;i++)
    for(int i=0;i<1;i++)
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
     }
     //recorrido=new int[rango];
     ultimo_mov=0;
     std::cerr << endl;
 }
  
 bool Aliadas::hayPuerta(Mapa* mapa){
     cout<<"entra en hayPuerta"<<endl;
     bool puerta = false;    
     
        //derecha
        cout<<"primer if"<<endl;
        if((mapa->getPuerta(spriteUnidad->getPosition().y,spriteUnidad->getPosition().x+16) )== true){
            puerta = true;
            cout<<"Hay puerta a la derecha"<<endl;     
        }
        //izquierda
        cout<<"segundo if"<<endl;
        if((mapa->getPuerta(spriteUnidad->getPosition().y,spriteUnidad->getPosition().x-16)) == true){
             puerta = true;
             cout<<"Hay puerta a la izquierda"<<endl;     
        }
        //arriba
        cout<<"tercer if"<<endl;
        if((spriteUnidad->getPosition().y<0)&&(mapa->getPuerta(spriteUnidad->getPosition().y-16,spriteUnidad->getPosition().x)) == true){
             puerta = true;
             cout<<"Hay puerta arriba"<<endl;
        }
        //abajo
        cout<<"cuarto if"<<endl;
        if((mapa->getPuerta(spriteUnidad->getPosition().y+16,spriteUnidad->getPosition().x)) == true){
             puerta = true;
             cout<<"Hay puerta abajo"<<endl;
        }     
        if(puerta==true){
           cout<<"hay puertesica"<<endl;
           //abrirPuerta(mapa);
        }else{
            cout<<"no hay puertesica"<<endl;
        }
     return puerta;
 }
 
 bool Aliadas::hayCofre(Mapa* mapa){
      bool cofre = false;    
     
        //derecha
        cout<<"primer if"<<endl;
        if((mapa->getCofre(spriteUnidad->getPosition().y,spriteUnidad->getPosition().x+16) )== true){
            cofre = true;
            cout<<"Hay cofre a la derecha"<<endl;     
        }
        //izquierda
        cout<<"segundo if"<<endl;
        if((mapa->getCofre(spriteUnidad->getPosition().y,spriteUnidad->getPosition().x-16)) == true){
             cofre = true;
             cout<<"Hay cofre a la izquierda"<<endl;     
        }
        //arriba
        cout<<"tercer if"<<endl;
        if((spriteUnidad->getPosition().y<0)&&(mapa->getCofre(spriteUnidad->getPosition().y-16,spriteUnidad->getPosition().x)) == true){
             cofre = true;
             cout<<"Hay cofre arriba"<<endl;
        }
        //abajo
        cout<<"cuarto if"<<endl;
        if((mapa->getCofre(spriteUnidad->getPosition().y+16,spriteUnidad->getPosition().x)) == true){
             cofre = true;
             cout<<"Hay cofre abajo"<<endl;
        }
     return cofre;
 }
 
 int Aliadas::getExp(){
         
    return experiencia;
}
 
Armas** Aliadas::getArmas(){
    return inventarioArmas;
} 

Objetos** Aliadas::getObjetos(){
    return inventarioObjetos;
}

int Aliadas::hayEnemigosCercanos(Enemigo** enemigos){
    
    int hayEnemigo = 0;
    
    //cerr << sizeof(enemigos) << endl;
    //cerr << sizeof(*enemigos) << endl;
    
    for(int i=0; i<sizeof(enemigos)-1; i++){
        if(this->getPosicionSpriteX()+16 == enemigos[i]->getPosicionSpriteX() && this->getPosicionSpriteY() == enemigos[i]->getPosicionSpriteY()){
            hayEnemigo = 1;
        }
        if(this->getPosicionSpriteX() == enemigos[i]->getPosicionSpriteX() && this->getPosicionSpriteY()-16 == enemigos[i]->getPosicionSpriteY()){
            hayEnemigo = 2;
        }
        if(this->getPosicionSpriteX()-16 == enemigos[i]->getPosicionSpriteX() && this->getPosicionSpriteY() == enemigos[i]->getPosicionSpriteY()){
            hayEnemigo = -1;
        }
        if(this->getPosicionSpriteX() == enemigos[i]->getPosicionSpriteX() && this->getPosicionSpriteY()+16 == enemigos[i]->getPosicionSpriteY()){
            hayEnemigo = -2;
        }
    }
    return hayEnemigo;
}

int Aliadas::hayCofresCercanos(Mapa* m){
    
    int hayCofre = 0;
    
    //cerr << sizeof(enemigos) << endl;
    //cerr << sizeof(*enemigos) << endl;
    
    for(int i=0; i<m->getNumCofres(); i++){
        if(m->getCofre(this->getPosicionSpriteX()+16, this->getPosicionSpriteY())==true){
            hayCofre = 1;
        }
        if(m->getCofre(this->getPosicionSpriteX(), this->getPosicionSpriteY()-16)==true){
            hayCofre = 2;
        }
        if(m->getCofre(this->getPosicionSpriteX()-16, this->getPosicionSpriteY())==true){
            hayCofre = -1;
        }
        if(m->getCofre(this->getPosicionSpriteX(), this->getPosicionSpriteY()+16)==true){
            hayCofre = -2;
        }
    }
    return hayCofre;
}

int Aliadas::hayPuertasCercanas(Mapa* m){
    return 0;
}