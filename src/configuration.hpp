#pragma once
#include <SFML/System/Vector2.hpp>



namespace conf {
constexpr sf::Vector2u const window_size = {1200, 800};

constexpr int cell_size = 5;
inline constexpr sf::Vector2u grid_size = {window_size.x / cell_size, window_size.y / cell_size};


}
