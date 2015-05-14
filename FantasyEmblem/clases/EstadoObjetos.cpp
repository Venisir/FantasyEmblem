/* 
 * File:   EstadoObjetos.cpp
 * Author: Oliver Rull
 * 
 * Created on 12 de mayo de 2015, 17:38
 */

#include "../headers/EstadoObjetos.h"

#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

EstadoObjetos* EstadoObjetos::pinstance = 0;
EstadoObjetos* EstadoObjetos::Instance(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice,bool *turno)
{
    if(pinstance==0)
    {
        pinstance=new EstadoObjetos(map,al,ene,cofr,indice,turno);
    }
    return pinstance;
}

EstadoObjetos::EstadoObjetos()
{
    
}


EstadoObjetos::EstadoObjetos(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice, bool *turno)
{
    texturaDedo=new Texture();
    texturaMenu=new Texture();
    cursorDedo= new Sprite();
    arma=new Sprite(),
    menu= new Sprite();
    reloj=new Clock();
    reloj2=new Clock();
    evento=new Event();
    stats=new Text();
    stats1=new Text();
    fuente=new Font();
    cursorActivo=true;
    cont=0;
    m=map;
    ali=al;
    enem=ene;
    cof=cofr;
    index=indice;
    turnoUsu=turno;
    
    init_State();
}

EstadoObjetos::~EstadoObjetos() {
    
    delete arma;
    delete fuente;
    delete stats1;
    delete stats;
    delete texturaDedo;
    delete texturaMenu;
    delete menu;
    delete cursorDedo;
    delete reloj;
    delete reloj2;
    delete evento;
}

void EstadoObjetos::init_State()
{
    if (!texturaMenu->loadFromFile("resources/menuObjeto.png"))
    {
            std::cerr << "Error cargando la imagen menuObjeto.png";
            exit(0);
    }
    
    
    if (!texturaDedo->loadFromFile("resources/dedo.png"))
    {
            std::cerr << "Error cargando la imagen dedo.png";
            exit(0);
    }

    
    menu->setTexture(*texturaMenu);
    cursorDedo->setTexture(*texturaDedo);

    
    /*posicionar sprites*/
    menu->setOrigin(420/2,280/2);
    cursorDedo->setOrigin(420/2,280/2);
    //menu->setScale(0,0);
    //cursorDedo->setScale(0,0);

    menu->setPosition(240,250);
    cursorDedo->setPosition(240,280);
    
    fuente->loadFromFile("resources/font.ttf");
    
    mostrarItems();
}

void EstadoObjetos::render_State()
{
    Juego::Instance()->getVentana()->clear();
    m->Draw();
    for(int x=0; x<m->getNumEnemigos(); x++){
       // if(aliadas[x]!=NULL){
            //aliadas[x]->Draw();
        //}
        enem[x]->Draw();
    }
    ali[0]->Draw();
    //enemigos[0]->Draw();
    
    for(int x=0; x<m->getNumCofres(); x++){
        cof[x]->Draw();
    }
    Juego::Instance()->getVentana()->draw(*menu);
    Juego::Instance()->getVentana()->draw(*cursorDedo);
    Juego::Instance()->getVentana()->draw(*stats);
    Juego::Instance()->getVentana()->draw(*stats1);
    Juego::Instance()->getVentana()->draw(*arma);
    Juego::Instance()->getVentana()->display();
}

void EstadoObjetos::mostrarItems(){
    
    arma=new Sprite(ali[0]->getArma()->getSprite());
    std::stringstream ss_stats;
        ss_stats <<   
               
              /* ali[0]->getArma()->getSprite() << */ali[0]->getArma()->getNombre()<<" " << ali[0]->getArma()->getUsos() << "\n" << "\n" 
               ;
               
        
        std::string s_stats = ss_stats.str();

        stats->setCharacterSize(12);
        stats->setFont(*fuente);
        stats->setString(s_stats);
        
        stats->setColor(sf::Color::White);
        stats->setPosition(50,135);
        arma->setPosition(40,135);
       /* 
        std::stringstream ss_stats1;
        ss_stats1 <<   
               
                ali[0]->getArma()->getNombre() << "\n" << "\n" <<
                ali[0]->getDef() << "\n" << "\n" <<
                ali[0]->getDefm() << "\n" << "\n" ;
        std::string s_stats1 = ss_stats1.str();

        stats1->setCharacterSize(12);
        stats1->setFont(*fuente);
        stats1->setString(s_stats1);
        
        stats1->setColor(sf::Color::White);
        stats1->setPosition(140,135);
         */
}

