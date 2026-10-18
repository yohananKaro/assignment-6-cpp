/**
 * @file Reptile.cpp
 * @brief Implementation of the Reptile class.
 */

#include "Reptile.hpp"

#include <iostream>
#include <stdexcept>

namespace zoo {

// ---- Constructor ----
Reptile::Reptile(const std::string& name, int age, const std::string& species,
                 bool isVenomous, double bodyLengthCm)
    : Animal(name, age, species),
      isVenomous_(isVenomous),
      bodyLengthCm_(bodyLengthCm)
{
    if (bodyLengthCm <= 0.0) {
        throw std::invalid_argument("Body length must be greater than zero.");
    }
    std::cout << "Reptile constructed: " << getName() << "\n";
}

// ---- Copy constructor ----
Reptile::Reptile(const Reptile& other)
    : Animal(other),
      isVenomous_(other.isVenomous_),
      bodyLengthCm_(other.bodyLengthCm_)
{
    std::cout << "Reptile copy-constructed: " << getName() << "\n";
}

// ---- Destructor ----
Reptile::~Reptile()
{
    std::cout << "Reptile destructed: " << getName() << "\n";
}

// ---- Clone ----
Animal* Reptile::clone() const { return new Reptile(*this); } // NOLINT(cppcoreguidelines-owning-memory)

// ---- Pure virtual overrides ----
std::string Reptile::makeSound() const
{
    return isVenomous_ ? "Hisss!" : "...";
}

std::string Reptile::getAnimalType() const
{
    return "Reptile";
}

std::string Reptile::getDiet() const
{
    return isVenomous_ ? "Rodents and eggs" : "Insects and plants";
}

// ---- Getters ----
bool   Reptile::getIsVenomous()   const { return isVenomous_; }
double Reptile::getBodyLengthCm() const { return bodyLengthCm_; }

// ---- Setters ----
void Reptile::setVenomous(bool isVenomous)
{
    isVenomous_ = isVenomous;
}

void Reptile::setBodyLengthCm(double bodyLengthCm)
{
    if (bodyLengthCm <= 0.0) {
        throw std::invalid_argument("Body length must be greater than zero.");
    }
    bodyLengthCm_ = bodyLengthCm;
}

} // namespace zoo
