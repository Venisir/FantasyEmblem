/* 
 * File:   EstadoConversacion.cpp
 * Author: Alberto
 * 
 * Created on 13 de mayo de 2015, 9:53
 */

#include "../headers/EstadoConversacion.h"

#include <sstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include "../tinyxml2.h"

using namespace tinyxml2;
using namespace std;
using namespace sf;

EstadoConversacion* EstadoConversacion::pinstance = 0;
EstadoConversacion* EstadoConversacion::Instance(Mapa* ma, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice,bool *turno,Objetos** obj, Armas** arm)
{
    if(pinstance==0)
    {
        pinstance=new EstadoConversacion(ma,al,ene,cofr,indice,turno,obj,arm);
    }
    return pinstance;
}

EstadoConversacion* EstadoConversacion::Instance() {
    return pinstance;
}



EstadoConversacion::EstadoConversacion()
{
    
}

void EstadoConversacion::reset() {
    pinstance=0;
}

EstadoConversacion::EstadoConversacion(Mapa* ma, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice, bool *turno,Objetos** obj, Armas** arm)
{
    
    texturaPersonajeIzq=new Texture();
    texturaPersonajeDer=new Texture();
    texturaPergamino=new Texture();
    
    personajeIzq= new Sprite();
    personajeDer=new Sprite();
    pergamino= new Sprite();
    
    reloj=new Clock();
    reloj2=new Clock();
    reloj3=new Clock();
    
    evento=new Event();
    
    recuadroTexto = new Text();
    nombre = new Text();
    
    fuente = new Font();
    
    m=ma;
    ali=al;
    enem=ene;
    cof=cofr;
    index=indice;
    
    arma = arma;
    objeto = obj;
    
    cambioMapa=-1;
    
    init_State();
}

EstadoConversacion::~EstadoConversacion() {
    delete texturaPersonajeIzq;
    delete texturaPersonajeDer;
    delete texturaPergamino;
    delete personajeIzq;
    delete personajeDer;
    delete pergamino;
    delete reloj;
    delete reloj2;
    delete reloj3;
    delete evento;
    delete m;
    delete ali;
    delete enem;
    delete cof;
    delete index;
    delete recuadroTexto;
    delete nombre;
    delete fuente;
}

void EstadoConversacion::setMapa(Mapa* me) {
    maux=me;
    cambioMapa=1;
}

void EstadoConversacion::init_State()
{
    if (!texturaPersonajeIzq->loadFromFile("resources/eirika.png"))
    {
            std::cerr << "Error cargando la imagen eirika.png";
            exit(0);
    }

    if (!texturaPersonajeDer->loadFromFile("resources/ike5.png"))
    {
            std::cerr << "Error cargando la imagen ike5.png";
            exit(0);
    }

    if (!texturaPergamino->loadFromFile("resources/pergamino.png"))
    {
            std::cerr << "Error cargando la imagen pergamino.png";
            exit(0);
    }
    
    personajeIzq->setTexture(*texturaPersonajeIzq);
    personajeDer->setTexture(*texturaPersonajeDer);
    pergamino->setTexture(*texturaPergamino);
    
    personajeIzq->setTextureRect(IntRect(0, 0, 169, 125));
    personajeDer->setTextureRect(IntRect(0, 0, 170, 127));
    /*posicionar sprites*/
    //personajeIzq->setOrigin(420/2,280/2);
    //personajeDer->setOrigin(420/2,280/2);
    //pergamino->setOrigin(420/2,280/2);
    
    //danyo->setScale(0,0);
    //menu->setScale(0,0);
    //cursorDedo->setScale(0,0);
    //objetos->setScale(0,0);

    //pergamino->setOrigin(100/2,480/2);
    
    personajeIzq->setPosition(0,128);
    personajeDer->setPosition(310,128);
    pergamino->setPosition(0,220);
    
    contX = 0;
    contY = 0;
    
    quienHabla = 0;
    
    
    //XMLDocument doc;
    doc.LoadFile("niveles/textos.tmx");
    //XMLElement* map;
    
    map = doc.FirstChildElement("map");
    escena = map->FirstChildElement("escena");
    texto = escena->FirstChildElement("texto");
    
    fuente->loadFromFile("resources/font.ttf");
    
    recuadroTexto->setColor(sf::Color::Black);
    recuadroTexto->setCharacterSize(16);
    recuadroTexto->setFont(*fuente);
    recuadroTexto->setPosition(40,260);
    
    nombre->setColor(sf::Color::White);
    nombre->setCharacterSize(16);
    nombre->setFont(*fuente);
    nombre->setPosition(69,229);
    
    siguienteTexto();
    //recuadroTexto->setString(texto->Attribute("textoL"));
     

}

