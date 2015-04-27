/* 
 * File:   Mapa.cpp
 * Author: Beatriz
 * 
 * Created on 15 de abril de 2015, 9:41
 */

#include "../headers/Escenario.h"
#include "../headers/MenuPrincipal.h"
#include "../headers/EstadoPause.h"
#include "../headers/Estado.h"
#include "../headers/Juego.h"
#include "../headers/Mapa.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string>
#include "../tinyxml2.h"

using namespace tinyxml2;
using namespace std;
using namespace sf;

Mapa::Mapa() {
   
    _width = 0;
    _height = 0;
    _tileWidth = 0;
    _tileHeight = 0;
    _imageWidth = 0;
    _imageHeight = 0;
    _numLayers = 0;
    _cont = 0;
    
    //Cargamos el XML y creamos la ventana
    XMLDocument doc;
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
    
    XMLElement *data;
    
    //Reservando memoria para la variable tilemap, que contendra los gid de las capas
    _tilemap = new int**[_numLayers];
    
    for(int i=0; i<_numLayers; i++){
        _tilemap[i] = new int*[_height];
    }
    
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            _tilemap[l][y]=new int[_width];
        }
    }
    
    //Reservando memoria para los sprite (variable tilemapSprite)
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
        //Hacemos que data apunte al primer tile de la capa actual
        data = layer2->FirstChildElement("data")->FirstChildElement("tile");
        //Hacemos un bucle para coger los tile de la capa en la que estamos
        for(int y=0; y<_height;y++){
            for(int x=0; x<_width; x++){
                //Del tile cogemos el gid (id del sprite) y lo ponemos en nuestra matriz 3D tilemap, que almacena todos
                data->QueryIntAttribute("gid", &_tilemap[l][y][x]);
                //Avanzo al siguiente tile
                data=data->NextSiblingElement("tile");
            }
        }
        //Pasamos a la siguiente capa
        layer2 = layer2->NextSiblingElement("layer");
    }
    
    //Asignamos a un string la ruta mas el filename
    string s1 = string(filename);
    string s = "niveles/"+s1;
    
    //Cargamos las texturas
    //Texture textura;
    textura = new Texture();
    
    if (!textura->loadFromFile(s))
    {
        std::cerr << "Error cargando la textura" << endl;
        exit(0);
    }
    
    //Separamos la textura que hemos cargado para obtener las distintas imagenes
    sf::Sprite **_tilesetSprite;
    _tilesetSprite = new sf::Sprite*[(_imageWidth/_tileWidth)*(_imageHeight/_tileHeight)];
    int fila = 0;
    int columna = 0;
    for(int l=0; l<(_imageWidth/_tileWidth)*(_imageHeight/_tileHeight); l++){
        _tilesetSprite[l] = new sf::Sprite;
        if(columna == _imageWidth/_tileWidth){
            columna = 0;
            fila++;
        }
        _tilesetSprite[l]->setTextureRect(sf::IntRect(columna*16,fila*16,16,16));
        columna++;
    }
    
    //Cargamos en la variabe _tilemapSprite las texturas de las capas
    for(int l=0; l<_numLayers;l++){
        for(int y=0; y<_height;y++){
            for(int x=0; x<_width; x++){
                int gid = _tilemap[l][y][x]-1;
                //std::cerr <<gid<< endl;
                //CONDICION PARA PONER NPC's CON CAPA
                //if(l==6){
                    //CREAR AQUI NPC's
                    //std::cerr <<"SOY UN NPC Y AQUI EN EL BOSQUE SOY MUY FELIZ"<< endl;
                /*}else*/if(l==2){
                    //CREAR AQUI COFRES
                    std::cerr <<"SOY UN COFREEEE Y AQUI EN EL BOSQUE SOY MUY FELIZ"<< endl;
                }else{
                    if(gid>=0){
                        //Si fuera menor que 0 no creo sprite...
                        _tilemapSprite[l][y][x] = new sf::Sprite(*textura, _tilesetSprite[gid]->getTextureRect());//sf::IntRect(0, 0, 16, 16));
                        _tilemapSprite[l][y][x]->setPosition(x*_tileWidth,y*_tileHeight);
                    }else{
                        _tilemapSprite[l][y][x] = NULL;
                    }
                }
            }
        }
    }
                //std::cerr <<s<< endl;
    
    Draw();
}

Mapa::~Mapa() {
}

void Mapa::Draw() {
    
    //Esto va entre el window.clear y el window.display
    
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            for(int x=0; x<_width; x++){
                if(_tilemapSprite[l][y][x] != NULL){
                    Juego::Instance()->getVentana()->draw(*(_tilemapSprite[l][y][x]));
                }
            }
        }
    }
}

void Mapa::setSpriteColor(int color1, int color2, int i, int j){
    if(j<480 && j>=0 && i>=0 && i<320){
        _tilemapSprite[3][i/16][j/16] = new Sprite(*textura, IntRect(144, 0, 16, 16));
        _tilemapSprite[3][i/16][j/16]->setPosition(j,i);
        _tilemapSprite[3][i/16][j/16]->setColor(Color(255, 255, 255, 128));
    }
}

void Mapa::defaultSpriteColor(int i, int j){
    if(j<480 && j>=0 && i>=0 && i<320){
        _tilemapSprite[3][i/16][j/16] = NULL;
    }
}


bool Mapa::getColision(int i, int j){
    if(_tilemap[4][i/16][j/16]!=0 || _tilemap[5][i/16][j/16]!=0){
        return true;
    }else{
        return false;
    }
}

/*--------------------------------GET ATRIBUTO----------------------------------
 Devuelve:
 * 0 no hay atributo
 * 1 hay bosque
 * 2 hay montaña
 * 3 hay un fuerte
 * 4 hay un trono
 */
int Mapa::getAtributo(int i, int j){
    if(_tilemap[1][i/16][j/16]==12 || _tilemap[1][i/16][j/16]==13 || _tilemap[1][i/16][j/16]==14){
        return 1;
    }else if(_tilemap[1][i/16][j/16]==23){
        return 2;
    }else if(_tilemap[1][i/16][j/16]==37){
        return 3;
    }else if(_tilemap[1][i/16][j/16]==72){
        return 4;
    }else{
        return 0;
    }
}

