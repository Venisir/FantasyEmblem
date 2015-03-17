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
    Texture cursor;
    Texture movimiento;
    
    if (!textura.loadFromFile("resources/patron.png"))
    {
        std::cerr << "Error cargando la imagen patron.png";
        exit(0);
    }
    
    if (!cursor.loadFromFile("resources/cursor.png"))
    {
        std::cerr << "Error cargando la imagen cursor.png";
        exit(0);
    }
    
    if (!movimiento.loadFromFile("resources/movimiento.png"))
    {
        std::cerr << "Error cargando la imagen movimiento.png";
        exit(0);
    }
    
    int matriz[ancho][alto];
    Sprite mapa[ancho][alto];
    Sprite spriteCursor(cursor);
    Sprite spriteMovimiento(movimiento);
    
    spriteCursor.setTextureRect(sf::IntRect(0, 0, 16, 16));
    spriteCursor.setOrigin(0,0);
    spriteCursor.setPosition(240, 160);
    
    spriteMovimiento.setTextureRect(sf::IntRect(0, 0, 16, 16));
    spriteMovimiento.setOrigin(0,0);
    //spriteMovimiento.setPosition(240, 160);
    
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
                        
                        //Tecla derecha
                        case sf::Keyboard::Right:
                            if(spriteCursor.getPosition().x<=448)
                                spriteCursor.move(16,0);
                        break;
                        
                        //Tecla izquierda
                        case sf::Keyboard::Left:
                            if(spriteCursor.getPosition().x>=16)
                                spriteCursor.move(-16,0);
                        break;
                        
                        //Tecla arriba
                        case sf::Keyboard::Up:
                            if(spriteCursor.getPosition().y>=16)
                                spriteCursor.move(0,-16);
                        break;
                        
                        //Tecla abajo
                        case sf::Keyboard::Down:
                            if(spriteCursor.getPosition().y<=302)
                                spriteCursor.move(0,16);
                        break;
                        
                        //Tecla de prueba M
                        case sf::Keyboard::M:
                            
                            int c= (int)(spriteCursor.getPosition().x);
                            int f= (int)(spriteCursor.getPosition().y);
                            
                            for(int i=f-16;i<=f+16;i+=16)
                            {
                                for(int j=c-16;j<=c+16;j+=16)
                                {
                                    if(i==f-16 && j==c)
                                    {
                                        mapa[j/16][(i-16)/16].setTexture(movimiento);
                                    }
                                    else if(i==f+16 && j==c)
                                    {
                                        mapa[j/16][(i+16)/16].setTexture(movimiento);
                                    }
                                    else if(i==f && j==c-16)
                                    {
                                       mapa[(j-16)/16][i/16].setTexture(movimiento); 
                                    }
                                    else if(i==f && j==c+16)
                                    {
                                        mapa[(j+16)/16][i/16].setTexture(movimiento); 
                                    }

                                    mapa[j/16][i/16].setTexture(movimiento);
                                }
                            }
                            
                            mapa[c/16][f/16]=sprite;
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
        
        window.draw(spriteCursor);
        window.display(); 
    }
    
    

    return 0;
}

