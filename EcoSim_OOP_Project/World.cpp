#include "World.h"
#include "Plant.h"
#include "Animal.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <typeinfo>

World::World(int width, int height)
    : width(width), height(height), turn(0), deathsThisTurn(0), birthsThisTurn(0), weather("Sunny"),
      resources(height, std::vector<Resource>(width)), rng(std::random_device{}()) {}

int World::getWidth() const { return width; }
int World::getHeight() const { return height; }
int World::getTurn() const { return turn; }
std::string World::getWeather() const { return weather; }

bool World::isInside(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

int World::randomInt(int minValue, int maxValue) {
    std::uniform_int_distribution<int> dist(minValue, maxValue);
    return dist(rng);
}

Resource& World::getResourceAt(int x, int y) {
    return resources[y][x];
}

const std::vector<std::shared_ptr<Organism>>& World::getOrganisms() const {
    return organisms;
}

void World::addOrganism(std::shared_ptr<Organism> organism) {
    organisms.push_back(organism);
}

void World::seedDefaultWorld() {
    organisms.clear();

    for (int i = 0; i < 45; i++) {
        addOrganism(std::make_shared<Plant>(randomInt(0, width - 1), randomInt(0, height - 1)));
    }
    for (int i = 0; i < 12; i++) {
        addOrganism(std::make_shared<Animal>("Rabbit", randomInt(0, width - 1), randomInt(0, height - 1), false));
    }
    for (int i = 0; i < 4; i++) {
        addOrganism(std::make_shared<Animal>("Wolf", randomInt(0, width - 1), randomInt(0, height - 1), true));
    }
}

void World::generateWeather() {
    int roll = randomInt(1, 100);
    if (roll <= 40) weather = "Sunny";
    else if (roll <= 65) weather = "Cloudy";
    else if (roll <= 88) weather = "Rainy";
    else weather = "Drought";
}

void World::regenerateResources() {
    double waterBonus = 0.0;
    double sunlightBonus = 0.0;

    if (weather == "Sunny") {
        sunlightBonus = 5.0;
        waterBonus = -1.0;
    } else if (weather == "Cloudy") {
        sunlightBonus = 1.0;
        waterBonus = 1.0;
    } else if (weather == "Rainy") {
        sunlightBonus = -1.0;
        waterBonus = 7.0;
    } else if (weather == "Drought") {
        sunlightBonus = 6.0;
        waterBonus = -4.0;
    }

    for (auto& row : resources) {
        for (auto& resource : row) {
            resource.regenerate(waterBonus, sunlightBonus);
        }
    }
}

bool World::spawnPlantNear(int x, int y) {
    for (int i = 0; i < 8; i++) {
        int nx = x + randomInt(-1, 1);
        int ny = y + randomInt(-1, 1);
        if (isInside(nx, ny)) {
            organisms.push_back(std::make_shared<Plant>(nx, ny));
            return true;
        }
    }
    return false;
}

bool World::spawnAnimalNear(int x, int y, const std::string& species, bool carnivore) {
    for (int i = 0; i < 8; i++) {
        int nx = x + randomInt(-1, 1);
        int ny = y + randomInt(-1, 1);
        if (isInside(nx, ny)) {
            organisms.push_back(std::make_shared<Animal>(species, nx, ny, carnivore));
            return true;
        }
    }
    return false;
}

bool World::eatPlantAt(int x, int y) {
    for (auto& organism : organisms) {
        if (organism->isAlive() && organism->getType() == "Plant" && organism->getX() == x && organism->getY() == y) {
            organism->die();
            return true;
        }
    }
    return false;
}

bool World::huntHerbivoreAt(int x, int y) {
    for (auto& organism : organisms) {
        if (organism->isAlive() && organism->getType() == "Herbivore" && organism->getX() == x && organism->getY() == y) {
            organism->die();
            return true;
        }
    }
    return false;
}

int World::countAnimalsAt(int x, int y) const {
    int count = 0;
    for (const auto& organism : organisms) {
        if (organism->isAlive() && organism->getType() != "Plant" && organism->getX() == x && organism->getY() == y) {
            count++;
        }
    }
    return count;
}

int World::countNearbySameSpecies(int x, int y, const std::string& species) const {
    int count = 0;
    for (const auto& organism : organisms) {
        if (!organism->isAlive() || organism->getSpecies() != species) continue;
        if (organism->getX() == x && organism->getY() == y) continue;
        int dx = std::abs(organism->getX() - x);
        int dy = std::abs(organism->getY() - y);
        if (dx <= 1 && dy <= 1) count++;
    }
    return count;
}

void World::recordBirth() {
    birthsThisTurn++;
}

void World::removeDeadOrganisms() {
    int before = static_cast<int>(organisms.size());
    organisms.erase(
        std::remove_if(organisms.begin(), organisms.end(), [](const std::shared_ptr<Organism>& o) {
            return !o->isAlive();
        }),
        organisms.end()
    );
    int after = static_cast<int>(organisms.size());
    deathsThisTurn += before - after;
}

void World::simulateTurn() {
    turn++;
    deathsThisTurn = 0;
    birthsThisTurn = 0;

    generateWeather();
    regenerateResources();

    // 使用快照避免本回合新生物馬上行動，讓回合邏輯更穩定。
    std::vector<std::shared_ptr<Organism>> currentOrganisms = organisms;
    for (auto& organism : currentOrganisms) {
        if (organism->isAlive()) {
            organism->act(*this);
        }
    }

    removeDeadOrganisms();
}

void World::printMap() const {
    std::vector<std::vector<char>> grid(height, std::vector<char>(width, '.'));

    for (const auto& organism : organisms) {
        if (!organism->isAlive()) continue;
        int x = organism->getX();
        int y = organism->getY();
        if (!isInside(x, y)) continue;

        // 若同格有多個生物，用 * 表示競爭或重疊。
        if (grid[y][x] != '.') grid[y][x] = '*';
        else grid[y][x] = organism->getSymbol();
    }

    std::cout << "\n===== EcoSim Map UI =====\n";
    std::cout << "Legend: G=Grass, R=Rabbit, W=Wolf, *=Multiple, .=Empty\n\n";
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << grid[y][x] << ' ';
        }
        std::cout << '\n';
    }
}

