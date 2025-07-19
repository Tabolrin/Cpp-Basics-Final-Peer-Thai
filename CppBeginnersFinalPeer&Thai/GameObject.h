#pragma once

#include <string>
#include "Vector2.h"

// Abstract base class for game objects
class GameObject 
{
    private:
        std::string tag;          
        Vector2<int> worldLocation; // Specify the template argument for Vector2

    protected:
        void setWorldLocation(const Vector2<int>& newLocation) { worldLocation = newLocation; }

        void setTag(const std::string& newTag) { tag = newTag; }

    public:
        GameObject(const std::string& tag, const Vector2<int>& location) : tag(tag), worldLocation(location) {}

        virtual void update() = 0;

        virtual ~GameObject() {}

        std::string getTag() const { return tag; }

        Vector2<int> getWorldLocation() const { return worldLocation; }
};