void EstadoConversacion::render_State()
{
    Juego::Instance()->getVentana()->clear();
      
    m->Draw();
    for(int x=0; x<m->getNumEnemigos(); x++){
       // if(aliadas[x]!=NULL){
            //aliadas[x]->Draw();
        //}
        enem[x]->Draw();
    }
    
    for(int i=0; i<sizeof(ali)/sizeof(int)+1; i++){
        ali[i]->Draw();
    }
    
    for(int x=0; x<m->getNumCofres(); x++){
        cof[x]->Draw();
    }
    
    Juego::Instance()->getVentana()->draw(*personajeIzq);
    Juego::Instance()->getVentana()->draw(*personajeDer);
    Juego::Instance()->getVentana()->draw(*pergamino);
    Juego::Instance()->getVentana()->draw(*recuadroTexto);
    Juego::Instance()->getVentana()->draw(*nombre);
    Juego::Instance()->getVentana()->display();
}

void EstadoConversacion::update_State()
{
    /*if(cambioMapa!=-1)
    {
        cambioMapa=-1;
        m=maux;
    }*/
  
    
    if (reloj2->getElapsedTime().asSeconds() >= 0.5) {
        
        for(int i=0; i<sizeof(ali)/sizeof(int)+1; i++){
            ali[i]->cambiaSpriteQuieto();
        }
    
        for(int x=0; x<m->getNumEnemigos(); x++){
            enem[x]->cambiaSpriteQuieto();
        }
        reloj2->restart();
    }
    if (reloj->getElapsedTime().asMilliseconds() >= 100) {
        reloj->restart();

        input();
    }
    
    if(reloj3->getElapsedTime().asSeconds() >= 0.08){
        
        if(quienHabla == 0){
            personajeIzq->setTextureRect(IntRect(contX*169, contY*125, 169, 125));
        }else{
            personajeDer->setTextureRect(IntRect(contX*177, contY*127, 170, 127));
        }
        
        contY++;
        
        if(contY == 3){
            contY = 0;
            contX++;
        }
        if(contX == 3)
            contX = 0;
        
        reloj3->restart();
    }
}

void EstadoConversacion::cambiaQuienHabla(){
    if(quienHabla == 0){
        quienHabla = 1;
    }else{
        quienHabla = 0;
    }
}

void EstadoConversacion::siguienteTexto(){
    
    if(texto){
        personajeIzq->setColor(Color(255, 255, 255, 255));
        personajeDer->setColor(Color(255, 255, 255, 255));

        string s1 = texto->Attribute("textoL");
        quienHabla = atoi(texto->Attribute("quienHabla"));
        string s2 = texto->Attribute("nombre");

        if(quienHabla == 1){
            personajeIzq->setTextureRect(IntRect(0*169, 0*125, 169, 125));
            personajeIzq->setColor(Color(255, 255, 255, 210));
        }else{
            personajeDer->setTextureRect(IntRect(0*177, 0*127, 170, 127));
            personajeDer->setColor(Color(255, 255, 255, 128));
        }

        nombre->setString(s2);
        recuadroTexto->setString(s1);

        texto = texto->NextSiblingElement("texto");
    }else{
        if(escena->NextSiblingElement("escena") != NULL){
            escena = escena->NextSiblingElement("escena");
            texto = escena->FirstChildElement("texto");
            Juego::Instance()->ponerEstadoEscenario();
            siguienteTexto();
        }else{
            Juego::Instance()->ponerEstadoEscenario();
            cerr << "No hay mas escenas!!" << endl;
        }
    }
}

void EstadoConversacion::input()
{
    while (Juego::Instance()->getVentana()->pollEvent(*evento)){
        if ((evento->type == Event::Closed)){
            Juego::Instance()->getVentana()->close();
        }

        if(evento->type == sf::Event::KeyPressed){
            switch(evento->key.code){
                case sf::Keyboard::Return:
                    siguienteTexto();
                break;
                case sf::Keyboard::Escape:
                    Juego::Instance()->getVentana()->close();               
                break;
            }
        }else{
            if(sf::Joystick::isConnected(0)){
                if(evento->type == sf::Event::JoystickButtonPressed){
                    
                    switch(evento->joystickButton.button){

                        /*Mi mando*/
                        /*
                        case 2:
                            siguienteTexto();
                        break;
                        */
                        /*Mando xBox 360*/
                        case 0:
                            siguienteTexto();
                        break;
                    }
                }
            }
        }
    }
}
