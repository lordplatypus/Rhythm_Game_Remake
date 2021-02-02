#include <SFML/Graphics.hpp>
#include "DeltaTime.h"
#include "Camera.h"
#include "Game.h"
#include "MP.h"

int main()
{
    bool isRunning = true;//bool for main game loop
    sf::RenderWindow window(sf::VideoMode(1440, 960), "Game"); //game window

    DeltaTime deltaTime;
    Camera camera{&window};
    camera.SetCameraViewSize(window.getSize().x, window.getSize().y);
    camera.SetTarget(sf::Vector2f(camera.GetCameraViewSize().x/2, camera.GetCameraViewSize().y/2));
    window.setView(camera.GetCamera());
    Game game{&camera};

    while (isRunning)
    {//main game loop
        sf::Event event; //events
        while (window.pollEvent(event))
        {//
            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect viewport(0.f, 0.f, 1.f, 1.f);

                float screenwidth = event.size.width / 360.0f;
                float screenheight = event.size.height / 240.0f;

                if(screenwidth > screenheight)
                {
                    viewport.width = screenheight / screenwidth;
                    viewport.left = (1.f - viewport.width) / 2.f;
                }
                else if(screenwidth < screenheight)
                {
                    viewport.height = screenwidth / screenheight;
                    viewport.top = (1.f - viewport.height) / 2.f;
                }

                camera.SetCameraViewSize(viewport);  
            }
            else if (event.type == sf::Event::Closed)
            {
                isRunning = false;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                isRunning = false;
            }
        }
        game.Update(deltaTime.GetDeltaTime(), MP::BeatTime());
        window.clear();
        game.Draw(window); //actually draw objects
        window.display();
    }
    return EXIT_SUCCESS;
}