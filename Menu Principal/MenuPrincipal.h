/* 
 * File:   MenuPrincipal.h
 * Author: Constanza y Andrea
 *
 * Created on 25 de marzo de 2015, 9:57
 */

#ifndef MENUPRINCIPAL_H
#define	MENUPRINCIPAL_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#define MAX_NUM_SPRITE 3
#define MAX_NUM_TEXT 3

class MenuPrincipal {
public:
    MenuPrincipal(float width, float height);
    ~MenuPrincipal();
    
    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    void Exit(sf::RenderWindow &window);
private:
    int selectedItemIndex;
    sf::Texture fondo_menu;
    sf::Texture botn1;
    sf::Texture botn2;
    sf::Texture botn3;
    sf::Texture texturas[MAX_NUM_TEXT];
    sf::Texture textura_fond;
    sf::Sprite menu[MAX_NUM_SPRITE];
    sf::Sprite fondo;
    sf::Time time1;
    sf::SoundBuffer mainmenu;
    sf::SoundBuffer mmcursor;
    sf::SoundBuffer mmselect;
    sf::Sound menusonido;
    sf::Sound cursor;
    sf::Sound select;
};

#endif	/* MENUPRINCIPAL_H */
