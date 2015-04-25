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

class Mapa {
public:
    Mapa();
    virtual ~Mapa();
    void Draw();
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
    
    int ***_tilemap;
    sf::Sprite ****_tilemapSprite;
    sf::Texture* textura;
};

#endif	/* MAPA_H */
