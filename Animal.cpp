/**
 * @file Animal.cpp
 * @brief Implementation of the Animal abstract base class.
 */

#include "Animal.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

namespace zoo {

// ---- Static member definition ----
int Animal::animalCount_ = 0;

// ---- Constructor ----
Animal::Animal(const std::string& name, int age, const std::string& species)
    : name_(name), age_(age), species_(species)
{
    if (age < 0) {
        throw std::invalid_argument("Age cannot be negative.");
    }
    ++animalCount_;
    std::cout << species_ << " Animal constructed: " << name_ << "\n";
}

// ---- Copy constructor ----
Animal::Animal(const Animal& other)
    : name_(other.name_), age_(other.age_), species_(other.species_)
{
    ++animalCount_;
    std::cout << species_ << " Animal copy-constructed: " << name_ << "\n";
}

// ---- Destructor ----
Animal::~Animal()
{
    --animalCount_;
    std::cout << species_ << " Animal destructed: " << name_ << "\n";
}

// ---- Concrete methods ----
std::string Animal::getDescription() const
{
    return "[" + getAnimalType() + "] " + name_ +
           " (" + species_ + "), Age: " + std::to_string(age_) +
           ", Sound: " + makeSound() +
           ", Diet: " + getDiet();
}

// ---- Getters ----
std::string Animal::getName()    const { return name_; }
int         Animal::getAge()     const { return age_; }
std::string Animal::getSpecies() const { return species_; }

// ---- Setters ----
void Animal::setName(const std::string& name) { name_ = name; }

void Animal::setAge(int age)
{
    if (age < 0) {
        throw std::invalid_argument("Age cannot be negative.");
    }
    age_ = age;
}

// ---- Static counter ----
int Animal::getAnimalCount() { return animalCount_; }

} // namespace zoo
