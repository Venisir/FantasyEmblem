/* 
 * File:   MenuAcciones.cpp
 * Author: Ricardo
 * 
 * Created on 26 de abril de 2015, 12:12
 */

#include "../headers/MenuAcciones.h"

using namespace std;

MenuAcciones* MenuAcciones::pinstance = 0;
MenuAcciones* MenuAcciones::Instance(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice,bool *turno)
{
    if(pinstance==0)
    {
        pinstance=new MenuAcciones(map,al,ene,cofr,indice,turno);
    }
    return pinstance;
}

MenuAcciones::MenuAcciones()
{
    
}

MenuAcciones::MenuAcciones(Mapa* map, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice, bool *turno)
{
    texturaDanyo=new Texture();
    texturaDedo=new Texture();
    texturaMenuNormal=new Texture();
    texturaMenuAtaque=new Texture();
    texturaMenuCofre=new Texture();
    texturaMenuPuerta=new Texture();
    texturaObjetos=new Texture();
    cursorDedo= new Sprite();
    danyo=new Sprite();
    menu= new Sprite();
    objetos= new Sprite();
    reloj=new Clock();
    reloj2=new Clock();
    evento=new Event();
    cont=0;
    m=map;
    ali=al;
    enem=ene;
    cof=cofr;
    index=indice;
    cursorActivo=true;
    turnoUsu=turno;
    
    init_State();
}


MenuAcciones::~MenuAcciones() {
    delete texturaDanyo;
    delete texturaDedo;
    delete texturaMenuNormal;
    delete texturaMenuAtaque;
    delete texturaMenuCofre;
    delete texturaMenuPuerta;
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
    
    if (!texturaMenuAtaque->loadFromFile("resources/menuaccionesAtacar.png"))
    {
        std::cerr << "Error cargando la imagen menuaccionesAtacar.png";
        exit(0);
    }
    
    if (!texturaMenuCofre->loadFromFile("resources/menuaccionesAbrirCofre.png"))
    {
        std::cerr << "Error cargando la imagen menuaccionesAbrirCofre.png";
        exit(0);
    }

    if (!texturaMenuPuerta->loadFromFile("resources/menuaccionesAbrirPuerta.png"))
    {
        std::cerr << "Error cargando la imagen menuaccionesAbrirPuerta.png";
        exit(0);
    }

    if (!texturaMenuNormal->loadFromFile("resources/menuacciones.png"))
    {
        std::cerr << "Error cargando la imagen menuacciones.png";
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
    numMenu = -1;
    seleccionarMenu();
    
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
    //cursorDedo->setScale(0,0);
    objetos->setScale(0,0);

    menu->setPosition(225,250);
    cursorDedo->setPosition(215,260);
    danyo->setPosition(480,175);
    objetos->setPosition(305,226);
    
    haAtacado = false;
}

void MenuAcciones::render_State()
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
    Juego::Instance()->getVentana()->display();
}

void MenuAcciones::update_State()
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
        if(numMenu == -1){
            seleccionarMenu();
        }
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
                case sf::Keyboard::Up:
                    if(cont>0 && cursorActivo==true)//que el contador este a 0 significa que esta en la primera opcion
                    {
                        cursorDedo->move(0,-20);
                        cont--;
                    }
                    break;
                case sf::Keyboard::Down:
                    if(numMenu == 3){
                        if(cont<3 && cursorActivo==true)
                        {
                            cursorDedo->move(0,20);
                            cont++;
                        }
                    }else{
                        if(cont<4 && cursorActivo==true)
                        {
                            cursorDedo->move(0,20);
                            cont++;
                        }
                    }
                    break;
                case sf::Keyboard::Return:
                    cursorActivo = false;
                        
                    if(numMenu == 3){
                        if(cont==0){
                            //estado
                           Juego::Instance()->ponerEstadoPersonaje(m,ali,enem,cof,index,turnoUsu);
                           
                           cursorActivo=true;
                        }
                        if(cont==1){
                            //objeto 
                            Juego::Instance()->ponerEstadoObjetos(m,ali,enem,cof,index,turnoUsu);
                           
                            cursorActivo=true;
                        }
                        if(cont==2){
                            //interru
                            cursorActivo=true;
                        }
                        if(cont==3){
                            //fin
                            cursorActivo=true;
                            cont=0;
                            cursorDedo->setPosition(215,260);
                            *index=-1;
                            *turnoUsu=false;
                            numMenu = -1;
                            haAtacado = false;
                            Escenario::Instance()->empiezaturnoIA();
                            Juego::Instance()->ponerEstadoEscenario();
                        }
                    }else{
                        if(cont==0)
                        {
                            //atacar, abrir cofre o abrir puerta
                            switch(numMenu){
                                case 0:
                                    //atacar
                                    cursorActivo = true;
                                    Juego::Instance()->ponerEstadoBatalla();
                                    cursorActivo=true;
                                    haAtacado = true;
                                    menu->setTexture(*texturaMenuNormal);
                                    numMenu = 3;
                                    break;
                                case 1:
                                    //abrir cofre
                                    cursorActivo = true;
                                    //Juego::Instance()->ponerEstadoBatalla();
                                    cursorActivo=true;
                                    break;
                                case 2:
                                    //abrir puerta
                                    cursorActivo = true;
                                    //Juego::Instance()->ponerEstadoBatalla();
                                    cursorActivo=true;
                                    break;
                                default: cerr << "ATENCION, BUGASO" << endl;
                            }
                        }

                        if(cont==1){
                            //estado
                           Juego::Instance()->ponerEstadoPersonaje(m,ali,enem,cof,index,turnoUsu);
                          
                           cursorActivo=true;
                        }
                        if(cont==2){
                            //objeto 
                            Juego::Instance()->ponerEstadoObjetos(m,ali,enem,cof,index,turnoUsu);
                            
                            cursorActivo=true;
                        }
                        if(cont==3){
                            //interru
                            cursorActivo=true;
                        }
                        if(cont==4){
                            //fin
                            cursorActivo=true;
                            cont=0;
                            cursorDedo->setPosition(215,260);
                            *index=-1;
                            *turnoUsu=false;
                            haAtacado=false;
                            numMenu = -1;
                            Escenario::Instance()->empiezaturnoIA();
                            Juego::Instance()->ponerEstadoEscenario();
                           
                        }
                    }
                    
                    break;
                case sf::Keyboard::BackSpace:
                    cursorActivo=true;
                    break;
                    
                case sf::Keyboard::Numpad1:
                    seleccionarMenu();
                break;
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

void MenuAcciones::seleccionarMenu(){
    
    if(ali[*index]->hayEnemigosCercanos(enem)!=0 && haAtacado == false){
        menu->setTexture(*texturaMenuAtaque);
        numMenu = 0;
    }else if(ali[*index]->hayCofresCercanos(m)!=0){
        menu->setTexture(*texturaMenuCofre);
        numMenu = 1;
    }else if(ali[*index]->hayPuertasCercanas(m)!=0){
        menu->setTexture(*texturaMenuPuerta);
        numMenu = 2;
    }else{
        if(numMenu!=3){
            menu->setTexture(*texturaMenuNormal);
            numMenu = 3;
        }
    }
    
}