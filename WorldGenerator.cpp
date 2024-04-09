#include "WorldGenerator.h"
#include <iostream>
#include <iomanip> // For std::setw
#include <algorithm> // For std::find

WorldGenerator::WorldGenerator() {
    //worldSize = generateWorldSize(1.2, 0.5, 0.7, 1.3);
    worldSize = 1;
    generateWorld();
}

void WorldGenerator::generateWorld() {
    // determine grid size
    grid_size = worldSize * 160;
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


    std::uniform_int_distribution<> w(1, 10);
    // grow each continent in all 4 directions
    for (int i = 0; i < continents.size(); i++) {
        int x = continents[i].x;
        int y = continents[i].y;

        // generate a random integer in each direction
        int dn = w(gen);
        int de = w(gen);

        // determine dimensions
        for(int i = 1; i<dn; i++){
            for(int j = 1; j<de; j++){
                
                bool edge = false;
                
                if ( i+1 == dn || j+1 == de){
                    edge = true;
                }
                
                if (x-i > 0){
                    plateMap[x - i][y] = plateMap[x][y];
                    if(edge && std::rand() % 2 == 0){
                        plateMap[x - i][y] = 0;
                    }
                }
                
                if (x+i < grid_size){
                    plateMap[x + i][y] = plateMap[x][y];
                    if(edge && std::rand() % 2 == 0){
                        plateMap[x + i][y] = 0;
                    }
                }
                
                if (y - j > 0){
                    plateMap[x][y - j] = plateMap[x][y];
                    if(edge && std::rand() % 2 == 0){
                        plateMap[x][y - j] = 0;
                    }
                }
                
                if (y + j < grid_size){
                    plateMap[x][y + j] = plateMap[x][y]; 
                    if(edge && std::rand() % 2 == 0){
                        plateMap[x][y + j] = 0;
                    }
                }
                

                if (y + j < grid_size && x + i < grid_size){
                    plateMap[x + i][y + j] = plateMap[x][y];    
                    if(edge && std::rand() % 2 == 0){
                        plateMap[x + i][y + j] = 0;
                    }
                }

                if (x + i < grid_size && y - j > 0){
                    plateMap[x + i][y - j] = plateMap[x][y];    
                    if(edge && std::rand() % 2 == 0){
                        plateMap[x + i][y - j] = 0;
                    }
                }

                if (x - i > 0 && y + j < grid_size){
                    plateMap[x - i][y + j] = plateMap[x][y];    
                    if(edge && std::rand() % 2 == 0){
                        plateMap[x - i][y + j] = 0;
                    }
                }

                if (y - j > 0 && x - i > 0){
                    plateMap[x - i][y - j] = plateMap[x][y];       
                    if(edge && std::rand() % 2 == 0){
                        plateMap[x - i][y - j] = 0;
                    }
                }
                
            }

                
        }

        //fill in
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
