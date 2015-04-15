/* 
 * File:   Menu.cpp
 * Author: Constanza y Andrea
 * 
 * Created on 11 de marzo de 2015, 10:42
 */

#include "../headers/MenuPrincipal.h"
#include <iostream>
using namespace  std;
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

MenuPrincipal::MenuPrincipal(float width, float height) {
    
        
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
    fondo.setTexture(textura_fond);
    
    //creacion de sprites
    for(int i=0; i<MAX_NUM_SPRITE; i++){
        posicionado=false;
        for(int j=0; j<MAX_NUM_TEXT; j++){
            //error? - solucionado
            if((i==j) && (posicionado==false)){
                menu[i].setTexture(texturas[j]);
                menu[i].setOrigin(texturas[j].getSize().x/2, texturas[j].getSize().y/2);
                menu[i].setPosition(width/2, (aux)+(44.75*(j+1)));
                aux=aux+47;
                posicionado=true;
            }
        }
    }
    
    //cargar audios
    if (!mainmenu.loadFromFile("resources/menu.wav")){
        std::cerr << "Error al cargar el archivo de audio";
    }
    
    if (!mmcursor.loadFromFile("resources/MainMenu_Cursor.wav")){
        std::cerr << "Error al cargar el archivo de audio";
    }
        
    if (!mmselect.loadFromFile("resources/MainMenu_Select.wav")){
        std::cerr << "Error al cargar el archivo de audio";
    }
    
    
    // Le asignamos el buffer cargado
    menusonido.setBuffer(mainmenu);
    // establecemos el volumen a 20
    menusonido.setVolume(20);
    //reproducir audio del menu
    menusonido.play();
    
    //cargar el buffer y asignar volumen del cursor y de la seleccion
    cursor.setBuffer(mmcursor);
    cursor.setVolume(100);

    select.setBuffer(mmselect);
    select.setVolume(100);
    
    //inicializo la variable selected
    selectedItemIndex = 0;
}

MenuPrincipal::~MenuPrincipal() {
}

void MenuPrincipal::draw(sf::RenderWindow& window){
    
    //dibujo el fondo y los sprites guardados en el array menu
    window.draw(fondo);
    for(int i=0; i<MAX_NUM_SPRITE; i++){
        window.draw(menu[i]);
    }
}

void MenuPrincipal::MoveUp(){
    if((selectedItemIndex-1>0) ){   
        
        menu[selectedItemIndex-1].setScale(1,1);
        selectedItemIndex--;
        menu[selectedItemIndex-1].setScale(1.2,1.2);        
        cursor.play();
    }  
}

void MenuPrincipal::MoveDown(){
    if((selectedItemIndex<MAX_NUM_SPRITE)){  
        
        menu[selectedItemIndex].setScale(1.2,1.2);
        if(selectedItemIndex>0)
            menu[selectedItemIndex-1].setScale(1,1);
        selectedItemIndex++;
        cursor.play();
    }
}

void MenuPrincipal::Exit(sf::RenderWindow& window){
    
    time1 = sf::seconds(1);
    select.play();
    sf::sleep(time1);
    window.close();
    
}

int MenuPrincipal::getSelectedItemIndex(){
    return selectedItemIndex;
}

