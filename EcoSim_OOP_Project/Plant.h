#ifndef PLANT_H
#define PLANT_H

#include "Organism.h"

class Plant : public Organism {
private:
    int reproduceCooldown;

public:
    Plant(int x = 0, int y = 0);

    void act(World& world) override;
    char getSymbol() const override;
    std::string getType() const override;
};

#endif
