/* 
 * File:   main.cpp
 * Author: Constanza
 *
 * Created on 4 de marzo de 2015, 9:46
 */

#include <iostream>
using namespace  std;
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{    
    sf::RenderWindow window(sf::VideoMode(480, 320), "SFML works!");

    sf::Texture fond;
    sf::Texture botn1;
    sf::Texture botn2;
    sf::Texture botn3;
    sf::SoundBuffer buffer;
    
        if (!buffer.loadFromFile("resources/1.wav")){
            std::cerr << "Error al cargar el archivo de audio";
        }
        
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
        
        // Creamos un sonido
	sf::Sound sonido;
	// Le asignamos el buffer cargado
	sonido.setBuffer(buffer);
	// establecemos el volumen a 80
	sonido.setVolume(60);
        //sonido.play();
	
        
        while (window.isOpen())
        {
            sf::Event event;
            sonido.play();
            while (window.pollEvent(event))
            {
                if ((event.type == sf::Event::Closed)){
                    window.close();
                }
                
                if (event.type == sf::Event::MouseMoved){
                   if((event.mouseMove.x>=108) && (event.mouseMove.x <=371)){
                        if((event.mouseMove.y>=31) && (event.mouseMove.y<=86)){
                            boton1.setScale(1.2,1.2);
                            boton2.setScale(1,1);
                            boton3.setScale(1,1);
                        }
                         if((event.mouseMove.y>=124) && (event.mouseMove.y<=177)){
                            boton1.setScale(1,1);
                            boton2.setScale(1.2,1.2);                            
                            boton3.setScale(1,1);
                        }
                         if((event.mouseMove.y>=217) && (event.mouseMove.y<=270)){
                            boton1.setScale(1,1);
                            boton2.setScale(1,1);
                            boton3.setScale(1.2,1.2);
                        }
                   }else{
                       boton1.setScale(1,1);
                       boton2.setScale(1,1);
                       boton3.setScale(1,1);
                   }             
                }
                if (event.type == sf::Event::MouseButtonPressed){
                    if (event.mouseButton.button == sf::Mouse::Left){
                        if((event.mouseButton.x>=108) && (event.mouseButton.x <=371)){
                            if((event.mouseButton.y>=217) && (event.mouseButton.y<=270)){
                                window.close();
                            }
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

