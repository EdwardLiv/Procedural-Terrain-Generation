#include "TerrainColor.h"

TerrainColor::TerrainColor() {

}

TerrainColor::TerrainColor(GUI::Settings s) {
    oceanElevation = 0.0;
    coastElevation = 0.4;
    beachElevation = 0.5;
    plainElevation = 0.55;
    forestElevation = 0.75;
    hillElevation = 0.85;
    mountainElevation = 1.0;

    oceanColor = s.oceanColor;
    coastColor = s.coastColor;
    beachColor = s.beachColor;
    plainColor = s.plainColor;
    forestColor = s.forestColor;
    hillColor = s.hillColor;
    mountainColor = s.mountainColor;
}

void TerrainColor::calculateColor(float triangleElevation) {
    this->triangleElevation = triangleElevation;

    if (triangleElevation < coastElevation) {
        interpolateColor(oceanElevation, coastElevation, oceanColor, coastColor);
    }
    else if (triangleElevation < beachElevation) {
        interpolateColor(coastElevation, beachElevation, coastColor, beachColor);
    }
    else if (triangleElevation < plainElevation) {
        interpolateColor(beachElevation, plainElevation, beachColor, plainColor);
    }
    else if (triangleElevation < forestElevation) {
        interpolateColor(plainElevation, forestElevation, plainColor, forestColor);
    }
    else if (triangleElevation < hillElevation) {
        interpolateColor(forestElevation, hillElevation, forestColor, hillColor);
    }
    else {
        interpolateColor(hillElevation, mountainElevation, hillColor, mountainColor);
    }
}

void TerrainColor::interpolateColor(float lowElevation, float highElevation, ofColor lowColor, ofColor highColor) {
    triangleColor.r = ofMap(triangleElevation, lowElevation, highElevation, lowColor.r, highColor.r);
    triangleColor.g = ofMap(triangleElevation, lowElevation, highElevation, lowColor.g, highColor.g);
    triangleColor.b = ofMap(triangleElevation, lowElevation, highElevation, lowColor.b, highColor.b);
}

ofColor TerrainColor::getColor() {
    return triangleColor;
}
