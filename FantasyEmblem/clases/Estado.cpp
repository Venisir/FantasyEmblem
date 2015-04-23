/* 
 * File:   Estado.cpp
 * Author: Alberto
 * 
 * Created on 23 de abril de 2015, 11:18
 */

#include "../headers/Estado.h"

/*
Estado::Estado() {

}

Estado::~Estado() {

}
*/

void Estado::render(){
    render_State();
}

void Estado::init(){
    init_State();
}

void Estado::update(){
    update_State();
}
