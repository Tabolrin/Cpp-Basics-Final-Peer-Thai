#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include "Vector2.h"

// Abstract base class for game objects
class GameObject
{
private:
    std::string tag;          // Tag to identify the game object
    Vector2 worldLocation;    // 2D position in the game world

public:
    // Constructor to initialize tag and worldLocation
    GameObject(const std::string& tag, const Vector2& location)
        : tag(tag), worldLocation(location) {
    }

    // Pure virtual function to make the class abstract
    virtual void update() = 0;

    // Virtual destructor for proper cleanup
    virtual ~GameObject() {}

    // Inline getter for tag
    std::string getTag() const { return tag; }

    // Inline setter for tag (restricted to class scope or friends)
    void setTag(const std::string& newTag) { tag = newTag; }

    // Inline getter for worldLocation
    Vector2 getWorldLocation() const { return worldLocation; }

    // Inline setter for worldLocation
    void setWorldLocation(const Vector2& newLocation) { worldLocation = newLocation; }
};

#endif