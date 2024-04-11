#pragma once

#include <vector>
#include <random>

class CellularAutomata {
public:
    CellularAutomata(int width, int height);
    std::vector<std::vector<bool>> generateMap(int iterations, float chanceToStartAlive);
    void printMap();

private:
    int width;
    int height;
    std::vector<std::vector<bool>> map;
    std::mt19937 rng;

    int countAliveNeighbours(int x, int y);
};
