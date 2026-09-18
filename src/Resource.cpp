// Resource.cpp
#include "Resource.h"

Resource::Resource(int resourceId, const std::string& resourceName, const std::string& resourceType, bool availability)
    : id(resourceId), name(resourceName), type(resourceType), isAvailable(availability) {}
    

int Resource::getId() const {
    return id;
}

std::string Resource::getName() const {
    return name;
}

std::string Resource::getType() const {
    return type;
}

bool Resource::getAvailability() const {
    return isAvailable;
}