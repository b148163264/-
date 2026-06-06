#include "Organism.h"
#include <algorithm>

Organism::Organism(const std::string& species, int x, int y, int hp, double energy)
    : Entity(x, y), hp(hp), energy(energy), age(0), alive(true), species(species) {}

void Organism::grow() {
    age++;
    if (age > 80) {
        consumeEnergy(2.0);
    }
}

void Organism::die() {
    alive = false;
}

void Organism::consumeEnergy(double amount) {
    energy -= amount;
    if (energy <= 0 || hp <= 0) {
        die();
    }
}

void Organism::addEnergy(double amount) {
    energy = std::min(150.0, energy + amount);
}

void Organism::addHp(int amount) {
    hp = std::min(100, hp + amount);
}

void Organism::damage(int amount) {
    hp -= amount;
    if (hp <= 0) {
        die();
    }
}

int Organism::getHp() const { return hp; }
double Organism::getEnergy() const { return energy; }
int Organism::getAge() const { return age; }
bool Organism::isAlive() const { return alive; }
std::string Organism::getSpecies() const { return species; }

void Organism::setEnergy(double value) {
    energy = value;
    if (energy <= 0) die();
}
