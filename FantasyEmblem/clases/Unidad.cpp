/* 
 * File:   Unidad.cpp
 * Author: Beatriz
 * 
 * Created on 15 de abril de 2015, 9:40
 */

#include "../headers/Unidad.h"
#include "../headers/Juego.h"
#include "../headers/Armas.h"
#include <stdio.h>
#include <string>

using namespace std;

Unidad::Unidad()
{
    
}

Unidad::Unidad(const char* name, const char* clas, int atributo[],int nivel, int rang, const char* nombreTextu) {
    nombre = name;
    clase = clas;
    arma_actual = new Armas("Espadon Sangriento", "Espada", 1, 1, 1, 1, 1);
    for(int i=0; i<7; i++)
        atributos[i] = atributo[i];
    lvl = nivel;
    rango = rang;
    activo = true;
    
    valorSprite = 1;
    siguienteSumar = true;
    
    spriteUnidad = new Sprite();
    texturaUnidad = new Texture();
    
    string s1 = string(nombreTextu);
    string s = "resources/"+s1;
    
    if (!texturaUnidad->loadFromFile(s))
    {
        std::cerr << "Error cargando la imagen textura de la unidad";
        exit(0);
    }
    
    spriteUnidad->setTexture(*texturaUnidad);
    spriteUnidad->setTextureRect(IntRect(0, 0, 20, 20));
    
    //spriteUnidad->setPosition(176,176);
}

Unidad::~Unidad() {
    
}

int Unidad::getPosicionCeldaX() {
    return spriteUnidad->getPosition().x/16;
}

int Unidad::getPosicionCeldaY() {
    return spriteUnidad->getPosition().y/16;
}

int Unidad::getPosicionSpriteX() {
    return spriteUnidad->getPosition().x;
}

int Unidad::getPosicionSpriteY() {
    return spriteUnidad->getPosition().y;
}

void Unidad::setPosition(int i, int j) {
    spriteUnidad->setPosition(i,j);
}

void Unidad::moverArriba(){
    spriteUnidad->setPosition(spriteUnidad->getPosition().x,spriteUnidad->getPosition().y-16);
}

void Unidad::moverAbajo(){
    spriteUnidad->setPosition(spriteUnidad->getPosition().x,spriteUnidad->getPosition().y+16);
}

void Unidad::moverIzquierda(){
    spriteUnidad->setPosition(spriteUnidad->getPosition().x-16,spriteUnidad->getPosition().y);
}

void Unidad::moverDerecha(){
    spriteUnidad->setPosition(spriteUnidad->getPosition().x+16,spriteUnidad->getPosition().y);
}
    
void Unidad::cambiaSpriteQuieto() {
    if(valorSprite == 0){
        siguienteSumar = true;
        valorSprite = 2;
    }else{
        if(valorSprite == 4){
            siguienteSumar = false;
            valorSprite = 2;
        }else{
            if(siguienteSumar == true){
                valorSprite = 4;
                siguienteSumar = false;
            }else{
                valorSprite = 0;
                siguienteSumar = true;
            }
        }
    }
    spriteUnidad->setTextureRect(sf::IntRect(valorSprite*16, 0, 16, 16));
}
    
void Unidad::verStats() {
    
    //spriteUnidad->setColor(sf::Color(0, 255, 0, 128));
    
    std::cerr << "HAS SELECCIONADO A: " <<endl;
    std::cerr << nombre << ", que es un " << clase << " de nivel " << lvl << "." <<endl;
    std::cerr << "Tiene equipada un " << arma_actual->getNombre() << ", que es de tipo " << arma_actual->getTipo() << "." <<endl;
    
    std::cerr << "Vida: " << atributos[0] <<endl;
    std::cerr << "Fuerza: " << atributos[1] <<endl;
    std::cerr << "Magia: " << atributos[2] <<endl;
    std::cerr << "Habilidad: " << atributos[3] <<endl;
    std::cerr << "Velocidad: " << atributos[4] <<endl;
    std::cerr << "Defensa: " << atributos[5] <<endl;
    std::cerr << "Defensa magica: " << atributos[6] <<endl;
    std::cerr << "Nivel: " << lvl <<endl;
    std::cerr << "Rango: " << rango <<endl;
}

void Unidad::Draw() {
    Juego::Instance()->getVentana()->draw(*spriteUnidad);
}

//------------------------------METODOS SET-------------------------------------
void Unidad::setHP(int hp){
    atributos[0]=hp;
}
void Unidad::setFuerza(int f){
    atributos[1]=f;
}
void Unidad::setMagia(int m){
    atributos[2]=m;
}
void Unidad::setHab(int h){
    atributos[3]=h;
}
void Unidad::setVel(int v){
    atributos[4]=v;
}
void Unidad::setDef(int d){
    atributos[5]=d;
}
void Unidad::setDefm(int dm){
    atributos[6]=dm;
}

//------------------------------METODOS GET-------------------------------------
int Unidad::getHP(){
    return atributos[0];
}
int Unidad::getFuerza(){
    return atributos[1];
}
int Unidad::getMagia(){
    return atributos[2];
}
int Unidad::getHab(){
    return atributos[3];
}
int Unidad::getVel(){
    return atributos[4];
}
int Unidad::getDef(){
    return atributos[5];
}
int Unidad::getDefm(){
    return atributos[6];
}
int Unidad::getRango(){
    return rango;
}
//Unidad::setExp(){
   // 
//}
 Sprite Unidad::getSprite()
{
    return *spriteUnidad;
}
 
const char* Unidad::getNombre(){
    return nombre;
}