void World::printStatistics() const {
    int plants = 0;
    int herbivores = 0;
    int carnivores = 0;
    double totalEnergy = 0.0;

    for (const auto& organism : organisms) {
        if (organism->getType() == "Plant") plants++;
        else if (organism->getType() == "Herbivore") herbivores++;
        else if (organism->getType() == "Carnivore") carnivores++;
        totalEnergy += organism->getEnergy();
    }

    double averageEnergy = organisms.empty() ? 0.0 : totalEnergy / organisms.size();

    std::cout << "\n===== Turn Statistics =====\n";
    std::cout << "Turn: " << turn << '\n';
    std::cout << "Weather: " << weather << '\n';
    std::cout << "Plants: " << plants << '\n';
    std::cout << "Rabbits: " << herbivores << '\n';
    std::cout << "Wolves: " << carnivores << '\n';
    std::cout << "Total organisms: " << organisms.size() << '\n';
    std::cout << "Average energy: " << std::fixed << std::setprecision(2) << averageEnergy << '\n';
    std::cout << "Deaths this turn: " << deathsThisTurn << '\n';
    std::cout << "Births this turn: " << birthsThisTurn << '\n';
}

void World::printResourcesSummary() const {
    double total = 0.0;
    for (const auto& row : resources) {
        for (const auto& r : row) {
            total += r.average();
        }
    }
    double average = total / (width * height);
    std::cout << "\nAverage resource level: " << std::fixed << std::setprecision(2) << average << "/100\n";
}
