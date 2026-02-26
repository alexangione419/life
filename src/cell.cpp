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

void spawn_pulsar(cell::grid& cells) {
    int startX = conf::grid_size.x / 2 - 6;  
    int startY = conf::grid_size.y / 2 - 6; 

    std::vector<std::pair<int,int>> offsets = {
        {2,0},{3,0},{4,0},{8,0},{9,0},{10,0},

        {0,2},{5,2},{7,2},{12,2},
        {0,3},{5,3},{7,3},{12,3},
        {0,4},{5,4},{7,4},{12,4},

        {2,5},{3,5},{4,5},{8,5},{9,5},{10,5},

        {2,7},{3,7},{4,7},{8,7},{9,7},{10,7},

        {0,8},{5,8},{7,8},{12,8},
        {0,9},{5,9},{7,9},{12,9},
        {0,10},{5,10},{7,10},{12,10},

        {2,12},{3,12},{4,12},{8,12},{9,12},{10,12}
    };

    for (auto [dx, dy] : offsets) {
        cells[startY + dy][startX + dx].alive = true;
    }
}

int count_population(cell::grid cells) {
    int pop = 0;

    for (int y = 0; y < conf::grid_size.y; y++) {
        for (int x = 0; x < conf::grid_size.x; x++) {
            if (cells[y][x].alive) {
                pop += 1;
            }
        }
    }

    return pop;
}
