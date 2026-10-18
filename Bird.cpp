/**
 * @file Bird.cpp
 * @brief Implementation of the Bird class.
 */

#include "Bird.hpp"

#include <iostream>
#include <stdexcept>

namespace zoo {

// ---- Constructor ----
Bird::Bird(const std::string& name, int age, const std::string& species,
           bool canFly, double wingspanMeters)
    : Animal(name, age, species),
      canFly_(canFly),
      wingspanMeters_(wingspanMeters)
{
    if (wingspanMeters <= 0.0) {
        throw std::invalid_argument("Wingspan must be greater than zero.");
    }
    std::cout << "Bird constructed: " << getName() << "\n";
}

// ---- Copy constructor ----
Bird::Bird(const Bird& other)
    : Animal(other),
      canFly_(other.canFly_),
      wingspanMeters_(other.wingspanMeters_)
{
    std::cout << "Bird copy-constructed: " << getName() << "\n";
}

// ---- Destructor ----
Bird::~Bird()
{
    std::cout << "Bird destructed: " << getName() << "\n";
}

// ---- Clone ----
Animal* Bird::clone() const { return new Bird(*this); } // NOLINT(cppcoreguidelines-owning-memory)

// ---- Pure virtual overrides ----
std::string Bird::makeSound() const
{
    return canFly_ ? "Tweet tweet!" : "Squawk!";
}

std::string Bird::getAnimalType() const
{
    return "Bird";
}

std::string Bird::getDiet() const
{
    return "Seeds and insects";
}

// ---- Getters ----
bool   Bird::getCanFly()         const { return canFly_; }
double Bird::getWingspanMeters() const { return wingspanMeters_; }

// ---- Setters ----
void Bird::setCanFly(bool canFly)
{
    canFly_ = canFly;
}

void Bird::setWingspanMeters(double wingspanMeters)
{
    if (wingspanMeters <= 0.0) {
        throw std::invalid_argument("Wingspan must be greater than zero.");
    }
    wingspanMeters_ = wingspanMeters;
}

} // namespace zoo
