#pragma once
#include <SFML/Window.hpp>
#include <SFML/Window/Window.hpp>

void processEvents(sf::Window& window, bool& paused, bool& set_new, bool& reset);
