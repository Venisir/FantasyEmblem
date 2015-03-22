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
    sf::RenderWindow window(sf::VideoMode(480, 320), "Fantasy Emblem");
    sf::Texture fondo_menu;
    sf::Texture botn1;
    sf::Texture botn2;
    sf::Texture botn3;
    
    sf::SoundBuffer mainmenu;
    sf::SoundBuffer mmcursor;
    sf::SoundBuffer mmselect;
    
    sf::Clock clock;
    sf::Time time1;
    
    int contador=0;
    
    bool continuar=false;
    bool hasonado1=false;
    bool hasonado2=false;
    bool hasonado3=false;
    
        if (!mainmenu.loadFromFile("resources/menu.wav")){
            std::cerr << "Error al cargar el archivo de audio";
        }
    
        if (!mmcursor.loadFromFile("resources/MainMenu_Cursor.wav")){
            std::cerr << "Error al cargar el archivo de audio";
        }
        
        if (!mmselect.loadFromFile("resources/MainMenu_Select.wav")){
            std::cerr << "Error al cargar el archivo de audio";
        }
    
        if (!fondo_menu.loadFromFile("resources/menu.png"))
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
        sf::Sprite fondo(fondo_menu);
        sf::Sprite boton1(botn1);
        sf::Sprite boton2(botn2);
        sf::Sprite boton3(botn3);
        
        //Poner coordenadas
        boton1.setOrigin(420/2,280/2);
        boton2.setOrigin(420/2,280/2);
        boton3.setOrigin(420/2,280/2);
        
        boton1.setPosition(480/2,68.25);
        boton2.setPosition(480/2,160);
        boton3.setPosition(480/2,251.75);
        
       // Creamos un sonido
	sf::Sound menusonido;
	// Le asignamos el buffer cargado
	menusonido.setBuffer(mainmenu);
	// establecemos el volumen a 80
	menusonido.setVolume(20);

        menusonido.play();
        
        sf::Sound cursor;
        cursor.setBuffer(mmcursor);
        cursor.setVolume(100);

	sf::Sound select;
        select.setBuffer(mmselect);
        select.setVolume(100);
        
        while (window.isOpen())
        {
            sf::Event event;
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
                            hasonado2=false;
                            hasonado3=false;
                            if(hasonado1==false){
                                cursor.play();
                                hasonado1=true;
                            }

                        }
                         if((event.mouseMove.y>=124) && (event.mouseMove.y<=177)){
                            boton1.setScale(1,1);
                            boton2.setScale(1.2,1.2);                            
                            boton3.setScale(1,1);
                            hasonado1=false;
                            hasonado3=false;
                            if(hasonado2==false){
                                cursor.play();
                                hasonado2=true;
                            }

                        }
                         if((event.mouseMove.y>=217) && (event.mouseMove.y<=270)){
                            boton1.setScale(1,1);
                            boton2.setScale(1,1);
                            boton3.setScale(1.2,1.2);
                            hasonado1=false;
                            hasonado2=false;
                            if(hasonado3==false){
                                cursor.play();
                                hasonado3=true;
                            }
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
                                time1 = sf::seconds(1);
                                select.play();
                                sf::sleep(time1);
                                window.close();
                            }
                        }
                    }       
                }
                if(event.type == sf::Event::KeyPressed){
                    switch(event.key.code){
                        case sf::Keyboard::Down:
                            if(contador==0){
                                boton1.setScale(1.2,1.2);
                                boton2.setScale(1,1);
                                boton3.setScale(1,1);
                                contador++;
                                //cout<<contador<<endl;
                                 hasonado2=false;
                                hasonado3=false;
                                if(hasonado1==false){
                                    cursor.play();
                                    hasonado1=true;
                                }
                                
                            }else if(contador==1){
                                boton1.setScale(1,1);
                                boton2.setScale(1.2,1.2);                            
                                boton3.setScale(1,1);
                                contador++;
                                //cout<<contador<<endl;
                                continuar=true;
                                hasonado1=false;
                                hasonado3=false;
                                if(hasonado2==false){
                                    cursor.play();
                                    hasonado2=true;
                                }
                            }else if(contador==2){
                                boton1.setScale(1,1);
                                boton2.setScale(1,1);
                                boton3.setScale(1.2,1.2);
                                contador++;
                                //cout<<contador<<endl;
                                hasonado1=false;
                                hasonado2=false;
                                if(hasonado3==false){
                                    cursor.play();
                                    hasonado3=true;
                                }
                            }
                            break;
                        case sf::Keyboard::Up:
                             if(contador==2 && continuar==true){
                                boton1.setScale(1.2,1.2);
                                boton2.setScale(1,1);
                                boton3.setScale(1,1);
                                contador--;
                                //cout<<contador<<endl;
                                continuar=false;
                                hasonado1=false;
                                hasonado2=false;
                                if(hasonado1==false){
                                    cursor.play();
                                    hasonado1=true;
                                }
                            }else if(contador==3){
                                boton1.setScale(1,1);
                                boton2.setScale(1.2,1.2);                            
                                boton3.setScale(1,1);
                                contador--;
                                //cout<<contador<<endl;
                                hasonado1=false;
                                hasonado3=false;
                                if(hasonado2==false){
                                    cursor.play();
                                    hasonado2=true;
                                }
                            }
                        break;
                        case sf::Keyboard::Return:
                            if(contador==3){
                                time1 = sf::seconds(1);
                                select.play();
                                sf::sleep(time1);
                                window.close();
                            }
                        break;  
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

