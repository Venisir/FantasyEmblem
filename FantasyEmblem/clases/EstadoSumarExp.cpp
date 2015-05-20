/* 
 * File:   EstadoSumarExp.cpp
 * Author: Oliver Rull
 * 
 * Created on 16 de mayo de 2015, 17:11
 */

#include "../headers/EstadoSumarExp.h"
#include "../headers/EstadoBatall.h"
#include "../headers/Estado.h"
#include "../headers/Juego.h"
#include "../headers/Aliadas.h"
#include "../headers/Enemigo.h"

#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>

//using namespace tinyxml2;
using namespace std;
using namespace sf;


EstadoSumarExp* EstadoSumarExp::pinstance = 0;

EstadoSumarExp* EstadoSumarExp::Instance (Aliadas* ali, Enemigo* ene, int i ) {
    if(pinstance == 0){ //¿Es la primera llamada?
        pinstance = new EstadoSumarExp( ali,  ene, i); //Creamos la instancia
    }else{
        pinstance = 0;
        pinstance = new EstadoSumarExp( ali,  ene, i); //Creamos la instancia
    }
    return pinstance; //Retornamos la direccion de la instancia
}

EstadoSumarExp::EstadoSumarExp(){
    
}

EstadoSumarExp::EstadoSumarExp(Aliadas* ali, Enemigo* ene, int i) {
    
    reloj = new Clock();
    evento = new Event();
    fondoBata = new Texture();
    batalla = new Sprite();
    stats=new Text();
    fuente = new Font();
    stats2=new Text();
    nombres=new Text();
    armas=new Text();
    vidas=new Text();
    exp2= new Text();
    per1= new Sprite();
    marco= new Texture();
    barra= new Texture();
    marcoExp = new Sprite();
    barraExp = new Sprite();
    per2= new Sprite();
    alia=ali;
    enem=ene;
    exp=i;
    init_State();
}



EstadoSumarExp::~EstadoSumarExp() {
    
    delete exp2;
    delete marco;
    delete barra;
    delete marcoExp;
    delete barraExp;
    delete nombres;
    delete vidas;
    delete armas;
    delete stats2;
    delete fuente;
    delete stats;
    delete fondoBata;
    delete reloj;
    delete evento;
    delete batalla;
    delete pinstance;
    
    delete per1;
    
    delete per2;
}

void EstadoSumarExp::init_State(){
    
    string s ="resources/fondoBatalla.png";
    if (!fondoBata->loadFromFile(s))
    {
        std::cerr << "Error cargando la imagen fondoBatalla.png";
        exit(0);
    }
    
    if (!marco->loadFromFile("resources/marcoExp.png"))
    {
        std::cerr << "Error cargando la imagen marcoExp.png";
        exit(0);
    }
    if (!barra->loadFromFile("resources/barraExp.png"))
    {
        std::cerr << "Error cargando la imagen barraExp.png";
        exit(0);
    }
    
    batalla->setTexture(*fondoBata);
    batalla->setOrigin(0,0);
    batalla->setPosition(0,0);
  
    marcoExp->setTexture(*marco);
    marcoExp->setOrigin(0,0);
    marcoExp->setPosition(165,30);
    
    aux=(float)alia->getExp()/(float)100;
    barraExp->setTexture(*barra);
    barraExp->setOrigin(0,0);
    barraExp->setPosition(193,51);
    barraExp->setScale(aux,1);
    
    suma=false;
    cont=1;
    per1= new Sprite(alia->getSpriteBatalla());
    per2= new Sprite(enem->getSpriteBatalla()); 
    
    per1->setTextureRect(IntRect(0,0,248,160));
    per1->setScale(1.5,1.5);
    per1->setPosition(80,25);
    
    per2->setTextureRect(IntRect(0,0,248,160));
    per2->setScale(1.5,1.5);
    per2->setPosition(-30,28);
    
    fuente->loadFromFile("resources/font.ttf");
    mostrarDats();
}

