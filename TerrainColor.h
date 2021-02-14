#pragma once

#include "ofMain.h"
#include "GUI.h"

class TerrainColor {
    private:
        ofColor triangleColor;
        ofColor oceanColor;
        ofColor coastColor;
        ofColor beachColor;
        ofColor plainColor;
        ofColor forestColor;
        ofColor hillColor;
        ofColor mountainColor;
        float triangleElevation;
        float oceanElevation;
        float coastElevation;
        float beachElevation;
        float plainElevation;
        float forestElevation;
        float hillElevation;
        float mountainElevation;

    public:
	    TerrainColor();
        TerrainColor(GUI::Settings s);
	    void calculateColor(float triangleElevation);
        void interpolateColor(float lowElevation, float highElevation, ofColor lowColor, ofColor highColor);
        ofColor getColor();
};
