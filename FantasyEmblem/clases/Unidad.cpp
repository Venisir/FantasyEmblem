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

Unidad::Unidad(const char* name, const char* clas, int atributo[],int nivel, int rang, const char* nombreTextu) {
    nombre = name;
    clase = clas;
    arma_actual = new Armas("Espadon Sangriento", "Espada", 1, 1, 1, 1, 1);
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
    
    string s1 = string(nombreTextu);
    string s = "resources/"+s1;
    
    if (!texturaUnidad->loadFromFile(s))
    {
        std::cerr << "Error cargando la imagen textura de la unidad";
        exit(0);
    }
    
    spriteUnidad->setTexture(*texturaUnidad);
    spriteUnidad->setTextureRect(IntRect(0, 0, 20, 20));
    
    mueve = false;
    //spriteUnidad->setPosition(176,176);
    
    destinoX = 0;
    destinoY = 0;
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
}

void Unidad::moverAbajo(){
    destinoX = spriteUnidad->getPosition().x;
    destinoY = spriteUnidad->getPosition().y+16;
    setMueve(true);
}

void Unidad::moverIzquierda(){
    destinoX = spriteUnidad->getPosition().x-16;
    destinoY = spriteUnidad->getPosition().y;
    setMueve(true);
}

void Unidad::moverDerecha(){
    destinoX = spriteUnidad->getPosition().x+16;
    destinoY = spriteUnidad->getPosition().y;
    setMueve(true);
}

void Unidad::setMueve(bool b) {
    mueve = b;
}

void Unidad::haLlegado() {
    setMueve(false);
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
    PVactual=PV;
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