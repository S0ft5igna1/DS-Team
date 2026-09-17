// Resource.h
#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

class Resource {
    private:
        int id;
        std::string name;
        std::string type;
        bool isAvailable;

    public:
        Resource(int resourceId, const std::string& resourceName, const std::string& resourceType, bool availability)
            : id(resourceId), name(resourceName), type(resourceType), isAvailable(availability) {}

        int getId() const {
            return id;
        }

        std::string getName() const {
            return name;
        }

        std::string getType() const {
            return type;
        }

        bool getAvailability() const {
            return isAvailable;
        }

    };
    #endif
