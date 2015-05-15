/* 
 * File:   Mapa.h
 * Author: Beatriz
 *
 * Created on 15 de abril de 2015, 9:41
 */

#ifndef MAPA_H
#define	MAPA_H
#include <SFML/Graphics.hpp>
#include "../tinyxml2.h"

#include "../headers/Cofre.h"
#include "../headers/Unidad.h"
//#include "../headers/Aliadas.h"
#include "../headers/Enemigo.h"

class Mapa {
public:
    Mapa();
    virtual ~Mapa();
    void Draw();
    void setSpriteColor(int color, int i, int j, int saltaComprobacion);
    void defaultSpriteColor(int i, int j);
    bool getColision(int j, int i);
    bool getPuerta(int j, int i);
    bool getCasillaPintada(int j, int i);
    int getAtributo(int j, int i);
    int getNumEnemigos();
    int getNumCofres();
    bool puedeMoverseAqui(int i, int j);
    void setSpriteColorAtaque(int i, int j);
    void defaultSpriteColorAtaque(int i, int j);
    void quitarPuerta(int i, int j);
    bool getCofre(int i, int j);
    
    Enemigo** getEnemigos();
    Cofre** getCofres();
private:
    //Variables provisoonales (las que no se usen en general hay que quitarlas)
    int _width;
    int _height;
    int _tileWidth;
    int _tileHeight;
    int _imageWidth;
    int _imageHeight;
    int _numLayers;
    int _cont;
    
    int numEnemigos;
    int numCofres;

    int ***_tilemap;
    sf::Sprite ****_tilemapSprite;
    sf::Texture* textura;
};

#endif	/* MAPA_H */

