/* 
 * File:   Escenario.cpp
 * Author: Ricardo
 * 
 * Created on 15 de abril de 2015, 9:41
 */


#include "../headers/Aliadas.h"
#include "../headers/Enemigo.h"
#include "../headers/Escenario.h"
#include "../headers/Estado.h"
#include "../headers/Juego.h"
#include "../headers/Mapa.h"
//#include "tinyxml2.h"

#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//using namespace tinyxml2;
using namespace std;
using namespace sf;

#define kVel 20

Escenario* Escenario::pinstance = 0;

Escenario* Escenario::Instance () {
    if(pinstance == 0){ //¿Es la primera llamada?
        pinstance = new Escenario(); //Creamos la instancia
    }
    return pinstance; //Retornamos la direccion de la instancia
}

Escenario::Escenario() {
    //Realizar inicializaciones necesarias de la instancia
    //ventana->create(sf::VideoMode(480,320), "Fantasy Emblem");
    texturaCursor = new Texture();
    spriteCursor = new Sprite();
    reloj = new Clock();
    relojCursor = new Clock();
    evento = new Event();
    mapa = new Mapa();
    aliadas=new Aliadas*[5];
    enemigos=new Enemigo*[5];
    cofres=new Cofre*[5];
    unidad_sel=new int();
    turnoUsu=new bool();
    primeritaVes=new bool();
    mapasonido=new SoundBuffer();
    mapasonido1= new Sound();
    
    fuente = new Font();
    t_stats = new Text();
    spriteMenuStats = new Sprite();
    texturaMenuStats = new Texture();
    
    texturaAbrirPuerta = new Texture();
    spriteAbrirPuerta = new Sprite();
    
    
    int atri[] = { 11, 22, 33, 44, 55, 66, 77};
    
    cofres=mapa->getCofres();
    enemigos=mapa->getEnemigos();
    aliadas[0] = new Aliadas("Alberto", "Espadachin", atri, 8, 5, "Mapa_espadachin_azul.png", 0);
    //enemigos[4] = new Enemigo("AlbertoMalo", "Guerrero", atri, 8, 2, "Mapa_espadachin_rojo.png");
    
    //enemigos[4]->setPosition(208,176);
    
    init_State();
}

Escenario::~Escenario() {
    /*if(pinstance != NULL)*/ 
    delete texturaCursor;
    delete spriteCursor;
    delete reloj;
    delete relojCursor;
    delete reloj2;
    delete evento;
    delete mapasonido;
    delete mapasonido1;
    //delete ventana;
    delete pinstance;
    delete mapa;
    delete aliadas;
    delete fuente;
    delete t_stats;
    delete texturaMenuStats;
    delete spriteMenuStats;
    delete primeritaVes;
    
    delete texturaAbrirPuerta;
    delete spriteAbrirPuerta;
}

void Escenario::init_State(){
    
    if(!texturaAbrirPuerta->loadFromFile("resources/abrirPuerta.png"))
    {
        std::cerr << "Error cargando la imagen abrirPuerta.png";
        exit(0);
    }
    
    if (!texturaCursor-> loadFromFile("resources/cursores.png"))
    {
        std::cerr << "Error cargando la imagen cursores.png";
        exit(0);
    }
    
    if (!texturaMenuStats-> loadFromFile("resources/menuStats.png"))
    {
        std::cerr << "Error cargando la imagen menuStats.png";
        exit(0);
    }
    
    
    if (!mapasonido->loadFromFile("resources/mapasonido.wav")){
        std::cerr << "Error al cargar el archivo de audio";
    }
    
    mapasonido1->setBuffer(*mapasonido);
    // establecemos el volumen a 20
    mapasonido1->setVolume(30);
    //reproducir audio del menu
    mapasonido1->setLoop(true);
    mapasonido1->play();
    
    spriteCursor->setTexture(*texturaCursor);
    spriteCursor->setTextureRect(IntRect(0, 0, 16, 16));
    
    spriteCursor->setPosition(176,176);
    
    spriteAbrirPuerta->setTexture(*texturaAbrirPuerta);
    spriteAbrirPuerta->setPosition(100,30);
    
    puertaSi = false;
    cofreSi = false;
    enemigoSi = false;
    
    cambiaSpriteCursorSeleccionar();
    
    cursorActivo = 0;
    varCursor = 0;    
   
    fuente->loadFromFile("resources/font.ttf");
    
    spriteMenuStats->setTexture(*texturaMenuStats);
    spriteMenuStats->setPosition(0,90);
    
    tieneQueMostrarStats = false;

    aliadas[0]->setPosition(176,176);
    
    fasesEnemigo = 1;
    turnoEnemigo = 0;
    
    *unidad_sel=-1;
    *turnoUsu=true;
    *primeritaVes = true;
    
    cont = 0;
    aux = 0;
}
void Escenario::paramusic(){
    mapasonido1->stop();
}

