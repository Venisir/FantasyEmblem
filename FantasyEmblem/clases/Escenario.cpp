/* 
 * File:   Escenario.cpp
 * Author: Alberto
 * 
 * Created on 15 de abril de 2015, 9:41
 */

#include "../headers/Aliadas.h"
#include "../headers/Enemigo.h"
#include "../headers/Escenario.h"
#include "../headers/Estado.h"
#include "../headers/Juego.h"
#include "../headers/Mapa.h"

#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

#define kVel 10

Escenario* Escenario::pinstance = 0;

Escenario* Escenario::Instance () {
    if(pinstance == 0){ //¿Es la primera llamada?
        pinstance = new Escenario("mapa1"); //Creamos la instancia
    }
    return pinstance; //Retornamos la direccion de la instancia
}

Escenario::Escenario() {

}

Escenario::Escenario(const char* nombremapa) {
    //Realizar inicializaciones necesarias de la instancia
    //ventana->create(sf::VideoMode(480,320), "Fantasy Emblem");
    texturaCursor = new Texture();
    spriteCursor = new Sprite();
    reloj = new Clock();
    relojCursor = new Clock();
    relojTurno = new Clock();
    evento = new Event();
    mapa = new Mapa(nombremapa);
    aliadas=new Aliadas*[5];
    //enemigos=new Enemigo*[5];
    cofres=new Cofre*[5];
    objeto=new Objetos*[3];
    arma=new Armas*[3];
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
    texturaTurnoUsu = new Texture();
    
    spriteTurnoUsu = new Sprite();
    spriteAbrirPuerta = new Sprite();
    
    int atri[] = { 20, 9, 1, 19, 19, 6, 4};
    var = 0;
    
    cofres=mapa->getCofres();
    enemigos=mapa->getEnemigos();
    aliadas[0] = new Aliadas("Eirika", "Espadachin", atri, 8, 5, "Mapa_Eirika.png","ike.png" ,"retrato2.png",95,objeto,arma);

    aliadas[1] = new Aliadas("Meisner", "Espadachin", atri, 8, 5, "Mapa_espadachin_azul.png","ike.png" ,"retrato1.png",0,objeto,arma);

    pause_open = new SoundBuffer();
    opause = new Sound();
    
    Mapacambio=-1;
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
    delete pause_open;
    delete opause;
    delete spriteAbrirPuerta;
    delete texturaTurnoUsu;
    delete spriteTurnoUsu;
}

void Escenario::ResetInstance(){
    //delete pinstance; // REM : it works even if the pointer is NULL (does nothing then)
    pinstance = 0; // so GetInstance will still work.
}

void Escenario::nuevoEscenario(const char* nombremapa) {   
    pinstance= new Escenario(nombremapa);
}



