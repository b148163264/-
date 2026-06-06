#include "Resource.h"

Resource::Resource(double water, double sunlight, double nutrient)
    : water(water), sunlight(sunlight), nutrient(nutrient) {}

double Resource::getWater() const { return water; }
double Resource::getSunlight() const { return sunlight; }
double Resource::getNutrient() const { return nutrient; }

bool Resource::consume(double waterAmount, double sunlightAmount, double nutrientAmount) {
    if (water < waterAmount || sunlight < sunlightAmount || nutrient < nutrientAmount) {
        return false;
    }

    water -= waterAmount;
    sunlight -= sunlightAmount;
    nutrient -= nutrientAmount;
    return true;
}

void Resource::regenerate(double weatherWaterBonus, double weatherSunlightBonus) {
    water = std::min(100.0, water + 3.0 + weatherWaterBonus);
    sunlight = std::min(100.0, sunlight + 3.0 + weatherSunlightBonus);
    nutrient = std::min(100.0, nutrient + 1.5);
}

double Resource::average() const {
    return (water + sunlight + nutrient) / 3.0;
}
