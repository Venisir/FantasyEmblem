/* 
 * File:   Cofre.h
 * Author: Constanza
 *
 * Created on 24 de abril de 2015, 17:01
 */

#ifndef COFRE_H
#define	COFRE_H

class Cofre {
public:
    Cofre();
    Cofre(const Cofre& orig);
    virtual ~Cofre();    
    
private:
    int x;
    int y;
    bool abierto;
    Armas dropArma;
    Objetos dropObjeto;
};

#endif	/* COFRE_H */

