#ifndef ENTITY_H
#define ENTITY_H

#include <utility>

class Entity {
private:
    int x;
    int y;

public:
    Entity(int x = 0, int y = 0);
    virtual ~Entity() = default;

    std::pair<int, int> getPosition() const;
    int getX() const;
    int getY() const;
    void setPosition(int newX, int newY);
};

#endif
