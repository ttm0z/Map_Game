#include "WorldGenerator.h"
#include <iostream>
#include <iomanip> // For std::setw
#include <algorithm> // For std::find

WorldGenerator::WorldGenerator() {
    worldSize = generateWorldSize(1.2, 0.5, 0.7, 1.3);
    generateWorld();
}

void WorldGenerator::generateWorld() {
    // determine grid size
    grid_size = worldSize * 100;
    plateMap.resize(grid_size, std::vector<int>(grid_size, 0));

    std::cout << "World Generation Algorithm" << std::endl;
    std::cout << "World Size (Earth Masses): "<< worldSize << std::endl;

    // determine number of continents
    int numContinents = 7 * grid_size / 25;
    std::cout<<"Number of Continents: " << numContinents << std::endl;

    // generate the highest points (centers) of each continent
    std::vector<Cell> continents;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(3, grid_size - 3);
    std::uniform_int_distribution<int> prob(0, 1);

    while (continents.size() < numContinents) {
        //generate new continent
        int x = dis(gen);
        int y = dis(gen);
        Cell newContinent = {x, y};

        // check for proximity to other continents
        bool tooClose = false;
        for (const Cell& continent : continents) {
            if (manhattanDistance(newContinent, continent) <= 5) {
                tooClose = true;
                break;
            }
        }
        if (!tooClose) {
            continents.push_back({x, y});
        }
    }

    // place continents on map
    for (int i = 1; i < numContinents + 1; i++) {
        Cell cont = continents[i - 1];
        plateMap[cont.x][cont.y] = i;
    }

    // grow each continent in all 4 directions
    for (int i = 0; i < continents.size(); i++) {
        int x = continents[i].x;
        int y = continents[i].y;
        int maxSteps = 5;
        for (int step = 0; step < maxSteps; step++) {
            int direction = std::uniform_int_distribution<int>(0, 3)(gen);
            switch (direction) {
                case 0: // Up
                    if (y > 0 && prob(gen) < 0.5) // Ensure within grid bounds and with a chance to stop
                        y--;
                        plateMap[x][y] = i;
                break;
                case 1: // Down
                    if (y < grid_size - 1 && prob(gen) < 0.66) // Ensure within grid bounds and with a chance to stop
                        y++;
                        plateMap[x][y] = i;

                break;
                case 2: // Left
                    if (x > 0 && prob(gen) < 0.66) // Ensure within grid bounds and with a chance to stop
                        x--;
                        plateMap[x][y] = i;
                break;
                case 3: // Right
                    if (x < grid_size - 1 && prob(gen) < 0.66) // Ensure within grid bounds and with a chance to stop
                        x++;
                        plateMap[x][y] = i;
                break;
            }
        }
    }
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

std::vector<std::vector<int>> WorldGenerator::getMap(){
    return plateMap;
}


int WorldGenerator::generatePlates() {
    return 0;
}
