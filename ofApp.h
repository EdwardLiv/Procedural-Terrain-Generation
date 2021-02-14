#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "TerrainGenerator.h"
#include "GUI.h"

class ofApp : public ofBaseApp {
	private:
		TerrainGenerator terrainGenerator;
		GUI gui;
		bool guiVisibility;

	public:
		void setup();
		void draw();
		void keyPressed(int key);
};
