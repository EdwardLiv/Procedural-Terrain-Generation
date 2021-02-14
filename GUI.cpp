#include "GUI.h"

GUI::GUI() {
    isAnySettingChanged = true;

    generalSettingsPanel.setup("General settings");

    generalSettingsPanel.add(seedSlider.setup("Seed", 1, 1, 100));
    seedSlider.addListener(this, &GUI::seedSliderChanged);

    generalSettingsPanel.add(tileSizeSlider.setup("Tile size", 50, 20, 80));
    tileSizeSlider.addListener(this, &GUI::tileSizeSliderChanged);

    generalSettingsPanel.add(mapWidthSlider.setup("Map width", 3000, 1000, 5000));
    mapWidthSlider.addListener(this, &GUI::mapWidthSliderChanged);

    generalSettingsPanel.add(mapHeightSlider.setup("Map height", 3000, 1000, 5000));
    mapHeightSlider.addListener(this, &GUI::mapHeightSliderChanged);

    noiseSettingsPanel.setup("Noise settings");
    noiseSettingsPanel.setPosition(10, 120);

    noiseSettingsPanel.add(octavesSlider.setup("Octaves", 5, 1, 9));
    octavesSlider.addListener(this, &GUI::octavesSliderChanged);

    noiseSettingsPanel.add(noiseScaleSlider.setup("Noise scale", 1.0, 0.5, 1.5));
    noiseScaleSlider.addListener(this, &GUI::noiseScaleSliderChanged);

    noiseSettingsPanel.add(lacunaritySlider.setup("Lacunarity", 2.0, 1.0, 3.0));
    lacunaritySlider.addListener(this, &GUI::lacunaritySliderChanged);

    noiseSettingsPanel.add(persistenceSlider.setup("Persistence", 0.5, 0.25, 0.75));
    persistenceSlider.addListener(this, &GUI::persistenceSliderChanged);

    elevationSettingsPanel.setup("Elevation settings");
    elevationSettingsPanel.setPosition(10, 230);

    elevationSettingsPanel.add(maxElevationSlider.setup("Max elevation", 500, 1, 1000));
    maxElevationSlider.addListener(this, &GUI::maxElevationSliderChanged);

    elevationSettingsPanel.add(flattenElevationSlider.setup("Flatten elevation", 1.0, 1.0, 3.0));
    flattenElevationSlider.addListener(this, &GUI::flattenElevationSliderChanged);

    mapTypesPanel.setup("Map types");
    mapTypesPanel.setPosition(10, 300);

    mapTypesPanel.add(isStandardMapToggle.setup("Standard", true));
    isStandardMapToggle.addListener(this, &GUI::isStandardMapToggleChanged);

    mapTypesPanel.add(isIslandMapToggle.setup("Island", false));
    isIslandMapToggle.addListener(this, &GUI::isIslandMapToggleChanged);

    mapTypesPanel.add(isLakeMapToggle.setup("Lake", false));
    isLakeMapToggle.addListener(this, &GUI::isLakeMapToggleChanged);

    colorPalettePanel.setup("Color palette");
    colorPalettePanel.setPosition(10, 390);

    colorPalettePanel.add(oceanColorPicker.set("Ocean", ofColor(100, 90, 255), ofColor(0, 0, 0), ofColor(255, 255, 255)));
    oceanColorPicker.addListener(this, &GUI::isOceanColorPickerChanged);

    colorPalettePanel.add(coastColorPicker.set("Coast", ofColor(60, 190, 255), ofColor(0, 0, 0), ofColor(255, 255, 255)));
    coastColorPicker.addListener(this, &GUI::isCoastColorPickerChanged);

    colorPalettePanel.add(beachColorPicker.set("Beach", ofColor(240, 240, 170), ofColor(0, 0, 0), ofColor(255, 255, 255)));
    beachColorPicker.addListener(this, &GUI::isBeachColorPickerChanged);

    colorPalettePanel.add(plainColorPicker.set("Plain", ofColor(140, 190, 90), ofColor(0, 0, 0), ofColor(255, 255, 255)));
    plainColorPicker.addListener(this, &GUI::isPlainColorPickerChanged);

    colorPalettePanel.add(forestColorPicker.set("Forest", ofColor(60, 100, 60), ofColor(0, 0, 0), ofColor(255, 255, 255)));
    forestColorPicker.addListener(this, &GUI::isForestColorPickerChanged);

    colorPalettePanel.add(hillColorPicker.set("Hill", ofColor(150, 150, 150), ofColor(0, 0, 0), ofColor(255, 255, 255)));
    hillColorPicker.addListener(this, &GUI::isHillColorPickerChanged);

    colorPalettePanel.add(mountainColorPicker.set("Mountain", ofColor(255, 255, 255), ofColor(0, 0, 0), ofColor(255, 255, 255)));
    mountainColorPicker.addListener(this, &GUI::isMountainColorPickerChanged);
}

