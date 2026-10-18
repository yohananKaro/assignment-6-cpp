/**
 * @file Animal.hpp
 * @brief Abstract base class for all animals in the zoo management system.
 */

#pragma once

#include <string>

namespace zoo {

/**
 * @class Animal
 * @brief Abstract base class representing a generic animal.
 *
 * Provides common properties (name, age, species) and a static counter.
 * Derived classes must implement makeSound(), getAnimalType(), and getDiet().
 */
class Animal {
public:
    /**
     * @brief Constructs an Animal.
     * @param name     The animal's name.
     * @param age      The animal's age (must be >= 0).
     * @param species  The animal's species.
     * @throws std::invalid_argument if age is negative.
     */
    Animal(const std::string& name, int age, const std::string& species);

    /**
     * @brief Copy constructor.
     */
    Animal(const Animal& other);

    /**
     * @brief Virtual destructor (required for polymorphic deletion).
     */
    virtual ~Animal();

    // ---- Pure virtual interface ----

    /** @brief Returns the sound the animal makes. */
    virtual std::string makeSound() const = 0;

    /**
     * @brief Creates a heap-allocated copy of this object (used by Zoo::addAnimal).
     * @return Pointer to the newly allocated copy.
     */
    virtual Animal* clone() const = 0;

    /** @brief Returns the type string ("Mammal", "Bird", "Reptile"). */
    virtual std::string getAnimalType() const = 0;

    /** @brief Returns the diet description of the animal. */
    virtual std::string getDiet() const = 0;

    // ---- Concrete methods ----

    /**
     * @brief Returns a formatted description of the animal.
     * Format: "[{type}] {name} ({species}), Age: {age}, Sound: {sound}, Diet: {diet}"
     */
    std::string getDescription() const;

    // ---- Getters ----
    std::string getName()    const;
    int         getAge()     const;
    std::string getSpecies() const;

    // ---- Setters ----
    void setName(const std::string& name);

    /**
     * @brief Sets the animal's age.
     * @throws std::invalid_argument if age is negative.
     */
    void setAge(int age);

    // ---- Static counter ----
    /** @brief Returns the total number of Animal instances currently alive. */
    static int getAnimalCount();

private:
    std::string name_;
    int         age_;
    std::string species_;

    static int animalCount_;
};

} // namespace zoo
