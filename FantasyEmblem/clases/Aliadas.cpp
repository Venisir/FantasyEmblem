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

Aliadas::Aliadas(const char* name, const char* clas, int atributo[],int nivel, int rang, const char* nombreTextu, const char* textuBatalla, const char* textuevadir, int experien, Objetos** obj, Armas** arm):Unidad(name, clas, atributo, nivel, rang, nombreTextu, textuBatalla, textuevadir) {

    experiencia = experien;
     
    //recorrido=new int[rango];
    //ultimo_mov=0;   
    
    inventarioObjetos=obj;
    inventarioArmas=arm;
    
    for(int i=0; i<3; i++){
        inventarioObjetos[i]=NULL;
        inventarioArmas[i]=NULL;
    }
    //PRUEBA -> VAMOS A PONERLE ALGUNOS OBJETOS
    inventarioObjetos[0] = new Objetos("LlaveInicialCofre", "llaveCofre", 1, 1, "Una llave chachi", 1, "espada.png");
    inventarioObjetos[1] = new Objetos("LlaveInicialPuerta", "llavePuerta", 1, 1, "Una llave chachi", 1, "espada.png");
    inventarioObjetos[2] = new Objetos("Anillo","anillo",3,1,"ooooroooo",false,"espada.png");
    
    spriteAviso = new Sprite();
    spriteAviso->setOrigin(100/2,45/2);
    spriteAviso->setPosition(240,160);
    
    texturaAvisoInventarioArmas = new Texture();
    texturaAvisoInventarioObjetos = new Texture();
    texturaAvisoLlaveCofre = new Texture();
    texturaAvisoLlavePuerta = new Texture();
    
    string noLlave = "resources/avisollavecofre.png";
    if (!texturaAvisoLlaveCofre->loadFromFile(noLlave))
    {
        std::cerr << "Error cargando la imagen textura del aviso de no hay llave de cofre";
        exit(0);
    }
    
    string s_armas = "resources/avisoarmas.png";
    if (!texturaAvisoInventarioArmas->loadFromFile(s_armas))
    {
        std::cerr << "Error cargando la imagen textura del aviso de inventario lleno de armas";
        exit(0);
    }
    
    string s_objetos = "resources/avisoobjetos.png";
    if (!texturaAvisoInventarioObjetos->loadFromFile(s_objetos))
    {
        std::cerr << "Error cargando la imagen textura del aviso de inventario lleno de objetos";
        exit(0);
    }
           
    string p_noLlave = "resources/avisollavepuerta.png";
    if (!texturaAvisoLlavePuerta->loadFromFile(p_noLlave))
    {
        std::cerr << "Error cargando la imagen textura del aviso de no hay llave de puerta";
        exit(0);
    }
    spriteAviso->setTexture(*texturaAvisoLlaveCofre);
}
 
Aliadas::~Aliadas() {
}
 
bool Aliadas::equiparArma(Armas* arma){
    bool equipada = false;
    if(arma!=NULL)
        arma_actual = arma;
    return equipada;
}

Objetos** Aliadas::usarObjeto(int pos){

    delete inventarioObjetos[pos];
    for(int i=0;i<sizeof(inventarioObjetos);i++){
            
        if(inventarioObjetos[i+1]!=NULL){
            inventarioObjetos[i]=inventarioObjetos[i+1];
        }
    }
    return inventarioObjetos;
}

 void Aliadas::subirNivel(){
    lvl++;
}

bool Aliadas::abrirCofre(Cofre* cofre){
    
    bool abierto = false;
    bool meter = false;
    //recorrer inventario en busca objeto tipo llave
    for(int i=0;i<3 && abierto!=true;i++){
        if(inventarioObjetos[i]!=NULL){
            if(strcmp(inventarioObjetos[i]->getTipo(),"llaveCofre")== 0){
                abierto = true;
                //cambiar sprite
                cofre->cambiaTexturaAbierto();
                
                if(cofre->getArma() != NULL){
                    for(int j=0;j<3;j++){
                        if((inventarioArmas[j]==NULL) && (meter==false)){
                            inventarioArmas[j] = cofre->getArma();
                            meter=true;
                        }
                    }
                    if(meter==false){
                        //salta aviso: no puedes coger arma
                        spriteAviso->setTexture(*texturaAvisoInventarioArmas);
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
                        spriteAviso->setTexture(*texturaAvisoInventarioObjetos);
                    }
                }
            }else{
                spriteAviso->setTexture(*texturaAvisoLlaveCofre);
            } 
        }
    }   
    return abierto;
}
 
Sprite* Aliadas::dameQuePinte(){
    return spriteAviso;
}

