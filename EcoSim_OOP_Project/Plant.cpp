#include "Plant.h"
#include "World.h"

Plant::Plant(int x, int y)
    : Organism("Grass", x, y, 45, 35.0), reproduceCooldown(0) {}

void Plant::act(World& world) {
    grow();
    consumeEnergy(0.5);
    if (!isAlive()) return;

    Resource& r = world.getResourceAt(getX(), getY());
    int sameNearby = world.countNearbySameSpecies(getX(), getY(), getSpecies());
    double cooperationBonus = sameNearby > 0 ? 1.25 : 1.0;

    // 光合作用：消耗水、陽光、養分，換成能量與生命值。
    if (r.consume(2.0, 3.0, 1.0)) {
        addEnergy(8.0 * cooperationBonus);
        addHp(1);
    } else {
        consumeEnergy(3.0);
    }

    if (reproduceCooldown > 0) reproduceCooldown--;

    if (getEnergy() >= 80.0 && reproduceCooldown == 0) {
        if (world.spawnPlantNear(getX(), getY())) {
            setEnergy(getEnergy() - 35.0);
            reproduceCooldown = 3;
            world.recordBirth();
        }
    }
}

char Plant::getSymbol() const {
    return 'G';
}

std::string Plant::getType() const {
    return "Plant";
}
