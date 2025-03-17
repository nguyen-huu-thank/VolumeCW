#define BUTTON_HPP
#ifdef BUTTON_HPP

#include <SFML/Graphics.hpp>
// #include <VolumeCW-API.hpp>

class button:public sf::CircleShape{
private:
    sf::RenderWindow*window;
public:
    button(sf::RenderWindow*window);
    bool touching(sf::Vector2i position);
    void monitor();
};

#endif