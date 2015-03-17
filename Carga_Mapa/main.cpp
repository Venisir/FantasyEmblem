#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string>
#include "tinyxml2.h"

   
using namespace tinyxml2;
using namespace std;
using namespace sf;
int main()
{
    XMLDocument doc;
    RenderWindow window(sf::VideoMode(480,320), "Fantasy Emblem");
    doc.LoadFile("niveles/mapaTiled.tmx");
    
    XMLElement* elemento = doc.FirstChildElement("map");
    
    int ancho = elemento->IntAttribute("width");
    int alto = elemento->IntAttribute("height");
    
    Sprite sprite;
    Texture textura;
    
    
    if (!textura.loadFromFile("resources/patron.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    
    int matriz[ancho][alto];
    Sprite mapa[ancho][alto];
    
    //preparamos el elemento para el primer tile
    elemento = doc.FirstChildElement("map")->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    
    //se rellena la matriz con los id de los sprites
    for(int i=0;i<ancho;i++)
    {
        for(int j=0;j<alto;j++)
        {
            matriz[i][j]=elemento->IntAttribute("gid");
            elemento=elemento->NextSiblingElement("tile");
        }
    }
    
    //se crea una matriz de sprites
    for(int i=0;i<ancho;i++)
    {
        for(int j=0;j<alto;j++)
        {
            sprite.setTexture(textura);
            sprite.setTextureRect(IntRect(0, 0, 16, 16));
            sprite.setPosition(i*16,j*16);
            mapa[i][j]=sprite;
        }
    }
    
    
    //mostrar el mapa
    while(window.isOpen())
    {
        Event evento;
        
        while(window.pollEvent(evento))
        {
            switch(evento.type)
            {
                case Event::Closed:
                    window.close();
                break;
                
                case sf::Event::KeyPressed:
                    
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(evento.key.code) 
                    {
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                        break;
                    }
            }
            
            
        }
        
        
        for(int i=0;i<ancho;i++)
        {
            for(int j=0;j<alto;j++)
            {
                window.draw(mapa[i][j]);
            }
        }
        
       window.display(); 
    }
    
    

    return 0;
}

