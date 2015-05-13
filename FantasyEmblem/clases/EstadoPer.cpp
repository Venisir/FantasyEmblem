/* 
 * File:   EstadoPer.cpp
 * Author: Oliver Rull
 * 
 * Created on 13 de mayo de 2015, 9:31
 */
#include "../headers/Aliadas.h"
#include "../headers/EstadoPer.h"
#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

EstadoPer* EstadoPer::pinstance = 0;
EstadoPer* EstadoPer::Instance(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice,bool *turno)
{
    if(pinstance==0)
    {
        pinstance=new EstadoPer(map,al,ene,cofr,indice,turno);
    }
    return pinstance;
}

EstadoPer::EstadoPer()
{
    
}


EstadoPer::EstadoPer(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice, bool *turno)
{
    
    texturaMenu=new Texture();
    
    menu= new Sprite();
    reloj=new Clock();
    reloj2=new Clock();
    evento=new Event();
    fuente = new Font();
    t_stats = new Text();
    
    cont=0;
    m=map;
    ali=al;
    enem=ene;
    cof=cofr;
    index=indice;
    turnoUsu=turno;
    
    init_State();
}

EstadoPer::~EstadoPer() {
    
    
    delete texturaMenu;
    delete menu;
    delete fuente;
    delete t_stats;
    delete reloj;
    delete reloj2;
    delete evento;
}

void EstadoPer::init_State()
{
    if (!texturaMenu->loadFromFile("resources/estadoper.png"))
    {
            std::cerr << "Error cargando la imagen estadoper.png";
            exit(0);
    }
    
    
    fuente->loadFromFile("resources/font.ttf");
    
    menu->setTexture(*texturaMenu);
    

    
    /*posicionar sprites*/
    menu->setOrigin(0,0);
    
    //menu->setScale(0,0);
    //cursorDedo->setScale(0,0);

    menu->setPosition(0,0);
    
}
void EstadoPer::mostrarStats(){
    
    
    //Tipo 0: Aliado
    //Tipo 1: Enemigo
        std::stringstream ss_stats;
        ss_stats << ali[0]->getNombre() << "    Lvl: " << ali[0]->getLvl() << "\n" <<  
                ali[0]->getClase() << "\n" << "\n" <<
                "HP: " << ali[0]->getHP() << "\n" <<
                "Fuerza: " << ali[0]->getFuerza() << "\n" <<
                "Magia: " << ali[0]->getMagia() << "\n" <<
                "Habilidad: " << ali[0]->getHab() << "\n" <<
                "Velocidad: " << ali[0]->getVel() << "\n" <<
                "Defensa: " << ali[0]->getDef() << "\n" <<
                "Defensa mag: " << ali[0]->getDefm() << "\n" <<
                "Rango: " << ali[0]->getRango();
        
        //std::string s_stats = new std::string(ss_stats.str());
        std::string s_stats = ss_stats.str();

        t_stats->setCharacterSize(8);
        t_stats->setFont(*fuente);
        t_stats->setString(s_stats);
        
        t_stats->setColor(sf::Color::White);
        t_stats->setPosition(10,100);
}      

void EstadoPer::render_State()
{
     Juego::Instance()->getVentana()->clear();
    Juego::Instance()->getVentana()->draw(*menu);
    Juego::Instance()->getVentana()->draw(*t_stats);
    Juego::Instance()->renderText();
    Juego::Instance()->getVentana()->display();
}

void EstadoPer::update_State()
{
    
    if (reloj->getElapsedTime().asMilliseconds() >= 100) {
        reloj->restart();

        input();
    }
}

void EstadoPer::input()
{
    while (Juego::Instance()->getVentana()->pollEvent(*evento)){
        if ((evento->type == Event::Closed)){
            Juego::Instance()->getVentana()->close();
        }

        if(evento->type == sf::Event::KeyPressed){
            switch(evento->key.code){
                case sf::Keyboard::Up:
                   
                   
                    break;
                case sf::Keyboard::Down:
                   
                    break;
                case sf::Keyboard::B:
                    *index=-1;
                    Juego::Instance()->ponerEstadoMenuAcciones(m,ali,enem,cof,index,turnoUsu); 
                    
                break;
                case sf::Keyboard::Escape:
                    Juego::Instance()->getVentana()->close();               
                break;
            }
        }
    }
}