#include "TerrainGenerator.h"
#include <vector>

TerrainGenerator::TerrainGenerator() {
    ofEnableDepthTest();
    glShadeModel(GL_FLAT);
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    camera.setPosition(ofVec3f(0, -350, 2050));
}

void TerrainGenerator::setup(GUI::Settings s) {
    this->seed = s.seed;
    this->tileSize = s.tileSize;
    this->mapWidth = s.mapWidth;
    this->mapHeight = s.mapHeight;
    this->octaves = s.octaves;
    this->noiseScale = s.noiseScale;
    this->lacunarity = s.lacunarity;
    this->persistence = s.persistence;
    this->maxElevation = s.maxElevation;

    terrainElevation = TerrainElevation(s);
    terrainElevation.initializeMatrix();
    terrainElevation.calculateNoise();
    terrainElevation.applyMapType();
    elevationMap = terrainElevation.getElevationMap();

    terrainColor = TerrainColor(s);

    mesh.clear();
    int columns = mapWidth / tileSize;
    int rows = mapHeight / tileSize;
    ofVec3f topLeft, topRight, bottomLeft, bottomRight;

    for (int j = 0; j < rows; j++) {
        for (int i = 0; i < columns; i++) {
            topLeft = ofVec3f(i, j);
            topRight = ofVec3f(i + 1, j);
            bottomLeft = ofVec3f(i, j + 1);
            bottomRight = ofVec3f(i + 1, j + 1);

            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)) {
                addTriangle(topLeft, topRight, bottomLeft);
                addTriangle(bottomLeft, topRight, bottomRight);
            }
            else {
                addTriangle(bottomLeft, topLeft, bottomRight);
                addTriangle(bottomRight, topLeft, topRight);
            }
        }
    }

    mesh.setupIndicesAuto();
    calculateNormals();
}

void TerrainGenerator::addTriangle(ofVec3f p1, ofVec3f p2, ofVec3f p3) {
    p1.z = elevationMap.at(p1.y).at(p1.x);
    p2.z = elevationMap.at(p2.y).at(p2.x);
    p3.z = elevationMap.at(p3.y).at(p3.x);

    float triangleElevation = (p1.z + p2.z + p3.z) / 3;

    addVertex(p1, triangleElevation);
    addVertex(p2, triangleElevation);
    addVertex(p3, triangleElevation);
}

void TerrainGenerator::addVertex(ofVec3f p, float triangleElevation) {
    p.x *= tileSize;
    p.y *= tileSize;

    if (p.z < 0) {
        p.z = 0;
    }

    triangleElevation = ofMap(triangleElevation, -maxElevation, maxElevation, 0, 1);
    terrainColor.calculateColor(triangleElevation);

    mesh.addVertex(p);
    mesh.addColor(terrainColor.getColor());
    mesh.addNormal(ofVec3f(0, 0, 0));
}

void TerrainGenerator::calculateNormals() {
    int p1, p2, p3;
    ofVec3f v1, v2, crossProduct;

    for (int i = 0; i < mesh.getIndices().size(); i += 3) {
        p1 = mesh.getIndices()[i];
        p2 = mesh.getIndices()[i+1];
        p3 = mesh.getIndices()[i+2];

        v1 = mesh.getVertices()[p1] - mesh.getVertices()[p2];
        v2 = mesh.getVertices()[p3] - mesh.getVertices()[p2];
        crossProduct = v2.cross(v1);

        mesh.getNormals()[p1] += crossProduct;
        mesh.getNormals()[p2] += crossProduct;
        mesh.getNormals()[p3] += crossProduct;
    }
}

void TerrainGenerator::draw() {
    camera.begin();
    light.enable();
    light.setParent(camera);
    ofPushMatrix();
    ofRotateXDeg(-45);
    ofTranslate(-mapWidth/2, -mapHeight/2);
    mesh.drawFaces();
    ofPopMatrix();
    camera.end();
}