void Escenario::cambiaSpriteCursorSeleccionar() {
    varCursor = 0;
    spriteCursor->setTextureRect(IntRect(0, 0, 16, 16));
    cursorActivo = 0;
}

void Escenario::cambiaSpriteCursorMano() {
    varCursor = 1;
    spriteCursor->setTextureRect(IntRect(0, 16, 16, 16));
    cursorActivo = 16;
}

bool Escenario::hayunidad()
{
    bool resultado=false;
    for(int i=0;i<1 && resultado==false;i++)
    {
        if(spriteCursor->getPosition()==aliadas[i]->getSprite().getPosition())
        {
            resultado=true;
            *unidad_sel=i;
        }
    }
    
    return resultado;
}

void Escenario::mostrarCuadriculaUnidad(int f, int c, int rangoUnidad, int color){
    
    mapa->setSpriteColor(color, c, f, 1);
            
    int auxiliar = 0;
    /*
    for(int y=rangoUnidad; y>0; y--){
        for(int x=-auxiliar; x<=auxiliar; x++){
            mapa->setSpriteColor(color, c+(x*16), f+(y*16), 0);
        }
        auxiliar ++;
    }
    */
    
    //Izquierda
    auxiliar = rangoUnidad;
    for(int y=0; y>= -rangoUnidad; y--){
        for(int x= -auxiliar; x<= auxiliar; x++){
            mapa->setSpriteColor(color, c+(x*16), f+(y*16), 0);
        }
        auxiliar --;
    }
    
    //Derecha
    auxiliar = rangoUnidad-1;
    for(int y=1; y<= rangoUnidad; y++){
        for(int x= -auxiliar; x<= auxiliar; x++){
            mapa->setSpriteColor(color, c+(x*16), f+(y*16), 0);
        }
        auxiliar --;
    }
    
    //Arriba
    auxiliar = rangoUnidad;
    for(int y=0; y>= -rangoUnidad; y--){
        for(int x= -auxiliar; x<= auxiliar; x++){
            mapa->setSpriteColor(color, c+(y*16), f+(x*16), 0);
        }
        auxiliar --;
    }
    
    //Abajo
    auxiliar = rangoUnidad-1;
    for(int y=1; y<= rangoUnidad; y++){
        for(int x= -auxiliar; x<= auxiliar; x++){
            mapa->setSpriteColor(color, c+(y*16), f+(x*16), 0);
        }
        auxiliar --;
    }
}

void Escenario::quitarCuadriculaUnidad(int f, int c, int rangoUnidad){
    
    int auxiliar = 0;
    for(int y=rangoUnidad; y>0; y--){
        for(int x=-auxiliar; x<=auxiliar; x++){
            mapa->defaultSpriteColor(c+(x*16), f+(y*16));
        }
        auxiliar ++;
    }
    
    auxiliar = rangoUnidad;
    for(int y=0; y>= -rangoUnidad; y--){
        for(int x= -auxiliar; x<= auxiliar; x++){
            mapa->defaultSpriteColor(c+(x*16), f+(y*16));
        }
        auxiliar --;
    }
}

