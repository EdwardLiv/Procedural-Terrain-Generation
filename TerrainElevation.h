#pragma once

#include "ofMain.h"
#include "GUI.h"

class TerrainElevation {
	private:
		int seed;
		int columns, rows;
		int octaves;
		float noiseScale;
		float lacunarity;
		float persistence;
		int maxElevation;
		float flattenElevation;
		int mapType;
		float minNoiseZ, maxNoiseZ;
		vector<vector<float>> elevationMap;

	public:
		TerrainElevation();
		TerrainElevation(GUI::Settings s);
		void initializeMatrix();
		void calculateNoise();
		void applyMapType();
		vector<vector<float>> getElevationMap();
};
