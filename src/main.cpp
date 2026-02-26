#include "configuration.hpp"
#include "cell.hpp"
#include "events.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <random>







int main(int argc, char* argv[]) {
	sf::RenderWindow window( sf::VideoMode( { conf::window_size.x, conf::window_size.y } ), "life");
    
    // get seed
    unsigned int seed;
    if (argc >= 2) {
        unsigned long ul_value = std::stoul(argv[1]); 
        seed = static_cast<unsigned int>(ul_value);

    } else {
        static std::random_device rd;
        seed = rd();
    }
    std::cout << "Seed used: " << seed << std::endl;


    cell::grid cells = init_cells(seed);
    cell::grid initial_grid = cells; // saves the "current" grid for resets

    bool paused = false;
    bool set_new = false;
    bool reset = false;
	while ( window.isOpen() ) {
        processEvents(window, paused, set_new, reset);

        if (reset) {
            reset = false;
            cells = initial_grid;
        }

        if (set_new) {
            set_new = false;
            cells = init_cells(seed);
            initial_grid = cells;
        }

        if (!paused) {
            cells = updateCells(cells);
        }

		window.clear();
        
        for (int y = 0; y < conf::grid_size.y; y++) {
            for (int x = 0; x < conf::grid_size.x; x++) {
                sf::RectangleShape rectangle({conf::cell_size, conf::cell_size});
                if (cells[y][x].alive) {
                    rectangle.setFillColor(sf::Color(0, 190, 0));
                } else {
                    rectangle.setFillColor(sf::Color::White);
                }
                rectangle.setPosition(cells[y][x].position);
                window.draw(rectangle);
            }
        }

		window.display();

	}
}