void EstadoSumarExp::mostrarDats(){
    
     std::stringstream ss_stats;
        ss_stats <<   
               
            enem->PosiGolpearTotal(alia)<< "\n" << 
            enem->TotalDanyo(alia)<< "\n"<<
            " 0";
               
               
        
        std::string s_stats = ss_stats.str();

        stats->setCharacterSize(14);
        stats->setFont(*fuente);
        stats->setString(s_stats);
        
        stats->setColor(sf::Color::White);
        stats->setPosition(55,220);
        
        std::stringstream ss_stats2;
        ss_stats2 <<   
               
            alia->PosiGolpearTotal(enem)<< "\n" << 
            alia->TotalDanyo(enem)<< "\n"<<
            " 0";
               
               
        
        std::string s_stats2 = ss_stats2.str();

        stats2->setCharacterSize(14);
        stats2->setFont(*fuente);
        stats2->setString(s_stats2);
        
        stats2->setColor(sf::Color::White);
        stats2->setPosition(450,220);
    
        std::stringstream nombres2;
        nombres2 <<   
               
            enem->getNombre()<<   "                                  " <<
            alia->getNombre();
            
               
               
        
        std::string nombre2 = nombres2.str();

        nombres->setCharacterSize(14);
        nombres->setFont(*fuente);
        nombres->setString(nombre2);
        
        nombres->setColor(sf::Color::White);
        nombres->setPosition(20,20);
        
        
        
        std::stringstream armas2;
        armas2 <<   
               
            enem->getArma()->getNombre()<<   "        " <<
            alia->getArma()->getNombre();
            
               
               
        
        std::string arma2 = armas2.str();

        armas->setCharacterSize(16);
        armas->setFont(*fuente);
        armas->setString(arma2);
        
        armas->setColor(sf::Color::Black);
        armas->setPosition(135,245);
        
       
}


void EstadoSumarExp::render_State(){
    Juego::Instance()->getVentana()->clear();
    
    Juego::Instance()->getVentana()->draw(*batalla);
    Juego::Instance()->getVentana()->draw(*per1);
    Juego::Instance()->getVentana()->draw(*per2);
    Juego::Instance()->getVentana()->draw(*stats);
    Juego::Instance()->getVentana()->draw(*stats2);
    Juego::Instance()->getVentana()->draw(*nombres);
    Juego::Instance()->getVentana()->draw(*vidas);
    Juego::Instance()->getVentana()->draw(*armas);
    
    Juego::Instance()->getVentana()->draw(*marcoExp);
    Juego::Instance()->getVentana()->draw(*barraExp);
    Juego::Instance()->getVentana()->draw(*exp2);
    Juego::Instance()->getVentana()->display();
}


void EstadoSumarExp::update_State(){
    if (reloj->getElapsedTime().asSeconds() >= 0.08) {
        
        std::stringstream vidas2;
        vidas2 <<   
               
            enem->getPV()<<   "   " <<
            alia->getPV();
          
        std::string vida2 = vidas2.str();

        vidas->setCharacterSize(16);
        vidas->setFont(*fuente);
        vidas->setString(vida2);
        
        vidas->setColor(sf::Color::Black);
        vidas->setPosition(204,283);
        
        std::stringstream exps2;
        exps2 <<   
            alia->getExp();
          
        std::string ex2 = exps2.str();

        exp2->setCharacterSize(10);
        exp2->setFont(*fuente);
        exp2->setString(ex2);
        
        exp2->setColor(sf::Color::White);
        exp2->setPosition(290,50);
        
        if(alia->getExp()>=99){
            alia->setExp(exp-cont);
            //EstadoBatall::Instance(alia,enem)->paramusica();
            //Escenario::Instance()->playmusic();
            Juego::Instance()->ponerEstadoSubirNivel(alia,enem);
        }
        
        if(cont>exp){
            Escenario::Instance()->playmusic();
            Escenario::Instance()->volverMenuAcciones();
        }
            
        alia->setExp(1);
        barraExp->setScale((float)alia->getExp()/(float)100,1);
        cont++;

            
        
        
            
        
        reloj->restart();
        
        input();
    }
}

void EstadoSumarExp::input() {
    
    while (Juego::Instance()->getVentana()->pollEvent(*evento)){
        if ((evento->type == Event::Closed)){
            Juego::Instance()->getVentana()->close();
        }
            
        if(evento->type == sf::Event::KeyPressed){
            switch(evento->key.code){
                case sf::Keyboard::B:
                    Juego::Instance()->ponerEstadoEscenario();              
                break;
                case sf::Keyboard::Escape:
                    Juego::Instance()->getVentana()->close();               
                break;
            }
        }
    }
}