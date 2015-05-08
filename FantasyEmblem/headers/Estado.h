/* 
 * File:   Estado.h
 * Author: Alberto
 *
 * Created on 23 de abril de 2015, 11:18
 */

#ifndef ESTADO_H
#define	ESTADO_H

class Estado {
public:
    /*
    Estado();
    virtual ~Estado();
    */
    void init();
    void render();
    void update();

private:
    virtual void init_State()=0;
    virtual void render_State()=0;
    virtual void update_State()=0;
};

#endif	/* ESTADO_H */

