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
EstadoObjetos* EstadoObjetos::Instance(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice,bool *turno, Objetos** obj, Armas** arm)
{
    if(pinstance==0)
    {
        pinstance=new EstadoObjetos(map,al,ene,cofr,indice,turno, obj,arm);
    }
    else{
        pinstance=0;
        pinstance=new EstadoObjetos(map,al,ene,cofr,indice,turno, obj,arm);
    }
    return pinstance;
}

EstadoObjetos* EstadoObjetos::Instance() {
    return pinstance;
}

void EstadoObjetos::reset() {
    pinstance=0;
}


EstadoObjetos::EstadoObjetos()
{
    
}


EstadoObjetos::EstadoObjetos(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice, bool *turno, Objetos** obj, Armas** arm)
{
    texturaDedo=new Texture();
    objeto1=new Sprite();
    objeto2=new Sprite();
    objeto3=new Sprite();
    texturaMenu=new Texture();
    cursorDedo= new Sprite();
    
    menu= new Sprite();
    reloj=new Clock();
    reloj2=new Clock();
    evento=new Event();
    stats=new Text*[3];
    stats2=new Text*[3];
    fuente=new Font();
    cursorActivo=true;
    cont=0;
    m=map;
    ali=al;
    enem=ene;
    cof=cofr;
    index=indice;
    turnoUsu=turno;
    seleccionada=0;
    objeto = obj;
    arma = arm;
    armitas=new Sprite*[3];
    objetitos=new Sprite*[3];
    init_State();
}

EstadoObjetos::~EstadoObjetos() {
    
    delete objetitos;
    delete armitas;
    delete arma;
    delete fuente;
    delete stats2;
    delete stats;
    delete texturaDedo;
    delete texturaMenu;
    delete menu;
    delete cursorDedo;
    delete reloj;
    delete reloj2;
    delete evento;
}

int EstadoObjetos::getSeleccionada(){
    return  seleccionada;
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
    
    
    for(int i=0; i<sizeof(stats)-1; i++){
        if(stats[i]!=NULL){
            Juego::Instance()->getVentana()->draw(*stats[i]);
        }
    }
    for(int i=0; i<sizeof(stats2)-1; i++){
        if(stats2[i]!=NULL){ 
            Juego::Instance()->getVentana()->draw(*stats2[i]);
        }
    }
    for(int i=0; i<sizeof(objetitos)-1; i++){
        if(objetitos[i]!=NULL){ 
            Juego::Instance()->getVentana()->draw(*objetitos[i]);
        }
    }
    for(int i=0; i<sizeof(armitas)-1; i++){
        if((armitas[i]!=NULL) && (arma[i]!=NULL)){ 
            Juego::Instance()->getVentana()->draw(*armitas[i]);
        }
    }
    Juego::Instance()->getVentana()->draw(*cursorDedo);
    Juego::Instance()->getVentana()->display();
}

