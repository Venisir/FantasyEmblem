/* 
 * File:   Unidad.cpp
 * Author: Beatriz
 * 
 * Created on 15 de abril de 2015, 9:40
 */

#include "../headers/Unidad.h"
#include "../headers/Juego.h"
#include "../headers/Armas.h"
#include <stdio.h>
#include <string>

using namespace std;

Unidad::Unidad()
{
    
}

Unidad::Unidad(const char* name, const char* clas, int atributo[],int nivel, int rang, const char* nombreTextu, const char* textuBatalla) {
    nombre = name;
    clase = clas;
    arma_actual = new Armas("Espada", "Espada", 1, 1, 1, 1, 1, "espada.png");
    for(int i=0; i<7; i++)
        atributos[i] = atributo[i];
    lvl = nivel;
    rango = rang;
    activo = true;
    PVactual=atributos[0];
    
    valorSprite = 1;
    siguienteSumar = true;
    
    spriteUnidad = new Sprite();
    texturaUnidad = new Texture();
    
    movimientos=new int[0];
    
    string s1 = string(nombreTextu);
    string s = "resources/"+s1;
    
    if (!texturaUnidad->loadFromFile(s))
    {
        std::cerr << "Error cargando la imagen textura de la unidad";
        exit(0);
    }
    
    spriteUnidad->setTexture(*texturaUnidad);
    spriteUnidad->setTextureRect(IntRect(0, 0, 20, 20));
    
    spriteBatalla = new Sprite();
    textBatalla = new Texture();
	    
    string s2 = string(textuBatalla);
    string s3 = "resources/"+s2;

    if (!textBatalla->loadFromFile(s3))
    {
        std::cerr << "Error cargando la imagen textura de la unidad";
        exit(0);
    }

    spriteBatalla->setTexture(*textBatalla);
    spriteBatalla->setTextureRect(IntRect(0,0,248,160));

    mueve = false;
    //spriteUnidad->setPosition(176,176);
    
    destinoX = 0;
    destinoY = 0;
    direccionDestino = 0;
    
    haJugado = false;
}

Unidad::~Unidad() {
    
}

int Unidad::getPosicionCeldaX() {
    return spriteUnidad->getPosition().x/16;
}

int Unidad::getPosicionCeldaY() {
    return spriteUnidad->getPosition().y/16;
}

int Unidad::getPosicionSpriteX() {
    return spriteUnidad->getPosition().x;
}

int Unidad::getPosicionSpriteY() {
    return spriteUnidad->getPosition().y;
}

void Unidad::setPosition(int i, int j) {
    spriteUnidad->setPosition(i,j);
}

void Unidad::moverArriba(){
    destinoX = spriteUnidad->getPosition().x;
    destinoY = spriteUnidad->getPosition().y-16;
    setMueve(true);
    direccionDestino = 2;
}

void Unidad::moverAbajo(){
    destinoX = spriteUnidad->getPosition().x;
    destinoY = spriteUnidad->getPosition().y+16;
    setMueve(true);
    direccionDestino = -2;
}

void Unidad::moverIzquierda(){
    destinoX = spriteUnidad->getPosition().x-16;
    destinoY = spriteUnidad->getPosition().y;
    setMueve(true);
    direccionDestino = -1;
}

void Unidad::moverDerecha(){
    destinoX = spriteUnidad->getPosition().x+16;
    destinoY = spriteUnidad->getPosition().y;
    setMueve(true);
    direccionDestino = 1;
}

void Unidad::setMueve(bool b) {
    mueve = b;
}

void Unidad::haLlegado() {
    setMueve(false);
}

