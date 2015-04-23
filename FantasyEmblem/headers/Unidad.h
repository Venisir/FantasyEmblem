/* 
 * File:   Unidad.h
 * Author: Beatriz
 *
 * Created on 15 de abril de 2015, 9:40
 */

#ifndef UNIDAD_H
#define	UNIDAD_H
class Unidad {
public:
    Unidad();
    Unidad(const Unidad& orig);
    virtual ~Unidad();
    //METODOS GET
    int getHP();
    int getFuerza();
    int getMagia();
    int getHab();
    int getVel();
    int getDef();
    int getDefm();
    int getExp();
    //METODOS SET
    int setHP();
    int setFuerza();
    int setMagia();
    int setHab();
    int setVel();
    int setDef();
    int setDefm();
    int setExp();
    
private:
    //Vida de la unidad
    int HP;
    //Fuerza 
    int fuerza;
    //Magia
    int magia;
    //Habilidad
    int hab;
    //Velocidad
    int vel;
    //Defensa
    int def;
    //Defensa magica
    int defm;
    //Nivel
    int lvl;
    //Experiencia
    int exp;
};

#endif	/* UNIDAD_H */

