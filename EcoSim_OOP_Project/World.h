#ifndef WORLD_H
#define WORLD_H

#include "Resource.h"
#include "Organism.h"
#include <memory>
#include <random>
#include <string>
#include <vector>

class World {
private:
    int width;
    int height;
    int turn;
    int deathsThisTurn;
    int birthsThisTurn;
    std::string weather;
    std::vector<std::vector<Resource>> resources;
    std::vector<std::shared_ptr<Organism>> organisms;
    std::mt19937 rng;

    void generateWeather();
    void regenerateResources();
    void removeDeadOrganisms();

public:
    World(int width = 20, int height = 20);

    int getWidth() const;
    int getHeight() const;
    int getTurn() const;
    std::string getWeather() const;

    bool isInside(int x, int y) const;
    int randomInt(int minValue, int maxValue);

    Resource& getResourceAt(int x, int y);
    const std::vector<std::shared_ptr<Organism>>& getOrganisms() const;

    void addOrganism(std::shared_ptr<Organism> organism);
    bool spawnPlantNear(int x, int y);
    bool spawnAnimalNear(int x, int y, const std::string& species, bool carnivore);

    bool eatPlantAt(int x, int y);
    bool huntHerbivoreAt(int x, int y);
    int countAnimalsAt(int x, int y) const;
    int countNearbySameSpecies(int x, int y, const std::string& species) const;

    void recordBirth();
    void simulateTurn();
    void printMap() const;
    void printStatistics() const;
    void printResourcesSummary() const;
    void seedDefaultWorld();
};

#endif
