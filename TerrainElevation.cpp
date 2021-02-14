#include "TerrainElevation.h"
#include <vector>

TerrainElevation::TerrainElevation() {

}

TerrainElevation::TerrainElevation(GUI::Settings s) {
    this->seed = s.seed;
    this->columns = s.mapWidth/s.tileSize;
    this->rows = s.mapHeight/s.tileSize;
    this->octaves = s.octaves;
    this->noiseScale = s.noiseScale;
    this->lacunarity = s.lacunarity;
    this->persistence = s.persistence;
    this->maxElevation = s.maxElevation;
    this->flattenElevation = s.flattenElevation;
    this->mapType = s.mapType;
}

void TerrainElevation::initializeMatrix() {
    elevationMap.clear();
    for (int y = 0; y <= rows; y++) {
        vector<float> row;
        for (int x = 0; x <= columns; x++)
            row.push_back(0);
        elevationMap.push_back(row);
    }
}

void TerrainElevation::calculateNoise() {
    ofSeedRandom(seed);
    vector<float> seedOffsetX, seedOffsetY;
    for (int i = 0; i < octaves; i++) {
        seedOffsetX.push_back(ofRandom(255));
        seedOffsetY.push_back(ofRandom(255));
    }

    float noiseX, noiseY, noiseZ;
    float frequency, amplitude;
    minNoiseZ = 1;
    maxNoiseZ = 0;
    for (int y = 0; y <= rows; y++) {
        for (int x = 0; x <= columns; x++) {
            frequency = 1;
            amplitude = 1;
            noiseZ = 0;

            for (int i = 0; i < octaves; i++) {
                noiseX = ((float)x-columns/2) / columns / noiseScale * frequency + seedOffsetX.at(i);
                noiseY = ((float)y-rows/2) / rows / noiseScale * frequency + seedOffsetY.at(i);
                noiseZ += ofNoise(noiseX, noiseY) * amplitude;
                frequency *= lacunarity;
                amplitude *= persistence;
            }

            if (noiseZ < minNoiseZ) {
                minNoiseZ = noiseZ;
            }
            if (noiseZ > maxNoiseZ) {
                maxNoiseZ = noiseZ;
            }

            elevationMap.at(y).at(x) = noiseZ;
        }
    }
}

void TerrainElevation::applyMapType() {
    float maxEuclideanDistance = pow(0.5, 0.5); //center to corner: sqrt(0.5^2 + 0.5^2)
    for (int y = 0; y <= rows; y++) {
        for (int x = 0; x <= columns; x++) {
            if (mapType==2) { //lake
                float euclideanDistance = pow(pow((float)x / columns - 0.5, 2) + pow((float)y / rows - 0.5, 2), 0.5);
                elevationMap.at(y).at(x) = ofMap(elevationMap.at(y).at(x), minNoiseZ, maxNoiseZ, 0, 1);
                elevationMap.at(y).at(x) = pow((elevationMap.at(y).at(x) + euclideanDistance / maxEuclideanDistance) / 2, flattenElevation);
            }
            else if (mapType==1) { //island
                float euclideanDistance = pow(pow((float)x / columns - 0.5, 2) + pow((float)y / rows - 0.5, 2), 0.5);
                elevationMap.at(y).at(x) = ofMap(elevationMap.at(y).at(x), minNoiseZ, maxNoiseZ, 0, 1);
                elevationMap.at(y).at(x) = pow((elevationMap.at(y).at(x) - euclideanDistance / maxEuclideanDistance + 1) / 2, flattenElevation);
            }
            else { //standard
                elevationMap.at(y).at(x) = pow(ofMap(elevationMap.at(y).at(x), minNoiseZ, maxNoiseZ, 0, 1), flattenElevation);
            }

            elevationMap.at(y).at(x) = ofMap(elevationMap.at(y).at(x), 0, 1, -maxElevation, maxElevation);
        }
    }
}

vector<vector<float>> TerrainElevation::getElevationMap() {
    return elevationMap;
}
