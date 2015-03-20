#include <iostream>
#include <SFML/Graphics.hpp>
#include "tinyxml2.h"

int main()
{
    tinyxml2::XMLDocument doc;
    
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(480, 320), "Fantasy Emblem");
    
    //Cargo la imagen donde reside la textura del sprite
    sf::Texture mapa;
    sf::Texture casilla;
    sf::Texture texPj1;
    sf::Texture cursor;
    
    sf::Clock clockSaltitos;
    
    if (!cursor.loadFromFile("resources/cursor.png"))
    {
        std::cerr << "Error cargando la imagen cursor.png";
        exit(0);
    }
    
    if (!mapa.loadFromFile("resources/Mapa.png"))
    {
        std::cerr << "Error cargando la imagen mapa.png";
        exit(0);
    }
    
    if (!casilla.loadFromFile("resources/casilla.png"))
    {
        std::cerr << "Error cargando la imagen casilla.png";
        exit(0);
    }
    
    if (!texPj1.loadFromFile("resources/Mapa_espadachin.png"))
    {
        std::cerr << "Error cargando la imagen mapa.png";
        exit(0);
    }
    
    //Y creo el spritesheet a partir de la imagen anterior
    sf::Sprite spritePj1(texPj1);
    sf::Sprite spriteMapa(mapa);;
    sf::Sprite spriteCasilla(casilla);
    sf::Sprite spriteCursor(cursor);
    
    mapa.setSmooth(true);
    texPj1.setSmooth(true);
    casilla.setSmooth(true);
    cursor.setSmooth(true);
    
    //Le pongo el centroide donde corresponde
    spriteMapa.setOrigin(0,0);
    spritePj1.setOrigin(0,0);
    spriteCasilla.setOrigin(0,0);
    spriteCursor.setOrigin(0,0);
    
    //Cojo el sprite que me interesa por defecto del sheet
    spritePj1.setTextureRect(sf::IntRect(0, 0, 20, 20));
    spriteMapa.setTextureRect(sf::IntRect(0, 0, 480, 320));
    spriteCasilla.setTextureRect(sf::IntRect(0, 0, 20, 20));
    spriteCursor.setTextureRect(sf::IntRect(0, 0, 20, 20));

    // Lo dispongo en el centro de la pantalla
    spriteMapa.setPosition(0,0);
    spritePj1.setPosition(0, 0);
    spriteCursor.setPosition(240, 160);
    
    int valorSprite = 1;
    bool siguienteSumar = true;
    
    //Bucle del juego
    while (window.isOpen())
    {
        sf::Time tiempoPasado = clockSaltitos.getElapsedTime();
        
        if(tiempoPasado.asSeconds()>=0.3)
        {
            if(valorSprite == 0)
            {
                siguienteSumar = true;
                valorSprite = 2;
            }
            else
            {
                if(valorSprite == 4){
                    siguienteSumar = false;
                    valorSprite = 2;
                }
                else
                {
                    if(siguienteSumar == true){
                        valorSprite = 4;
                        siguienteSumar = false;
                    }
                    else
                    {
                        valorSprite = 0;
                        siguienteSumar = true;
                    }
                }
            }
            
            //std::cerr << "ValorSprite: " << valorSprite << "   tiempoPasado: " << tiempoPasado.asSeconds();
            spritePj1.setTextureRect(sf::IntRect(valorSprite*16, 0, 16, 16));
            clockSaltitos.restart();
            
            window.clear();
            window.draw(spriteMapa);
            window.draw(spritePj1);
            window.display();
            
        }
    
        //Bucle de obtención de eventos
        
        sf::Event event;
        sf::Time tiempoPasadoMovimiento;
        
        int valorSpriteMovimiento = 0;
        float destino;
                
        while (window.pollEvent(event))
        {
            switch(event.type){
                
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break; 
                
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
                        
                        case sf::Keyboard::M:
                            
                            //Mostrar casillas disponibles
                            std::cerr << "Posicion de spritePj1-> x: " << spritePj1.getPosition().x << "   y: " << spritePj1.getPosition().y << std::endl;
                            
                            break;
                        //Mapeo del cursor
                        case sf::Keyboard::Right:
                            
                            ///////////////////////////////////////////////////////////////////////////////
                            //Escala por defecto
                            spritePj1.setScale(1,1);
                            
                            clockSaltitos.restart();
                            
                            destino = spritePj1.getPosition().x+16.0;
                            
                            while(spritePj1.getPosition().x != destino){
                                
                                tiempoPasadoMovimiento = clockSaltitos.getElapsedTime();
                                if(tiempoPasadoMovimiento.asSeconds() >= 0.1){
                                    spritePj1.move(1,0);
                                    spritePj1.setTextureRect(sf::IntRect(valorSpriteMovimiento, 32, 20, 20));
                                    
                                    window.clear();
                                    window.draw(spriteMapa);
                                    window.draw(spritePj1);
                                    window.display();
            
                                    if(valorSpriteMovimiento != 96){
                                        valorSpriteMovimiento = valorSpriteMovimiento+32;
                                    }
                                    else
                                    {
                                        valorSpriteMovimiento = 0;
                                    }
                                    
                                    clockSaltitos.restart();
                                }
                            }
                            
                            spritePj1.setTextureRect(sf::IntRect(0, 0, 16, 16));
                            
                            
                            ///////////////////////////////////////////////////////////////////////////////
                        break;
                        
                        case sf::Keyboard::Left:
                            
                            ///////////////////////////////////////////////////////////////////////////////
                            
                            
                            clockSaltitos.restart();
                            
                            destino = spritePj1.getPosition().x-16.0;
                            
                            while(spritePj1.getPosition().x != destino){
                                
                                tiempoPasadoMovimiento = clockSaltitos.getElapsedTime();
                                if(tiempoPasadoMovimiento.asSeconds() >= 0.1){
                                    spritePj1.move(-1,0);
                                    spritePj1.setTextureRect(sf::IntRect(valorSpriteMovimiento, 64, 20, 20));
                                    
                            
                            
                                    window.clear();
                                    window.draw(spriteMapa);
                                    window.draw(spritePj1);
                                    window.display();
            
                                    if(valorSpriteMovimiento != 96){
                                        valorSpriteMovimiento = valorSpriteMovimiento+32;
                                    }
                                    else
                                    {
                                        valorSpriteMovimiento = 0;
                                    }
                                    
                                    clockSaltitos.restart();
                                }
                            }
                            
                            spritePj1.setTextureRect(sf::IntRect(0, 0, 16, 16));
                            
                            
                            ///////////////////////////////////////////////////////////////////////////////
                        break;
                        
                        case sf::Keyboard::Down:
                            
                            ///////////////////////////////////////////////////////////////////////////////
                            //Escala por defecto
                            spritePj1.setScale(1,1);
                            
                            clockSaltitos.restart();
                            
                            destino = spritePj1.getPosition().y+16.0;
                            
                            while(spritePj1.getPosition().y != destino){
                                
                                tiempoPasadoMovimiento = clockSaltitos.getElapsedTime();
                                if(tiempoPasadoMovimiento.asSeconds() >= 0.1){
                                    spritePj1.move(0,1);
                                    spritePj1.setTextureRect(sf::IntRect(valorSpriteMovimiento, 96, 20, 20));
                                    
                                    window.clear();
                                    window.draw(spriteMapa);
                                    window.draw(spritePj1);
                                    window.display();
            
                                    if(valorSpriteMovimiento != 96){
                                        valorSpriteMovimiento = valorSpriteMovimiento+32;
                                    }
                                    else
                                    {
                                        valorSpriteMovimiento = 0;
                                    }
                                    
                                    clockSaltitos.restart();
                                }
                            }
                            
                            spritePj1.setTextureRect(sf::IntRect(0, 0, 16, 16));
                            
                            
                            ///////////////////////////////////////////////////////////////////////////////
                        break;
                        
                        case sf::Keyboard::Up:
                            
                            ///////////////////////////////////////////////////////////////////////////////
                            //Escala por defecto
                            spritePj1.setScale(1,1);
                            
                            clockSaltitos.restart();
                            
                            destino = spritePj1.getPosition().y-16.0;
                            
                            while(spritePj1.getPosition().y != destino){
                                
                                tiempoPasadoMovimiento = clockSaltitos.getElapsedTime();
                                if(tiempoPasadoMovimiento.asSeconds() >= 0.1){
                                    spritePj1.move(0,-1);
                                    spritePj1.setTextureRect(sf::IntRect(valorSpriteMovimiento, 128, 20, 20));
                                    
                                    window.clear();
                                    window.draw(spriteMapa);
                                    window.draw(spritePj1);
                                    window.display();
            
                                    if(valorSpriteMovimiento != 96){
                                        valorSpriteMovimiento = valorSpriteMovimiento+32;
                                    }
                                    else
                                    {
                                        valorSpriteMovimiento = 0;
                                    }
                                    
                                    clockSaltitos.restart();
                                }
                            }
                            
                            spritePj1.setTextureRect(sf::IntRect(0, 0, 16, 16));
                            
                            
                            ///////////////////////////////////////////////////////////////////////////////
                        break;
                        
                        
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                        break;
                        
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            std::cout << event.key.code << std::endl;
                        break;
                           
                        
                     break;
                    }
            }

            window.clear();
            window.draw(spriteMapa);
            window.draw(spritePj1);
            window.display();
            
        }
    }
    return 0;
}
