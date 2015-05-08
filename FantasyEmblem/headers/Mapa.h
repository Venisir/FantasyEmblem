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
#include "../headers/Aliadas.h"
#include "../headers/Enemigo.h"
class Mapa {
public:
    Mapa();
    virtual ~Mapa();
    void Draw();
    void setSpriteColor(int color1, int color2, int i, int j);
    void defaultSpriteColor(int i, int j);
    bool getColision(int i, int j);
    int getAtributo(int i, int j);
    Enemigo** getEnemigos();
    int getNumEnemigos();
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
    
    int ***_tilemap;
    sf::Sprite ****_tilemapSprite;
    sf::Texture* textura;
};

#endif	/* MAPA_H */

