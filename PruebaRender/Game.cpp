/* 
 * File:   Game.cpp
 * Author: Alberto
 * 
 * Created on 25 de marzo de 2015, 9:35
 */

#include "Game.h"
#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

Game::Game(RenderWindow *v) {
    ventana = v;
}

Game::~Game() {
    
    delete evento;
    delete reloj;
    delete relojUpdate;
    delete reloj_fps;
    delete fuente;
    delete t_fps;
    delete t_fps2;
    
    //delete ventana;
    
}

void Game::init() {
    evento = new sf::Event();
    
    reloj = new sf::Clock();
    relojUpdate = new sf::Clock();
    reloj_fps = new sf::Clock();
    
    contadorUpdate = 0;
    fuente = new sf::Font();
    fuente->loadFromFile("resources/font.ttf");
    
    t_fps = new sf::Text("",*fuente,20);
    t_fps->setColor(sf::Color::White);
    t_fps->setPosition(0,0);
    
    t_fps2 = new sf::Text("",*fuente,20);
    t_fps2->setColor(sf::Color::White);
    t_fps2->setPosition(0,40);
    
    state = 0;
}

Game::Game(const Game& orig) {
}

void Game::render() {
    timeUpdate = reloj_fps->restart().asSeconds();
    fps = (float) 1 / timeUpdate;
    
    ventana->clear();
    
    stringstream ss_fps;
    ss_fps << "FPS: "<<fps;
    std::string s_fps = ss_fps.str();
    
    t_fps->setString(s_fps);
    
    stringstream ss_fps2;
    ss_fps2 << "Update veces: "<<contadorUpdate;
    std::string s_fps2 = ss_fps2.str();
    
    t_fps2->setString(s_fps2);
    
    ventana->draw(*t_fps);
    ventana->draw(*t_fps2);
    ventana->display();
}

void Game::update() {
    if (reloj->getElapsedTime().asMilliseconds() >= 100) {
        reloj->restart();
        
        input();
        
        contadorUpdate++;
    }
}

void Game::run() {
    
    //Vamos a ejecutar todo esto en el main. Consejo de Fidel.
    /*
    init();
    while (ventana->isOpen()) {
        evento = new sf::Event();
        update();
        render();
        delete evento;
    }
    */
}

void Game::input(){
    
        while(ventana->pollEvent(*evento))
        {
            switch(state)
            {
                case 0://estado por defecto
                    switch(evento->type)
                    {
                        case Event::Closed:
                            ventana->close();
                        break;

                        case sf::Event::KeyPressed:

                            //Verifico si se pulsa alguna tecla de movimiento
                            switch(evento->key.code) 
                            {
                                //Tecla ESC para salir
                                case sf::Keyboard::Escape:
                                    ventana->close();
                                break;
                                
                                case sf::Keyboard::Q:
                                    
                                break;
                            }
                        break;
                    }
                    break;
            }
        }
                       
}