bool Aliadas::abrirPuerta(Mapa* mapa){
    bool llave=false;
    cout<<"entra a abrirPuerta"<<endl;
    for(int i=0;i<3 && llave==false;i++){
        if(inventarioObjetos[i]!=NULL){
            if(strcmp(inventarioObjetos[i]->getTipo(),"llavePuerta")== 0){  
                //spriteAviso->setTexture(*texturaAvisoInventarioArmas);
                if(mapa->getPuerta(getPosicionSpriteY()+16,getPosicionSpriteX())){
                    cout<<"abajo"<<endl;
                    mapa->quitarPuerta(getPosicionSpriteY()+16,getPosicionSpriteX());
                    cout<<"He abierto la puerta :D"<<endl;
                }else if((spriteUnidad->getPosition().y<0)&&(mapa->getPuerta(getPosicionSpriteY()-16,getPosicionSpriteX()))){
                    cout<<"arriba"<<endl;
                    mapa->quitarPuerta(getPosicionSpriteY()-16,getPosicionSpriteX());
                    cout<<"He abierto la puerta :D"<<endl;
                }else if(mapa->getPuerta(getPosicionSpriteY(),getPosicionSpriteX()+16)){
                    cout<<"derecha"<<endl;
                    mapa->quitarPuerta(getPosicionSpriteY(),getPosicionSpriteX()+16);
                    cout<<"He abierto la puerta :D"<<endl;
                }else if(mapa->getPuerta(getPosicionSpriteY(),getPosicionSpriteX()-16)){
                    cout<<"izquierda"<<endl;
                    mapa->quitarPuerta(getPosicionSpriteY(),getPosicionSpriteX()-16);
                    cout<<"He abierto la puerta :D"<<endl;
                }
                llave=true;
            }
        }
    }
    
    if(!llave){
        spriteAviso->setTexture(*texturaAvisoLlavePuerta);
    }
    return llave;
}
/*
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
}*/
  /*
int* Aliadas::getRecorrido(){
    return recorrido;
}*/
  /*
void Aliadas::recorre()
{
    //for(int i=0;i<ultimo_mov;i++)
    for(int i=0;i<1;i++)
    {
        switch(movimientos[i])
        {
            case 1:
                moverDerecha(); 
                std::cerr << movimientos[i] << " " << endl;
                break;
            case 2:
                moverArriba();
                std::cerr << movimientos[i] << " " << endl;
               break;
            case -1:
                moverIzquierda();
                std::cerr << movimientos[i] << " " << endl;
               break;
            case -2:
                moverAbajo();
                std::cerr << movimientos[i] << " " << endl;
               break; 
         }
     }
     ultimo_mov=0;
 }
  */
 bool Aliadas::hayPuerta(Mapa* mapa){
     bool puerta = false;    
     
        //derecha
        if((mapa->getPuerta(spriteUnidad->getPosition().y,spriteUnidad->getPosition().x+16) )== true){
            puerta = true;  
        }
        //izquierda
        if((mapa->getPuerta(spriteUnidad->getPosition().y,spriteUnidad->getPosition().x-16)) == true){
             puerta = true;     
        }
        //arriba
        if((spriteUnidad->getPosition().y<0)&&(mapa->getPuerta(spriteUnidad->getPosition().y-16,spriteUnidad->getPosition().x)) == true){
             puerta = true;
        }
        //abajo
        if((mapa->getPuerta(spriteUnidad->getPosition().y+16,spriteUnidad->getPosition().x)) == true){
             puerta = true;
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
        if((mapa->getCofre(spriteUnidad->getPosition().y,spriteUnidad->getPosition().x+16) )== true){
            cofre = true;
        }
        //izquierda
        if((mapa->getCofre(spriteUnidad->getPosition().y,spriteUnidad->getPosition().x-16)) == true){
             cofre = true;   
        }
        //arriba
        if((spriteUnidad->getPosition().y<0)&&(mapa->getCofre(spriteUnidad->getPosition().y-16,spriteUnidad->getPosition().x)) == true){
             cofre = true;
        }
        //abajo
        if((mapa->getCofre(spriteUnidad->getPosition().y+16,spriteUnidad->getPosition().x)) == true){
             cofre = true;
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

int Aliadas::cualEsElEnemigoCercano(Enemigo** enemigos){
    
    int _aux = 0;
    
    for(int i=0; i<sizeof(enemigos)-1; i++){
        if(this->getPosicionSpriteX()+16 == enemigos[i]->getPosicionSpriteX() && this->getPosicionSpriteY() == enemigos[i]->getPosicionSpriteY()){
            _aux = i;
        }
        if(this->getPosicionSpriteX() == enemigos[i]->getPosicionSpriteX() && this->getPosicionSpriteY()-16 == enemigos[i]->getPosicionSpriteY()){
            _aux = i;
        }
        if(this->getPosicionSpriteX()-16 == enemigos[i]->getPosicionSpriteX() && this->getPosicionSpriteY() == enemigos[i]->getPosicionSpriteY()){
            _aux = i;
        }
        if(this->getPosicionSpriteX() == enemigos[i]->getPosicionSpriteX() && this->getPosicionSpriteY()+16 == enemigos[i]->getPosicionSpriteY()){
            _aux = i;
        }
    }
    return _aux;
}

int Aliadas::hayCofresCercanos(Mapa* m){
    
    int hayCofre = 0;
    
    if(m->getCofre(this->getPosicionSpriteY(), this->getPosicionSpriteX())==true){
        hayCofre = 1;
    }
    return hayCofre;
}

int Aliadas::hayPuertasCercanas(Mapa* m){
    
    int hayPuerta = 0;
    bool yano = false;
    
    if((m->getPuerta(this->getPosicionSpriteY()+16, this->getPosicionSpriteX())==true)){
        //Esta abajo
        hayPuerta = -2;
        yano = true;
    }
    if((m->getPuerta(this->getPosicionSpriteY(), this->getPosicionSpriteX()-16)==true)){
        hayPuerta = 1;
    }
    if((m->getPuerta(this->getPosicionSpriteY()-16, this->getPosicionSpriteX())==true)){
        //Esta arriba
        hayPuerta = 2;
    }
    if((m->getPuerta(this->getPosicionSpriteY(), this->getPosicionSpriteX()+16)==true)){
        hayPuerta = -1;
    }
    return hayPuerta;
}

void Aliadas::setExp(int i){
    
    if((experiencia+i)>=100){
        experiencia=(experiencia+i)-100;
        
    }else if ((experiencia+i)<100){
        experiencia=experiencia+1;
    }
}