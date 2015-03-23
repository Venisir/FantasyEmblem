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
    
    window.setSize(sf::Vector2u(960, 640));
    
    XMLElement* elemento = doc.FirstChildElement("map");
    
    int ancho = elemento->IntAttribute("width");
    int alto = elemento->IntAttribute("height");
    string estado= "default";
    int state=0;//estado por defecto
    //array donde almacenaremos mediante un numero entero el paso a dar por el personaje (1 derecha,2 arriba,-1 izquierda,-2 abajo)
    int* recorrido= new int[2];//en este entregable de prueba lo hacemos con un array de tamaño 2
    int contador=0;
    
    Sprite sprite;
    Texture textura;
    Texture cursor;
    Texture movimiento;
    Texture texPj1;
    
    sf::Clock clockSaltitos;
    
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
    
    if (!texPj1.loadFromFile("resources/Mapa_espadachin.png"))
    {
        std::cerr << "Error cargando la imagen mapa.png";
        exit(0);
    }
    
    int matriz[ancho][alto];
    
    //Creo el spritesheet a partir de la imagen anterior
    Sprite spritePj1(texPj1);
    Sprite mapa[ancho][alto];
    Sprite spriteCursor(cursor);
    Sprite spriteMovimiento(movimiento);
    
    spritePj1.setTextureRect(sf::IntRect(0, 0, 20, 20));
    spritePj1.setOrigin(0,0);
    spritePj1.setPosition(160, 160);
    
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
    
    int valorSprite = 1;
    bool siguienteSumar = true;
    
    while(window.isOpen())
    {
        //BLOQUE DEL PERSONAJE
        Time tiempoPasado = clockSaltitos.getElapsedTime();
        
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
            /*
            window.clear();
            window.draw(spriteCursor);
            window.draw(spritePj1);
            window.display();
            */
        }
        
        Event evento;
        
        sf::Time tiempoPasadoMovimiento;
        
        int valorSpriteMovimiento = 0;
        float destino;
        
        
        while(window.pollEvent(evento))
        {
            switch(state)
            {
                case 0:/*estado por defecto*/
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
                                case sf::Keyboard::Return:
                                    estado="sel_movimiento";
                                    state=1;
                                    if(spriteCursor.getPosition()==spritePj1.getPosition()){
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

                                        mapa[c/16][f/16].setTexture(textura);
                                    }
                                break;
                            }
                        break;
                    }
                break;
                
                case 1://estado seleccionar el movimiento que tiene que hacer el personaje
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
                                    
                                    if(contador<2)
                                    {
                                        recorrido[contador]=1;
                                        contador++;
                                    }
                                break;

                                //Tecla izquierda
                                case sf::Keyboard::Left:
                                    if(spriteCursor.getPosition().x>=16)
                                        spriteCursor.move(-16,0);
                                    
                                    if(contador<2)
                                    {
                                        recorrido[contador]=-1;
                                        contador++;
                                    }
                                    
                                break;

                                //Tecla arriba
                                case sf::Keyboard::Up:
                                    if(spriteCursor.getPosition().y>=16)
                                        spriteCursor.move(0,-16);
                                    
                                    if(contador<2)
                                    {
                                        recorrido[contador]=2;
                                        contador++;
                                    }
                                break;

                                //Tecla abajo
                                case sf::Keyboard::Down:
                                    if(spriteCursor.getPosition().y<=302)
                                        spriteCursor.move(0,16);
                                    
                                    if(contador<2)
                                    {
                                        recorrido[contador]=-2;
                                        contador++;
                                    }
                                    
                                break;
                                
                                case sf::Keyboard::Return:
                                    
                                    if(contador!=0)//si se ha decidido algun movimiento para el personaje
                                    {
                                        state=2;
                                        estado="movimientopj";
                                    }
                                    else
                                    {
                                        state=0;
                                        estado="default";
                                    }
                                    
                                    for(int i=0;i<ancho;i++)
                                    {
                                        for(int j=0;j<alto;j++)
                                        {
                                            mapa[i][j].setTexture(textura);
                                        }
                                    }
                                    
                                break;
                            }
                        break;
                    }
                break;
                
                case 2:
                    for(int i=0;i < contador;i++)
                    {
                        switch(recorrido[i])
                        {
                            case 1://derecha
                                clockSaltitos.restart();

                                destino = spritePj1.getPosition().x+16.0;

                                while(spritePj1.getPosition().x != destino){

                                    tiempoPasadoMovimiento = clockSaltitos.getElapsedTime();
                                    if(tiempoPasadoMovimiento.asSeconds() >= 0.1){
                                        spritePj1.move(1,0);
                                        spritePj1.setTextureRect(sf::IntRect(valorSpriteMovimiento, 32, 20, 20));

                                        //////////////////////////////////////////////////
                                        window.clear();
                                        for(int i=0;i<ancho;i++)
                                        {
                                            for(int j=0;j<alto;j++)
                                            {
                                                window.draw(mapa[i][j]);
                                            }
                                        }
                                        window.draw(spritePj1);
                                        window.display();
                                        //////////////////////////////////////////////////

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
                                
                                break;

                            case 2://arriba
                                
                                clockSaltitos.restart();
                                
                                destino = spritePj1.getPosition().y-16.0;
                                
                                while(spritePj1.getPosition().y != destino){
                                
                                    tiempoPasadoMovimiento = clockSaltitos.getElapsedTime();
                                    if(tiempoPasadoMovimiento.asSeconds() >= 0.1){
                                        spritePj1.move(0,-1);
                                        spritePj1.setTextureRect(sf::IntRect(valorSpriteMovimiento, 128, 20, 20));

                                        //////////////////////////////////////////////////
                                        window.clear();
                                        for(int i=0;i<ancho;i++)
                                        {
                                            for(int j=0;j<alto;j++)
                                            {
                                                window.draw(mapa[i][j]);
                                            }
                                        }
                                        window.draw(spritePj1);
                                        window.display();
                                        //////////////////////////////////////////////////

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
                                
                                break;

                            case -1://izquierda
                                
                                clockSaltitos.restart();
                                
                                destino = spritePj1.getPosition().x-16.0;
                                
                                while(spritePj1.getPosition().x != destino){
                                
                                    tiempoPasadoMovimiento = clockSaltitos.getElapsedTime();
                                    if(tiempoPasadoMovimiento.asSeconds() >= 0.1){
                                        spritePj1.move(-1,0);
                                        spritePj1.setTextureRect(sf::IntRect(valorSpriteMovimiento, 64, 20, 20));

                                        //////////////////////////////////////////////////
                                        window.clear();
                                        for(int i=0;i<ancho;i++)
                                        {
                                            for(int j=0;j<alto;j++)
                                            {
                                                window.draw(mapa[i][j]);
                                            }
                                        }
                                        window.draw(spritePj1);
                                        window.display();
                                        //////////////////////////////////////////////////
                                        
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
                                
                                break;

                            case -2://abajo
                                clockSaltitos.restart();

                                destino = spritePj1.getPosition().y+16.0;
                                
                                while(spritePj1.getPosition().y != destino){

                                    tiempoPasadoMovimiento = clockSaltitos.getElapsedTime();
                                    if(tiempoPasadoMovimiento.asSeconds() >= 0.1){
                                    spritePj1.move(0,1);
                                    spritePj1.setTextureRect(sf::IntRect(valorSpriteMovimiento, 96, 20, 20));

                                        //////////////////////////////////////////////////
                                        window.clear();
                                        for(int i=0;i<ancho;i++)
                                        {
                                            for(int j=0;j<alto;j++)
                                            {
                                                window.draw(mapa[i][j]);
                                            }
                                        }
                                        window.draw(spritePj1);
                                        window.display();
                                        //////////////////////////////////////////////////

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
                                
                                break; 
                        }
                    }
                    contador=0;
                    state=0;
                    estado="default";
                break;
            /*fin switch estado*/        
            }
        }
        
        for(int i=0;i<ancho;i++)
        {
            for(int j=0;j<alto;j++)
            {
                window.draw(mapa[i][j]);
            }
        }
        
        window.draw(spritePj1);
        window.draw(spriteCursor);
        window.display(); 
    }
    
    

    return 0;
}

