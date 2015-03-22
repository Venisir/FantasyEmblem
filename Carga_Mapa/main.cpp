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
 
    XMLDocument doc;
    RenderWindow window(sf::VideoMode(480,320), "Fantasy Emblem");
    doc.LoadFile("niveles/mapa1.tmx");
    
    //Tamanyo de mapa
    XMLElement* map = doc.FirstChildElement("map");

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
    
    //Cargando GID multiples capas 
    
    XMLElement **data;
    data = new XMLElement*[_numLayers];
    data[0] = map->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    
    /*
    int _AUX = 0;
    
    data[0]->QueryIntAttribute("gid", &_AUX );
    
    std::cerr <<_AUX;
    */
     
    //XMLElement *data[0] = map->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    
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
    
    
    
    sf::Sprite ****_tilemapSprite;
    _tilemapSprite = new sf::Sprite***[_numLayers];
    for(int l=0; l<_numLayers; l++){
        _tilemapSprite[l] = new sf::Sprite**[_height];
    }
    
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height;y++){
            _tilemapSprite[l][y] = new sf::Sprite*[_width];
            for(int x=0; x<_width; x++){
                //...
                _tilemapSprite[l][y][x] = new sf::Sprite();
            }
        }
    }
    
    XMLElement *layer2 = map->FirstChildElement("layer");
     
    for(int l=0; l<_numLayers;l++){
        
        data[l] = layer2->FirstChildElement("data")->FirstChildElement("tile");
        
        for(int y=0; y<_height;y++){
            for(int x=0; x<_width; x++){
                
                //std::cerr <<"   l: " << l << "   y: " << y <<"   x: " << x <<endl;
                data[l]->QueryIntAttribute("gid", &_tilemap[l][y][x]);
                //Avanzo al siguiente tag
                data[l]=data[l]->NextSiblingElement("tile");
            }
        }
        
        layer2 = layer2->NextSiblingElement("layer");
    }
    
    Texture textura;
    
    /*
    string estrin = string(filename);
    string cadena = strcat("niveles/",estrin);
    
    std::cerr << cadena <<endl;
    std::cerr << filename <<endl;
    */
    //string s = strcat("niveles/Tilev1.png");
    string s = "niveles/Tilev1.png";
    
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
                
                //if(gid>=_tsw*_tsh){
                //    std::cerr << "Error, git at (l,x,y)=("<<endl; 
                //
                //}else 
                    
                    if(gid>0){
                    //Si fuera 0 no creo sprite...
                    //_tilemapSprite[l][y][x] = new sf::Sprite(textura, sf::IntRect(0, 0, 16, 16));
                    
                    _tilemapSprite[l][y][x] = new sf::Sprite(textura, _tilesetSprite[gid]->getTextureRect());//sf::IntRect(0, 0, 16, 16));
                    
                    
                    _tilemapSprite[l][y][x]->setPosition(x*_tileWidth,y*_tileHeight);
                    //std::cerr << l << y << x <<endl;
                }else{
                    _tilemapSprite[l][y][x] = NULL;
                }
            }
        }
    }

    //std::cerr << filename <<endl;
    
    //_tilemapSprite[2][8][7]->setPosition(100,100);
    
    /*
    //for(int l=0; l<_numLayers;l++){
        for(int y=0;y<_height;y++){
            for(int x=0;x<_width;x++){
                window.draw(*_tilemapSprite[1][y][x]);
            }
        }
    //}
    */
    
    /*
    void Tilemap::setActiveLayer(int layer){
        _activeLayer = layer;
    }
    */
    
    /*
    Sprite sprite;
    Texture textura;
    
    
    if (!textura.loadFromFile("resources/patron.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    
    int matriz[ancho][alto];
    Sprite mapa[ancho][alto];
    
    //preparamos el elemento para el primer tile
    elemento = doc.FirstChildElement("map")->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    
    //se rellena la matriz con los id de los sprites
    for(int i=0;i<ancho;i++)
    {
        for(int j=0;j<alto;j++)
        {
            matriz[i][j]=elemento->IntAttribute("gid");
            elemento=elemento->NextSiblingElement("tile");
        }
    }
    
    //se crea una matriz de sprites
    for(int i=0;i<ancho;i++)
    {
        for(int j=0;j<alto;j++)
        {
            sprite.setTexture(textura);
            sprite.setTextureRect(IntRect(0, 0, 16, 16));
            sprite.setPosition(i*16,j*16);
            mapa[i][j]=sprite;
        }
    }
    
    
    //mostrar el mapa
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
                
                case sf::Event::KeyPressed:
                    
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(evento.key.code) 
                    {
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                        break;
                    }
            }
            
            
        }
        
        
        for(int i=0;i<ancho;i++)
        {
            for(int j=0;j<alto;j++)
            {
                window.draw(mapa[i][j]);
            }
        }
        
       window.display(); 
    }
    
    

    return 0;
     */
    
    
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

