/* 
 * File:   Aliadas.h
 * Author: Constanza
 *
 * Created on 24 de abril de 2015, 15:22
 */

#ifndef ALIADAS_H
#define	ALIADAS_H

class Aliadas:public Unidad {
public:
    Aliadas();
    Aliadas(const Aliadas& orig);
    virtual ~Aliadas();    
    equiparArma(Armas arma);
    usarObjeto(Objetos obj);
    subirNivel();
    abrirCofre();
    
private:
    int experiencia;
    Objetos inventarioObjetos[3];
    Armas inventarioArmas[3];
};

#endif	/* ALIADAS_H */