void Escenario::mostrarStats(int numUnidad, int tipo){
    
    //Tipo 0: Aliado
    //Tipo 1: Enemigo
    
    if(tipo == 0){
        std::stringstream ss_stats;
        ss_stats << aliadas[numUnidad]->getNombre() << "    Lvl: " << aliadas[numUnidad]->getLvl() << "\n" <<  
                aliadas[numUnidad]->getClase() << "\n" << "\n" <<
                "HP: " << aliadas[numUnidad]->getHP() << "\n" <<
                "Fuerza: " << aliadas[numUnidad]->getFuerza() << "\n" <<
                "Magia: " << aliadas[numUnidad]->getMagia() << "\n" <<
                "Habilidad: " << aliadas[numUnidad]->getHab() << "\n" <<
                "Velocidad: " << aliadas[numUnidad]->getVel() << "\n" <<
                "Defensa: " << aliadas[numUnidad]->getDef() << "\n" <<
                "Defensa mag: " << aliadas[numUnidad]->getDefm() << "\n" <<
                "Rango: " << aliadas[numUnidad]->getRango();
        
        std::string s_stats = ss_stats.str();

        t_stats->setCharacterSize(8);
        t_stats->setFont(*fuente);
        t_stats->setString(s_stats);
        
        t_stats->setColor(sf::Color::White);
        t_stats->setPosition(10,100);
        
    }else{
        std::stringstream ss_stats;        
        
        ss_stats << enemigos[numUnidad]->getNombre() << "    Lvl: " << enemigos[numUnidad]->getLvl() << "\n" <<  
                enemigos[numUnidad]->getClase() << "\n" << "\n" <<
                "HP: " << enemigos[numUnidad]->getHP() << "\n" <<
                "Fuerza: " << enemigos[numUnidad]->getFuerza() << "\n" <<
                "Magia: " << enemigos[numUnidad]->getMagia() << "\n" <<
                "Habilidad: " << enemigos[numUnidad]->getHab() << "\n" <<
                "Velocidad: " << enemigos[numUnidad]->getVel() << "\n" <<
                "Defensa: " << enemigos[numUnidad]->getDef() << "\n" <<
                "Defensa mag: " << enemigos[numUnidad]->getDefm() << "\n" <<
                "Rango: " << enemigos[numUnidad]->getRango();
        
        std::string s_stats = ss_stats.str();

        t_stats->setCharacterSize(8);
        t_stats->setFont(*fuente);
        t_stats->setString(s_stats);
        
        t_stats->setColor(sf::Color::White);
        t_stats->setPosition(10,100);
    }
}

void Escenario::empiezaturnoIA()
{
    reloj2=new Clock();
}

void Escenario::render_State(){
    
    Juego::Instance()->getVentana()->clear();
    
    mapa->Draw();
    
    for(int x=0; x<mapa->getNumEnemigos(); x++){
       // if(aliadas[x]!=NULL){
            //aliadas[x]->Draw();
        //}
        enemigos[x]->Draw();
    }
    aliadas[0]->Draw();
    //enemigos[0]->Draw();
    
    for(int x=0; x<mapa->getNumCofres(); x++){
        cofres[x]->Draw();
    }
    
    if(tieneQueMostrarStats == true){
        Juego::Instance()->getVentana()->draw(*spriteMenuStats);
        Juego::Instance()->getVentana()->draw(*t_stats);
    }
    
    if(puertaSi==true){
        Juego::Instance()->getVentana()->draw(*spriteAbrirPuerta);
    }
    
    if(*turnoUsu==true)
    {
        Juego::Instance()->getVentana()->draw(*spriteCursor);
    }
    
    Juego::Instance()->renderText();
    
    Juego::Instance()->getVentana()->display();
}

