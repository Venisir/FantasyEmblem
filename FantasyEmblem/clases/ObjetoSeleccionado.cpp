/* 
 * File:   ObjetoSeleccionado.cpp
 * Author: Oliver Rull
 * 
 * Created on 12 de mayo de 2015, 19:16
 */

#include "../headers/ObjetoSeleccionado.h"

#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;

ObjetoSeleccionado* ObjetoSeleccionado::pinstance = 0;
ObjetoSeleccionado* ObjetoSeleccionado::Instance(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice,bool *turno,Objetos** obj, Armas** arm)
{
    if(pinstance==0)
    {
        pinstance=new ObjetoSeleccionado(map,al,ene,cofr,indice,turno,obj,arm);
    }
    return pinstance;
}

ObjetoSeleccionado::ObjetoSeleccionado()
{
    
}


ObjetoSeleccionado::ObjetoSeleccionado(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice, bool *turno, Objetos** obj, Armas** arm)
{
    //arma=new Sprite();
    texturaDedo=new Texture();
    texturaMenu=new Texture();
    cursorDedo= new Sprite();
    usar=new Texture();
    tirar=new Texture();
    usado=new Sprite();
    tirado=new Sprite();
    menu= new Sprite();
    reloj=new Clock();
    reloj2=new Clock();
    evento=new Event();
    stats=new Text*[3];
    stats1=new Text();
    fuente=new Font();
    objeto1=new Sprite();
    objeto2=new Sprite();
    objeto3=new Sprite();
    cursorActivo=true;
    cont=0;
    m=map;
    ali=al;
    enem=ene;
    cof=cofr;
    index=indice;
    turnoUsu=turno;
    objeto = obj;
    arma = arm;
    objetos = new Sprite*[3];
    
    init_State();
}

ObjetoSeleccionado::~ObjetoSeleccionado() {
    
    delete objeto1;
    delete objeto2;
    delete objeto3;
    delete arma;
    delete fuente;
    delete stats1;
    delete stats;
    delete texturaDedo;
    delete texturaMenu;
    delete usar;
    delete tirar;
    delete usado;
    delete tirado;
    delete menu;
    delete cursorDedo;
    delete reloj;
    delete reloj2;
    delete evento;
    delete objetos;
}

void ObjetoSeleccionado::init_State()
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
    if (!usar->loadFromFile("resources/usar2.png"))
    {
            std::cerr << "Error cargando la imagen usar2.png";
            exit(0);
    }
    if (!tirar->loadFromFile("resources/tirar2.png"))
    {
            std::cerr << "Error cargando la imagen tirar2.png";
            exit(0);
    }

    
    menu->setTexture(*texturaMenu);
    cursorDedo->setTexture(*texturaDedo);
    usado->setTexture(*usar);
    tirado->setTexture(*tirar);
    
    /*posicionar sprites*/
    menu->setOrigin(420/2,280/2);
    cursorDedo->setOrigin(420/2,280/2);
    usado->setOrigin(420/2,280/2);
    tirado->setOrigin(420/2,280/2);
    //menu->setScale(0,0);
    //cursorDedo->setScale(0,0);

    menu->setPosition(240,250);
    cursorDedo->setPosition(275,365);
    usado->setPosition(280,350);
    tirado->setPosition(350,350);
    fuente->loadFromFile("resources/font.ttf");
    
    mostrarItems();
}

void ObjetoSeleccionado::render_State()
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
    
    Juego::Instance()->getVentana()->draw(*usado);
    Juego::Instance()->getVentana()->draw(*tirado);
    Juego::Instance()->getVentana()->draw(*cursorDedo);
    
    for(int i=0; i<sizeof(stats)-1; i++){
        if(stats[i]!=NULL){ 
            //cout<<"por favor vaa"<<endl;
            Juego::Instance()->getVentana()->draw(*stats[i]);
        }
    }
    //Juego::Instance()->getVentana()->draw(*stats1);
    //Juego::Instance()->getVentana()->draw(*arma);
    Juego::Instance()->getVentana()->draw(*objeto1);
    Juego::Instance()->getVentana()->draw(*objeto2);
    Juego::Instance()->getVentana()->draw(*objeto3);
    Juego::Instance()->getVentana()->display();
}

