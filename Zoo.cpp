/**
 * @file Zoo.cpp
 * @brief Implementation of the Zoo class.
 */

#include "Zoo.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

namespace zoo {

// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic,cppcoreguidelines-owning-memory)

// ---- Static member definition ----
int Zoo::totalZoosCreated_ = 0;

// ---- Default constructor ----
Zoo::Zoo()
    : name_("Unnamed Zoo"),
      animals_(new Animal*[4U]),
      capacity_(4),
      count_(0)
{
    ++totalZoosCreated_;
}

// ---- Parameterised constructor ----
Zoo::Zoo(const std::string& name, int capacity)
    : name_(name),
      animals_(nullptr),
      capacity_(capacity),
      count_(0)
{
    if (capacity <= 0) {
        throw std::invalid_argument("Zoo capacity must be greater than zero.");
    }
    animals_ = new Animal*[static_cast<std::size_t>(capacity)];
    ++totalZoosCreated_;
}

// ---- Destructor ----
Zoo::~Zoo()
{
    for (int i = 0; i < count_; ++i) {
        delete animals_[i];
    }
    delete[] animals_;
}

// ---- Animal management ----

void Zoo::addAnimal(const Animal& animal)
{
    if (count_ >= capacity_) {
        resize();
    }
    if (count_ >= 0 && count_ < capacity_) {
        animals_[count_] = animal.clone();
        ++count_;
    }
}

void Zoo::removeAnimal(int index)
{
    if (index < 0 || index >= count_) {
        throw std::out_of_range("Zoo::removeAnimal: index out of range.");
    }
    delete animals_[index];
    for (int i = index; i < count_ - 1; ++i) {
        animals_[i] = animals_[i + 1];
    }
    animals_[count_ - 1] = nullptr;
    --count_;
}

Animal* Zoo::findAnimal(const std::string& name) const
{
    for (int i = 0; i < count_; ++i) {
        if (animals_[i]->getName() == name) {
            return animals_[i];
        }
    }
    return nullptr;
}

const Animal& Zoo::getAnimal(int index) const
{
    if (index < 0 || index >= count_) {
        throw std::out_of_range("Zoo::getAnimal: index out of range.");
    }
    return *animals_[index];
}

// ---- Display ----

void Zoo::printAllAnimals() const
{
    std::cout << "=== " << name_ << " ===\n";
    for (int i = 0; i < count_; ++i) {
        std::cout << (i + 1) << ". " << animals_[i]->getDescription() << "\n";
    }
}

void Zoo::makeAllSounds() const
{
    for (int i = 0; i < count_; ++i) {
        std::cout << animals_[i]->getName() << " says: "
                  << animals_[i]->makeSound() << "\n";
    }
}

// ---- Getters ----
std::string Zoo::getZooName()  const { return name_; }
int         Zoo::getCapacity() const { return capacity_; }
int         Zoo::getCount()    const { return count_; }
bool        Zoo::isEmpty()     const { return count_ == 0; }

// ---- Setters ----
void Zoo::setZooName(const std::string& name) { name_ = name; }

// ---- Static counter ----
int Zoo::getTotalZoosCreated() { return totalZoosCreated_; }

// ---- Private helpers ----
void Zoo::resize()
{
    int newCapacity = capacity_ * 2;
    Animal** newAnimals = new Animal*[static_cast<std::size_t>(newCapacity)];
    for (int i = 0; i < count_; ++i) {
        newAnimals[i] = animals_[i];
    }
    delete[] animals_;
    animals_  = newAnimals;
    capacity_ = newCapacity;
}

// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic,cppcoreguidelines-owning-memory)

} // namespace zoo