void Escenario::update_State(){
    
    //Reloj del cursor
    if (relojCursor->getElapsedTime().asSeconds() >= 0.5) {
           
        if(*primeritaVes == true){
            *primeritaVes = false;
            cerr << "GRINGO, A HABLAR" << endl;
            Juego::Instance()->ponerEstadoConversacion(mapa,aliadas,enemigos,cofres,unidad_sel,turnoUsu);     
        }
        
        aliadas[0]->cambiaSpriteQuieto();
        for(int x=0; x<mapa->getNumEnemigos(); x++){
            // if(aliadas[x]!=NULL){
                //aliadas[x]->Draw();
            //}
            enemigos[x]->cambiaSpriteQuieto();
        }
        //enemigos[0]->cambiaSpriteQuieto();
        
        if(varCursor == 0){
            spriteCursor->setTextureRect(IntRect(cursorActivo, 0, 16, 16));
            cursorActivo = abs(cursorActivo-16);
        }else{
            spriteCursor->setTextureRect(IntRect(cursorActivo, 16, 16, 16));
            cursorActivo = abs(cursorActivo-16);
        }
        relojCursor->restart();
    }
    
    //Reloj del input y del movimiento
    if (reloj->getElapsedTime().asMilliseconds() >= 100) {
        
        if(aliadas[0]->getMueve()==true){
            //cerr << aliadas[0]->getSprite().getPosition().x << "<->" << aliadas[0]->getDestinoX() << "     " << aliadas[0]->getSprite().getPosition().y << "<->" << aliadas[0]->getDestinoY() << endl;
            if(aliadas[0]->verSiHaLlegado() == true){
                aliadas[0]->haLlegado();
                if(aliadas[0]->getSprite().getPosition().x == spriteCursor->getPosition().x && aliadas[0]->getSprite().getPosition().y == spriteCursor->getPosition().y){
                    aux = 0;
                    aliadas[0]->cambiaSprite(0, 0, 20, 20);
                    cambiaSpriteCursorSeleccionar();
                    Juego::Instance()->ponerEstadoMenuAcciones(mapa,aliadas,enemigos,cofres,unidad_sel,turnoUsu); 
                }else{
                    aux++;
                    switch(aliadas[0]->getRecorrido()[aux]){
                        case 1:
                            aliadas[0]->moverDerecha(); 
                            break;
                        case 2:
                            aliadas[0]->moverArriba(); 
                            break;
                        case -1:
                            aliadas[0]->moverIzquierda(); 
                            break;
                        case -2:
                            aliadas[0]->moverAbajo(); 
                            break;
                    }
                }  
            }else{
                Time tiempoPasado = reloj->restart();
                float ti = tiempoPasado.asSeconds();
                
                switch(aliadas[0]->getRecorrido()[aux]){
                    case 1:
                        aliadas[0]->setPosition(aliadas[0]->getSprite().getPosition().x+(kVel*ti),aliadas[0]->getSprite().getPosition().y);
                        aliadas[0]->cambiaSprite(cont*32, 32, 20, 20);
                        break;
                    case 2:
                        aliadas[0]->setPosition(aliadas[0]->getSprite().getPosition().x,aliadas[0]->getSprite().getPosition().y-(kVel*ti));
                        aliadas[0]->cambiaSprite(cont*32, 128, 20, 20);
                        break;
                    case -1:
                        aliadas[0]->setPosition(aliadas[0]->getSprite().getPosition().x-(kVel*ti),aliadas[0]->getSprite().getPosition().y);
                        aliadas[0]->cambiaSprite(cont*32, 64, 20, 20);
                        break;
                    case -2:
                        aliadas[0]->setPosition(aliadas[0]->getSprite().getPosition().x,aliadas[0]->getSprite().getPosition().y+(kVel*ti));
                        aliadas[0]->cambiaSprite(cont*32, 96, 20, 20);
                        break;
                        
                }
                cont++;
                if(cont==4)
                    cont = 0;
            }
        }else{            
            if(*turnoUsu==true)
            {
                input();
            }
        }
        reloj->restart();
    }
    
    //Reloj del turno del enemigo
    if(*turnoUsu==false && reloj2->getElapsedTime().asSeconds() >= 1)
    {
        tieneQueMostrarStats = false;
        
        cerr << "Se mueve el enemigo " << turnoEnemigo << "   Fase del enemigo: " << fasesEnemigo << "PosX: " << enemigos[turnoEnemigo]->getPosicionSpriteX() << endl;
        
        switch(fasesEnemigo){
            case 1: mostrarCuadriculaUnidad(enemigos[turnoEnemigo]->getPosicionSpriteX(), enemigos[turnoEnemigo]->getPosicionSpriteY(),enemigos[turnoEnemigo]->getRango(), 1);
                reloj2->restart();
                break;
            case 2: quitarCuadriculaUnidad(enemigos[turnoEnemigo]->getPosicionSpriteX(), enemigos[turnoEnemigo]->getPosicionSpriteY(),enemigos[turnoEnemigo]->getRango());
                reloj2->restart();
                break;
            case 3:
                turnoEnemigo++;
                fasesEnemigo = 0;
                    
                if(turnoEnemigo == mapa->getNumEnemigos()){
                    delete reloj2;
                    *turnoUsu=true;
                    turnoEnemigo = 0;
                    fasesEnemigo = 0;
                }
                break;
            case 4:
                break;
        }
        
        fasesEnemigo++;
    }
}

