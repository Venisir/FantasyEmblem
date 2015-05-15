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
    level =new Text();
    vida=new Text();
    clase=new Text();
    stats=new Text();
    stats1=new Text();
    
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
    
    delete stats;
    delete stats1;
    delete clase;
    delete vida;
    delete level;
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
    mostrarDatos();
    mostrarStats();
    
}
void EstadoPer::mostrarDatos(){
    
    
    //Tipo 0: Aliado
    //Tipo 1: Enemigo
        std::stringstream ss_stats;
        ss_stats << ali[0]->getNombre();
        
        //std::string s_stats = new std::string(ss_stats.str());
        std::string s_stats = ss_stats.str();

        t_stats->setCharacterSize(18);
        t_stats->setFont(*fuente);
        t_stats->setString(s_stats);
        
        t_stats->setColor(sf::Color::Black);
        t_stats->setPosition(65,135);
        
        std::stringstream levell;
        levell << ali[0]->getLvl() << "  " << ali[0]->getExp() ;
        //ali[0]->getHP() << ""<< ali[0]->getPV();
         
        
        //std::string s_stats = new std::string(ss_stats.str());
        std::string level2 = levell.str();
        
        level->setCharacterSize(16);
        level->setFont(*fuente);
        level->setString(level2);
        
        level->setColor(sf::Color::Black);
        level->setPosition(83,224);
        
        std::stringstream vidal;
        vidal<< ali[0]->getHP() << " "<< ali[0]->getPV();
        
         
        
        //std::string s_stats = new std::string(ss_stats.str());
        std::string vida2 = vidal.str();
        
        vida->setCharacterSize(16);
        vida->setFont(*fuente);
        vida->setString(vida2);
        
        vida->setColor(sf::Color::Black);
        vida->setPosition(80,245);
        
        std::stringstream clasel;
        clasel<< ali[0]->getClase();
        
         
        
        //std::string s_stats = new std::string(ss_stats.str());
        std::string clase2 = clasel.str();
        
        clase->setCharacterSize(16);
        clase->setFont(*fuente);
        clase->setString(clase2);
        
        clase->setColor(sf::Color::Black);
        clase->setPosition(40,204);
}      

void EstadoPer::mostrarStats(){
    std::stringstream ss_stats;
        ss_stats <<   
               
                "HP:   " << ali[0]->getHP() << "\n" << "\n" <<
                "Str:  " << ali[0]->getFuerza() << "\n" << "\n" <<
                "Mag:  " << ali[0]->getMagia() << "\n" << "\n" <<
                "Hab:  " << ali[0]->getHab() << "\n" << "\n" 
               /* "Velocidad: " << ali[0]->getVel() << "\n" <<
                "Defensa: " << ali[0]->getDef() << "\n" <<
                "Defensa mag: " << ali[0]->getDefm() << "\n" <<
                "Rango: " << ali[0]->getRango()*/;
        
        std::string s_stats = ss_stats.str();

        stats->setCharacterSize(14);
        stats->setFont(*fuente);
        stats->setString(s_stats);
        
        stats->setColor(sf::Color::White);
        stats->setPosition(190,87);
        
         std::stringstream ss_stats1;
        ss_stats1 <<   
               
                "Spd:  " << ali[0]->getVel() << "\n" << "\n" <<
                "Def:  " << ali[0]->getDef() << "\n" << "\n" <<
                "Res:  " << ali[0]->getDefm() << "\n" << "\n" <<
                "Rng:   " << ali[0]->getRango();
        
        std::string s_stats1 = ss_stats1.str();

        stats1->setCharacterSize(14);
        stats1->setFont(*fuente);
        stats1->setString(s_stats1);
        
        stats1->setColor(sf::Color::White);
        stats1->setPosition(333,87);
}


void EstadoPer::render_State()
{
    Juego::Instance()->getVentana()->clear();
    Juego::Instance()->getVentana()->draw(*menu);
    Juego::Instance()->getVentana()->draw(*t_stats);
    Juego::Instance()->getVentana()->draw(*level);
    Juego::Instance()->getVentana()->draw(*vida);
    Juego::Instance()->getVentana()->draw(*clase);
    Juego::Instance()->getVentana()->draw(*stats);
    Juego::Instance()->getVentana()->draw(*stats1);
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