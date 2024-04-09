#ifndef WORLDGENERATOR_H
#define WORLDGENERATOR_H

#include <vector>
#include <random>

struct Cell {
    int x;
    int y;
};

class WorldGenerator {
private:
    double worldSize;
    int grid_size;
    std::vector<std::vector<int>> plateMap;

public:
    WorldGenerator();
    void generateWorld();
    int manhattanDistance(const Cell& p1, const Cell& p2);
    double generateWorldSize(double mean, double std_dev, double min_val, double max_val);
    int generatePlates();
    int getGridSize();
    std::vector<std::vector<int>> getMap();
};

#endif
