#pragma once

#include <string>
#include "Vector2.h"

// Abstract base class for game objects
class GameObject 
{
    private:         

    protected:
        std::string tag;
        Vector2<int> position;

    public:
        GameObject(const Vector2<int>& location) : tag(tag), position(location) {}

        virtual void update() = 0;

        virtual ~GameObject() {}

        std::string getTag() const { return tag; }

        Vector2<int> getPosition() const { return position; }

        void setPosition(const Vector2<int>& newLocation) { position = newLocation; }

        void setTag(const std::string& newTag) { tag = newTag; }
};
