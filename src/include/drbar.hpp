#define DRBAR_HPP
#ifdef DRBAR_HPP

#include <SFML/Graphics.hpp>
// #include <VolumeCW-API.hpp>
// #include <VolumeCW-API.hpp>

class drbar
{
private:
    sf::RectangleShape bar;
    sf::CircleShape driver;
    inline void update();
public:
    bool track=0;
    void setPosition(sf::Vector2f pos);
    void setSizeBar(sf::Vector2f size);
    void setRadiusDr(float rdu);
    void setColorDr(sf::Color color);
    void setColorBar(sf::Color color);
    void drawon(sf::RenderWindow&window);
    void driveto(float x);
    bool touching(sf::Vector2i position);
    drbar(/* args */);
};



#endif