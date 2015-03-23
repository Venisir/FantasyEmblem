#include <iostream>
using namespace  std;
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{    
    sf::RenderWindow window(sf::VideoMode(480, 320), "Fantasy Emblem");
    window.setSize(sf::Vector2u(960,640));
    sf::Texture fondo_menu;
    sf::Texture botn1;
    sf::Texture dedito;
    sf::Texture estado_per;
    sf::Texture dano;
    sf::Texture objec;
    
    sf::SoundBuffer mainmenu;
    sf::SoundBuffer mmcursor;
    sf::SoundBuffer mmselect;
    
    sf::Clock clock;
    sf::Time time1;
    
    int contador=0;
    
    bool continuar=false;
    bool hasonado1=false;
    bool hasonado2=false;
    bool hasonado3=false;
    bool hasonado4=false;
    bool hasonado5=false;
    
        if (!mainmenu.loadFromFile("recursos/menu.wav")){
            std::cerr << "Error al cargar el archivo de audio";
        }
    
        if (!mmcursor.loadFromFile("recursos/MainMenu_Cursor.wav")){
            std::cerr << "Error al cargar el archivo de audio";
        }
        
        if (!mmselect.loadFromFile("recursos/MainMenu_Select.wav")){
            std::cerr << "Error al cargar el archivo de audio";
        }
    
        if (!fondo_menu.loadFromFile("recursos/patron.png"))
        {
                std::cerr << "Error cargando la imagen patron.png";
                exit(0);
        }
        
        if (!botn1.loadFromFile("recursos/menu.png"))
        {
                std::cerr << "Error cargando la imagen boton1.png";
                exit(0);
        }
        

        if (!dedito.loadFromFile("recursos/dedo.png"))
        {
                std::cerr << "Error cargando la imagen dedo.png";
                exit(0);
        }
         if (!estado_per.loadFromFile("recursos/estado.png"))
        {
                std::cerr << "Error cargando la imagen estado.png";
                exit(0);
        }
    
         if (!dano.loadFromFile("recursos/dano.png"))
        {
                std::cerr << "Error cargando la imagen dano.png";
                exit(0);
        }
        if (!objec.loadFromFile("recursos/objeto.png"))
        {
                std::cerr << "Error cargando la imagen objeto.png";
                exit(0);
        }
        //Creamos el sprite
        sf::Sprite fondo(fondo_menu);
        sf::Sprite boton1(botn1);
        sf::Sprite dedo(dedito);
        sf::Sprite estado(estado_per);
        sf::Sprite danyo(dano);
        sf::Sprite objeto(objec);
        
        //Poner coordenadas
        boton1.setOrigin(420/2,280/2);
        dedo.setOrigin(420/2,280/2);
        danyo.setOrigin(420/2,280/2);
        objeto.setOrigin(420/2,280/2);
        estado.setScale(0,0);
        danyo.setScale(0,0);
        boton1.setScale(0,0);
        dedo.setScale(0,0);
        objeto.setScale(0,0);
        
        boton1.setPosition(225,250);
        dedo.setPosition(215,260);
        danyo.setPosition(480,175);
        objeto.setPosition(305,226);
       // Creamos un sonido
	sf::Sound menusonido;
	// Le asignamos el buffer cargado
	menusonido.setBuffer(mainmenu);
	// establecemos el volumen a 80
	menusonido.setVolume(20);

        menusonido.play();
        
        sf::Sound cursor;
        cursor.setBuffer(mmcursor);
        cursor.setVolume(100);

	sf::Sound select;
        select.setBuffer(mmselect);
        select.setVolume(100);
        
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if ((event.type == sf::Event::Closed)){
                    window.close();
                }
                
              
                if(event.type == sf::Event::KeyPressed){
                    switch(event.key.code){
                        case sf::Keyboard::A:
                            boton1.setScale(1,1);
                            dedo.setScale(1,1);
                        break;  
                        case sf::Keyboard::Down:
                            if(contador==0){
                                
                                contador++;
                                //cout<<contador<<endl;
                                hasonado2=false;
                                hasonado3=false;
                                hasonado4=false;
                                hasonado5=false;
                                if(hasonado1==false){
                                    cursor.play();
                                    hasonado1=true;
                                }
                                
                            }else if(contador==1){
                                dedo.setPosition(215,280);
                                contador++;
                                //cout<<contador<<endl;
                                continuar=true;
                                hasonado1=false;
                                hasonado3=false;
                                hasonado4=false;
                                hasonado5=false;
                                if(hasonado2==false){
                                    cursor.play();
                                    hasonado2=true;
                                }
                            }else if(contador==2){
                                dedo.setPosition(215,300);
                                contador++;
                                //cout<<contador<<endl;
                                hasonado1=false;
                                hasonado2=false;
                                hasonado4=false;
                                hasonado5=false;
                                if(hasonado3==false){
                                    cursor.play();
                                    hasonado3=true;
                                }
                            }else if(contador==3){
                                dedo.setPosition(215,320);
                                contador++;
                                //cout<<contador<<endl;
                                hasonado1=false;
                                hasonado2=false;
                                hasonado3=false;
                                hasonado5=false;
                                if(hasonado4==false){
                                    cursor.play();
                                    hasonado4=true;
                                }
                            }else if(contador==4){
                                dedo.setPosition(215,340);
                                contador++;
                                //cout<<contador<<endl;
                                hasonado1=false;
                                hasonado2=false;
                                hasonado4=false;
                                hasonado3=false;
                                if(hasonado5==false){
                                    cursor.play();
                                    hasonado5=true;
                                }
                            }
                            break;
                        case sf::Keyboard::Up:
                             if(contador==2 && continuar==true){
                                dedo.setPosition(215,260);
                                contador--;
                                //cout<<contador<<endl;
                                continuar=false;
                                hasonado1=false;
                                hasonado2=false;
                                hasonado4=false;
                                hasonado5=false;
                                if(hasonado1==false){
                                    cursor.play();
                                    hasonado1=true;
                                }
                            }else if(contador==3){
                                dedo.setPosition(215,280);
                                contador--;
                                //cout<<contador<<endl;
                                hasonado1=false;
                                hasonado3=false;
                                hasonado4=false;
                                hasonado5=false;
                                if(hasonado2==false){
                                    cursor.play();
                                    hasonado2=true;
                                }
                            }else if(contador==4){
                                dedo.setPosition(215,300);
                                contador--;
                                //cout<<contador<<endl;
                                hasonado1=false;
                                hasonado2=false;
                                hasonado4=false;
                                hasonado5=false;
                                if(hasonado3==false){
                                    cursor.play();
                                    hasonado3=true;
                                }
                            }else if(contador==5){
                                dedo.setPosition(215,320);
                                contador--;
                                //cout<<contador<<endl;
                                hasonado1=false;
                                hasonado3=false;
                                hasonado2=false;
                                hasonado5=false;
                                if(hasonado4==false){
                                    cursor.play();
                                    hasonado4=true;
                                }
                            }
                        break;
                        case sf::Keyboard::Return:
                            if(contador==5){
                                time1 = sf::seconds(1);
                                select.play();
                                sf::sleep(time1);
                                window.close();
                            }else if(contador==2){
                                estado.setScale(1,1);
                                select.play();
                            }else if(contador==1){
                                danyo.setScale(0.8,0.8);
                                select.play();
                            }else if(contador==3){
                                objeto.setScale(1,1);
                                select.play();
                            }
                        break;  
                        case sf::Keyboard::B:
                            if(contador==2){
                                estado.setScale(0,0);
                            }else if(contador==1){
                                danyo.setScale(0,0);
                            }else if(contador==3){
                                objeto.setScale(0,0);
                            }
                        break;  
                    }
                }
        }
        window.clear();        
        window.draw(fondo);
        window.draw(boton1);
        window.draw(dedo);
        window.draw(estado);
        window.draw(danyo);
        window.draw(objeto);
        window.display();
        }

        return 0;
}


