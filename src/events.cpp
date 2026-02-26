#include "events.hpp"
#include <SFML/Window/Keyboard.hpp>

void processEvents(sf::Window &window, bool& paused, bool& set_new, bool& reset, bool& spawn_pulsar) {
    while ( const std::optional event = window.pollEvent() ) {

	    if ( event->is<sf::Event::Closed>() ) {
			window.close();

        } else if ( const auto* keyPressed = event->getIf<sf::Event::KeyPressed>() ) {
            if ( keyPressed->scancode == sf::Keyboard::Scancode::Escape ) {
                window.close();
            } else if ( keyPressed->scancode == sf::Keyboard::Scancode::Space ) {
                paused = !paused;
            } else if ( keyPressed->scancode == sf::Keyboard::Scancode::N ) {
                set_new = true;
            } else if ( keyPressed->scancode == sf::Keyboard::Scancode::R ) {
                reset = true;
            } else if ( keyPressed->scancode == sf::Keyboard::Scancode::P ) {
                spawn_pulsar = true;
            }
        }

	}
}
