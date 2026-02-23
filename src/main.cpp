#include "configuration.hpp"
#include "events.hpp"
#include "cell.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <random>

std::array<std::array<Cell, conf::grid_size.x>, conf::grid_size.y> updateCells(std::array<std::array<Cell, conf::grid_size.x>, conf::grid_size.y>& cells) {
    std::array<std::array<Cell, conf::grid_size.x>, conf::grid_size.y> next = cells;

    for (int y = 0; y < conf::grid_size.y; y++) {
        for (int x = 0; x < conf::grid_size.x; x++) {
            int livingNeighbors = 0;

            if (y >= 1) {
                if (cells[y-1][x].alive) {
                    livingNeighbors++;
                }

                if (x < conf::grid_size.x-1) {
                    if (cells[y-1][x+1].alive) {
                        livingNeighbors++;
                    }

                    if (cells[y][x+1].alive) {
                        livingNeighbors++;
                    }
                }
            }

            if (x >= 1) {
                if (cells[y][x-1].alive) {
                    livingNeighbors++;
                }

                if (y < conf::grid_size.y-1) {
                    if (cells[y+1][x-1].alive) {
                        livingNeighbors++;
                    }

                    if (cells[y+1][x].alive) {
                        livingNeighbors++;
                    }
                    
                }
            }

            if (y >= 1 && x >= 1) {
                if (cells[y-1][x-1].alive) {
                    livingNeighbors++;
                }
            }
            
            if (y < conf::grid_size.y-1 && x < conf::grid_size.x-1) {
                if (cells[y+1][x+1].alive) {
                    livingNeighbors++;
                }
            }


            if (livingNeighbors < 2) {
                next[y][x].alive = false;
            } else if (livingNeighbors == 3) {
                next[y][x].alive = true;
            } else if (livingNeighbors >= 4) {
                next[y][x].alive = false;
            }
                
        }
    }


    return next;
}

int main() {
	sf::RenderWindow window( sf::VideoMode( { conf::window_size.x, conf::window_size.y } ), "life");

    std::array<std::array<Cell, conf::grid_size.x>, conf::grid_size.y> cells; 
    
    for (int y = 0; y < conf::grid_size.y; y++) {
        for (int x = 0; x < conf::grid_size.x; x++) {
            static std::random_device rd;
            static std::mt19937 gen(rd());               
            static std::bernoulli_distribution dist(0.2);

            cells[y][x] = Cell{{static_cast<float>(x*conf::cell_size), static_cast<float>(y*conf::cell_size)}, dist(gen)};
        }
    }


	while ( window.isOpen() ) {
        processEvents(window);
		
		window.clear();
        
        for (int y = 0; y < conf::grid_size.y; y++) {
            for (int x = 0; x < conf::grid_size.x; x++) {
                sf::RectangleShape rectangle({conf::cell_size, conf::cell_size});
                if (cells[y][x].alive) {
                    rectangle.setFillColor(sf::Color::Green);
                } else {
                    rectangle.setFillColor(sf::Color::White);
                }
                rectangle.setPosition(cells[y][x].position);
                window.draw(rectangle);
            }
        }

		window.display();

        cells = updateCells(cells);
	}
}
