/* 
 * File:   EstadoConversacion.h
 * Author: Alberto
 *
 * Created on 13 de mayo de 2015, 9:53
 */

#ifndef ESTADOCONVERSACION_H
#define	ESTADOCONVERSACION_H

#include "../headers/Juego.h"
#include "../headers/Aliadas.h"
#include "../headers/Enemigo.h"
#include "../headers/Escenario.h"
#include "../headers/Unidad.h"
#include "../headers/Estado.h"
#include "../headers/Mapa.h"
#include "../headers/EstadoBatall.h"
#include "../headers/Cofre.h"
#include "../tinyxml2.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <string>

using namespace tinyxml2;
using namespace std;
using namespace sf;

class EstadoConversacion:public Estado {
public:

    static EstadoConversacion* Instance(Mapa* ma, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice,bool *turno,Objetos** obj, Armas** arm);
    static EstadoConversacion* Instance();
    void input();
    void cambiaQuienHabla();
    void siguienteTexto();
    void setMapa(Mapa* me);
    void reset();
    
protected:
    EstadoConversacion();

    EstadoConversacion(Mapa* ma, Aliadas** al, Enemigo** ene, Cofre** cofr, int *indice,bool *turno,Objetos** obj, Armas** arm);
    ~EstadoConversacion();        

private:
    static EstadoConversacion* pinstance;
    void init_State();
    void render_State();
    void update_State();
    
    sf::Texture *texturaPersonajeIzq;
    sf::Texture *texturaPersonajeDer;
    sf::Texture *texturaPergamino;
    
    sf::Sprite *personajeIzq;
    sf::Sprite *personajeDer;
    sf::Sprite *pergamino;
    
    sf::Clock *reloj;
    sf::Clock *reloj2;
    sf::Clock *reloj3;
    
    sf::Event *evento;
    
    sf::Text *recuadroTexto;
    sf::Text *nombre;
    sf::Font *fuente;
    
    int contX;
    int contY;
    
    int quienHabla;
    int cambioMapa;
    
    
    Mapa* maux;//mapa auxiliar;
    Mapa *m;//mapa proveniente del escenario 
    Aliadas **ali;//array de unidades aliadas proveniente del escenario
    Enemigo **enem;//array de unidades enemigas proveniete del escenario
    Cofre **cof;
    Objetos **objeto;
    Armas **arma;
    int *index;//indice de la unidad aliada seleccionada
    
    XMLDocument doc;
    XMLElement *map;
    XMLElement *escena;
    XMLElement *texto;
};


#endif	/* ESTADOCONVERSACION_H */

