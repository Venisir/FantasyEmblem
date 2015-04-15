#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string>
#include "tinyxml2.h"

//Incluyo la clase Game
#include "Game.h"

using namespace tinyxml2;
using namespace std;
using namespace sf;

int main() {
    
    //Creo la ventana
    RenderWindow window(sf::VideoMode(480,320), "Fantasy Emblem");
    window.setSize(sf::Vector2u(960, 640));
    //window.setFramerateLimit(1);
    
    //Creo una instancia de juego en memoria dinamica
    Game* juego=new Game(&window);
    
    //Ejecuto el juego
    
    juego->init();
    
    while (window.isOpen()){
        juego->update();
        juego->render();
    }
    
    //El juego termina y lo borro
    delete juego;
    
    //Acabo la aplicacion
    return 0;
}