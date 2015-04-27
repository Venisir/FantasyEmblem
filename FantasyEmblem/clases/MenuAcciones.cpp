/* 
 * File:   MenuAcciones.cpp
 * Author: Ricardo
 * 
 * Created on 26 de abril de 2015, 12:12
 */

#include "../headers/MenuAcciones.h"


using namespace std;

MenuAcciones* MenuAcciones::pinstance = 0;
MenuAcciones* MenuAcciones::Instance(Mapa* map, Aliadas** al, Enemigo** ene, int *indice)
{
    if(pinstance==0)
    {
        pinstance=new MenuAcciones(map,al,ene,indice);
    }
    return pinstance;
}

MenuAcciones::MenuAcciones()
{
    
}


MenuAcciones::MenuAcciones(Mapa* map, Aliadas** al, Enemigo** ene, int *indice)
{
    texturaDanyo=new Texture();
    texturaDedo=new Texture();
    texturaMenu=new Texture();
    texturaObjetos=new Texture();
    cursorDedo= new Sprite();
    danyo=new Sprite();
    menu= new Sprite();
    objetos= new Sprite();
    reloj=new Clock();
    evento=new Event();
    m=map;
    ali=al;
    enem=ene;
    index=indice;
    
    init_State();
}

MenuAcciones::~MenuAcciones() {
    delete texturaDanyo;
    delete texturaDedo;
    delete texturaMenu;
    delete texturaObjetos;
    delete menu;
    delete objetos;
    delete danyo;
    delete cursorDedo;
    delete reloj;
    delete evento;
}

void MenuAcciones::init_State()
{
    if (!texturaMenu->loadFromFile("resources/menuacciones.png"))
    {
            std::cerr << "Error cargando la imagen boton1.png";
            exit(0);
    }

    if (!texturaDedo->loadFromFile("resources/dedo.png"))
    {
            std::cerr << "Error cargando la imagen dedo.png";
            exit(0);
    }

    if (!texturaDanyo->loadFromFile("resources/dano.png"))
    {
            std::cerr << "Error cargando la imagen dano.png";
            exit(0);
    }
    
    if (!texturaObjetos->loadFromFile("resources/objeto.png"))
    {
            std::cerr << "Error cargando la imagen objeto.png";
            exit(0);
    }
    
    menu->setTexture(*texturaMenu);
    cursorDedo->setTexture(*texturaDedo);
    danyo->setTexture(*texturaDanyo);
    objetos->setTexture(*texturaObjetos);
    
    /*posicionar sprites*/
    menu->setOrigin(420/2,280/2);
    cursorDedo->setOrigin(420/2,280/2);
    danyo->setOrigin(420/2,280/2);
    objetos->setOrigin(420/2,280/2);
    danyo->setScale(0,0);
    //menu->setScale(0,0);
    cursorDedo->setScale(0,0);
    objetos->setScale(0,0);

    menu->setPosition(225,250);
    cursorDedo->setPosition(215,260);
    danyo->setPosition(480,175);
    objetos->setPosition(305,226);
}

void MenuAcciones::render_State()
{
    Juego::Instance()->getVentana()->clear();
    m->Draw();
    ali[0]->Draw();
    enem[0]->Draw();
    Juego::Instance()->getVentana()->draw(*menu);
    Juego::Instance()->getVentana()->display();
}

void MenuAcciones::update_State()
{
    if (reloj->getElapsedTime().asMilliseconds() >= 100) {
        reloj->restart();

        input();
    }
}

void MenuAcciones::input()
{
    while (Juego::Instance()->getVentana()->pollEvent(*evento)){
        if ((evento->type == Event::Closed)){
            Juego::Instance()->getVentana()->close();
        }

        if(evento->type == sf::Event::KeyPressed){
            switch(evento->key.code){
                case sf::Keyboard::Numpad9:
                    *index=-1;
                    Juego::Instance()->ponerEstadoEscenario(); 
                    
                break;
                case sf::Keyboard::Escape:
                    Juego::Instance()->getVentana()->close();               
                break;
            }
        }
    }
}