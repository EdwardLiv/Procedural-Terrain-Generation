#include "ofApp.h"

void ofApp::setup() {
	ofBackground(0);
	guiVisibility = true;
}

void ofApp::draw() {
	if (gui.getIsAnySettingChanged()) {
		terrainGenerator.setup(gui.getSettings());
		gui.setIsAnySettingChanged();
	}

	terrainGenerator.draw();

	if (guiVisibility) {
		gui.draw();
	}
}

void ofApp::keyPressed(int key) {
	if (key == 32) { //Space key
		guiVisibility = !guiVisibility;
	}
}
