#ifndef ORGANISM_H
#define ORGANISM_H

#include "Entity.h"
#include <string>

class World;

class Organism : public Entity {
private:
    int hp;
    double energy;
    int age;
    bool alive;
    std::string species;

public:
    Organism(const std::string& species, int x, int y, int hp, double energy);
    virtual ~Organism() = default;

    virtual void act(World& world) = 0;
    virtual char getSymbol() const = 0;
    virtual std::string getType() const = 0;

    void grow();
    void die();
    void consumeEnergy(double amount);
    void addEnergy(double amount);
    void addHp(int amount);
    void damage(int amount);

    int getHp() const;
    double getEnergy() const;
    int getAge() const;
    bool isAlive() const;
    std::string getSpecies() const;

    void setEnergy(double value);
};

#endif