bool Unidad::verSiHaLlegado() {
    
    bool ret;
    ret = false;
    
    switch(direccionDestino){
        //derecha
        case 1:
            if(this->getSprite().getPosition().x >= this->getDestinoX() && this->getSprite().getPosition().y == this->getDestinoY()){
                ret = true;
                this->setPosition(getDestinoX(), getDestinoY());
            }
            break;
        //arriba
        case 2:
            if(this->getSprite().getPosition().x == this->getDestinoX() && this->getSprite().getPosition().y <= this->getDestinoY()){
                ret = true;
                this->setPosition(getDestinoX(), getDestinoY());
            }
            break;
        //izquierda
        case -1:
            if(this->getSprite().getPosition().x <= this->getDestinoX() && this->getSprite().getPosition().y == this->getDestinoY()){
                ret = true;
                this->setPosition(getDestinoX(), getDestinoY());
            }
            break;
        //abajo
        case -2:
            if(this->getSprite().getPosition().x == this->getDestinoX() && this->getSprite().getPosition().y >= this->getDestinoY()){
                ret = true;
                this->setPosition(getDestinoX(), getDestinoY());
            }
            break;       
    }
    
    return ret;
}

bool Unidad::getMueve() {
    return mueve;
}

int Unidad::getDestinoX() {
    return destinoX;
}

int Unidad::getDestinoY() {
    return destinoY;
}

void Unidad::cambiaSpriteQuieto() {
    if(valorSprite == 0){
        siguienteSumar = true;
        valorSprite = 2;
    }else{
        if(valorSprite == 4){
            siguienteSumar = false;
            valorSprite = 2;
        }else{
            if(siguienteSumar == true){
                valorSprite = 4;
                siguienteSumar = false;
            }else{
                valorSprite = 0;
                siguienteSumar = true;
            }
        }
    }
    spriteUnidad->setTextureRect(sf::IntRect(valorSprite*16, 0, 16, 16));
}
    
void Unidad::cambiaSprite(int a, int b, int c, int d) {
    spriteUnidad->setTextureRect(sf::IntRect(a, b, c, d));
}

void Unidad::verStats() {
    
    //spriteUnidad->setColor(sf::Color(0, 255, 0, 128));
    
    std::cerr << "HAS SELECCIONADO A: " <<endl;
    std::cerr << nombre << ", que es un " << clase << " de nivel " << lvl << "." <<endl;
    std::cerr << "Tiene equipada un " << arma_actual->getNombre() << ", que es de tipo " << arma_actual->getTipo() << "." <<endl;
    
    std::cerr << "Vida: " << atributos[0] <<endl;
    std::cerr << "Fuerza: " << atributos[1] <<endl;
    std::cerr << "Magia: " << atributos[2] <<endl;
    std::cerr << "Habilidad: " << atributos[3] <<endl;
    std::cerr << "Velocidad: " << atributos[4] <<endl;
    std::cerr << "Defensa: " << atributos[5] <<endl;
    std::cerr << "Defensa magica: " << atributos[6] <<endl;
    std::cerr << "Nivel: " << lvl <<endl;
    std::cerr << "Rango: " << rango <<endl;
}

void Unidad::Draw() {
    Juego::Instance()->getVentana()->draw(*spriteUnidad);
}

//------------------------------METODOS SET-------------------------------------
void Unidad::setHP(int hp){
    atributos[0]=hp;
}
void Unidad::setFuerza(int f){
    atributos[1]=f;
}
void Unidad::setMagia(int m){
    atributos[2]=m;
}
void Unidad::setHab(int h){
    atributos[3]=h;
}
void Unidad::setVel(int v){
    atributos[4]=v;
}
void Unidad::setDef(int d){
    atributos[5]=d;
}
void Unidad::setDefm(int dm){
    atributos[6]=dm;
}