void EstadoObjetos::update_State()
{
    if (reloj2->getElapsedTime().asSeconds() >= 0.5) {
        ali[0]->cambiaSpriteQuieto();
        for(int x=0; x<m->getNumEnemigos(); x++){
            // if(aliadas[x]!=NULL){
                //aliadas[x]->Draw();
            //}
            enem[x]->cambiaSpriteQuieto();
        }
        
        reloj2->restart();
    }
    if (reloj->getElapsedTime().asMilliseconds() >= 100) {
        reloj->restart();

        input();
    }
}

void EstadoObjetos::input()
{
    while (Juego::Instance()->getVentana()->pollEvent(*evento)){
        if ((evento->type == Event::Closed)){
            Juego::Instance()->getVentana()->close();
        }

        if(evento->type == sf::Event::KeyPressed){
            switch(evento->key.code){
                case sf::Keyboard::Up:
                    if(cont==1 && cursorActivo==true)
                    {
                        cursorDedo->setPosition(240,280);
                        cont--;
                    }
                    else if(cont==2 && cursorActivo==true)
                    {
                        cursorDedo->setPosition(240,303);
                        cont--;
                    }
                    else if(cont==3 && cursorActivo==true)
                    {
                        cursorDedo->setPosition(240,326);
                        cont--;
                    }
                    else if(cont==4 && cursorActivo==true)
                    {
                        cursorDedo->setPosition(335,280);
                        cont--;
                    }
                    else if(cont==5 && cursorActivo==true)
                    {
                        cursorDedo->setPosition(335,303);
                        cont--;
                    }
                    break;
                case sf::Keyboard::Down:
                    if(cont==0 && cursorActivo==true)
                    {
                        cursorDedo->setPosition(240,303);
                        cont++;
                    }
                    else if(cont==1 && cursorActivo==true)
                    {
                        cursorDedo->setPosition(240,326);
                        cont++;
                    }
                    else if(cont==2 && cursorActivo==true)
                    {
                        cursorDedo->setPosition(335,280);
                        cont++;
                    }
                    else if(cont==3 && cursorActivo==true)
                    {
                        cursorDedo->setPosition(335,303);
                        cont++;
                    }
                    else if(cont==4 && cursorActivo==true)
                    {
                        cursorDedo->setPosition(335,326);
                        cont++;
                    }
                    break;
                case sf::Keyboard::Return:
                    cursorActivo = false;
                        
                    if(cont==0)
                    {
                        //atacar
                        cursorActivo = true;
                    Juego::Instance()->ponerEstadoObjetosSeleccionado(m,ali,enem,cof,index,turnoUsu);
                       
                    }
                    
                    if(cont==1)
                    {
                        //estado
                        Juego::Instance()->ponerEstadoObjetosSeleccionado(m,ali,enem,cof,index,turnoUsu);
                    }
                    
                    if(cont==2)
                    {
                        //objeto
                        Juego::Instance()->ponerEstadoObjetosSeleccionado(m,ali,enem,cof,index,turnoUsu);
                    }
                    
                    if(cont==3)
                    {
                        //interru
                        Juego::Instance()->ponerEstadoObjetosSeleccionado(m,ali,enem,cof,index,turnoUsu);
                    }
                    
                    if(cont==4)
                    {
                        //fin
                        Juego::Instance()->ponerEstadoObjetosSeleccionado(m,ali,enem,cof,index,turnoUsu);
                       
                    }
                    if(cont==5){
                        
                        Juego::Instance()->ponerEstadoObjetosSeleccionado(m,ali,enem,cof,index,turnoUsu);
                    }
                    break;
                case sf::Keyboard::BackSpace:
                    cursorActivo=true;
                    break;
                case sf::Keyboard::B:
                    *index=-1;
                    cursorActivo=true;
                    Juego::Instance()->ponerEstadoMenuAcciones(m,ali,enem,cof,index,turnoUsu); 
                    
                break;
                case sf::Keyboard::Escape:
                    Juego::Instance()->getVentana()->close();               
                break;
            }
        }
    }
}