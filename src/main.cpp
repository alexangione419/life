#include "configuration.hpp"
#include "cell.hpp"
#include "events.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
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

    // this should be a struct of sorts
    bool s_pulsar = false;
    bool paused = false;
    bool set_new = false;
    bool reset = false;
	while ( window.isOpen() ) {
        processEvents(window, paused, set_new, reset, s_pulsar);

        if (s_pulsar) {
            s_pulsar = false;
            spawn_pulsar(cells);
        }

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


        sf::RectangleShape legend({300, 150});
        legend.setFillColor(sf::Color(111, 111, 111));
        legend.setPosition({conf::window_size.x-300, 0});
        legend.setOutlineThickness(5.f);
        legend.setOutlineColor(sf::Color(150, 150, 150));


        sf::Font font;
        if (!font.openFromFile("./assets/fonts/0xProtoNerdFont-Regular.ttf")) {
            return -1; 
        }

        sf::Text title(font);
        title.setString("Alex's Conway's Game of Life");
        title.setCharacterSize(15);
        title.setFillColor(sf::Color::White);

        sf::FloatRect bounds = title.getLocalBounds();
        title.setOrigin({
            bounds.position.x + bounds.size.x / 2.f,
            bounds.position.y + bounds.size.y / 2.f
        });

        title.setPosition({
            legend.getPosition().x + legend.getSize().x / 2.f,
            legend.getPosition().y + legend.getSize().y / 4.f
        });


        sf::Text population(font);
        population.setCharacterSize(15);
        int pop = count_population(cells);
        population.setString("Population: " + std::to_string(pop));
        population.setOrigin({
            bounds.position.x + bounds.size.x / 2.f,
            bounds.position.y + bounds.size.y / 2.f
        });

        population.setPosition({
            legend.getPosition().x + legend.getSize().x / 2.f,
            legend.getPosition().y + legend.getSize().y / 2.f
        });



        window.draw(legend);
        window.draw(population);
        window.draw(title);

		window.display();

	}
}





