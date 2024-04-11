#include "WorldGenerator.h"
#include "CellularAutomataMap.h"
#include <iostream>
#include <iomanip> // For std::setw
#include <algorithm> // For std::find

WorldGenerator::WorldGenerator() {
    //worldSize = generateWorldSize(1.2, 0.5, 0.7, 1.3);
    worldSize = 1;
    generateWorld();
}

void WorldGenerator::generateWorld() {
    
    // seed values for CA
    const int iterations = 5;
    const float chanceToStartAlive = 0.4f;
    
    // determine grid size
    grid_size = worldSize * 160;
    worldMap.resize(grid_size, std::vector<bool>(grid_size, 0));

    CellularAutomata automata(grid_size, grid_size);

    std::cout << "World Generation Algorithm" << std::endl;
    std::cout << "World Size (Earth Masses): "<< worldSize << std::endl;
    worldMap = automata.generateMap(iterations, chanceToStartAlive);


}

// Function to calculate the Manhattan distance between two points
int WorldGenerator::manhattanDistance(const Cell& p1, const Cell& p2) {
    return std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y);
}


int WorldGenerator::getGridSize(){
    return grid_size;
}


/**
 * Generate world size selected from gaussian range 0.2m - 2.5m
*/
double WorldGenerator::generateWorldSize(double mean, double std_dev, double min_val, double max_val) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(mean, std_dev);

    double result;
    do {
        result = distribution(gen);
    } while (result < min_val || result > max_val);

    return result;
}

std::vector<std::vector<bool>> WorldGenerator::getMap(){
    return worldMap;
}


int WorldGenerator::generatePlates() {
    return 0;
}
