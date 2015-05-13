/* 
 * File:   ObjetoSeleccionado.cpp
 * Author: Oliver Rull
 * 
 * Created on 12 de mayo de 2015, 19:16
 */

#include "../headers/ObjetoSeleccionado.h"

using namespace std;

ObjetoSeleccionado* ObjetoSeleccionado::pinstance = 0;
ObjetoSeleccionado* ObjetoSeleccionado::Instance(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice,bool *turno)
{
    if(pinstance==0)
    {
        pinstance=new ObjetoSeleccionado(map,al,ene,cofr,indice,turno);
    }
    return pinstance;
}

ObjetoSeleccionado::ObjetoSeleccionado()
{
    
}


ObjetoSeleccionado::ObjetoSeleccionado(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice, bool *turno)
{
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

ObjetoSeleccionado::~ObjetoSeleccionado() {
    
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
    Juego::Instance()->getVentana()->display();
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
                        
                    if(cont==0)
                    {
                        //atacar
                        cursorActivo = true;
                    
                       
                    }
                    
                    if(cont==1)
                    {
                        //estado
                    }
                    
                    break;
                case sf::Keyboard::BackSpace:
                    cursorActivo=true;
                    
                    break;
                case sf::Keyboard::B:
                    *index=-1;
                    cursorActivo=true;
                    Juego::Instance()->ponerEstadoObjetos(m,ali,enem,cof,index,turnoUsu); 
                    
                break;
                case sf::Keyboard::Escape:
                    Juego::Instance()->getVentana()->close();               
                break;
            }
        }
    }
}