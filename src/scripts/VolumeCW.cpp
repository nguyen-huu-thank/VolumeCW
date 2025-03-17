#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <thread>
// #include <SFML/Window/Mouse.hpp>
// #include <windows.h>


float GetAudioVolume();
void SetAudioVolume(float volume);
class button:public sf::CircleShape{
private:
    sf::RenderWindow*window;
public:
    button(sf::RenderWindow*window);
    bool touching(sf::Vector2i position);
    void monitor();
};

class drbar
{
private:
    sf::RectangleShape bar;
    sf::CircleShape driver;
    public:
    bool track=0;
    inline void update();
    inline void setPosition(sf::Vector2f pos);
    inline void setSizeBar(sf::Vector2f size);
    inline void setRadiusDr(float rdu);
    inline void setColorDr(sf::Color color);
    inline void setColorBar(sf::Color color);
    void drawon(sf::RenderWindow&window);
    inline void driveto(float x);
    inline bool touching(sf::Vector2i position);
    inline drbar(/* args */);
};

    

sf::Vector2u Desktop=sf::VideoMode().getDesktopMode().size;

sf::RenderWindow window(sf::VideoMode(sf::Vector2u(500,200)),"test",sf::Style::Close);

bool mv=0;
void settitle(){
    sf::String title="Volume:";
    while(1){
        title=sf::String("Volume:")+std::to_string(int(GetAudioVolume()*100))+"%";
        window.setTitle(title);
    }
}

inline float dau(int x){
    return (x<0)?-0.01:0.01;
}

void blockupdown(){
    sf::Vector2i window_pos=window.getPosition();
    int lenght=ceill(Desktop.x/100.0);
    // std::cout<<lenght;
    while(1){
        // std::cout<<mv;
        sf::Vector2i temp=window.getPosition();
        if(mv)window_pos=temp;
        else if(abs(temp.x-window_pos.x)>=lenght){
            // std::cout<<"tang";
            SetAudioVolume(GetAudioVolume()+dau(temp.x-window_pos.x));
            window_pos=temp;
        }
    }
}

int main(){
    // button mv(&window);
    // mv.setFillColor(sf::Color(255,0,0));
    // mv.setPosition(sf::Vector2f(0,0));
    // mv.setRadius(20);
    // window.display();
    // window.clear(sf::Color(255,255,255));
    // window.draw(mv);
    //
    drbar dba;
    dba.setPosition(sf::Vector2f(15,90));
    dba.setColorDr(sf::Color(0,0,255));
    dba.setRadiusDr(15);
    dba.setColorBar(sf::Color(120,120,120));
    dba.setSizeBar(sf::Vector2f(470,20));
    //
    std::thread blud(blockupdown);
    std::thread settt(settitle);
    sf::Vector2i pos=window.getPosition();
    sf::Vector2i window_pos=window.getPosition();
    button bl(&window);
    bl.setFillColor(sf::Color(255,0,0));
    bl.setRadius(20);
    bl.setPosition(sf::Vector2f(0,0));
    window.clear(sf::Color(255,255,255));
    window.draw(bl);
    dba.drawon(window);
    window.display();
    dba.update();
    while (1)
    {
        sf::Vector2i temp=window.getPosition();
        temp.y=window_pos.y;
        // window.setPosition(sf::Vector2i(temp));
        // sf::Vector2i pos=window.getPosition();
        std::optional event=window.waitEvent();
        if(event->is<sf::Event::Closed>()){
            window.close();
            return 0;
        }
        else if(event->is<sf::Event::Resized>()){
            window.setSize(sf::Vector2u(500,200));
        }
        // else if(event->getIf<sf::Event::JoystickMoved>()){
        //     window.clear(sf::Color(255,0,0));
        //     window.display();
        // }
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            // std::wcout<<L"nhấn\n";
            if(bl.touching(sf::Mouse::getPosition(window))){
                mv=1;
                bl.monitor();
            }
            else if(dba.track){
                dba.driveto(sf::Mouse::getPosition(window).x);
            }
            else if(dba.touching(sf::Mouse::getPosition(window))){
                dba.track=1;
                dba.driveto(sf::Mouse::getPosition(window).x);
            }
        }
        else if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            mv=0;
            dba.track=0;
            // std::wcout<<L"thả\n";
        }
        window.clear(sf::Color(255,255,255));
        window.draw(bl);
        dba.drawon(window);
        window.display();
    }
    blud.join();
    settt.join();
    return 1;
}

