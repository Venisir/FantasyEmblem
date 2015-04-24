/* 
 * File:   Unidad.cpp
 * Author: Beatriz
 * 
 * Created on 15 de abril de 2015, 9:40
 */

#include "../headers/Unidad.h"
#include <stdio.h>
#include <string>

using namespace std;

Unidad::Unidad(string name, string clas, Armas arma, int atributo[],int nivel, int rang) {
    nombre = name;
    clase = clas;
    arma_actual = arma;
    atributos = atributo;
    lvl = nivel;
    rango = rang;
    activo = true;
}

Unidad::Unidad(const Unidad& orig) {
}

Unidad::~Unidad() {
}

//------------------------------METODOS SET-------------------------------------
Unidad::setHP(int hp){
    atributos[0]=hp;
}
Unidad::setFuerza(int f){
    atributos[1]=f;
}
Unidad::setMagia(int m){
    atributos[2]=m;
}
Unidad::setHab(int h){
    atributos[3]=h;
}
Unidad::setVel(int v){
    atributos[4]=v;
}
Unidad::setDef(int d){
    atributos[5]=d;
}
Unidad::setDefm(int dm){
    atributos[6]=dm;
}

//------------------------------METODOS GET-------------------------------------
Unidad::setHP(){
    return atributos[0];
}
Unidad::setFuerza(){
    return atributos[1];
}
Unidad::setMagia(){
    return atributos[2];
}
Unidad::setHab(){
    return atributos[3];
}
Unidad::setVel(){
    return atributos[4];
}
Unidad::setDef(){
    return atributos[5];
}
Unidad::setDefm(){
    return atributos[6];
}
//Unidad::setExp(){
   // 
//}