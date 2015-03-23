#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string>
#include "tinyxml2.h"

using namespace tinyxml2;
using namespace std;
using namespace sf;

int main()
{
    int _width = 0;
    int _height = 0;
    int _tileWidth = 0;
    int _tileHeight = 0;
    int _imageWidth = 0;
    int _imageHeight = 0;
    int _numLayers = 0;
 
    //Cargamos el XML y creamos la ventana
    XMLDocument doc;
    RenderWindow window(sf::VideoMode(480,320), "Fantasy Emblem");
    doc.LoadFile("niveles/mapa1.tmx");
    XMLElement* map = doc.FirstChildElement("map");

    //Cogemos los tamanyos de mapa y de los tile
    map->QueryIntAttribute( "width", &_width );
    map->QueryIntAttribute( "height", &_height );
    map->QueryIntAttribute( "tilewidth", &_tileWidth );
    map->QueryIntAttribute( "tileheight", &_tileHeight );
    
    //Imagen del tileset
    XMLElement *img = map->FirstChildElement("tileset")->FirstChildElement("image");
    const char *filename = img->Attribute("source");
    img->QueryIntAttribute( "height", &_imageHeight );
    img->QueryIntAttribute( "width", &_imageWidth );
    
    
    //Cuantas capas tiene mi XML
    XMLElement *layer = map->FirstChildElement("layer");
    while(layer){
        _numLayers++;
        layer = layer->NextSiblingElement("layer");
    }
    
    //Cargando GID multiples capas (reservamos espacio a la variable que contendra los tile de una capa)
    XMLElement **data;
    data = new XMLElement*[_numLayers];
    //data[0] = map->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    
    //Reservando memoria para la variable tilemap, que contendra los gid de las capas
    int ***_tilemap;
    _tilemap = new int**[_numLayers];
    
    for(int i=0; i<_numLayers; i++){
        _tilemap[i] = new int*[_height];
    }
    
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            _tilemap[l][y]=new int[_width];
        }
    }
    
    //Resrvando memoria para los sprite (variable tilemapSprite)
    sf::Sprite ****_tilemapSprite;
    _tilemapSprite = new sf::Sprite***[_numLayers];
    for(int l=0; l<_numLayers; l++){
        _tilemapSprite[l] = new sf::Sprite**[_height];
    }
    
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height;y++){
            _tilemapSprite[l][y] = new sf::Sprite*[_width];
            for(int x=0; x<_width; x++){
                _tilemapSprite[l][y][x] = new sf::Sprite();
            }
        }
    }
    
    //Creamos un XMLElement que contendra la layer en la que estamos mirando actualmente (en este caso la primera)
    XMLElement *layer2 = map->FirstChildElement("layer");
    
    //Bucle que recorre las capas una a una
    for(int l=0; l<_numLayers;l++){
        //Creo que lo de data se puede optimizar y que no es tan necesario
        //Con solo crear una variable y no una matriz sería suficiente
        /****************************************************************/
        
        //Hacemos que la primera posicion de data apunte al primer tile de la capa actual
        data[l] = layer2->FirstChildElement("data")->FirstChildElement("tile");
        //Hacemos un bucle para rellenar la matriz con los tile
        for(int y=0; y<_height;y++){
            for(int x=0; x<_width; x++){
                //Del tile cogemos el gid (id del sprite) y lo ponemos en nuestra matriz 3D tilemap, que almacena todos
                data[l]->QueryIntAttribute("gid", &_tilemap[l][y][x]);
                //Avanzo al siguiente tile
                data[l]=data[l]->NextSiblingElement("tile");
            }
        }
        //Pasamos a la siguiente capa
        layer2 = layer2->NextSiblingElement("layer");
    }
    
    Texture textura;

    string s1 = string(filename);
    string s = "niveles/"+s1;
    std::cerr << s <<endl;
    
    if (!textura.loadFromFile(s))
    {
        std::cerr << "Error cargando la textura" << endl;
        exit(0);
    }
            
    sf::Sprite **_tilesetSprite;
    _tilesetSprite = new sf::Sprite*[(_imageWidth/16)*(_imageHeight/16)];
    
    int fila = 0;
    int columna = 0;
    
    for(int l=0; l<(_imageWidth/16)*(_imageHeight/16); l++){
        
        _tilesetSprite[l] = new sf::Sprite;
        
        if(columna == _imageWidth/16){
            columna = 0;
            fila++;
        }
        
        _tilesetSprite[l]->setTextureRect(sf::IntRect(columna*16,fila*16,16,16));
        
        columna++;
        
        //std::cerr << l <<endl;
    }
    
    
    for(int l=0; l<_numLayers;l++){
        for(int y=0; y<_height;y++){
            for(int x=0; x<_width; x++){
                
                int gid = _tilemap[l][y][x]-1;
                    
                    if(gid>0){
                    //Si fuera 0 no creo sprite...;
                    
                    _tilemapSprite[l][y][x] = new sf::Sprite(textura, _tilesetSprite[gid]->getTextureRect());//sf::IntRect(0, 0, 16, 16));
                    
                    
                    _tilemapSprite[l][y][x]->setPosition(x*_tileWidth,y*_tileHeight);
                    //std::cerr << l << y << x <<endl;
                }else{
                    _tilemapSprite[l][y][x] = NULL;
                }
            }
        }
    }
    
    while(window.isOpen())
    {
        Event evento;
        
        while(window.pollEvent(evento))
        {
            switch(evento.type)
            {
                case Event::Closed:
                    window.close();
                break;
                
            }
        }
        window.clear();
        
        for(int l=0; l<_numLayers; l++){
            for(int y=0; y<_height; y++){
                for(int x=0; x<_width; x++){
                    //OJO, esta dibujando solo la capa de colisiones
                    if(_tilemapSprite[l][y][x] != NULL){
                        window.draw(*(_tilemapSprite[l][y][x]));
                    }
                }
            }
        }
        
        
        window.display();
    }
    return 0;
}

