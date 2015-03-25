#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string>
#include "tinyxml2.h"

//Incluyo la clase Game
#include "Game.h"

using namespace tinyxml2;
using namespace std;
using namespace sf;

int main() {
    
    //Creo la ventana
    RenderWindow window(sf::VideoMode(480,320), "Fantasy Emblem");
    window.setSize(sf::Vector2u(960, 640));
    window.setFramerateLimit(60);
    
    //Creo una instancia de juego en memoria dinamica
    Game* juego=new Game(&window);
    
    sf::Clock reloj;
    sf::Clock updateClock;
    
    int state = 0;
    
    //Ejecuto el juego
    
    juego->init();
    
    while (window.isOpen()){
        
        Event evento;
        
        while(window.pollEvent(evento))
        {
            switch(state)
            {
                case 0://estado por defecto
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
                        break;
                    }
                    break;
            }
        }
                                
        delete evento;
        
        juego->update();
        juego->render();
    }
    
    //El juego termina y lo borro
    delete juego;
    //Acabo la aplicacion
    return 0;
}


/////////////////////////////////////////////////

/*
int main()
{
    
    XMLDocument doc;
    RenderWindow window(sf::VideoMode(480,320), "Fantasy Emblem");
        
    doc.LoadFile("niveles/mapaTiled.tmx");
    
    window.setSize(sf::Vector2u(960, 640));
    
    XMLElement* elemento = doc.FirstChildElement("map");
    
    //variables que recojen el ancho y alto del tileset para poder crear la matriz
    int ancho = elemento->IntAttribute("width");
    int alto = elemento->IntAttribute("height");
    string estado= "default";
    int state=0;//estado por defecto
    //array donde almacenaremos mediante un numero entero el paso a dar por el personaje (1 derecha,2 arriba,-1 izquierda,-2 abajo)
    int* recorrido= new int[2];//en este entregable de prueba lo hacemos con un array de tamaño 2
    int contador=0;//contador para recorrer el array del recorrido
    
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
    
    int matriz[ancho][alto];//matriz de enteros que recojera los valores alojados en el tmx
    
    //Creacion de los sprites personaje,cursor y la matriz de sprites
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
    
    //el siguiente bloque de código es para que el personaje realice una animacion de movimiento (mas bien respiracion) cuando esta quieto
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
            
            
            spritePj1.setTextureRect(sf::IntRect(valorSprite*16, 0, 16, 16));
            clockSaltitos.restart();
        }
        
        Event evento;//variable de tipo event que recojera los distintos tipos de eventos que pueden ocurrir cuando la ventana esta abierta
        
        sf::Time tiempoPasadoMovimiento;
        
        int valorSpriteMovimiento = 0;//indice de la animacion de sprites de movimiento
        float destino;//variable que almacena el destino del movimiento del personaje
        
        
        while(window.pollEvent(evento))
        {
            switch(state)
            {
                case 0://estado por defecto
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

                                //Tecla enter
                                case sf::Keyboard::Return:
                                    //muestra la cuadricula del personaje si el personaje y el cursor estan en la misma posicion                                    
                                    if(spriteCursor.getPosition()==spritePj1.getPosition()){
                                        int c= (int)(spriteCursor.getPosition().x);//posicion x
                                        int f= (int)(spriteCursor.getPosition().y);//posicion y

                                        //(los 16 es por el tamaño del sprite) se recorre desde x-1,y-1 hasta x+1,y+1 pintando asi la cuadricula
                                        for(int i=f-16;i<=f+16;i+=16)
                                        {
                                            for(int j=c-16;j<=c+16;j+=16)
                                            {
                                                //se diferencian 4 casos uno para cada direccion (arriba,abajo,izquierda,derecha) y se pinta un cuadrado mas en funcion de la direccion pertinente
                                                if(i==f-16 && j==c)
                                                {
                                                    mapa[j/16][(i-16)/16].setTexture(movimiento);//arriba
                                                }
                                                else if(i==f+16 && j==c)
                                                {
                                                    mapa[j/16][(i+16)/16].setTexture(movimiento);//abajo
                                                }
                                                else if(i==f && j==c-16)
                                                {
                                                   mapa[(j-16)/16][i/16].setTexture(movimiento); //izquierda
                                                }
                                                else if(i==f && j==c+16)
                                                {
                                                    mapa[(j+16)/16][i/16].setTexture(movimiento); //derecha
                                                }

                                                mapa[j/16][i/16].setTexture(movimiento);//se pinta la posicion del centro con la textura original para que quede libre de la cuadricula
                                            }
                                        }

                                        mapa[c/16][f/16].setTexture(textura);
                                        estado="sel_movimiento";
                                        state=1;//pasa al estado de seleccion de movimiento
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
                                    //Si no se han introducido el numero maximo de valores en el array que almacena el recorrido, almacena el entero correspondiente a la direccion seleccionada
                                     Se aplica en las 4 direcciones
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
                                        state=2;//pasa al estado de movimiento
                                        estado="movimientopj";
                                    }
                                    else
                                    {
                                        state=0;//pasa al estado por defecto
                                        estado="default";
                                    }
                                    
                                    //refresca el mapa para hacer desaparecer la cuadricula
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
                    state=0;
                    estado="default";
                    for(int i=0;i < contador;i++)//recorre el array que ha almacenado el recorrido en funcion de los elementos que contenga
                    {
                        switch(recorrido[i])
                        {
                            case 1://derecha
                                clockSaltitos.restart();//se reinicia el clock que hace la animacion de movimiento

                                destino = spritePj1.getPosition().x+16.0;//se almacena el destino del personaje

                                while(spritePj1.getPosition().x != destino){//mientras no haya llegado al destino

                                    tiempoPasadoMovimiento = clockSaltitos.getElapsedTime();//se almacela el tiempo pasado 
                                    if(tiempoPasadoMovimiento.asSeconds() >= 0.1){
                                        spritePj1.move(1,0);//movemos el sprite/
                                        //cambiamos el sprite por el sprite correspondiente del spritesheet gracias a la variable valorSpriteMovimiento
                                        spritePj1.setTextureRect(sf::IntRect(valorSpriteMovimiento, 32, 20, 20));

                                        //////////////////////////////////////////////////
                                        window.clear();//limpia la ventana
                                        //resfesca el mapa 
                                        for(int i=0;i<ancho;i++)
                                        {
                                            for(int j=0;j<alto;j++)
                                            {
                                                window.draw(mapa[i][j]);
                                            }
                                        }
                                        window.draw(spritePj1);//pinta el sprite del personaje
                                        window.display();
                                        //////////////////////////////////////////////////

                                        if(valorSpriteMovimiento != 96){//aumenta en 32 cada vez el valor de la variable para indicar la posicion x del spritesheet
                                            valorSpriteMovimiento = valorSpriteMovimiento+32;
                                        }
                                        else
                                        {
                                            valorSpriteMovimiento = 0;
                                        }
                                        clockSaltitos.restart();
                                    }
                                }
                                //una vez ha terminado de hacer el movimiento vuelve a su posicion original
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

                break;
            //fin switch estado    
            }
        }
        
        //refresco del mapa
        for(int i=0;i<ancho;i++)
        {
            for(int j=0;j<alto;j++)
            {
                window.draw(mapa[i][j]);
            }
        }
        
        ///pinta persinaje y cursor
        window.draw(spritePj1);
        window.draw(spriteCursor);
        window.display(); 
    }
    
    

    return 0;
}
*/
