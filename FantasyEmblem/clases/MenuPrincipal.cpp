/* 
 * File:   Menu.cpp
 * Author: Constanza y Andrea
 * 
 * Created on 11 de marzo de 2015, 10:42
 */

#include "../headers/MenuPrincipal.h"
#include "../headers/Estado.h"
#include "../headers/Juego.h"

#include <iostream>
#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace  std;

MenuPrincipal* MenuPrincipal::pinstance = 0;

MenuPrincipal* MenuPrincipal::Instance () {
    if(pinstance == 0){ //¿Es la primera llamada?
        pinstance = new MenuPrincipal(); //Creamos la instancia
    }
    return pinstance; //Retornamos la direccion de la instancia
}

MenuPrincipal::MenuPrincipal() {
    
    //Realizar inicializaciones necesarias de la instancia
    fondo_menu = new Texture();
    botn1 = new Texture();
    botn2 = new Texture();
    botn3 = new Texture();
    
    for(int i=0; i<MAX_NUM_TEXT; i++){
        texturas[i] = new Texture();
    }
    
    for(int i=0; i<MAX_NUM_SPRITE; i++){
        menu[i] = new Sprite();
    }
    textura_fond = new Texture();
    fondo = new Sprite();
    //time1 = new Time();
    mainmenu = new SoundBuffer();
    mmcursor = new SoundBuffer();
    mmselect = new SoundBuffer();
    menusonido = new Sound();
    cursor = new Sound();
    select = new Sound(); 
    
    reloj = new Clock();
    evento = new Event();
    
    init_State();
}

MenuPrincipal::~MenuPrincipal() {
    delete fondo_menu;
    delete botn1;
    delete botn2;
    delete botn3;
    //delete[] texturas;
    delete textura_fond;
    //delete[] menu;
    delete fondo;
    //delete time1;
    delete mainmenu;
    delete mmcursor;
    delete mmselect;
    delete menusonido;
    delete cursor;
    delete select;  
    
    for(int i=0; i<MAX_NUM_TEXT; i++){
        delete texturas[i];
    }
    
    for(int i=0; i<MAX_NUM_SPRITE; i++){
        delete menu[i];
    }
    
    delete reloj;
    delete evento;
}

void MenuPrincipal::init_State() {

    if (!fondo_menu->loadFromFile("resources/menu.png"))
    {
        std::cerr << "Error cargando la imagen menu.png";
        exit(0);
    }
        
    if (!botn1->loadFromFile("resources/boton1.png"))
    {
        std::cerr << "Error cargando la imagen boton1.png";
        exit(0);
    }
        
    if (!botn2->loadFromFile("resources/boton2.png"))
    {
        std::cerr << "Error cargando la imagen boton2.png";
        exit(0);
    }
        
    if (!botn3->loadFromFile("resources/boton3.png"))
    {
        std::cerr << "Error cargando la imagen boton3.png";
        exit(0);
    }
    
    for(int i=0; i<MAX_NUM_TEXT; i++){
        if(i==0)
            texturas[i] = botn1;
        if(i==1)
            texturas[i] = botn2;
        if(i==2)
            texturas[i] = botn3;
    }
    
    int aux=47/2;
    bool posicionado;
    
    textura_fond = fondo_menu;
    fondo->setTexture(*textura_fond);
    
    //creacion de sprites
    for(int i=0; i<MAX_NUM_SPRITE; i++){
        posicionado=false;
        for(int j=0; j<MAX_NUM_TEXT; j++){
            //error? - solucionado
            if((i==j) && (posicionado==false)){
                menu[i]->setTexture(*texturas[j]);
                menu[i]->setOrigin(texturas[j]->getSize().x/2, texturas[j]->getSize().y/2);
                menu[i]->setPosition(480/2, (aux)+(44.75*(j+1)));
                aux=aux+47;
                posicionado=true;
            }
        }
    }
    
    //cargar audios
   /* if (!mainmenu->loadFromFile("resources/menu.wav")){
        std::cerr << "Error al cargar el archivo de audio";
    }*/
    
    if (!mmcursor->loadFromFile("resources/MainMenu_Cursor.wav")){
        std::cerr << "Error al cargar el archivo de audio";
    }
        
    if (!mmselect->loadFromFile("resources/MainMenu_Select.wav")){
        std::cerr << "Error al cargar el archivo de audio";
    }
    
    
    //cargar el buffer y asignar volumen del cursor y de la seleccion
    cursor->setBuffer(*mmcursor);
    cursor->setVolume(100);

    select->setBuffer(*mmselect);
    select->setVolume(100);
    
    //inicializo la variable selected
    selectedItemIndex = 0;
    
    //Para que por defecto este seleccionada la Nueva Partida
    menu[selectedItemIndex]->setScale(1.2,1.2);
    selectedItemIndex++;
        
}

