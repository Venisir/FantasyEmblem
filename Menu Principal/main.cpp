/* 
 * File:   main.cpp
 * Author: Constanza
 *
 * Created on 4 de marzo de 2015, 9:46
 */

#include <iostream>
#include <SFML/Graphics.hpp>
int main()
{
    //variables
    bool nuevojuego=false;
    bool continuar=false;
    bool salir=false;
    
    sf::RenderWindow window(sf::VideoMode(480, 320), "SFML works!");

    sf::Texture fond;
    sf::Texture botn1;
    sf::Texture botn2;
    sf::Texture botn3;
        
        if (!fond.loadFromFile("resources/menu.png"))
        {
                std::cerr << "Error cargando la imagen menu.png";
                exit(0);
        }
        
        if (!botn1.loadFromFile("resources/boton1.png"))
        {
                std::cerr << "Error cargando la imagen boton1.png";
                exit(0);
        }
        
        if (!botn2.loadFromFile("resources/boton2.png"))
        {
                std::cerr << "Error cargando la imagen boton2.png";
                exit(0);
        }
        
        if (!botn3.loadFromFile("resources/boton3.png"))
        {
                std::cerr << "Error cargando la imagen boton3.png";
                exit(0);
        }
        
        //Creamos el sprite
        sf::Sprite fondo(fond);
        sf::Sprite boton1(botn1);
        sf::Sprite boton2(botn2);
        sf::Sprite boton3(botn3);
        
        //Poner coordenadas
        //fondo.setOrigin(480/2,320/2);
        boton1.setOrigin(420/2,280/2);
        boton2.setOrigin(420/2,280/2);
        boton3.setOrigin(420/2,280/2);
        
        boton1.setPosition(480/2,68.25);
        boton2.setPosition(480/2,160);
        boton3.setPosition(480/2,251.75);
        
        while (window.isOpen())
        {
            sf::Event event;

            while (window.pollEvent(event))
            {
                if ((event.type == sf::Event::Closed) || (event.key.code == sf::Keyboard::Escape)){
                    window.close();
                }
                 if (event.type == sf::Event::MouseMoved){
                    
                /*}
                if (event.mouseButton.button == sf::Mouse::Left)
                {**/
                   if((event.mouseMove.x>=108) && (event.mouseMove.x <=371)){
                        if((event.mouseMove.y>=31) && (event.mouseMove.y<=86)){
                            boton1.scale(2,2);
                        }
                   }               
                } 
           }

            window.clear();
            window.draw(fondo);
            window.draw(boton1);
            window.draw(boton2);
            window.draw(boton3);
            window.display();

        }

        return 0;
}

