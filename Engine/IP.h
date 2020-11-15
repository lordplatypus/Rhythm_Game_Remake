#ifndef IP_H_
#define ID_H_
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class IP
{
public:
    IP();
    ~IP();
    //Store "window" address, used to get mouse position
    static void SetWindow(sf::Window* window);

    //Keyboard Stuff

    //Returns true if the button given is currently being pressed - constantly active
    static bool GetButton(sf::Keyboard::Key buttonID);

    //Individual buttons - activates 1 per button press
    static bool PressLeft();
    static bool PressRight();
    static bool PressUp();
    static bool PressDown();
    static bool PressSpace();
    static bool PressW();
    static bool PressA();
    static bool PressS();
    static bool PressD();
    static bool PressZ();
    static bool PressX();

    //Mouse Stuff

    static bool GetMouseClick(sf::Mouse::Button buttonID);
    static bool LeftClick();
    static bool RightClick();
    static sf::Vector2i GetMousePosition();
    static void SetMousePosition(sf::Vector2i position);
};

#endif