void SetAudioVolume(float newVolume){
    CoInitialize(NULL);
    IMMDeviceEnumerator* pEnumerator = NULL;
    CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);

    IMMDevice* pDevice = NULL;
    pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);

    IAudioEndpointVolume* pVolume = NULL;
    pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (void**)&pVolume);
    pVolume->SetMasterVolumeLevelScalar(newVolume, NULL);

    pVolume->Release();
    pDevice->Release();
    pEnumerator->Release();
    CoUninitialize();
}


float GetAudioVolume() {
    CoInitialize(nullptr);  // Initialize COM library

    IMMDeviceEnumerator* pEnumerator = nullptr;
    IMMDevice* pDevice = nullptr;
    IAudioEndpointVolume* pVolume = nullptr;
    float volume = 0.0f;

    // Get the audio device
    CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, IID_PPV_ARGS(&pEnumerator));
    if (pEnumerator) {
        pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
        if (pDevice) {
            pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, nullptr, (void**)&pVolume);
            if (pVolume) {
                pVolume->GetMasterVolumeLevelScalar(&volume);  // Get volume (0.0 - 1.0)
                pVolume->Release();
            }
            pDevice->Release();
        }
        pEnumerator->Release();
    }

    CoUninitialize();
    return volume;  // Convert to percentage (0 - 100)
}

// #include <button.hpp>
// #include <cmath>
// #include <VolumeCW-API.hpp>

#define Pos getPosition()
#define rdu getRadius()



bool button::touching(sf::Vector2i pos){
    return pow(pos.x-(Pos.x+rdu),2)+pow(pos.y-(Pos.y+rdu),2)<=pow(rdu,2);
}
button::button(sf::RenderWindow*wido){window=wido;}
void button::monitor(){
    SendMessage(window->getNativeHandle(),WM_NCLBUTTONDOWN,HTCAPTION,0);
}
// #include <drbar.hpp>
// #include <VolumeCW-API.hpp>



inline void drbar::update(){
    return driver.setPosition(sf::Vector2f(bar.getPosition().x,
    bar.getPosition().y+bar.getSize().y/2.0-driver.getRadius()));
}

void drbar::setPosition(sf::Vector2f p){
    return bar.setPosition(p);
}

void drbar::setSizeBar(sf::Vector2f size){
    return bar.setSize(size);
}

void drbar::setRadiusDr(float rdus){
    return driver.setRadius(rdus);
}
void drbar::setColorDr(sf::Color dv){
    return driver.setFillColor(dv);
}

void drbar::setColorBar(sf::Color dv){
    return bar.setFillColor(dv);
}

void drbar::drawon(sf::RenderWindow&wd){
    wd.draw(bar);
    wd.draw(driver);
}
drbar::drbar(){}

void drbar::driveto(float x){
    if(x<bar.getPosition().x){x=bar.getPosition().x;}
    else if(x>bar.getPosition().x+bar.getSize().x){x=bar.getPosition().x+bar.getSize().x;}
    x-=driver.getRadius();
    driver.setPosition(sf::Vector2f(x,driver.getPosition().y));
}

bool drbar::touching(sf::Vector2i pos){
    return pos.x>=bar.getPosition().x&&pos.x<=(bar.getPosition().x+bar.getSize().x)
    &&pos.y>=bar.getPosition().y&&pos.y<=bar.getPosition().y+bar.getSize().y;
}