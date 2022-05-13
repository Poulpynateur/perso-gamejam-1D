#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <chrono>
#include <thread>
#include <iostream>

#include "src/manager.hpp"
#include "src/render/renderer.hpp"

#define TARGET_FPS 60
#define MS_PER_FRAME 1000 / TARGET_FPS

int main()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);

    srand(time(NULL));

    sf::Vector2f windowSize(800, 800);
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y, 32), "La sausage party");

    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    sf::Vector2f bounds(window.getSize().x / 4, window.getSize().y / 4);
    manager_t manager(bounds);
    renderer_t renderer(window, bounds);

    sf::Event event;
    sf::Uint64 tick = 0;
    while (window.isOpen()) {

        // auto start = std::chrono::high_resolution_clock::now();

        manager.world.inputs.reinit();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    manager.world.inputs.left_key = true;
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    manager.world.inputs.right_key = true;
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    manager.world.inputs.up_key = true;
                }
            }
        }

        // Le jeu
        manager.update(tick);
        renderer.render(manager.world);
        manager.clean();

        tick++;
    }

    return 0;
}