//------------------------------METODOS GET-------------------------------------
int Unidad::getHP(){
    return atributos[0];
}
int Unidad::getFuerza(){
    return atributos[1];
}
int Unidad::getMagia(){
    return atributos[2];
}
int Unidad::getHab(){
    return atributos[3];
}
int Unidad::getVel(){
    return atributos[4];
}
int Unidad::getDef(){
    return atributos[5];
}
int Unidad::getDefm(){
    return atributos[6];
}
int Unidad::getRango(){
    return rango;
}
const char* Unidad::getNombre(){
    return nombre;
}
int Unidad::getLvl(){
    return lvl;
}
const char* Unidad::getClase(){
    return clase;
}
Sprite Unidad::getSprite()
{
    return *spriteUnidad;
}
 
Armas* Unidad::getArma(){
    return arma_actual;
}

int Unidad::getPV(){
    return PVactual;
}

void Unidad::setPV(int PV){
    PVactual=PVactual-PV;
}

int Unidad::danyoPropio(Unidad* uni){
    int aux=0;
    aux=this->getFuerza()+(arma_actual->getPoder()+bonoArmaDanyo(uni));
    return aux;
}
 
int Unidad::bonoArmaDanyo(Unidad* uni){
    int bono=0;
    if(strcmp(arma_actual->getTipo(),"espada")== 0){
        if(strcmp(uni->getArma()->getTipo(),"lanza")== 0){
            bono=-1;
        }else if(strcmp(uni->getArma()->getTipo(),"hacha")== 0){
            bono=1;
        }else if(strcmp(uni->getArma()->getTipo(),"espada")== 0){
            bono=0;
        }
    }else if(strcmp(arma_actual->getTipo(),"lanza")== 0){
        if(strcmp(uni->getArma()->getTipo(),"lanza")== 0){
            bono=0;
        }else if(strcmp(uni->getArma()->getTipo(),"hacha")== 0){
            bono=-1;
        }else if(strcmp(uni->getArma()->getTipo(),"espada")== 0){
            bono=1;
        }
    }else if(strcmp(arma_actual->getTipo(),"hacha")== 0){
        if(strcmp(uni->getArma()->getTipo(),"lanza")== 0){
            bono=1;
        }else if(strcmp(uni->getArma()->getTipo(),"hacha")== 0){
            bono=0;
        }else if(strcmp(uni->getArma()->getTipo(),"espada")== 0){
            bono=-1;
        }
    }
    return bono;
}

int Unidad::bonoArmaGolpe(Unidad* uni){
     int bonoGol=0;
    if(strcmp(arma_actual->getTipo(),"espada")== 0){
        if(strcmp(uni->getArma()->getTipo(),"lanza")== 0){
            bonoGol=-15;
        }else if(strcmp(uni->getArma()->getTipo(),"hacha")== 0){
            bonoGol=15;
        }else if(strcmp(uni->getArma()->getTipo(),"espada")== 0){
            bonoGol=0;
        }
    }else if(strcmp(arma_actual->getTipo(),"lanza")== 0){
        if(strcmp(uni->getArma()->getTipo(),"lanza")== 0){
            bonoGol=0;
        }else if(strcmp(uni->getArma()->getTipo(),"hacha")== 0){
            bonoGol=-15;
        }else if(strcmp(uni->getArma()->getTipo(),"espada")== 0){
            bonoGol=15;
        }
    }else if(strcmp(arma_actual->getTipo(),"hacha")== 0){
        if(strcmp(uni->getArma()->getTipo(),"lanza")== 0){
            bonoGol=15;
        }else if(strcmp(uni->getArma()->getTipo(),"hacha")== 0){
            bonoGol=0;
        }else if(strcmp(uni->getArma()->getTipo(),"espada")== 0){
            bonoGol=-15;
        }
    }
    return bonoGol;
}

int Unidad::TotalDanyo(Unidad* uni){
    int aux=0;
    aux=danyoPropio(uni)-uni->getDef();
    return aux;
}

int Unidad::PosiGolpear(Unidad* uni){
    int golpe=0;
    golpe=(getHab()*2)+getArma()->getGolpe()+bonoArmaGolpe(uni);
    return golpe;
}

