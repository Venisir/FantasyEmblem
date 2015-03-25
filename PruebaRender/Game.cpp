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
    delete ventana;
}

void Game::init() {
    reloj = new sf::Clock();
    relojUpdate = new sf::Clock();
    reloj_fps = new sf::Clock();
    
    fuente = new sf::Font();
    fuente->loadFromFile("resources/font.ttf");
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
    sf::Text t_fps(s_fps,*fuente,20);
    
    t_fps.setColor(sf::Color::White);
    t_fps.setPosition(0,0);
    
    ventana->draw(t_fps);
    ventana->display();
}

void Game::update() {
    if (reloj->getElapsedTime().asMilliseconds() >= 70) {
        reloj->restart();
        //input();
    }
}

void Game::run() {
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

}