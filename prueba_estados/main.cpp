#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <sstream>

using namespace std;
using namespace sf;


int main()
{
    int estado=0;
    int estadoanterior=estado;
    string s;
    
    sf::RenderWindow window(sf::VideoMode(640, 480), "P0. Fundamentos de los Videojuegos. DCCIA");
    
    cout << "Hola, empezamos en el estado por defecto" << endl;
    
    while(estado!=-1)
    {  
        Event evento;
        while(window.pollEvent(evento))
        {
            switch(estado)
            {
                case 0:
                    switch(evento.type)
                    {
                        case Event::KeyPressed:
                            switch(evento.key.code)
                            {
                                case Keyboard::A:
                                    estadoanterior=estado;
                                    estado=1;
                                    cout << "Dejando estado 0 pasando a estado 1" << endl;
                                    break;
                                case Keyboard::Escape:
                                    estado=-1;
                                    break;
                                case Keyboard::B:
                                    cout << "Has pulsado la tecla b en el estado " << estado << endl;
                                    break;
                            }
                    }
                    break;
                break;

                case 1:
                    switch(evento.type)
                    {
                        case Event::KeyPressed:
                            switch(evento.key.code)
                            {
                                case Keyboard::A:
                                    cout << "Pasando a estado 3" << endl;
                                    estadoanterior=estado;
                                    estado=3;
                                    break;
                                case Keyboard::B:
                                    cout << "Has pulsado la tecla b en el estado " << estado << endl;
                                    break;
                                case Keyboard::J:
                                    cout << "El estado anterior al " << estado << "es el estado " << estadoanterior << endl;
                                    break;
                            }
                    }
                    break;
                break;

                case 3:
                    
                    switch(evento.type)
                    {
                        case Event::KeyPressed:
                            switch(evento.key.code)
                            {
                                case Keyboard::A:
                                    cout << "Paso a Estado 0" << endl;
                                    estadoanterior=estado;
                                    estado=0;
                                    break;
                                case Keyboard::B:
                                    cout << "Has pulsado la tecla b en el estado " << estado << endl;
                                    break;
                                    
                                case Keyboard::V:
                                    cout << "El estado anterior al " << estado << "es el estado " << estadoanterior << endl;
                            }
                    }
                    break;
                break;      
            }
        }    
    }
 
    return 0;
}