void Escenario::input() {
    
    while (Juego::Instance()->getVentana()->pollEvent(*evento)){
        if ((evento->type == Event::Closed)){
            Juego::Instance()->getVentana()->close();
        }
            
        if(evento->type == sf::Event::KeyPressed){
            switch(evento->key.code){
                
                case sf::Keyboard::Down:
                    if(spriteCursor->getPosition().y<320-16)
                    {
                        spriteCursor->move(0,16);
                        std::cerr << "Cursor en: (" << spriteCursor->getPosition().x << ", " << spriteCursor->getPosition().y << ")" <<endl;
                    }
                    if(*unidad_sel!=-1)//hay una unidad seleccionada
                    {
                        aliadas[*unidad_sel]->guardamovimiento(-2);
                        std::cerr << "-2" << endl;
                    }
                break;
                
                case sf::Keyboard::Up:
                    if(spriteCursor->getPosition().y>=16)
                    {
                        spriteCursor->move(0,-16);       
                        std::cerr << "Cursor en: (" << spriteCursor->getPosition().x << ", " << spriteCursor->getPosition().y << ")" <<endl;
                    }
                    if(*unidad_sel!=-1)//hay una unidad seleccionada
                    {
                        aliadas[*unidad_sel]->guardamovimiento(2);
                        std::cerr << "2" << endl;
                    }
                break;
                
                case sf::Keyboard::Left:
                    if(spriteCursor->getPosition().x>=16){
                        spriteCursor->move(-16,0);              
                        std::cerr << "Cursor en: (" << spriteCursor->getPosition().x << ", " << spriteCursor->getPosition().y << ")" <<endl;
                    }
                    if(*unidad_sel!=-1)//hay una unidad seleccionada
                    {
                        aliadas[*unidad_sel]->guardamovimiento(-1);
                        std:cerr << "-1" << endl;
                    }
                break;
                
                case sf::Keyboard::Right:
                    if(spriteCursor->getPosition().x<480-16){
                        spriteCursor->move(16,0);       
                        std::cerr << "Cursor en: (" << spriteCursor->getPosition().x << ", " << spriteCursor->getPosition().y << ")" <<endl;
                    }
                    if(*unidad_sel!=-1)//hay una unidad seleccionada
                    {
                        aliadas[*unidad_sel]->guardamovimiento(1);
                        std::cerr << "1" << endl;
                    }
                break;
                
                case sf::Keyboard::Numpad1:
                        aliadas[0]->hayPuerta(mapa);           
                break;
                
                case sf::Keyboard::Numpad2:
                    cerr << aliadas[0]->hayEnemigosCercanos(enemigos);
                break;
                
                case sf::Keyboard::Numpad3:
                    Juego::Instance()->ponerEstadoConversacion(mapa,aliadas,enemigos,cofres,unidad_sel,turnoUsu);
                break;
                
                case sf::Keyboard::Numpad4:
                    cerr<< "Posicion CELDA unidad: (" << aliadas[0]->getPosicionCeldaX() << ", " << aliadas[0]->getPosicionCeldaY() << ")" << endl;
                    cerr<< "Posicion PIXEL unidad: (" << aliadas[0]->getPosicionSpriteX() << ", " << aliadas[0]->getPosicionSpriteY() << ")" << endl;
                    cerr << unidad_sel << endl;
                break;
                
                case sf::Keyboard::Numpad5:
                    mostrarCuadriculaUnidad(enemigos[0]->getPosicionSpriteX(), enemigos[0]->getPosicionSpriteY(),enemigos[0]->getRango(), 1);
                break;
                
                case sf::Keyboard::Numpad6:
                    mostrarCuadriculaUnidad(aliadas[0]->getPosicionSpriteX(), aliadas[0]->getPosicionSpriteY(),aliadas[0]->getRango(), 0);
                break;
                
                case sf::Keyboard::Numpad7:
                    quitarCuadriculaUnidad(aliadas[0]->getPosicionSpriteX(), aliadas[0]->getPosicionSpriteY(),aliadas[0]->getRango());
                break;
                
                case sf::Keyboard::Numpad8:
                    Juego::Instance()->ponerEstadoMenuPrincipal();              
                break;
                case sf::Keyboard::Numpad9:
                    Juego::Instance()->ponerEstadoPause();              
                break;
                
                case sf::Keyboard::Return:
                    if(*unidad_sel==-1)
                    {
                        if(hayunidad()==true)
                        {
                            //pintar cuadricula personaje
                            cambiaSpriteCursorMano();    
                            mostrarCuadriculaUnidad(aliadas[0]->getPosicionSpriteX(), aliadas[0]->getPosicionSpriteY(),aliadas[0]->getRango(), 0);
                        }
                    }
                    else
                    {
                        if(aliadas[*unidad_sel]->getPosicionSpriteX()==spriteCursor->getPosition().x && aliadas[*unidad_sel]->getPosicionSpriteY()==spriteCursor->getPosition().y){
                            quitarCuadriculaUnidad(aliadas[0]->getPosicionSpriteX(), aliadas[0]->getPosicionSpriteY(),aliadas[0]->getRango());
                            cambiaSpriteCursorSeleccionar();
                            *unidad_sel=-1;
                        }else{
                            if(mapa->getColision(spriteCursor->getPosition().x,spriteCursor->getPosition().y)==true && mapa->puedeMoverseAqui(spriteCursor->getPosition().x,spriteCursor->getPosition().y)==true){
                                quitarCuadriculaUnidad(aliadas[0]->getPosicionSpriteX(), aliadas[0]->getPosicionSpriteY(),aliadas[0]->getRango());
                                aliadas[*unidad_sel]->recorre();
                                //aliadas[*unidad_sel]->hayPuerta(mapa);
                                //devuelve las casillas de la cuadricula a su estado original
                                //*unidad_sel=-1;
                            }
                        }
                    }
                break;
                
                case sf::Keyboard::A:
                    aliadas[0]->setPosition(aliadas[0]->getPosicionSpriteX()-16, aliadas[0]->getPosicionSpriteY());
                break;
                
                case sf::Keyboard::W:
                    aliadas[0]->setPosition(aliadas[0]->getPosicionSpriteX(), aliadas[0]->getPosicionSpriteY()-16);
                break;
                
                case sf::Keyboard::S:
                    aliadas[0]->setPosition(aliadas[0]->getPosicionSpriteX(), aliadas[0]->getPosicionSpriteY()+16);
                break;
                
                case sf::Keyboard::D:
                    aliadas[0]->setPosition(aliadas[0]->getPosicionSpriteX()+16, aliadas[0]->getPosicionSpriteY());
                break;
                
                case sf::Keyboard::Escape:
                    Juego::Instance()->getVentana()->close();               
                break;
            }
            
            tieneQueMostrarStats = false;
            
            for(int i=0; i<1; i++){
                if(spriteCursor->getPosition().x == aliadas[i]->getPosicionSpriteX() && spriteCursor->getPosition().y == aliadas[i]->getPosicionSpriteY()){
                    mostrarStats(i, 0);
                    tieneQueMostrarStats = true;
                }
            }

            for(int i=0; i<mapa->getNumEnemigos(); i++){
                if(spriteCursor->getPosition().x == enemigos[i]->getPosicionSpriteX() && spriteCursor->getPosition().y == enemigos[i]->getPosicionSpriteY()){
                    mostrarStats(i, 1);
                    tieneQueMostrarStats = true;
                }
            }
        }
    }
}

bool Escenario::getPuertaSi(){
    return puertaSi;
}

bool Escenario::getCofreSi(){
    return cofreSi;
}

bool Escenario::getEnemigoSi(){
    return enemigoSi;
}

void Escenario::volverMenuAcciones(){
    
    Juego::Instance()->ponerEstadoMenuAcciones(mapa,aliadas,enemigos,cofres,unidad_sel,turnoUsu); 

}