void ObjetoSeleccionado::mostrarItems(){
    
    cerr << sizeof(ali[0]->getObjetos()) << endl;
    for(int i=0; i<sizeof(ali[0]->getObjetos());i++){
        if(i==0){
            objetos[i]= new Sprite(ali[0]->getObjetos()[i]->getSprite());
            //=objeto1;
        }
         if(i==1){
            objetos[i]= new Sprite(ali[0]->getObjetos()[i]->getSprite());
        } 
        if(i==2){
            objetos[i]= new Sprite(ali[0]->getObjetos()[i]->getSprite());
        }
    }
    
    //arma=new Sprite(ali[0]->getArma()->getSprite());
    /*std::stringstream ss_stats;
        ss_stats <<   
              
              ali[0]->getObjetos()[0]->getNombre() << "\n" << "\n"<< 
              ali[0]->getObjetos()[1]->getNombre() << "\n" << "\n"<< 
              ali[0]->getObjetos()[2]->getNombre()  
               ;
               
        
        std::string s_stats = ss_stats.str();
*/
    
    std::string s_stats;
    
    for(int i=0; i<sizeof(objeto)-1; i++){
        
        if(objeto[i]!=NULL){
            std::stringstream ss_stats;
            
            ss_stats<<objeto[i]->getNombre();
            

            stats[i] = new Text(ss_stats.str(),*fuente,12);
            
            stats[i]->setColor(sf::Color::White);
            stats[i]->setPosition(50,135+(22*i));
            
        }
        
    }
        
        //stats->setString(s_stats);
        
        
        /*objeto1->setPosition(40,135);
        objeto2->setPosition(40,157);
        objeto3->setPosition(40,179);*/
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


void ObjetoSeleccionado::update_State()
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

void ObjetoSeleccionado::input()
{
    while (Juego::Instance()->getVentana()->pollEvent(*evento)){
        if ((evento->type == Event::Closed)){
            Juego::Instance()->getVentana()->close();
        }

        if(evento->type == sf::Event::KeyPressed){
            switch(evento->key.code){
                case sf::Keyboard::Left:
                    if(cont==1 && cursorActivo==true)
                    {
                        cursorDedo->move(-70,0);
                        cont--;
                    }
                    break;
                case sf::Keyboard::Right:
                    if(cont==0 && cursorActivo==true)
                    {
                        cursorDedo->move(70,0);
                        cont++;
                    }
                    
                    break;
                case sf::Keyboard::Return:
                    cursorActivo = false;
                   for(int i=0; i<sizeof(objeto)-1;i++){
                        if(i==EstadoObjetos::Instance(m,ali,enem,cof,index,turnoUsu,objeto,arma)->getSeleccionada()){
                            cout<<i<<endl;
                            if(cont==0)
                            {
                                //usar
                                cursorActivo = true;  
                                cout<<"antes de usarObjeto"<<endl;
                               objeto = ali[0]->usarObjeto(i);
                               //cout<<"despues de usarObjeto "<<objeto[i]->getNombre()<<endl;
                               //objetos[i] = new Sprite();
                               //objeto[i]->setNombre("");
                               stats[i]->setString("");
                               //ali[0]->getObjetos()[i]->setNombre(NULL);

                                cout<<"usar"<<endl;

                            }

                            if(cont==1)
                            {
                                //tirar
                                //std::stringstream ss_stats;
                                //std::string s_stats =ss_stats.str();
                                objeto[i]->~Objetos();
                                //stats[i]->setString(s_stats);
                                //ali[0]->getObjetos()[i]=NULL;
                                //ali[0]->getObjetos()[i]->getSprite().
                                //tirar
                                cout<<"tirar"<<endl;

                            }
                        }
                   }
                    
                    
                    break;
                case sf::Keyboard::BackSpace:
                    cursorActivo=true;
                    
                    break;
                case sf::Keyboard::B:
                    *index=-1;
                    cursorActivo=true;
                    Juego::Instance()->ponerEstadoObjetos(m,ali,enem,cof,index,turnoUsu,objeto,arma); 
                    
                break;
                case sf::Keyboard::Escape:
                    Juego::Instance()->getVentana()->close();               
                break;
            }
        }
    }
}