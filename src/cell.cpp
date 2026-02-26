#include "cell.hpp"
#include <random>

cell::grid init_cells(unsigned int seed) {
    cell::grid cells; 

    static std::mt19937 gen(seed);               
    static std::bernoulli_distribution dist(0.5);

    // grid initialization
    for (int y = 0; y < conf::grid_size.y; y++) {
        for (int x = 0; x < conf::grid_size.x; x++) {
            cells[y][x] = Cell{{static_cast<float>(x*conf::cell_size), static_cast<float>(y*conf::cell_size)}, dist(gen)};
        }
    }

    return cells;
}

cell::grid updateCells(cell::grid& cells) {
    cell::grid next = cells;

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
