#ifndef ANIMAL_H
#define ANIMAL_H

#include "Organism.h"

class Animal : public Organism {
private:
    bool carnivore;
    int reproduceCooldown;

    void move(World& world);
    void eat(World& world);
    void compete(World& world);
    void cooperate(World& world);

public:
    Animal(const std::string& species, int x, int y, bool carnivore = false);

    void act(World& world) override;
    char getSymbol() const override;
    std::string getType() const override;
    bool isCarnivore() const;
};

#endif
