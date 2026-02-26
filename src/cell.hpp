#pragma once
#include "configuration.hpp"
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <array>


struct Cell {
    sf::Vector2f position;
    bool alive;
};

namespace cell {
using grid = std::array<std::array<Cell, conf::grid_size.x>, conf::grid_size.y>;
}

cell::grid init_cells(unsigned int seed);
cell::grid updateCells(cell::grid& cells); 
void spawn_pulsar(cell::grid& cells);
int count_population(cell::grid cells);
