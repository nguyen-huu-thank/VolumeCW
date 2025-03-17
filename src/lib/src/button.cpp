#include <button.hpp>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <VolumeCW-API.hpp>

#define Pos getPosition()
#define rdu getRadius()

#include <windows.h>

bool button::touching(sf::Vector2i pos){
    return pow(pos.x-(Pos.x+rdu),2)+pow(pos.y-(Pos.y+rdu),2)<=pow(rdu,2);
}
button::button(sf::RenderWindow*wido){window=wido;}
void button::monitor(){
    SendMessage(window->getNativeHandle(),WM_NCLBUTTONDOWN,HTCAPTION,0);
}