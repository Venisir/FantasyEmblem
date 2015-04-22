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

int main()
{    
    /*
    sf::RenderWindow window(sf::VideoMode(480, 320), "Fantasy Emblem");
    window.setSize(sf::Vector2u(960,640));
    MenuPrincipal MenuPrincipal(window.getSize().x, window.getSize().y);
    
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if ((event.type == sf::Event::Closed)){
                    window.close();
                }
                   
                if(event.type == sf::Event::KeyPressed){
                    switch(event.key.code){
                        case sf::Keyboard::Down:
                            MenuPrincipal.MoveDown();                 
                        break;
                        case sf::Keyboard::Up:
                            MenuPrincipal.MoveUp();
                        break;
                        
                        case sf::Keyboard::Return:
                            if(MenuPrincipal.getSelectedItemIndex()==3){
                                MenuPrincipal.Exit(window);
                            }
                            
                        break;  
                        
                    }
                }
        }
        window.clear(); 
        MenuPrincipal.draw(window);
        window.display();
        }
    */
    
    RenderWindow window(sf::VideoMode(480,320), "Fantasy Emblem");
    window.setSize(sf::Vector2u(960, 640));
    
    Cursor* cursor = new Cursor(&window);
    
    //Ejecuto el juego
    
    cursor->init();
    
    while (window.isOpen()){
        cursor->update();
        cursor->render();
    }
    
    //El juego termina y lo borro
    delete cursor;
    
        return 0;
}

