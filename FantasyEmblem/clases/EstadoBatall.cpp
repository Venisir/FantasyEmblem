/* 
 * File:   EstadoBatall.cpp
 * Author: Oliver Rull
 * 
 * Created on 27 de abril de 2015, 17:15
 */

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


EstadoBatall* EstadoBatall::pinstance = 0;

EstadoBatall* EstadoBatall::Instance (Aliadas* ali, Enemigo* ene) {
    if(pinstance == 0){ //¿Es la primera llamada?
        pinstance = new EstadoBatall( ali,  ene); //Creamos la instancia
    }
    return pinstance; //Retornamos la direccion de la instancia
}

EstadoBatall::EstadoBatall(){
    
}

EstadoBatall::EstadoBatall(Aliadas* ali, Enemigo* ene) {
    
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
    per1= new Sprite();
    batasonido=new SoundBuffer();
    batasonido1= new Sound();
    
    per2= new Sprite();
    alia=ali;
    enem=ene;
    
    init_State();
}



EstadoBatall::~EstadoBatall() {
    
    delete batasonido1;
    delete batasonido;
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

void EstadoBatall::init_State(){
    
    string s ="resources/fondoBatalla.png";
    if (!fondoBata->loadFromFile(s))
    {
        std::cerr << "Error cargando la imagen fondoBatalla.png";
        exit(0);
    }
    
    
    batalla->setTexture(*fondoBata);
    batalla->setOrigin(0,0);
    batalla->setPosition(0,0);
  
    reini= false;
    atacado= false;
    atacado2=false;
    turno2=false;
    atacar2=false;
    aux3=0;
    contPer1i = 0;
    contPer1j = 0;
    contPer2i = 0;
    contPer2j = 0;
    per1= new Sprite(alia->getSpriteBatalla());
    per2= new Sprite(enem->getSpriteBatalla()); 
    
    per1->setTextureRect(IntRect(0,0,248,160));
    per1->setScale(1.5,1.5);
    per1->setPosition(80,25);
    
    per2->setTextureRect(IntRect(0,0,248,160));
    per2->setScale(1.5,1.5);
    per2->setPosition(-30,28);
    
    fuente->loadFromFile("resources/font.ttf");
    
    if (!batasonido->loadFromFile("resources/batalla.wav")){
        std::cerr << "Error al cargar el archivo de audio";
    }
    
    batasonido1->setBuffer(*batasonido);
    batasonido1->setVolume(30);
    batasonido1->play();
    aux= rand()%(101-1);
    aux2= rand()%(101-1);
    
    mostrarDats();
}

void EstadoBatall::paramusica(){
    batasonido1->stop();
}
void EstadoBatall::playmusica(){
    batasonido1->play();
}

void EstadoBatall::mostrarDats(){
    
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
        nombres->setPosition(30,20);
        
        
        
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


void EstadoBatall::render_State(){
    Juego::Instance()->getVentana()->clear();
    
    Juego::Instance()->getVentana()->draw(*batalla);
    Juego::Instance()->getVentana()->draw(*per1);
    Juego::Instance()->getVentana()->draw(*per2);
    Juego::Instance()->getVentana()->draw(*stats);
    Juego::Instance()->getVentana()->draw(*stats2);
    Juego::Instance()->getVentana()->draw(*nombres);
    Juego::Instance()->getVentana()->draw(*vidas);
    Juego::Instance()->getVentana()->draw(*armas);
    Juego::Instance()->getVentana()->display();
}


void EstadoBatall::update_State(){
    if (reloj->getElapsedTime().asSeconds() >= 0.08) {
        //cerr << contPer1i << "  " << contPer1j << endl;
        
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
        
        per2->setTextureRect(IntRect(contPer2i*248,contPer2j*160,248,160));
        per1->setTextureRect(IntRect(contPer1i*248,contPer1j*160,248,160));
        
            if(atacado==false){
                if(contPer1i==7){
                    contPer1i=0;
                    contPer1j++;
                }
                contPer1i++;

                if(contPer1i==7 && contPer1j== 5){
                    contPer1i = 0;
                    contPer1j = 0;
                    atacado=true;
                    turno2=true;
                    if(atacar2==true){
                        reini=true;
                    }
                    
                    if(aux<=alia->PosiGolpearTotal(enem)){
                        enem->setPV(alia->TotalDanyo(enem));
                        if(enem->getPV()<=0){
                            
                            if(alia->getLvl()>enem->getLvl()){
                                aux3=30-(2*(alia->getLvl()-enem->getLvl()));
                                if(aux3<10){
                                    aux3=10;
                                }
                            }else if(alia->getLvl() < enem->getLvl()){
                                aux3=30+(2*(enem->getLvl()-alia->getLvl()));
                            }
                            //Debe morir el enemigo
                            
                            Juego::Instance()->ponerEstadoSumaExp(alia, enem, aux3);
                            
                        }
                    }
                   
                    //Juego::Instance()->ponerEstadoEscenario();
                }
            }

            if(turno2==true){
                if(atacado2==false){
                    if(contPer2i==7){
                        contPer2i=0;
                        contPer2j++;
                    }
                    contPer2i++;

                    if(contPer2i==7 && contPer2j== 6){
                        contPer2i = 0;
                        contPer2j = 0;
                        atacado2=true;
                        // sleep(1);
                        if(atacar2==true){
                            reini=true;
                        }
                        
                        if(aux2<=enem->PosiGolpearTotal(alia)){
                            alia->setPV(enem->TotalDanyo(alia));
                            if(alia->getPV()<=0){
                                //Debe morir el aliado
                                
                                batasonido1->stop();
                                //Juego::Instance()->ponerEstadoGameOver();
                            }
                        }


                        //Juego::Instance()->ponerEstadoEscenario();
                    }
                }
                
            }
            if(alia->GolpesDoble(enem)==2 && enem->GolpesDoble(alia)==1 && atacado2==true){
                atacado=false;
                //atacado2=false;
                //turno2=false;
                atacar2=true;
            } else if(alia->GolpesDoble(enem)==1 && enem->GolpesDoble(alia)==2 && atacado2==true){
                atacado2=false;
                //atacado2=false;
                //turno2=false;
                atacar2=true;
            }if(alia->GolpesDoble(enem)==2 && enem->GolpesDoble(alia)==2 && atacado2==true){
                atacado=false;
                atacado2=false;
                turno2=false;
                atacar2=true;
            }if(alia->GolpesDoble(enem)==1 && enem->GolpesDoble(alia)==1 && atacado2==true){
                //atacado=false;
                //atacado2=false;
                //turno2=false;
                reini=true;
            }
        
        
            if(reini==true){
                
                atacado=false;
                atacado2=false;
                turno2=false;
                reini=false;
                
                if(enem->getPV()>=0){
                
                    if(alia->getLvl()>=enem->getLvl()){
                        aux3=10-(1*(alia->getLvl()-enem->getLvl()));
                        if(aux3<1){
                            aux3=1;
                        }
                    }else if(alia->getLvl() < enem->getLvl()){
                        aux3=10+(1*(enem->getLvl()-alia->getLvl()));
                    }

                    Juego::Instance()->ponerEstadoSumaExp(alia, enem, aux3);
                }           
               
            }
        
        reloj->restart();
        
        input();
    }
}

void EstadoBatall::input() {
    
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