int Unidad::PosiGolpearTotal(Unidad* uni){
    int golTotal=0;
    golTotal=PosiGolpear(uni)-uni->Evadir();
    return golTotal;
}
int Unidad::VelocidadAtaque(){
    int velo=0;
    velo=getVel()-getArma()->getPeso();
    return velo;
}

int Unidad::Evadir(){
    int evasion=0;
    evasion=(VelocidadAtaque()*2);
    return evasion;
}

int Unidad::GolpesDoble(Unidad* uni){
    int golpes=1;
    if((VelocidadAtaque()-uni->VelocidadAtaque())>=4){
        golpes=2;
    }else{
        golpes=1;
    }
    
    return golpes;
}

void Unidad::Atacar(Unidad* uni){
    int aux, aux2, aux3;
    
    if(GolpesDoble(uni)==1){
        aux= rand()%(101-1);
        if(aux<=PosiGolpearTotal(uni)){
            aux2=uni->getPV()-TotalDanyo(uni);
            uni->setPV(aux2);
            aux=rand()%(101-1);
            if(aux<=uni->PosiGolpearTotal(this)){
                aux3=this->getPV()- uni->TotalDanyo(this);
                this->setPV(aux3);
                if(uni->GolpesDoble(this)==2){
                    aux=rand()%(101-1);
                    if(aux<=uni->PosiGolpearTotal(this)){
                    aux3=this->getPV()-uni->TotalDanyo(this);
                    this->setPV(aux3);
                    }
                }
            }
        }
    }else if(GolpesDoble(uni)==2){
        aux= rand()%(101-1);
        if(aux<=PosiGolpearTotal(uni)){
            aux2=uni->getPV()-TotalDanyo(uni);
            uni->setPV(aux2);
            aux=rand()%(101-1);
            if(aux<=uni->PosiGolpearTotal(this)){
                aux3=this->getPV()-uni->TotalDanyo(this);
                this->setPV(aux3);
                aux=rand()%(101-1);
                if(aux<=PosiGolpearTotal(uni)){
                    aux2=uni->getPV()-TotalDanyo(uni);
                    uni->setPV(aux2);
                    if(uni->GolpesDoble(this)==2){
                        aux=rand()%(101-1);
                        if(aux<=uni->PosiGolpearTotal(this)){
                            aux3=this->getPV()-uni->TotalDanyo(this);
                            this->setPV(aux3);
                        }
                    }
                }
            }
        }
    }
}


