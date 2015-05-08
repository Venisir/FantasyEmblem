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

Enemigo::Enemigo(const char* name, const char* clas, int atributo[],int nivel, int rang, const char* nombreTextu):Unidad(name, clas, atributo, nivel, rang, nombreTextu) {

}

Enemigo::~Enemigo() {
}

