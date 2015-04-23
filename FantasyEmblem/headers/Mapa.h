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
    Mapa(const Mapa& orig);
    virtual ~Mapa();
    void Draw();
private:
    //Variables provisoonales (las que no se usen en general hay que quitarlas)
    int _width = 0;
    int _height = 0;
    int _tileWidth = 0;
    int _tileHeight = 0;
    int _imageWidth = 0;
    int _imageHeight = 0;
    int _numLayers = 0;
    int _cont=0;
    int ***_tilemap;
    sf::Sprite ****_tilemapSprite;
};

#endif	/* MAPA_H */