void Unidad::recorridoA(int destinox, int destinoy) 
{
    movs.clear();
    
    vector<Celda*> abierta;
    vector<Celda*> cerrada;
    sf::Vector2i posaux= sf::Vector2i(getPosicionSpriteX(),getPosicionSpriteY());
    Celda* n;
    Celda* ady;
    
    int coste=1;//coste de moverse en cualquiera de las 4 direcciones, equivale a g
    int manhatan,f,g;
    int menorf;
    int nodomenor=0;
    int adyacentes=0;//numero de celdas adyacentes
    vector<Celda*>::iterator iter;
    
    Celda* celdaInicio=new Celda(posaux,0,0,0); //la celda inicio no tiene padre
    
    /*Ponemos la celda de inicio en la abierta*/
    abierta.push_back(celdaInicio);
    
    while(abierta.empty()!=true && movs.empty()==true)
    {
        menorf=100000000000000000000;
        /*obtenemos el nodo con menor f(n) de la lista abierta*/        
        cerr << endl;
        
        for(int i=0;i<abierta.size();i++)
        {
            g=abierta.at(i)->getG();
            manhatan=abs(abierta.at(i)->getCoordenadas().x-destinox)+abs(abierta.at(i)->getCoordenadas().y-destinoy);
            f=g+manhatan;
            if(f<menorf)
            {
                menorf=f;
                n=abierta.at(i);
                cerr << "x" << n->getCoordenadas().x << endl;
                cerr << "y" << n->getCoordenadas().y << endl;
                cerr << endl;
                nodomenor=i;
            }
        }
        
        cerr << endl;
        
        iter=abierta.begin()+nodomenor;
        abierta.erase(iter);
        cerrada.push_back(n);
        
        //si n es la celda correspondiente al destino
        if(n->getCoordenadas().x == destinox && n->getCoordenadas().y == destinoy)
        {
            movs=cerrada;
        }
        else if(movs.empty()==true)
        {
            /*obtenemos los adyacentes*/
            
            //arriba
            if(Escenario::Instance()->getMapa()->getCasillaPintada(n->getCoordenadas().x,n->getCoordenadas().y-16)==true)
            {
                posaux= sf::Vector2i(n->getCoordenadas().x,n->getCoordenadas().y-16);
                g=n->getG()+coste;
                manhatan=abs(posaux.x-destinox)+abs(posaux.y-destinoy);
                f=g+manhatan;
                ady=new Celda(posaux,g,f,manhatan,n);
                abierta.push_back(ady);
                adyacentes++;
            }
            //abajo
            if(Escenario::Instance()->getMapa()->getCasillaPintada(n->getCoordenadas().x,n->getCoordenadas().y+16)==true)
            {
                posaux= sf::Vector2i(n->getCoordenadas().x,n->getCoordenadas().y+16);
                g=n->getG()+coste;
                manhatan=abs(posaux.x-destinox)+abs(posaux.y-destinoy);
                f=g+manhatan;
                ady=new Celda(posaux,g,f,manhatan,n);
                abierta.push_back(ady);
                adyacentes++;
            }
                       
            //derecha
            if(Escenario::Instance()->getMapa()->getCasillaPintada(n->getCoordenadas().x+16,n->getCoordenadas().y)==true)
            {
                posaux= sf::Vector2i(n->getCoordenadas().x+16,n->getCoordenadas().y);
                g=n->getG()+coste;
                manhatan=abs(posaux.x-destinox)+abs(posaux.y-destinoy);
                f=g+manhatan;
                ady=new Celda(posaux,g,f,manhatan,n);
                abierta.push_back(ady);
                adyacentes++;
            }
            
            //izquierda
            if(Escenario::Instance()->getMapa()->getCasillaPintada(n->getCoordenadas().x-16,n->getCoordenadas().y)==true)
            {
                posaux= sf::Vector2i(n->getCoordenadas().x-16,n->getCoordenadas().y);
                g=n->getG()+coste;
                manhatan=abs(posaux.x-destinox)+abs(posaux.y-destinoy);
                f=g+manhatan;
                ady=new Celda(posaux,g,f,manhatan,n);
                abierta.push_back(ady);
                adyacentes++;
                cerr << abierta.back()->getCoordenadas().x << endl;
                cerr << abierta.back()->getCoordenadas().y << endl;
            }
                     
            
            /*Para cada adyacente a n*/
            //for(int i=0;i<abierta.size()-adyacentes;i++)
            //{
                //comprobamos cual de las celdas adyacentes esta en la lista cerrada ( y borrarla asi de la )
                /*for(int j=0;j<cerrada.size();j++)
                {
                    if(cerrada.at(j)->getCoordenadas().x==abierta.at(i)->getCoordenadas().x && cerrada.at(j)->getCoordenadas().y==abierta.at(i)->getCoordenadas().y){
                        iter = abierta.begin()+i;
                        abierta.erase(iter);
                        break;
                    }
                }*/
                
                /*compruebo si alguna de las adyacentes esta en la lista abierta, en caso de estarlo compruebo cual de las g es mejor y elmino la peor de la lista abierta*/
                /*for(int w=0;w<abierta.size();w++)
                {
                    if(abierta.at(w)->getCoordenadas().x==abierta.at(i)->getCoordenadas().x && abierta.at(w)->getCoordenadas().y==abierta.at(i)->getCoordenadas().y){
                        if(w!=i){
                            if(abierta.at(w)->getG()<abierta.at(i)->getG()){
                                iter = abierta.begin()+i;
                                abierta.erase(iter);
                                cerr << "6sdadadadfgjhg888" << endl;
                            }
                            else{
                                iter = abierta.begin()+w;
                                abierta.erase(iter);
                                cerr << "6sdadadadfgjhg" << endl;
                            }
                            break;
                        }
                    }
                }*/
            //}  
        }
        //delete ady;
    }
    MovstoInt();
    
}

