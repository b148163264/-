#ifndef RESOURCE_H
#define RESOURCE_H

#include <algorithm>

class Resource {
private:
    double water;
    double sunlight;
    double nutrient;

public:
    Resource(double water = 60.0, double sunlight = 60.0, double nutrient = 60.0);

    double getWater() const;
    double getSunlight() const;
    double getNutrient() const;

    bool consume(double waterAmount, double sunlightAmount, double nutrientAmount);
    void regenerate(double weatherWaterBonus, double weatherSunlightBonus);
    double average() const;
};

#endif
