/* 
 * File:   main.cpp
 * Author: Hexaiden
 *
 * Created on 15 de abril de 2015, 9:12
 */

#include <iostream>
using namespace  std;
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../headers/MenuPrincipal.h"
#include "../headers/Cursor.h"
#include "../headers/Escenario.h"
#include "../headers/Estado.h"
#include "../headers/Juego.h"

int main()
{    
    RenderWindow window(sf::VideoMode(480,320), "Fantasy Emblem", sf::Style::Close);
    window.setSize(sf::Vector2u(960, 640));
    window.setFramerateLimit(60);
    
    Juego *juego = Juego::Instance();
    
    //Le pongo la ventana al juego
    juego->setVentana(&window);

    //Ejecuto el juego
    juego->init();
    
    while (window.isOpen()){
        
        //std::cerr << "YES" <<endl;
        juego->update();
        juego->render();
        //window.close();
    }
    
    //El juego termina y lo borro
    //delete juego;
    
    return 0;
}