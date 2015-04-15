#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <sstream>



#define kVel 10
#define kVel2 20

int main()
{
    
    //con estas dos variables seremos capaces de acceder a cualquier sprite del sheet que generemos
    int i=0;
    int j=0;
    int goles=0;
    
    
    //para mover la porteria usaremos una variable para denotar el sentido en el cual se mueve (0 derecha, 1 izquierda)
    int sentido=1;

    std::stringstream s;
    
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(640, 480), "P0. Fundamentos de los Videojuegos. DCCIA");

    //Cargo la imagen donde reside la textura del sprite
    sf::Texture tex;
    sf::Texture tex2;
    
    //texto y fuente
    sf::Text texto;
    sf::Font font;
    
    if(!font.loadFromFile("resources/arial.ttf"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    
    texto.setFont(font);
    texto.setColor(sf::Color::Red);
    texto.setPosition(10,450);
    texto.setCharacterSize(24);
    
    //primeramente recojo la textura para formar el sprite de la porteria
    if (!tex.loadFromFile("resources/porteria.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    
    //creo el sprite de la porteria
    sf::Sprite porteria;
    porteria.setTexture(tex);
    int anchoporteria= porteria.getTexture()->getSize().x;
    // Lo dispongo en el centro de la pantalla
    porteria.setPosition(320-anchoporteria/2, 0);

    //Cargo la textura de la pelota
    if (!tex2.loadFromFile("resources/pelota.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    sf::Sprite pelota;
    pelota.setTexture(tex2);
    
	//Le pongo el centroide donde corresponde
    pelota.setOrigin(65/2,65/2);
    

    
    // Lo dispongo en el centro de la pantalla
    pelota.setPosition(320, 420);

    
    //creamos e iniciamos el reloj, el reloj lo usaremos para cada cierto tiempo cambiar el sprite de la pelota
    sf::Clock clock;
    
    sf::Clock clock2;//con este reloj controlaremos el movimiento de la porteria
	

    //Bucle del juego
    while (window.isOpen())
    {
        //Bucle de obtención de eventos
        sf::Event event;
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
                        
                        //Mapeo del cursor
                        case sf::Keyboard::Right:
                            //Escala por defecto
                            pelota.setScale(1,1);
                            pelota.move(kVel,0);
                        break;

                        case sf::Keyboard::Left:
                            pelota.setScale(1,1);
                            pelota.move(-kVel,0); 
                        break;
                                                
                        
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                        break;
                        
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            std::cout << event.key.code << std::endl;
                        break;
                              
                    }

            }
            
        }

        //selecciono el sprite que quiero del sheet
        pelota.setTextureRect(sf::IntRect(i*65, j*65, 65, 65));
        
        //cada cierto tiempo cambiamos las variables que afeceta a la seleccion del sprite de la pelota
        if(clock.getElapsedTime().asMilliseconds()>= 200)
        {
            //a cada intervalo de 200 milisegundos incremento j para seleccionar un sprite diferente
            j++;
            if(j==2)//he llegado al numero maximo de columnas del sheet, j=0 e incremento i
            {
                j=0;
                i++;
            }
            
            //este if controla el caso en el que se haya llegado a la parte deseada (fila) del spritesheet, por tanto reinicia el contador
            if(i==2)
            {
                i=0;
            }
	
            
            //movimiento automatico de la pelota
            pelota.move(0,-kVel);
            
            //movimiento de la porteria
            if(sentido==0)
            {
                porteria.move(kVel2,0);
            }
            else
            {
                porteria.move(-kVel2,0);
            }     
            
            //con este bloque se controlan los casos donde la porteria/pelota vayan a salir de la ventana
            //en el caso de la porteria cambia el sentido para moverse en la dirección contraria, en el de la pelota vuelve a la posicion original
            if(porteria.getPosition().x <0)
            {
                sentido=0;
            }
            if(porteria.getPosition().x + anchoporteria > window.getSize().x)
            {
                sentido=1;
            }

            if(pelota.getPosition().y < 0)
            {
                pelota.setPosition(320, 420);
            }

            //colision de la pelota con la porteria
            if(pelota.getGlobalBounds().intersects(porteria.getGlobalBounds()))
            {
                goles++;
                pelota.setPosition(320,420);
            }
            

            
            clock.restart();//reinicio el clock
        }
        s << "Goles: " << goles;
        texto.setString(s.str());
        s.str("");
        
              
        window.clear();
        window.draw(porteria);
        window.draw(pelota);
        window.draw(texto);
        window.display();
    }

    return 0;
}

