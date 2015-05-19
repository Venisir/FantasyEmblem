/* 
 * File:   Creditos.cpp
 * Author: Oliver Rull
 * 
 * Created on 19 de mayo de 2015, 19:21
 */

#include "../headers/Creditos.h"
#include "../headers/EstadoPause.h"
#include "../headers/Estado.h"
#include "../headers/Juego.h"

#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

//using namespace tinyxml2;
using namespace std;
using namespace sf;

Creditos* Creditos::pinstance = 0;

Creditos* Creditos::Instance () {
    if(pinstance == 0){ //¿Es la primera llamada?
        pinstance = new Creditos(); //Creamos la instancia
    }
    return pinstance; //Retornamos la direccion de la instancia
}

Creditos::Creditos() {
    //Realizar inicializaciones necesarias de la instancia
    fuente = new sf::Font();
    t_textoPause = new Text();
    reloj = new Clock();
    evento = new Event();
    t_textoPause3 = new Text();
    t_textoPause2 = new Text();
    t_textoPause4 = new Text();
    pause_close = new SoundBuffer();
    cpause = new Sound();
    per1=new Texture();
    sprite1=new Sprite();
    per3=new Texture();
    sprite3=new Sprite();
    per4=new Texture();
    sprite4=new Sprite();
     per2=new Texture();
    sprite2=new Sprite();
    init_State();
}

Creditos::~Creditos() {
    /*if(pinstance != NULL)*/ 
    delete fuente;
    delete t_textoPause;
    delete t_textoPause2;
    delete t_textoPause4;
    delete reloj;
    delete evento;
    delete t_textoPause3; 
    delete pinstance;
    delete pause_close;
    delete cpause;
    delete per1;
    delete sprite1;
    delete per2;
    delete sprite2;
    delete per3;
    delete sprite3;
    delete per4;
    delete sprite4;
}

void Creditos::init_State(){
    
    cont=0;
    cont3i=0;
    cont3j=0;
    cont4i=0;
    cont4j=0;
    cont1i=0;
    cont1j=0;
    cont2i=0;
    cont2j=0;
    fuente->loadFromFile("resources/font.ttf");
    
    if (!per2->loadFromFile("resources/ike.png"))
    {
        std::cerr << "Error cargando la imagen intro.png";
        exit(0);
    }
    if (!per1->loadFromFile("resources/black.png"))
    {
        std::cerr << "Error cargando la imagen intro.png";
        exit(0);
    }
    if (!per4->loadFromFile("resources/eirikaBatalla.png"))
    {
        std::cerr << "Error cargando la imagen espadachinBatalla.png";
        exit(0);
    }
    if (!per3->loadFromFile("resources/espadachinBatalla.png"))
    {
        std::cerr << "Error cargando la imagen eirikaBatalla.png";
        exit(0);
    }
    
    sprite1->setTexture(*per1);
    sprite1->setOrigin(0,0);
    sprite1->setTextureRect(IntRect(0,0,248,160));
    sprite1->setPosition(-80,160);
    
    sprite2->setTexture(*per2);
    sprite2->setOrigin(0,0);
    sprite2->setTextureRect(IntRect(0,0,248,160));
    sprite2->setPosition(290,160);
    
    sprite3->setTexture(*per3);
    sprite3->setOrigin(0,0);
    sprite3->setTextureRect(IntRect(0,0,248,160));
    sprite3->setPosition(-80,0);
    sprite3->setScale(0,0);
    
    sprite4->setTexture(*per4);
    sprite4->setOrigin(0,0);
    sprite4->setTextureRect(IntRect(0,0,248,160));
    sprite4->setPosition(290,0);
    sprite4->setScale(0,0);
    
    std::stringstream ss_textoPause;
    ss_textoPause << "Create by Hexaiden";
           
            
            
    std::string s_textoPause = ss_textoPause.str();
    
    //sf::Text t_textoPause(s_textoPause,*fuente,20);
    
    t_textoPause->setFont(*fuente);
    t_textoPause->setCharacterSize(20);
    t_textoPause->setString(s_textoPause);
    t_textoPause->setColor(sf::Color::White);
    
    //Centrar el texto
    sf::FloatRect textRect = t_textoPause->getLocalBounds();
    t_textoPause->setOrigin(textRect.left + textRect.width/2.0f,
                  textRect.top  + textRect.height/2.0f);
    t_textoPause->setPosition(sf::Vector2f(480/2.0f,320/2.0f));

    std::stringstream ss_textoPause2;
    ss_textoPause2 << 
            
            "EQUIPO DE TRABAJO"<<"\n"<<"\n"<<"\n"<<
            
            "Andrea Dura"<< "\n"<<
            "Alberto Salieto"<< "\n"<<
            "Beatriz Sabater"<< "\n"<<
            "Carlos Oliver"<< "\n"<<
            "Constanza Casquet"<< "\n"<<
            "Ricardo Valls"<< "\n";
            
    std::string s_textoPause2 = ss_textoPause2.str();
    
    //sf::Text t_textoPause(s_textoPause,*fuente,20);
    
    t_textoPause2->setFont(*fuente);
    t_textoPause2->setCharacterSize(18);
    t_textoPause2->setString(s_textoPause2);
    t_textoPause2->setColor(sf::Color::White);
    
    //Centrar el texto
    t_textoPause2->setOrigin(0,0);
    t_textoPause2->setPosition(135,320);
    
    
    std::stringstream ss_textoPause3;
    ss_textoPause3 << 
            
            "Fantasy Emblem";
            
    std::string s_textoPause3 = ss_textoPause3.str();
    
    //sf::Text t_textoPause(s_textoPause,*fuente,20);
    
    t_textoPause3->setFont(*fuente);
    t_textoPause3->setCharacterSize(32);
    t_textoPause3->setString(s_textoPause3);
    t_textoPause3->setColor(sf::Color::White);
    
    //Centrar el texto
    t_textoPause3->setOrigin(0,0);
    t_textoPause3->setPosition(110,320);

    std::stringstream ss_textoPause4;
    ss_textoPause4 << 
            
            "Fundamentos de los videojuegos";
            
    std::string s_textoPause4 = ss_textoPause4.str();
    
    //sf::Text t_textoPause(s_textoPause,*fuente,20);
    
    t_textoPause4->setFont(*fuente);
    t_textoPause4->setCharacterSize(18);
    t_textoPause4->setString(s_textoPause4);
    t_textoPause4->setColor(sf::Color::White);
    
    //Centrar el texto
    t_textoPause4->setOrigin(0,0);
    t_textoPause4->setPosition(60,320);

    
    if (!pause_close->loadFromFile("resources/creditos.wav")){
        std::cerr << "Error al cargar el archivo de audio";
    }
    
    cpause->setBuffer(*pause_close);
    cpause->setVolume(80);
    cpause->setLoop(true);
    cpause->play();

}