GUI::Settings GUI::getSettings(void) {
    struct Settings s;

    s.seed = seedSlider;
    s.tileSize = tileSizeSlider;
    s.mapWidth = mapWidthSlider;
    s.mapHeight = mapHeightSlider;
    s.octaves = octavesSlider;
    s.noiseScale = noiseScaleSlider;
    s.lacunarity = lacunaritySlider;
    s.persistence = persistenceSlider;
    s.maxElevation = maxElevationSlider;
    s.flattenElevation = flattenElevationSlider;
    s.oceanColor = oceanColorPicker;
    s.coastColor = coastColorPicker;
    s.beachColor = beachColorPicker;
    s.plainColor = plainColorPicker;
    s.forestColor = forestColorPicker;
    s.hillColor = hillColorPicker;
    s.mountainColor = mountainColorPicker;

    if (isLakeMapToggle) {
        s.mapType = 2;
    }
    else if (isIslandMapToggle) {
        s.mapType = 1;
    }
    else {
        s.mapType = 0;
    }

    return s;
}

void GUI::draw() {
    ofDisableDepthTest();
    generalSettingsPanel.draw();
    noiseSettingsPanel.draw();
    elevationSettingsPanel.draw();
    mapTypesPanel.draw();
    colorPalettePanel.draw();
    ofEnableDepthTest();
}

void GUI::setIsAnySettingChanged() {
    isAnySettingChanged = !isAnySettingChanged;
}

bool GUI::getIsAnySettingChanged() {
    return isAnySettingChanged;
}

void GUI::seedSliderChanged(int& seedSlider) {
    isAnySettingChanged = true;
}

void GUI::tileSizeSliderChanged(int& tileSizeSlider) {
    isAnySettingChanged = true;
}

void GUI::mapWidthSliderChanged(int& mapWidthSlider) {
    isAnySettingChanged = true;
}

void GUI::mapHeightSliderChanged(int& mapHeightSlider) {
    isAnySettingChanged = true;
}

void GUI::octavesSliderChanged(int& octavesSlider) {
    isAnySettingChanged = true;
}

void GUI::noiseScaleSliderChanged(float& noiseScaleSlider) {
    isAnySettingChanged = true;
}

void GUI::lacunaritySliderChanged(float& lacunaritySlider) {
    isAnySettingChanged = true;
}

void GUI::persistenceSliderChanged(float& persistenceSlider) {
    isAnySettingChanged = true;
}

void GUI::maxElevationSliderChanged(int& maxElevationSlider) {
    isAnySettingChanged = true;
}

void GUI::flattenElevationSliderChanged(float& flattenElevationSlider) {
    isAnySettingChanged = true;
}

void GUI::isOceanColorPickerChanged(ofColor& oceanColorPicker) {
    isAnySettingChanged = true;
}

void GUI::isCoastColorPickerChanged(ofColor& coastColorPicker) {
    isAnySettingChanged = true;
}

void GUI::isBeachColorPickerChanged(ofColor& beachColorPicker) {
    isAnySettingChanged = true;
}

void GUI::isPlainColorPickerChanged(ofColor& plainColorPicker) {
    isAnySettingChanged = true;
}

void GUI::isForestColorPickerChanged(ofColor& forestColorPicker) {
    isAnySettingChanged = true;
}

void GUI::isHillColorPickerChanged(ofColor& hillColorPicker) {
    isAnySettingChanged = true;
}

void GUI::isMountainColorPickerChanged(ofColor& mountainColorPicker) {
    isAnySettingChanged = true;
}

void GUI::isStandardMapToggleChanged(bool& isStandardMapToggle) {
    isStandardMapToggle = true;
    isAnySettingChanged = true;

    isIslandMapToggle.removeListener(this, &GUI::isIslandMapToggleChanged);
    isIslandMapToggle = false;
    isIslandMapToggle.addListener(this, &GUI::isIslandMapToggleChanged);

    isLakeMapToggle.removeListener(this, &GUI::isLakeMapToggleChanged);
    isLakeMapToggle = false;
    isLakeMapToggle.addListener(this, &GUI::isLakeMapToggleChanged);
}

void GUI::isIslandMapToggleChanged(bool& isIslandMapToggle) {
    isIslandMapToggle = true;
    isAnySettingChanged = true;

    isStandardMapToggle.removeListener(this, &GUI::isStandardMapToggleChanged);
    isStandardMapToggle = false;
    isStandardMapToggle.addListener(this, &GUI::isStandardMapToggleChanged);

    isLakeMapToggle.removeListener(this, &GUI::isLakeMapToggleChanged);
    isLakeMapToggle = false;
    isLakeMapToggle.addListener(this, &GUI::isLakeMapToggleChanged);
}

void GUI::isLakeMapToggleChanged(bool& isLakeMapToggle) {
    isLakeMapToggle = true;
    isAnySettingChanged = true;

    isStandardMapToggle.removeListener(this, &GUI::isStandardMapToggleChanged);
    isStandardMapToggle = false;
    isStandardMapToggle.addListener(this, &GUI::isStandardMapToggleChanged);

    isIslandMapToggle.removeListener(this, &GUI::isIslandMapToggleChanged);
    isIslandMapToggle = false;
    isIslandMapToggle.addListener(this, &GUI::isIslandMapToggleChanged);
}
