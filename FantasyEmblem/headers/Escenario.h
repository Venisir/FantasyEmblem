/* 
 * File:   Escenario.h
 * Author: Ricardo
 *
 * Created on 15 de abril de 2015, 9:41
 */

#ifndef ESCENARIO_H
#define	ESCENARIO_H

#include "../headers/Juego.h"
#include "../headers/Aliadas.h"
#include "../headers/Enemigo.h"
#include "../headers/Escenario.h"
#include "../headers/Unidad.h"
#include "../headers/Estado.h"
#include "../headers/Mapa.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string>

//using namespace tinyxml2;
using namespace std;
using namespace sf;

class Escenario: public Estado{
public:
    
    static Escenario* Instance();
    
    static void ResetInstance();
    static void nuevoEscenario(const char* nombremapa);
    void input();
    
    void cambiaSpriteCursorMano();
    void cambiaSpriteCursorSeleccionar();
    void mostrarCuadriculaUnidad(int xx, int yy, int rangoUnidad, int color);
    void quitarCuadriculaUnidad(int xx, int yy, int rangoUnidad);
    bool hayunidad();
    bool hayunidadAqui(int i, int j);
    Mapa* getMapa();
    Enemigo** getEnemigos();
    void mostrarStats(int numUnidad, int tipo);
    void setEnemigo(Enemigo* malo);
    void empiezaturnoIA();
    void volverMenuAcciones();
    void paramusic();
    void pausemusic();
    void playmusic();
    
    void deseleccionarUnidad();
    
    bool getPuertaSi();
    bool getCofreSi();
    bool getEnemigoSi();
    
    void teclaArriba();
    void teclaDerecha();
    void teclaIzquierda();
    void teclaAbajo();
    void teclaIntro();
    void cambiaMapa(const char* nombremapa);
    
    void borraEnemigo(int e);
    void borraAliado(int a);
    void setCambio(int n);

protected:
    Escenario();
    Escenario(const char* nombremapa);
    ~Escenario();

private:
    static Escenario* pinstance;
    
    void init_State();
    void render_State();
    void update_State();
    
    sf::Texture* texturaCursor;
    sf::Texture* texturaTurnoUsu;
    sf::Texture* texturaMenuStats;
    sf::Sprite* spriteMenuStats;
    sf::Sprite* spriteTurnoUsu;
    sf::Sprite* spriteCursor;
    sf::Clock* reloj;
    sf::Clock* relojCursor;
    sf::Clock* reloj2;
    sf::Clock* relojTurno;
    sf::Event* evento;
    sf::Font* fuente;
    sf::Text* t_stats;
    sf::SoundBuffer* mapasonido;
    sf::Sound* mapasonido1;
    
    sf::Texture* texturaAbrirPuerta;
    sf::Sprite* spriteAbrirPuerta;
    
    Mapa* mapa;
    
    int cursorActivo;
    int varCursor;
    int *unidad_sel;
    bool *turnoUsu;
    bool *primeritaVes;
    bool debeEntrar;
    
    int turnoEnemigo;
    int fasesEnemigo;
    int aux;
    int cont;
    int var;
    
    bool tieneQueMostrarStats;
    bool puertaSi;
    bool cofreSi;
    bool enemigoSi;
    bool turnoSi;
    
    bool vengaEntra;
    
    Aliadas** aliadas;//aray de unidades aliadas (posiblemente esten en mapa)
    Enemigo** enemigos;//array de unidades enemigas
    Cofre** cofres;
    
    Objetos** objeto;
    Armas** arma;
    
    int Mapacambio;
    
    sf::SoundBuffer* pause_open;
    sf::Sound* opause;
};

#endif	/* ESCENARIO_H */