void Creditos::render_State(){
    Juego::Instance()->getVentana()->clear();
    Juego::Instance()->getVentana()->draw(*t_textoPause);
    Juego::Instance()->getVentana()->draw(*t_textoPause2);
    Juego::Instance()->getVentana()->draw(*t_textoPause3);
    Juego::Instance()->getVentana()->draw(*t_textoPause4);
     Juego::Instance()->getVentana()->draw(*sprite1);
      Juego::Instance()->getVentana()->draw(*sprite2);
      Juego::Instance()->getVentana()->draw(*sprite3);
      Juego::Instance()->getVentana()->draw(*sprite4);
    Juego::Instance()->getVentana()->display();
}


void Creditos::update_State(){
    if (reloj->getElapsedTime().asMicroseconds() >= 10) {
        
        sprite2->setTextureRect(IntRect(cont2i*248,cont2j*160,248,160));
        sprite1->setTextureRect(IntRect(cont1i*248,cont1j*160,248,160));
        sprite4->setTextureRect(IntRect(cont4i*248,cont4j*160,248,160));
        sprite3->setTextureRect(IntRect(cont3i*248,cont3j*160,248,160));
        if(cont>10){
                if(cont1i==7){
                    cont1i=0;
                    cont1j++;
                }
                cont1i++;

                if(cont1i==7 && cont1j== 6){
                    cont1i = 0;
                    cont1j = 0;
                }
                if(cont2i==7){
                    cont2i=0;
                    cont2j++;
                }
                cont2i++;

                if(cont2i==7 && cont2j== 5){
                    cont2i = 0;
                    cont2j = 0;
                }
        }
         if(cont>60){
                sprite3->setScale(1,1);
                sprite4->setScale(1,1);
                if(cont3i==7){
                    cont3i=0;
                    cont3j++;
                }
                cont3i++;

                if(cont3i==7 && cont3j== 6){
                    cont3i = 0;
                    cont3j = 0;
                }
                if(cont4i==7){
                    cont4i=0;
                    cont4j++;
                }
                cont4i++;

                if(cont4i==7 && cont4j== 5){
                    cont4i = 0;
                    cont4j = 0;
                }
        }
        
        if(cont>10){
            t_textoPause->move(0,-1);
            //t_textoPause2->move(0,-1);
        } 
        
        if(cont>15){
            //t_textoPause->move(0,-1);
            t_textoPause2->move(0,-1);
        } 
        if(cont>250){
            //t_textoPause->move(0,-1);
            t_textoPause3->move(0,-1);
        } 
        
        if(cont>375 && cont<580){
            //t_textoPause->move(0,-1);
            t_textoPause4->move(0,-1);
        } 
        
        cont++;
        reloj->restart();
        
        input();
    }
}

void Creditos::input() {
    
    while (Juego::Instance()->getVentana()->pollEvent(*evento)){
        if ((evento->type == Event::Closed)){
            Juego::Instance()->getVentana()->close();
        }
            
        if(evento->type == sf::Event::KeyPressed){
            switch(evento->key.code){
                case sf::Keyboard::Numpad9:
                      Juego::Instance()->getVentana()->close();            
                break;
                case sf::Keyboard::Escape:
                    Juego::Instance()->getVentana()->close();               
                break;
            }
        }else{
            if(sf::Joystick::isConnected(0)){
                
                if(evento->type == sf::Event::JoystickButtonPressed){
                    
                    switch(evento->joystickButton.button){

                        case 9:
                            Juego::Instance()->getVentana()->close();  
                        break;
                    }
                }
            }
        }
    }
}