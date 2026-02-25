#include "events.hpp"
#include <SFML/Window/Keyboard.hpp>

void processEvents(sf::Window &window, bool& paused) {
    while ( const std::optional event = window.pollEvent() ) {

	    if ( event->is<sf::Event::Closed>() ) {
			window.close();

        } else if ( const auto* keyPressed = event->getIf<sf::Event::KeyPressed>() ) {
            if ( keyPressed->scancode == sf::Keyboard::Scancode::Escape ) {
                window.close();
            } else if ( keyPressed->scancode == sf::Keyboard::Scancode::Space ) {
                paused = !paused;
            }
        }

	}
}