void MenuPrincipal::MoveUp(){
    if((selectedItemIndex-1>0) ){   
        
        menu[selectedItemIndex-1]->setScale(1,1);
        selectedItemIndex--;
        menu[selectedItemIndex-1]->setScale(1.2,1.2);        
        cursor->play();
    }  
}

void MenuPrincipal::MoveDown(){
    if((selectedItemIndex<MAX_NUM_SPRITE)){
        menu[selectedItemIndex]->setScale(1.2,1.2);
        if(selectedItemIndex>0)
            menu[selectedItemIndex-1]->setScale(1,1);
        selectedItemIndex++;
        cursor->play();
    }
}

void MenuPrincipal::render_State(){
    Juego::Instance()->getVentana()->clear();
    
    //dibujo el fondo y los sprites guardados en el array menu
    Juego::Instance()->getVentana()->draw(*fondo);
    
    for(int i=0; i<MAX_NUM_SPRITE; i++){
        Juego::Instance()->getVentana()->draw(*menu[i]);
    }
    
    Juego::Instance()->getVentana()->display();
}


void MenuPrincipal::update_State(){
    if (reloj->getElapsedTime().asMilliseconds() >= 100) {
        reloj->restart();
        
        input();
    }
}

void MenuPrincipal::Exit(){
    time1 = seconds(1);
    select->play();
    sleep(time1);
    Juego::Instance()->getVentana()->close();
}

int MenuPrincipal::getSelectedItemIndex(){
    return selectedItemIndex;
}

void MenuPrincipal::input(){
    
    while (Juego::Instance()->getVentana()->pollEvent(*evento))
    {
        if ((evento->type == sf::Event::Closed)){
            Juego::Instance()->getVentana()->close();
        }
                   
        if(evento->type == sf::Event::KeyPressed){
            switch(evento->key.code){
                case sf::Keyboard::Down:
                    MoveDown();
                break;
                case sf::Keyboard::Up:
                    MoveUp();
                break;
                        
                case sf::Keyboard::Return:
                    if(getSelectedItemIndex()==1){
                        PantallaStart::Instance()->pararmusica();
                        Juego::Instance()->ponerEstadoEscenario();
                    }      
                    if(getSelectedItemIndex()==2){
                        Juego::Instance()->ponerEstadoEscenario();
                        Juego::Instance()->reiniciarEstadoEscenario();
                    }      
                    if(getSelectedItemIndex()==3){
                        Exit();
                    }      
                break;  
            }
        }else{
            if(sf::Joystick::isConnected(0)){
                
                if (evento->type == sf::Event::JoystickMoved)
                {
                    if (evento->joystickMove.axis == sf::Joystick::PovX){
                        if(evento->joystickMove.position == -100){
                            MoveDown();
                        }else if(evento->joystickMove.position == +100){
                            MoveUp();
                        }
                    }
                }
                
                if(evento->type == sf::Event::JoystickButtonPressed){
                    
                    switch(evento->joystickButton.button){

                        case 2:
                            if(getSelectedItemIndex()==1){
                                PantallaStart::Instance()->pararmusica();
                                Juego::Instance()->ponerEstadoEscenario();
                            }      
                            if(getSelectedItemIndex()==2){
                                Juego::Instance()->ponerEstadoEscenario();
                                Juego::Instance()->reiniciarEstadoEscenario();
                            }      
                            if(getSelectedItemIndex()==3){
                                Exit();
                            }
                        break;
                    }
                }
            }
        }
    }
}

