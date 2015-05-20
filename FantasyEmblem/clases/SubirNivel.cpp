/* 
 * File:   SubirNivel.cpp
 * Author: Oliver Rull
 * 
 * Created on 17 de mayo de 2015, 11:19
 */

#include "../headers/SubirNivel.h"


#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>

//using namespace tinyxml2;
using namespace std;
using namespace sf;


SubirNivel* SubirNivel::pinstance = 0;

SubirNivel* SubirNivel::Instance (Aliadas* ali, Enemigo* ene) {
    if(pinstance == 0){ //¿Es la primera llamada?
        pinstance = new SubirNivel( ali,  ene); //Creamos la instancia
    }else{
        pinstance = 0;
        pinstance = new SubirNivel( ali,  ene); //Creamos la instancia
    }
        
    return pinstance; //Retornamos la direccion de la instancia
}

SubirNivel::SubirNivel(){
    
}

SubirNivel::SubirNivel(Aliadas* ali, Enemigo* ene) {
    
    nivel= new Texture();
    nivel1=new Sprite();
    reloj = new Clock();
    evento = new Event();
    fondoBata = new Texture();
    batalla = new Sprite();
    stats=new Text();
    fuente = new Font();
    stats2=new Text();
    stats3=new Text();
    stats4=new Text();
    nombres=new Text();
    armas=new Text();
    vidas=new Text();
    exp2= new Text();
    clase= new Text();
    per1= new Sprite();
    marco= new Texture();
    barra= new Texture();
    marcoExp = new Sprite();
    barraExp = new Sprite();
    per2= new Sprite();
    mas=new Texture();
    mas1=new Sprite();
    alia=ali;
    enem=ene;
    level=new SoundBuffer();
    level1= new Sound();
    up=new SoundBuffer();
    up1=new Sound();
    
    init_State();
}



