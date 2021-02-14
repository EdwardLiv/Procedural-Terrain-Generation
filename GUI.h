#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class GUI {
	private:
		bool isAnySettingChanged;

		ofxPanel generalSettingsPanel;
		ofxIntSlider seedSlider;
		ofxIntSlider tileSizeSlider;
		ofxIntSlider mapWidthSlider;
		ofxIntSlider mapHeightSlider;

		ofxPanel noiseSettingsPanel;
		ofxIntSlider octavesSlider;
		ofxFloatSlider noiseScaleSlider;
		ofxFloatSlider lacunaritySlider;
		ofxFloatSlider persistenceSlider;

		ofxPanel elevationSettingsPanel;
		ofxIntSlider maxElevationSlider;
		ofxFloatSlider flattenElevationSlider;

		ofxPanel mapTypesPanel;
		ofxToggle isStandardMapToggle;
		ofxToggle isIslandMapToggle;
		ofxToggle isLakeMapToggle;

		ofxPanel colorPalettePanel;
		ofParameter<ofColor> oceanColorPicker;
		ofParameter<ofColor> coastColorPicker;
		ofParameter<ofColor> beachColorPicker;
		ofParameter<ofColor> plainColorPicker;
		ofParameter<ofColor> forestColorPicker;
		ofParameter<ofColor> hillColorPicker;
		ofParameter<ofColor> mountainColorPicker;

	public:
		GUI();

		struct Settings {
			int seed;
			int tileSize;
			int mapWidth;
			int mapHeight;
			int octaves;
			float noiseScale;
			float lacunarity;
			float persistence;
			int maxElevation;
			float flattenElevation;
			int mapType;
			ofColor oceanColor;
			ofColor coastColor;
			ofColor beachColor;
			ofColor plainColor;
			ofColor forestColor;
			ofColor hillColor;
			ofColor mountainColor;
		};

		struct Settings getSettings();

		void draw();

		void setIsAnySettingChanged();
		bool getIsAnySettingChanged();

		void seedSliderChanged(int& seedSlider);
		void tileSizeSliderChanged(int& tileSizeSlider);
		void mapWidthSliderChanged(int& mapWidthSlider);
		void mapHeightSliderChanged(int& mapHeightSlider);
		void octavesSliderChanged(int& octavesSlider);
		void noiseScaleSliderChanged(float& noiseScaleSlider);
		void lacunaritySliderChanged(float& lacunaritySlider);
		void persistenceSliderChanged(float& persistenceSlider);
		void maxElevationSliderChanged(int& maxElevationSlider);
		void flattenElevationSliderChanged(float& flattenElevationSlider);
		void isStandardMapToggleChanged(bool& isStandardMapToggle);
		void isIslandMapToggleChanged(bool& isIslandMapToggle);
		void isLakeMapToggleChanged(bool& isLakeMapToggle);
		void isOceanColorPickerChanged(ofColor& oceanColorPicker);
		void isCoastColorPickerChanged(ofColor& coastColorPicker);
		void isBeachColorPickerChanged(ofColor& beachColorPicker);
		void isPlainColorPickerChanged(ofColor& plainColorPicker);
		void isForestColorPickerChanged(ofColor& forestColorPicker);
		void isHillColorPickerChanged(ofColor& hillColorPicker);
		void isMountainColorPickerChanged(ofColor& mountainColorPicker);
};
