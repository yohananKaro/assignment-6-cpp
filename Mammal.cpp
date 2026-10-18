/**
 * @file Mammal.cpp
 * @brief Implementation of the Mammal class.
 */

#include "Mammal.hpp"

#include <iostream>
#include <stdexcept>

namespace zoo {

// ---- Constructor ----
Mammal::Mammal(const std::string& name, int age, const std::string& species,
               bool isDomesticated, int numberOfLegs)
    : Animal(name, age, species),
      isDomesticated_(isDomesticated),
      numberOfLegs_(numberOfLegs)
{
    if (numberOfLegs < 0) {
        throw std::invalid_argument("Number of legs cannot be negative.");
    }
    std::cout << "Mammal constructed: " << getName() << "\n";
}

// ---- Copy constructor ----
Mammal::Mammal(const Mammal& other)
    : Animal(other),
      isDomesticated_(other.isDomesticated_),
      numberOfLegs_(other.numberOfLegs_)
{
    std::cout << "Mammal copy-constructed: " << getName() << "\n";
}

// ---- Destructor ----
Mammal::~Mammal()
{
    std::cout << "Mammal destructed: " << getName() << "\n";
}

// ---- Clone ----
Animal* Mammal::clone() const { return new Mammal(*this); } // NOLINT(cppcoreguidelines-owning-memory)

// ---- Pure virtual overrides ----
std::string Mammal::makeSound() const
{
    return isDomesticated_ ? "Purr..." : "Roar!";
}

std::string Mammal::getAnimalType() const
{
    return "Mammal";
}

std::string Mammal::getDiet() const
{
    return isDomesticated_ ? "Meat and plants" : "Meat";
}

// ---- Getters ----
bool Mammal::getIsDomesticated() const { return isDomesticated_; }
int  Mammal::getNumberOfLegs()   const { return numberOfLegs_; }

// ---- Setters ----
void Mammal::setDomesticated(bool isDomesticated)
{
    isDomesticated_ = isDomesticated;
}

void Mammal::setNumberOfLegs(int numberOfLegs)
{
    if (numberOfLegs < 0) {
        throw std::invalid_argument("Number of legs cannot be negative.");
    }
    numberOfLegs_ = numberOfLegs;
}

} // namespace zoo
