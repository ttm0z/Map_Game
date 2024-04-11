#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

// Simple 2D Perlin Noise implementation
class PerlinNoise {
public:
    PerlinNoise();
    double noise(double x, double y);

private:
    int permutation[256];

    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y);
};

PerlinNoise::PerlinNoise() {
    // initialize permutation table by populating and shuffling
    for (int i = 0; i < 256; ++i) {
        permutation[i] = i;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(permutation, permutation + 256, g);
}

double PerlinNoise::noise(double x, double y) {
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    x -= floor(x);
    y -= floor(y);
    double u = fade(x);
    double v = fade(y);

    int A = permutation[X] + Y;
    int AA = permutation[A];
    int AB = permutation[A + 1];
    int B = permutation[X + 1] + Y;
    int BA = permutation[B];
    int BB = permutation[B + 1];

    return lerp(v, lerp(u, grad(AA, x, y),
                           grad(BA, x - 1, y)),
                   lerp(u, grad(AB, x, y - 1),
                           grad(BB, x - 1, y - 1)));
}

double PerlinNoise::fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double PerlinNoise::lerp(double t, double a, double b) {
    return a + t * (b - a);
}

double PerlinNoise::grad(int hash, double x, double y) {
    int h = hash & 15;
    double u = h < 8 ? x : y;
    double v = h < 4 ? y : (h == 12 || h == 14 ? x : 0);
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

int main() {
    PerlinNoise perlin;

    const int width = 100;
    const int height = 100;

    // initialize the noisemap
    std::vector<std::vector<double>> noiseMap(width, std::vector<double>(height));

    // Generate Perlin noise map
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            noiseMap[x][y] = perlin.noise(x * 0.1, y * 0.1);
        }
    }
    
    // print the noise map
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << noiseMap[x][y] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
