#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <chrono>
#include <thread>
#include <iostream>

#include "src/ressources_loader.hpp"
#include "src/world.hpp"
#include "src/renderer.hpp"

#define TARGET_FPS 60
#define MS_PER_FRAME 1000 / TARGET_FPS

int main()
{
    srand(time(NULL));

    sf::Vector2f windowSize(800, 800);
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y, 32), "La sausage party");

    window.setFramerateLimit(60);

    ressources_loader_t::instance();

    world_t world = world_t(windowSize);
    renderer_t renderer = renderer_t(window, windowSize);

    sf::Event event;
    sf::Uint64 tick = 0;
    while (window.isOpen()) {

        // auto start = std::chrono::high_resolution_clock::now();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Le jeu
        world.update(tick);
        renderer.render(world);

    	tick++;
    }

    return 0;
}