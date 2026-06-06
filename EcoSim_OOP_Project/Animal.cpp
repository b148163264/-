#include "Animal.h"
#include "World.h"
#include <cstdlib>

Animal::Animal(const std::string& species, int x, int y, bool carnivore)
    : Organism(species, x, y, carnivore ? 70 : 55, carnivore ? 70.0 : 55.0),
      carnivore(carnivore), reproduceCooldown(0) {}

void Animal::act(World& world) {
    grow();
    consumeEnergy(carnivore ? 4.0 : 3.0);
    if (!isAlive()) return;

    move(world);
    eat(world);
    compete(world);
    cooperate(world);

    if (reproduceCooldown > 0) reproduceCooldown--;

    double threshold = carnivore ? 110.0 : 95.0;
    if (getEnergy() >= threshold && reproduceCooldown == 0) {
        if (world.spawnAnimalNear(getX(), getY(), getSpecies(), carnivore)) {
            setEnergy(getEnergy() - 45.0);
            reproduceCooldown = 4;
            world.recordBirth();
        }
    }
}

void Animal::move(World& world) {
    int dx[5] = {0, 1, -1, 0, 0};
    int dy[5] = {0, 0, 0, 1, -1};
    int dir = world.randomInt(0, 4);
    int nx = getX() + dx[dir];
    int ny = getY() + dy[dir];

    if (world.isInside(nx, ny)) {
        setPosition(nx, ny);
    }
}

void Animal::eat(World& world) {
    if (carnivore) {
        if (world.huntHerbivoreAt(getX(), getY())) {
            addEnergy(35.0);
        } else {
            consumeEnergy(2.5);
        }
    } else {
        if (world.eatPlantAt(getX(), getY())) {
            addEnergy(25.0);
        } else {
            consumeEnergy(1.5);
        }
    }
}

void Animal::compete(World& world) {
    int animalsHere = world.countAnimalsAt(getX(), getY());
    if (animalsHere >= 2) {
        consumeEnergy((animalsHere - 1) * 2.0);
    }
}

void Animal::cooperate(World& world) {
    int sameNearby = world.countNearbySameSpecies(getX(), getY(), getSpecies());
    if (sameNearby > 0) {
        addEnergy(1.5);
        addHp(1);
    }
}

char Animal::getSymbol() const {
    return carnivore ? 'W' : 'R';
}

std::string Animal::getType() const {
    return carnivore ? "Carnivore" : "Herbivore";
}

bool Animal::isCarnivore() const {
    return carnivore;
}
