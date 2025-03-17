#include <drbar.hpp>
#include <SFML/Graphics.hpp>
#include <VolumeCW-API.hpp>



inline void drbar::update(){
    return driver.setPosition(sf::Vector2f(bar.getPosition().x,
    bar.getPosition().y+bar.getSize().y/2.0-driver.getRadius()));
}

APIvolumcw void drbar::setPosition(sf::Vector2f p){
    return bar.setPosition(p);
}

APIvolumcw void drbar::setSizeBar(sf::Vector2f size){
    return bar.setSize(size);
}

APIvolumcw void drbar::setRadiusDr(float rdu){
    return driver.setRadius(rdu);
}

APIvolumcw void drbar::setColorDr(sf::Color dv){
    return driver.setFillColor(dv);
}

APIvolumcw void drbar::setColorBar(sf::Color dv){
    return bar.setFillColor(dv);
}

APIvolumcw void drbar::drawon(sf::RenderWindow&wd){
    update();
    wd.draw(bar);
    wd.draw(driver);
}
drbar::drbar(){}

APIvolumcw void drbar::driveto(float x){
    if(x<bar.getPosition().x){x=bar.getPosition().x;}
    else if(x>bar.getPosition().x+bar.getSize().x){x=bar.getPosition().x+bar.getSize().x;}
    x-=driver.getRadius();
    driver.setPosition(sf::Vector2f(x,driver.getPosition().y));
}

APIvolumcw bool drbar::touching(sf::Vector2i pos){
    return pos.x>=bar.getPosition().x&&pos.x<=(bar.getPosition().x+bar.getSize().x)
    &&pos.y>=bar.getPosition().y&&pos.y<=bar.getPosition().y+bar.getSize().y;
}