void EstadoObjetos::mostrarItems(){
   

    for(int i=0; i<sizeof(objeto)-1; i++){

        if(objeto[i]!=NULL){
            std::stringstream ss_stats;

            ss_stats<<objeto[i]->getNombre();
            cout<<ss_stats.str()<<endl;

            stats[i] = new Text(ss_stats.str(),*fuente,10);

            stats[i]->setColor(sf::Color::White);
            stats[i]->setPosition(50,135+(22*i));
            objetitos[i] = new Sprite(objeto[i]->getSprite());
            objetitos[i]->setPosition(35,135+(22*i));
            
        }
        else
        {
            std::stringstream ss_stats;

            cout<<ss_stats.str()<<endl;

            stats[i] = new Text(ss_stats.str(),*fuente,10);

            stats[i]->setColor(sf::Color::White);
            stats[i]->setPosition(50,135+(22*i));
            objetitos[i] = NULL;
        }
    }
    
    for(int i=0; i<sizeof(arma)-1; i++){

        if(arma[i]!=NULL){
            std::stringstream ss_stats2;

            ss_stats2<<arma[i]->getNombre();
            cout<<ss_stats2.str()<<endl;

            stats2[i] = new Text(ss_stats2.str(),*fuente,10);

            stats2[i]->setColor(sf::Color::White);
            stats2[i]->setPosition(140,135+(22*i));
            armitas[i] = new Sprite(arma[i]->getSprite());
            armitas[i]->setPosition(125,135+(22*i));
            
        }
        else
        {
            std::stringstream ss_stats2;

            cout<<ss_stats2.str()<<endl;

            stats2[i] = new Text(ss_stats2.str(),*fuente,10);

            stats2[i]->setColor(sf::Color::White);
            stats2[i]->setPosition(140,135+(22*i));
            armitas[i]=NULL;
        }
    }
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
                        cout<<"objeto1"<<endl;
                        cursorDedo->setPosition(240,280);
                        seleccionada--;
                        cont--;
                    }
                    else if(cont==2 && cursorActivo==true)
                    {
                        cout<<"objeto2"<<endl;
                        cursorDedo->setPosition(240,303);
                        seleccionada--;
                        cont--;
                    }
                    else if(cont==3 && cursorActivo==true)
                    {
                        cout<<"objeto3"<<endl;
                        cursorDedo->setPosition(240,326);
                        seleccionada--;
                        cont--;
                    }
                    else if(cont==4 && cursorActivo==true)
                    {
                        cout<<"objeto4"<<endl;
                        cursorDedo->setPosition(335,280);
                        seleccionada--;
                        cont--;
                    }
                    else if(cont==5 && cursorActivo==true)
                    {
                        cout<<"objeto5"<<endl;
                        cursorDedo->setPosition(335,303);
                        seleccionada--;
                        cont--;
                    }
                    break;
                case sf::Keyboard::Down:
                    if(cont==0 && cursorActivo==true)
                    {
                        cout<<"objeto2"<<endl;
                        cursorDedo->setPosition(240,303);
                        seleccionada++;
                        cont++;
                    }
                    else if(cont==1 && cursorActivo==true)
                    {
                        cout<<"objeto3"<<endl;
                        cursorDedo->setPosition(240,326);
                        seleccionada++;
                        cont++;
                    }
                    else if(cont==2 && cursorActivo==true)
                    {
                        cout<<"objeto4"<<endl;
                        cursorDedo->setPosition(335,280);
                        seleccionada++;
                        cont++;
                    }
                    else if(cont==3 && cursorActivo==true)
                    {
                        cout<<"objeto5"<<endl;
                        cursorDedo->setPosition(335,303);
                        seleccionada++;
                        cont++;
                    }
                    else if(cont==4 && cursorActivo==true)
                    {
                        cout<<"objeto6"<<endl;
                        cursorDedo->setPosition(335,326);
                        seleccionada++;
                        cont++;
                    }
                    break;
                case sf::Keyboard::Return:
                    cursorActivo = false;
                        
                    if(cont==0)
                    {
                        //atacar
                        cursorActivo = true;
                    Juego::Instance()->ponerEstadoObjetosSeleccionado(m,ali,enem,cof,index,turnoUsu,objeto,arma);
                       
                    }
                    
                    if(cont==1)
                    {
                        //estado
                        Juego::Instance()->ponerEstadoObjetosSeleccionado(m,ali,enem,cof,index,turnoUsu,objeto,arma);
                    }
                    
                    if(cont==2)
                    {
                        //objeto
                        Juego::Instance()->ponerEstadoObjetosSeleccionado(m,ali,enem,cof,index,turnoUsu,objeto,arma);
                    }
                    
                    if(cont==3)
                    {
                        //interru
                        Juego::Instance()->ponerEstadoObjetosSeleccionado(m,ali,enem,cof,index,turnoUsu,objeto,arma);
                    }
                    
                    if(cont==4)
                    {
                        //fin
                        Juego::Instance()->ponerEstadoObjetosSeleccionado(m,ali,enem,cof,index,turnoUsu,objeto,arma);
                       
                    }
                    if(cont==5){
                        
                        Juego::Instance()->ponerEstadoObjetosSeleccionado(m,ali,enem,cof,index,turnoUsu,objeto,arma);
                    }
                    break;
                case sf::Keyboard::BackSpace:
                    cursorActivo=true;
                    break;
                case sf::Keyboard::B:
                    //*index=-1;
                    cursorActivo=true;
                    Juego::Instance()->ponerEstadoMenuAcciones(m,ali,enem,cof,index,turnoUsu,objeto,arma); 
                    
                break;
                case sf::Keyboard::Escape:
                    Juego::Instance()->getVentana()->close();               
                break;
            }
        }
    }
}