void Unidad::muestraMovs(){

    for(int i=0; i<movs.size(); i++){
        
        cerr << "size: " << movs.size() << endl;
        cerr << "i: " << i << endl;
        cerr << "x: " << movs.at(i)->getCoordenadas().x << endl;
        cerr << "y: " << movs.at(i)->getCoordenadas().y << endl;
        
        cerr << endl;
    }
        
        //movs.clear();
}

Sprite Unidad::getSpriteBatalla(){
    return *spriteBatalla;
}

bool Unidad::getHaJugado(){
    return haJugado;
}

void Unidad::setHaJugado(bool b){
    
    cerr << "He entrado en setHaJugado" << endl;
    haJugado = b;
    if(haJugado == true){
        spriteUnidad->setColor(sf::Color(128,128,128));
    }else{
        spriteUnidad->setColor(sf::Color(255,255,255));
    }
}

int* Unidad::getMovimientos() {
    return movimientos;
}

void Unidad::MovstoInt() {
    
    movimientos=new int [movs.size()-1];//-1 porque movs contiene la posicion de inicio
    
    for(int i=0;i<movs.size()-1;i++)
    {
        cerr << "He entrado, y decido que la direccion es ";
        
        //priemro compruebo las posibles direcciones del eje x
        if(movs.at(i+1)->getCoordenadas().x == movs.at(i)->getCoordenadas().x+16)
        {
            //Escenario::Instance()->getMapa()->setSpriteColorAtaque(movs.at(i+1)->getCoordenadas().x+16,movs.at(i+1)->getCoordenadas().y);
            movimientos[i]=1;//derecha
            cerr << "derecha." << endl;
        }
        else if(movs.at(i+1)->getCoordenadas().x == movs.at(i)->getCoordenadas().x-16)
        {
            //Escenario::Instance()->getMapa()->setSpriteColorAtaque(movs.at(i+1)->getCoordenadas().x-16,movs.at(i+1)->getCoordenadas().y);
            movimientos[i]=-1;//izquierda
            cerr << "izquierda." << endl;
        }
        //le toca el turno al eje y
        else if(movs.at(i+1)->getCoordenadas().y == movs.at(i)->getCoordenadas().y+16)
        {
            //Escenario::Instance()->getMapa()->setSpriteColorAtaque(movs.at(i+1)->getCoordenadas().x,movs.at(i+1)->getCoordenadas().y+16);
            movimientos[i]=-2;//abajo
            cerr << "abajo." << endl;
        }
        else if(movs.at(i+1)->getCoordenadas().y == movs.at(i)->getCoordenadas().y-16)
        {
            //Escenario::Instance()->getMapa()->setSpriteColorAtaque(movs.at(i+1)->getCoordenadas().x,movs.at(i+1)->getCoordenadas().y-16);
            movimientos[i]=2;//arriba
            cerr << "arriba." << endl;
        }
    }
    
    /*
    for(int i=0; i<sizeof(movimientos)/sizeof(int); i++){
        
        //cerr << "size: " << movimientos.size() << endl;
        //cerr << "i: " << i << endl;
        cerr << "x: " << movimientos[i] << " "<< endl;
        //cerr << "y: " << movimientos.at(i)->getCoordenadas().y << endl;
        
    }
    
    cerr << endl;
     */
}