void Escenario::init_State(){
    
     
    if (!texturaCursor-> loadFromFile("resources/cursores.png"))
    {
        std::cerr << "Error cargando la imagen cursores.png";
        exit(0);
    }
    
    if (!texturaTurnoUsu-> loadFromFile("resources/turnoJugador.png"))
    {
        std::cerr << "Error cargando la imagen turnoJugador.png";
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
    
    spriteTurnoUsu->setTexture(*texturaTurnoUsu);
    spriteTurnoUsu->setOrigin(120/2,60/2);
    spriteTurnoUsu->setPosition(240,160);
    
    puertaSi = false;
    cofreSi = false;
    enemigoSi = false;
    
    vengaEntra = false;
    
    cambiaSpriteCursorSeleccionar();
    
    cursorActivo = 0;
    varCursor = 0;    
    bool debeEntrar = false;
   
    fuente->loadFromFile("resources/font.ttf");
    
    spriteMenuStats->setTexture(*texturaMenuStats);
    spriteMenuStats->setPosition(0,90);
    
    tieneQueMostrarStats = false;

    aliadas[0]->setPosition(176,176);
    aliadas[1]->setPosition(224,176);
    
    fasesEnemigo = 1;
    turnoEnemigo = 0;
    
    *unidad_sel=-1;
    *turnoUsu=true;
    *primeritaVes = true;
    
    cont = 0;
    aux = 0;
    
    if (!pause_open->loadFromFile("resources/PauseMenu_Open.wav")){
        std::cerr << "Error al cargar el archivo de audio";
    }
    
    opause->setBuffer(*pause_open);
    opause->setVolume(80);
    
    turnoSi = false;
}

void Escenario::paramusic(){
    mapasonido1->stop();
}

void Escenario::playmusic(){
    mapasonido1->play();
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
    for(int i=0; i<sizeof(aliadas)/sizeof(int)+1 && resultado==false; i++)
    {
        if(spriteCursor->getPosition()==aliadas[i]->getSprite().getPosition())
        {
            resultado=true;
            *unidad_sel=i;
        }
    }
    return resultado;
}

bool Escenario::hayunidadAqui(int i, int j)
{
    bool resultado=false;
    for(int w=0; w<sizeof(enemigos)/sizeof(int)+1; w++){
        if(enemigos[w]->getSprite().getPosition().x == j && enemigos[w]->getSprite().getPosition().y == i){
            resultado=true;
            cerr << "Enemigo " << w << ", x: " << enemigos[w]->getSprite().getPosition().x << " y:" << enemigos[w]->getSprite().getPosition().y << endl;
            cerr << "i: " << i << "  j: " << j << endl;
        }
    }
    return resultado;
}

Mapa* Escenario::getMapa() 
{
    return mapa;
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
            //if(hayunidadAqui(c+(x*16),f+(y*16))==false)
                mapa->setSpriteColor(color, c+(x*16), f+(y*16), 0);
        }
        auxiliar --;
    }
    
    //Derecha
    auxiliar = rangoUnidad-1;
    for(int y=1; y<= rangoUnidad; y++){
        for(int x= -auxiliar; x<= auxiliar; x++){
            //if(hayunidadAqui(c+(x*16),f+(y*16))==false)
                mapa->setSpriteColor(color, c+(x*16), f+(y*16), 0);
        }
        auxiliar --;
    }
    
    //Arriba
    auxiliar = rangoUnidad;
    for(int y=0; y>= -rangoUnidad; y--){
        for(int x= -auxiliar; x<= auxiliar; x++){
            //if(hayunidadAqui(c+(x*16),f+(y*16))==false)
                mapa->setSpriteColor(color, c+(y*16), f+(x*16), 0);
        }
        auxiliar --;
    }
    
    //Abajo
    auxiliar = rangoUnidad-1;
    for(int y=1; y<= rangoUnidad; y++){
        for(int x= -auxiliar; x<= auxiliar; x++){
            //if(hayunidadAqui(c+(x*16),f+(y*16))==false)
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

void Escenario::cambiaMapa(const char* nombremapa) {
    mapa=new Mapa(nombremapa);
    cofres=mapa->getCofres();
    enemigos=mapa->getEnemigos();
    int atri[] = { 11, 22, 33, 44, 55, 66, 77};

    aliadas[0] = new Aliadas("Alberto", "Espadachin", atri, 8, 5, "Mapa_espadachin_azul.png","ike.png" ,"ike.png",95,objeto,arma);
    aliadas[1] = new Aliadas("Albertina", "Espadachina", atri, 8, 5, "Mapa_espadachin_azul.png","ike.png" ,"ike.png",95,objeto,arma);
    EstadoConversacion::Instance()->reset();
    EstadoConversacion::Instance(mapa,aliadas,enemigos,cofres,unidad_sel,turnoUsu,objeto,arma);
}

void Escenario::setCambio(int n) {
    Mapacambio=n;
}


void Escenario::empiezaturnoIA()
{
    reloj2=new Clock();
}

void Escenario::render_State(){
    
    Juego::Instance()->getVentana()->clear();
    ////////////////////////////
    sf::Vector2f position(Juego::Instance()->getVentana()->getSize().x / 4, Juego::Instance()->getVentana()->getSize().y/4);
    
    if(spriteCursor->getPosition().y+16<(mapa->getAltura()*16)/2){
        if(spriteCursor->getPosition().y + 16 > Juego::Instance()->getVentana()->getSize().y/4){
            position.y = spriteCursor->getPosition().y + 16;
        }else{
            position.y = Juego::Instance()->getVentana()->getSize().y/4;
        }
    }else{
        if(spriteCursor->getPosition().y + 16 < (mapa->getAltura()*16)-Juego::Instance()->getVentana()->getSize().y/4){
            position.y = spriteCursor->getPosition().y + 16;
        }else{
            position.y = (mapa->getAltura()*16)-Juego::Instance()->getVentana()->getSize().y/4;
        }
    }
    
    sf::View view2=Juego::Instance()->getVentana()->getView();
    view2.setCenter(position);
    
    Juego::Instance()->getVentana()->setView(view2);
    Juego::Instance()->setView(view2);
    ///////////////////////////////////////////
    mapa->Draw();
    
    for(int x=0; x<mapa->getNumEnemigos(); x++){
        enemigos[x]->Draw();
    }
    
    for(int x=0; x<mapa->getNumCofres(); x++){
        cofres[x]->Draw();
    }
    
    for(int i=0; i<sizeof(aliadas)/sizeof(int)+1; i++){
        aliadas[i]->Draw();
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
    
    if(turnoSi == true){
        Juego::Instance()->getVentana()->draw(*spriteTurnoUsu);
    }
    
    Juego::Instance()->renderText();
    Juego::Instance()->getVentana()->display();
}

void Escenario::update_State(){
    
    if(Mapacambio!=-1)
    {
        if(Mapacambio==1)
        {
            Mapacambio=-1;
            cambiaMapa("mapaPruebas");
            init_State();
        }
    }
    
    //Reloj del cursor
    if (relojCursor->getElapsedTime().asSeconds() >= 0.5) {
           
        if(*primeritaVes == true){
            *primeritaVes = false;

            cerr << "GRINGO, A HABLAR" << endl;
            Juego::Instance()->ponerEstadoConversacion(mapa,aliadas,enemigos,cofres,unidad_sel,turnoUsu,objeto,arma);     
        }
        
        for(int i=0; i<sizeof(aliadas)/sizeof(int)+1; i++){
            if(aliadas[i]->getMueve()==false)
            aliadas[i]->cambiaSpriteQuieto();
        }
        
        for(int x=0; x<mapa->getNumEnemigos(); x++){
            if(enemigos[x]->getMueve()==false)
            enemigos[x]->cambiaSpriteQuieto();
        }
        
        if(varCursor == 0){
            spriteCursor->setTextureRect(IntRect(cursorActivo, 0, 16, 16));
            cursorActivo = abs(cursorActivo-16);
        }else{
            spriteCursor->setTextureRect(IntRect(cursorActivo, 16, 16, 16));
            cursorActivo = abs(cursorActivo-16);
        }
        relojCursor->restart();
    }
    
    if (relojTurno->getElapsedTime().asSeconds() >= 2) {
        turnoSi = false;
    }
    
    //Reloj del input y del movimiento
    if (reloj->getElapsedTime().asMilliseconds() >= 70) {
        
        
        ////////////////////////////////////////////////////////////////////
        if(*unidad_sel!=-1 && aliadas[*unidad_sel]->getMueve()==true){
            
            if(aliadas[*unidad_sel]->verSiHaLlegado() == true){
                aliadas[*unidad_sel]->haLlegado();
                if(aliadas[*unidad_sel]->getSprite().getPosition().x == spriteCursor->getPosition().x && aliadas[*unidad_sel]->getSprite().getPosition().y == spriteCursor->getPosition().y){
                    aux = 0;
                    aliadas[*unidad_sel]->cambiaSprite(0, 0, 20, 20);
                    cambiaSpriteCursorSeleccionar();
                    cout<<"petaescenarioantes"<<endl;
                    Juego::Instance()->ponerEstadoMenuAcciones(mapa,aliadas,enemigos,cofres,unidad_sel,turnoUsu,objeto,arma); 
                    cout<<"petaescenariodespues"<<endl;
                
                    //*unidad_sel = -1;
                }else{
                    aux++;
                    switch(aliadas[*unidad_sel]->getMovimientos()[aux]){
                        case 1:
                            aliadas[*unidad_sel]->moverDerecha(); 
                            break;
                        case 2:
                            aliadas[*unidad_sel]->moverArriba(); 
                            break;
                        case -1:
                            aliadas[*unidad_sel]->moverIzquierda(); 
                            break;
                        case -2:
                            aliadas[*unidad_sel]->moverAbajo(); 
                            break;
                    }
                }  
            }else{
                Time tiempoPasado = reloj->restart();
                float ti = tiempoPasado.asSeconds();
                ////////////////////////////////////////////////
                /*ANTIGUO METODO*/
                /*
                switch(aliadas[*unidad_sel]->getRecorrido()[aux]){
                    case 1:
                        aliadas[*unidad_sel]->setPosition(aliadas[*unidad_sel]->getSprite().getPosition().x+(kVel*ti),aliadas[*unidad_sel]->getSprite().getPosition().y);
                        aliadas[*unidad_sel]->cambiaSprite(cont*32, 32, 20, 20);
                        break;
                    case 2:
                        aliadas[*unidad_sel]->setPosition(aliadas[*unidad_sel]->getSprite().getPosition().x,aliadas[*unidad_sel]->getSprite().getPosition().y-(kVel*ti));
                        aliadas[*unidad_sel]->cambiaSprite(cont*32, 128, 20, 20);
                        break;
                    case -1:
                        aliadas[*unidad_sel]->setPosition(aliadas[*unidad_sel]->getSprite().getPosition().x-(kVel*ti),aliadas[*unidad_sel]->getSprite().getPosition().y);
                        aliadas[*unidad_sel]->cambiaSprite(cont*32, 64, 20, 20);
                        break;
                    case -2:
                        aliadas[*unidad_sel]->setPosition(aliadas[*unidad_sel]->getSprite().getPosition().x,aliadas[*unidad_sel]->getSprite().getPosition().y+(kVel*ti));
                        aliadas[*unidad_sel]->cambiaSprite(cont*32, 96, 20, 20);
                        break;
                        
                 
                }
                */
                /////////////////////////////////////////////
                
                /*ESTRELLA ESTRELLITA DONDE ESTAS*/
                
                switch(aliadas[*unidad_sel]->getMovimientos()[aux]){
                    case 1:
                        aliadas[*unidad_sel]->setPosition(aliadas[*unidad_sel]->getSprite().getPosition().x+(kVel*ti),aliadas[*unidad_sel]->getSprite().getPosition().y);
                        aliadas[*unidad_sel]->cambiaSprite(cont*32, 32, 20, 20);
                        break;
                    case 2:
                        aliadas[*unidad_sel]->setPosition(aliadas[*unidad_sel]->getSprite().getPosition().x,aliadas[*unidad_sel]->getSprite().getPosition().y-(kVel*ti));
                        aliadas[*unidad_sel]->cambiaSprite(cont*32, 128, 20, 20);
                        break;
                    case -1:
                        aliadas[*unidad_sel]->setPosition(aliadas[*unidad_sel]->getSprite().getPosition().x-(kVel*ti),aliadas[*unidad_sel]->getSprite().getPosition().y);
                        aliadas[*unidad_sel]->cambiaSprite(cont*32, 64, 20, 20);
                        break;
                    case -2:
                        aliadas[*unidad_sel]->setPosition(aliadas[*unidad_sel]->getSprite().getPosition().x,aliadas[*unidad_sel]->getSprite().getPosition().y+(kVel*ti));
                        aliadas[*unidad_sel]->cambiaSprite(cont*32, 96, 20, 20);
                        break;
                        
                }
                
                /////////////////////////////////////////////
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
    
        //Reloj del turno del enemigo
        if(*turnoUsu==false /*&& reloj2->getElapsedTime().asSeconds() >= 1*/){
            if(enemigos[turnoEnemigo]->getMueve()==true){
                if(enemigos[turnoEnemigo]->verSiHaLlegado() == true){
                    enemigos[turnoEnemigo]->haLlegado();
                    if(enemigos[turnoEnemigo]->getSprite().getPosition().x == enemigos[turnoEnemigo]->getSprite().getPosition().x-16 && enemigos[turnoEnemigo]->getSprite().getPosition().y == enemigos[turnoEnemigo]->getSprite().getPosition().y){
                        aux = 0;
                        enemigos[turnoEnemigo]->cambiaSprite(0, 0, 20, 20);
                        //cambiaSpriteCursorSeleccionar();
                        //Juego::Instance()->ponerEstadoMenuAcciones(mapa,aliadas,enemigos,cofres,unidad_sel,turnoUsu); 

                        //*unidad_sel = -1;
                    }else{
                        aux++;
                        switch(enemigos[turnoEnemigo]->getMovimientos()[aux]){
                            case 1:
                                enemigos[turnoEnemigo]->moverDerecha(); 
                                break;
                            case 2:
                                enemigos[turnoEnemigo]->moverArriba(); 
                                break;
                            case -1:
                                enemigos[turnoEnemigo]->moverIzquierda(); 
                                break;
                            case -2:
                                enemigos[turnoEnemigo]->moverAbajo(); 
                                break;
                        }
                    }  
                }else{
                    Time tiempoPasado = reloj->restart();
                    float ti = tiempoPasado.asSeconds();

                    switch(enemigos[turnoEnemigo]->getMovimientos()[aux]){
                        case 1:
                            enemigos[turnoEnemigo]->setPosition(enemigos[turnoEnemigo]->getSprite().getPosition().x+(kVel*ti),enemigos[turnoEnemigo]->getSprite().getPosition().y);
                            enemigos[turnoEnemigo]->cambiaSprite(cont*32, 32, 20, 20);
                            break;
                        case 2:
                            enemigos[turnoEnemigo]->setPosition(enemigos[turnoEnemigo]->getSprite().getPosition().x,enemigos[turnoEnemigo]->getSprite().getPosition().y-(kVel*ti));
                            enemigos[turnoEnemigo]->cambiaSprite(cont*32, 128, 20, 20);
                            break;
                        case -1:
                            enemigos[turnoEnemigo]->setPosition(enemigos[turnoEnemigo]->getSprite().getPosition().x-(kVel*ti),enemigos[turnoEnemigo]->getSprite().getPosition().y);
                            enemigos[turnoEnemigo]->cambiaSprite(cont*32, 64, 20, 20);
                            break;
                        case -2:
                            enemigos[turnoEnemigo]->setPosition(enemigos[turnoEnemigo]->getSprite().getPosition().x,enemigos[turnoEnemigo]->getSprite().getPosition().y+(kVel*ti));
                            enemigos[turnoEnemigo]->cambiaSprite(cont*32, 96, 20, 20);
                            break;
                    }
                    cont++;
                    if(cont==4)
                        cont = 0;
                }
            }else{
                tieneQueMostrarStats = false;

                //cerr << "Se mueve el enemigo " << turnoEnemigo << "   Fase del enemigo: " << fasesEnemigo << "PosX: " << enemigos[turnoEnemigo]->getPosicionSpriteX() << endl;

                switch(fasesEnemigo){
                    case 1: 
                        mostrarCuadriculaUnidad(enemigos[turnoEnemigo]->getPosicionSpriteX(), enemigos[turnoEnemigo]->getPosicionSpriteY(),enemigos[turnoEnemigo]->getRango(), 1);
                            
                        reloj2->restart();
                        
                        break;
                    case 2: 
                        
                        debeEntrar= false;
                        
                        for(int i=0; i<sizeof(aliadas)/sizeof(int)+1; i++){
                            if(mapa->getCasillaPintada(aliadas[i]->getPosicionSpriteX(),aliadas[i]->getPosicionSpriteY()) == true){
                                debeEntrar = true;
                                var = i;
                            }
                        }
                        if(debeEntrar == true){
                            enemigos[turnoEnemigo]->recorridoA(aliadas[var]->getPosicionSpriteX(),aliadas[var]->getPosicionSpriteY());
                            enemigos[turnoEnemigo]->borraultimo();
                            enemigos[turnoEnemigo]->recorre();

                            quitarCuadriculaUnidad(enemigos[turnoEnemigo]->getPosicionSpriteX(), enemigos[turnoEnemigo]->getPosicionSpriteY(),enemigos[turnoEnemigo]->getRango());
                            
                            
                        }else{
                            enemigos[turnoEnemigo]->recorridoA(enemigos[turnoEnemigo]->getSprite().getPosition().x,enemigos[turnoEnemigo]->getSprite().getPosition().y);
                            enemigos[turnoEnemigo]->recorre();
                            quitarCuadriculaUnidad(enemigos[turnoEnemigo]->getPosicionSpriteX(), enemigos[turnoEnemigo]->getPosicionSpriteY(),enemigos[turnoEnemigo]->getRango());
                            
                        }
                        reloj2->restart();
                        break;
                        
                    case 3:
                        
                        cerr << "Hola1" << endl;
                        enemigos[turnoEnemigo]->cambiaSprite(0, 0, 20, 20);
                        turnoEnemigo++;
                        fasesEnemigo = 0;
                        vengaEntra = false;
                        reloj2->restart();
                        aux = 0;
                        if(turnoEnemigo == mapa->getNumEnemigos()){
                            delete reloj2;
                            *turnoUsu=true;
                            turnoEnemigo = 0;
                            fasesEnemigo = 0;
                            relojTurno->restart();
                            turnoSi = true;
                        }
                        if(debeEntrar == true){
                            Juego::Instance()->ponerEstadoBatallaEnemigo(aliadas[var],enemigos[turnoEnemigo]);
                        }
                        input();
                        break;
                    case 4:
                        break;
                }
                fasesEnemigo++;
            }
        }
        reloj->restart();
    }
}

void Escenario::teclaArriba(){
    if(spriteCursor->getPosition().y>=16){
        spriteCursor->move(0,-16);       
        std::cerr << "Cursor en: (" << spriteCursor->getPosition().x << ", " << spriteCursor->getPosition().y << ")" <<endl;
    }
    if(*unidad_sel!=-1){
        aliadas[*unidad_sel]->guardamovimiento(2);
    }
}

void Escenario::teclaDerecha(){
    if(spriteCursor->getPosition().x<480-16){
        spriteCursor->move(16,0);       
        std::cerr << "Cursor en: (" << spriteCursor->getPosition().x << ", " << spriteCursor->getPosition().y << ")" <<endl;
    }
    if(*unidad_sel!=-1){
        aliadas[*unidad_sel]->guardamovimiento(1);
    }
}

void Escenario::teclaIzquierda(){
    if(spriteCursor->getPosition().x>=16){
        spriteCursor->move(-16,0);              
        std::cerr << "Cursor en: (" << spriteCursor->getPosition().x << ", " << spriteCursor->getPosition().y << ")" <<endl;
    }
    if(*unidad_sel!=-1){
        aliadas[*unidad_sel]->guardamovimiento(-1);
    }
}

void Escenario::teclaAbajo(){
    
    if(spriteCursor->getPosition().y<(mapa->getAltura()*16)-16){
        spriteCursor->move(0,16);
        std::cerr << "Cursor en: (" << spriteCursor->getPosition().x << ", " << spriteCursor->getPosition().y << ")" <<endl;
    }
    if(*unidad_sel!=-1){
        aliadas[*unidad_sel]->guardamovimiento(-2);
    }
}

void Escenario::teclaIntro(){
    if(*unidad_sel==-1){
        if(hayunidad()==true){
            if(aliadas[*unidad_sel]->getHaJugado() == false){
                //pintar cuadricula personaje
                cambiaSpriteCursorMano();    
                mostrarCuadriculaUnidad(aliadas[*unidad_sel]->getPosicionSpriteX(), aliadas[*unidad_sel]->getPosicionSpriteY(),aliadas[*unidad_sel]->getRango(), 0);
            }else{
                cerr << "Esa unidad ya se ha movido" << endl;
                *unidad_sel = -1;
            }
        }
    }else{
        if(aliadas[*unidad_sel]->getPosicionSpriteX()==spriteCursor->getPosition().x && aliadas[*unidad_sel]->getPosicionSpriteY()==spriteCursor->getPosition().y){
            quitarCuadriculaUnidad(aliadas[*unidad_sel]->getPosicionSpriteX(), aliadas[*unidad_sel]->getPosicionSpriteY(),aliadas[*unidad_sel]->getRango());
            cambiaSpriteCursorSeleccionar();
            *unidad_sel=-1;
        }else{
            if(mapa->getColision(spriteCursor->getPosition().x,spriteCursor->getPosition().y)==true && mapa->puedeMoverseAqui(spriteCursor->getPosition().x,spriteCursor->getPosition().y)==true){
                //ANTIGUO
                //aliadas[*unidad_sel]->recorre();
                //ESTRELLA
                
                aliadas[*unidad_sel]->recorridoA(spriteCursor->getPosition().x, spriteCursor->getPosition().y);
                
                quitarCuadriculaUnidad(aliadas[*unidad_sel]->getPosicionSpriteX(), aliadas[*unidad_sel]->getPosicionSpriteY(),aliadas[*unidad_sel]->getRango());
                aliadas[*unidad_sel]->recorre();
            }
        }
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
                    teclaAbajo();
                break;
                
                case sf::Keyboard::Up:
                    teclaArriba();
                break;
                
                case sf::Keyboard::Left:
                    teclaIzquierda();
                break;
                
                case sf::Keyboard::Right:
                    teclaDerecha();
                break;
                
                case sf::Keyboard::Return:
                    teclaIntro();
                break;
                
                case sf::Keyboard::Numpad1:
                    //Limpiar consola
                    system("cls");
                break;
                
                case sf::Keyboard::Numpad2:
                    //Estado conversacion
                break;
                
                case sf::Keyboard::Numpad3:
                    if(sf::Joystick::isConnected(0)){
                        cerr << "Mando conectado!" << endl;
                    }else{
                        cerr << "Mando no conectado!" << endl;
                    }
                break;
                
                case sf::Keyboard::Numpad4:
                    borraAliado(0);
                break;
                
                case sf::Keyboard::Numpad5:
                    borraEnemigo(0);
                break;
                
                case sf::Keyboard::Numpad6:
                    //mapa->getCofre(aliadas[0]->getPosicionSpriteY(),aliadas[0]->getPosicionSpriteX());
                break;
                
                case sf::Keyboard::Numpad7:
                    Juego::Instance()->ponerEstadoConversacion(mapa,aliadas,enemigos,cofres,unidad_sel,turnoUsu,objeto,arma);     
        
                break;
                
                case sf::Keyboard::Numpad8:
                break;
                
                case sf::Keyboard::Numpad9:
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
                
                case sf::Keyboard::P:
                    //Pause
                    mapasonido1->pause();
                    opause->play();
                    Juego::Instance()->ponerEstadoPause();    
                break;
                
                case sf::Keyboard::M:
                    //Menu principal
                    mapasonido1->pause();
                    Juego::Instance()->ponerEstadoMenuPrincipal();    
                break;
                
                case sf::Keyboard::Escape:
                    Juego::Instance()->getVentana()->close();               
                break;
                
                case sf::Keyboard::Num5:
                    Mapacambio=1;
                break;
            }
        }else{
            if(sf::Joystick::isConnected(0)){
                
                if (evento->type == sf::Event::JoystickMoved)
                {
                    /*Mi mando*/
                    /*
                    if (evento->joystickMove.axis == sf::Joystick::PovX){
                        if(evento->joystickMove.position == -100){
                            teclaAbajo();
                        }else if(evento->joystickMove.position == +100){
                            teclaArriba();
                        }
                    }
                    if (evento->joystickMove.axis == sf::Joystick::PovY){
                        if(evento->joystickMove.position == -100){
                            teclaIzquierda();
                        }else if(evento->joystickMove.position == +100){
                            teclaDerecha();
                        }
                    }
                    */
                    /*Mando xBox*/
                    if (evento->joystickMove.axis == sf::Joystick::PovX){
                        if(evento->joystickMove.position == -100){
                            teclaAbajo();
                        }else if(evento->joystickMove.position == +100){
                            teclaArriba();
                        }
                    }else if (evento->joystickMove.axis == sf::Joystick::PovY){
                        if(evento->joystickMove.position == -100){
                            teclaIzquierda();
                        }else if(evento->joystickMove.position == +100){
                            teclaDerecha();
                        }
                    }
                    
                    /*
                    if (evento->joystickMove.joystickId == 0){
                        //cerr << x << " " << y << endl;
                        if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) == -100){
                            teclaIzquierda();
                        }else if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) == +100){
                            teclaDerecha();
                        }else if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == -100){
                            teclaArriba();
                        }else if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == +100){
                            teclaAbajo();
                        }
                    }
                    */
                }
                
                if(evento->type == sf::Event::JoystickButtonPressed){
                    
                    switch(evento->joystickButton.button){
                        /*Mi mando*/
                        /*
                        case 2:
                            teclaIntro();
                        break;
                        case 9:
                            mapasonido1->pause();
                            opause->play();
                            Juego::Instance()->ponerEstadoPause();  
                        break;
                        */
                        
                        /*Mando xBox360*/
                        case 0:
                            teclaIntro();
                        break;
                        case 7:
                            mapasonido1->pause();
                            opause->play();
                            Juego::Instance()->ponerEstadoPause();  
                        break;
                        
                    }
                }
            }
            
            tieneQueMostrarStats = false;
            
            for(int i=0; i<sizeof(aliadas)/sizeof(int)+1; i++){
                if(spriteCursor->getPosition().x == aliadas[i]->getPosicionSpriteX() && spriteCursor->getPosition().y == aliadas[i]->getPosicionSpriteY()){
                    mostrarStats(i, 0);
                    tieneQueMostrarStats = true;
                }
            }

            for(int i=0; i< mapa->getNumEnemigos(); i++){
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
    Juego::Instance()->ponerEstadoMenuAcciones(mapa,aliadas,enemigos,cofres,unidad_sel,turnoUsu,objeto,arma); 
}

void Escenario::deseleccionarUnidad(){
    *unidad_sel = -1;
}

void Escenario::borraEnemigo(int e){
    delete enemigos[e];
    
    for(int i=e; i<sizeof(enemigos)/sizeof(int); i++){
        if(enemigos[i+1]!=NULL){ 
            enemigos[i] = enemigos[i+1];
        }
    }
}

void Escenario::borraAliado(int a){
    aliadas[a] = NULL;
    
    for(int i=a; i<sizeof(aliadas)/sizeof(int); i++){
        //if(aliadas[i+1]!=NULL){
            aliadas[i] = aliadas[i+1];
        //}
    }
}

Enemigo** Escenario::getEnemigos(){
    return enemigos;
}