SubirNivel::~SubirNivel() {
    
    delete nivel;
    delete nivel1;
    delete level;
    delete level1;
    delete up;
    delete up1;
    delete mas;
    delete mas1;
    delete clase;
    delete exp2;
    delete marco;
    delete barra;
    delete marcoExp;
    delete barraExp;
    delete nombres;
    delete vidas;
    delete armas;
    delete stats2;
    delete stats3;
    delete stats4;
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

void SubirNivel::init_State(){
    
    string s ="resources/fondoBatalla.png";
    if (!fondoBata->loadFromFile(s))
    {
        std::cerr << "Error cargando la imagen fondoBatalla.png";
        exit(0);
    }
     if (!marco->loadFromFile("resources/marcoSubir.png"))
    {
        std::cerr << "Error cargando la imagen marcoSubir.png";
        exit(0);
    }
    if (!barra->loadFromFile("resources/clase.png"))
    {
        std::cerr << "Error cargando la imagen clase.png";
        exit(0);
    }
    
    if (!mas->loadFromFile("resources/mas1.png"))
    {
        std::cerr << "Error cargando la imagen mas1.png";
        exit(0);
    }
    
    if (!nivel->loadFromFile("resources/level.png"))
    {
        std::cerr << "Error cargando la imagen level.png";
        exit(0);
    }
    
    nivel1->setTexture(*nivel);
    nivel1->setOrigin(0,0);
    nivel1->setPosition(135,40);
    
    mas1->setTexture(*mas);
    mas1->setOrigin(0,0);
    mas1->setPosition(291,93);
    
    marcoExp->setTexture(*marco);
    marcoExp->setOrigin(0,0);
    marcoExp->setPosition(115,120);
    
    
    barraExp->setTexture(*barra);
    barraExp->setOrigin(0,0);
    barraExp->setPosition(135,80);
    
    batalla->setTexture(*fondoBata);
    batalla->setOrigin(0,0);
    batalla->setPosition(0,0);
  
    aux1=rand()%(101-1);
    aux2=rand()%(101-1);
    aux3=rand()%(101-1);
    aux4=rand()%(101-1);
    aux5=rand()%(101-1);
    aux6=rand()%(101-1);
    aux7=rand()%(101-1);
    
    suma=false;
    cont=0;
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
    
    if (!level->loadFromFile("resources/LevelUp.wav")){
        std::cerr << "Error al cargar el archivo de audio";
    }
    
    level1->setBuffer(*level);
    level1->setVolume(90);
    level1->play();
    if (!up->loadFromFile("resources/up.wav")){
        std::cerr << "Error al cargar el archivo de audio";
    }
    
    up1->setBuffer(*up);
    up1->setVolume(90);
    
}

void SubirNivel::mostrarDats(){
    
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


void SubirNivel::render_State(){
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
    Juego::Instance()->getVentana()->draw(*stats4);
    Juego::Instance()->getVentana()->draw(*stats3);
    Juego::Instance()->getVentana()->draw(*barraExp);
    Juego::Instance()->getVentana()->draw(*clase);
    Juego::Instance()->getVentana()->draw(*mas1);
    Juego::Instance()->getVentana()->draw(*nivel1);
    Juego::Instance()->getVentana()->display();
}


void SubirNivel::update_State(){
    if (reloj->getElapsedTime().asSeconds() >= 0.08) {
        
        std::stringstream clases2;
        clases2 <<   
               
            alia->getClase()<<   "  LV " <<
            alia->getLvl();
          
        std::string clase2 = clases2.str();

        clase->setCharacterSize(14);
        clase->setFont(*fuente);
        clase->setString(clase2);
        
        clase->setColor(sf::Color::White);
        clase->setPosition(150,95);
        
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
        
        std::stringstream ss_stats4;
        ss_stats4 <<   
               
                "HP:   " << alia->getHP() << "\n" << "\n" <<
                "Str:  " << alia->getFuerza() << "\n" << "\n" <<
                "Mag:  " << alia->getMagia() << "\n" << "\n" <<
                "Hab:  " << alia->getHab() << "\n" << "\n" 
               /* "Velocidad: " << ali[0]->getVel() << "\n" <<
                "Defensa: " << ali[0]->getDef() << "\n" <<
                "Defensa mag: " << ali[0]->getDefm() << "\n" <<
                "Rango: " << ali[0]->getRango()*/;
        
        std::string s_stats4 = ss_stats4.str();

        stats4->setCharacterSize(14);
        stats4->setFont(*fuente);
        stats4->setString(s_stats4);
        
        stats4->setColor(sf::Color::White);
        stats4->setPosition(128,146);
        
         std::stringstream ss_stats5;
        ss_stats5 <<   
               
                "Spd:  " << alia->getVel() << "\n" << "\n" <<
                "Def:  " << alia->getDef() << "\n" << "\n" <<
                "Res:  " << alia->getDefm() << "\n" << "\n" <<
                "Rng:   " << alia->getRango();
        
        std::string s_stats5 = ss_stats5.str();

        stats3->setCharacterSize(14);
        stats3->setFont(*fuente);
        stats3->setString(s_stats5);
        
        stats3->setColor(sf::Color::White);
        stats3->setPosition(253,146);
        if(strcmp(alia->getClase(),"Guerrero")==0){
            
            if(cont==5){
                alia->subirNivel();
                up1->play();
                nivel1->setScale(0,0);
               // mas1->setPosition(200,146);
            }
            if(aux1<=80){
                if(cont==10){
                    up1->play();
                    alia->setHP(1);
                    mas1->setPosition(200,146);
                }
            }
            if(aux2<=70){
                if(cont==15) {
                     up1->play();
                    alia->setFuerza(1);
                     mas1->setPosition(200,173);
                }
            }
            if(aux3<0){
                if(cont==20){
                    up1->play();
                    alia->setMagia(1);
                    mas1->setPosition(200,200);
                }
            }
            if(aux4<=45){
                if(cont==25){
                    up1->play();
                    alia->setHab(1);
                    mas1->setPosition(200,228);
                }
            }
            if(aux5<=30){
                if(cont==30){
                    up1->play();
                    alia->setVel(1);
                    mas1->setPosition(325,148);
                }
            }
            if(aux6<=60){
                if(cont==35){
                    up1->play();
                    alia->setDef(1);
                    mas1->setPosition(325,173);
                }
            }
            if(aux7<=25){
                if(cont==40){
                    up1->play();
                    alia->setDefm(1);
                    mas1->setPosition(325,173);
                    
                }
            }
            
            
            
            if(cont==41){
                mas1->setScale(0,0);
            }
            
            if(cont==45){
                Escenario::Instance()->playmusic();
                Escenario::Instance()->volverMenuAcciones();
            }
        }
        if(strcmp(alia->getClase(),"Espadachin")==0){
            
            if(cont==5){
                up1->play();
                alia->subirNivel();
                nivel1->setScale(0,0);
               // mas1->setPosition(200,146);
            }
            if(aux1<=55){
                if(cont==10){
                    up1->play();
                    alia->setHP(1);
                    mas1->setPosition(200,146);
                }
            }
            if(aux2<=50){
                if(cont==15){
                    up1->play();
                    alia->setFuerza(1);
                     mas1->setPosition(200,173);
                }
            }
            if(aux3<0){
                if(cont==20){
                    up1->play();
                    alia->setMagia(1);
                    mas1->setPosition(200,200);
                }
            }
            if(aux4<=60){
                if(cont==25){
                    up1->play();
                    alia->setHab(1);
                    mas1->setPosition(200,228);
                }
            }
            if(aux5<=70){
                if(cont==30){
                    up1->play();
                    alia->setVel(1);
                    mas1->setPosition(325,148);
                }
            }
            if(aux6<=40){
                if(cont==35){
                    up1->play();
                    alia->setDef(1);
                    mas1->setPosition(325,173);
                }
            }
            if(aux7<=50){
                if(cont==40){
                    up1->play();
                    alia->setDefm(1);
                    mas1->setPosition(325,173);
                    
                }
            }
            
            
            
            if(cont==41){
                mas1->setScale(0,0);
            }
            
            if(cont==45){
                Escenario::Instance()->playmusic();
                Escenario::Instance()->volverMenuAcciones();
            }
        }
        if(strcmp(alia->getClase(),"Arquero")==0){
            
            if(cont==5){
                up1->play();
                alia->subirNivel();
                nivel1->setScale(0,0);
               // mas1->setPosition(200,146);
            }
            if(aux1<=50){
                if(cont==10){
                    up1->play();
                    alia->setHP(1);
                    mas1->setPosition(200,146);
                }
            }
            if(aux2<=40){
                if(cont==15){
                    up1->play();
                    alia->setFuerza(1);
                     mas1->setPosition(200,173);
                }
            }
            if(aux3<0){
                if(cont==20){
                    up1->play();
                    alia->setMagia(1);
                    mas1->setPosition(200,200);
                }
            }
            if(aux4<=70){
                if(cont==25){
                    up1->play();
                    alia->setHab(1);
                    mas1->setPosition(200,228);
                }
            }
            if(aux5<=65){
                if(cont==30){
                    up1->play();
                    alia->setVel(1);
                    mas1->setPosition(325,148);
                }
            }
            if(aux6<=45){
                if(cont==35){
                    up1->play();
                    alia->setDef(1);
                    mas1->setPosition(325,173);
                }
            }
            if(aux7<=20){
                if(cont==40){
                    up1->play();
                    alia->setDefm(1);
                    mas1->setPosition(325,173);
                    
                }
            }
            
            
            
            if(cont==41){
                mas1->setScale(0,0);
            }
            
            if(cont==45){
                Escenario::Instance()->playmusic();
                Escenario::Instance()->volverMenuAcciones();
            }
        }       
        cont++;    
        
        reloj->restart();
        
        input();
    }
}

void SubirNivel::input() {
    
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
