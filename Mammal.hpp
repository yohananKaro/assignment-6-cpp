/**
 * @file Mammal.hpp
 * @brief Declaration of the Mammal class, derived from Animal.
 */

#pragma once

#include "Animal.hpp"
#include <string>

namespace zoo {

/**
 * @class Mammal
 * @brief Represents a mammal in the zoo.
 *
 * Extends Animal with domestication status and number of legs.
 */
class Mammal : public Animal {
public:
    /**
     * @brief Constructs a Mammal.
     * @param name            The mammal's name.
     * @param age             The mammal's age (must be >= 0).
     * @param species         The mammal's species.
     * @param isDomesticated  Whether the mammal is domesticated.
     * @param numberOfLegs    Number of legs (must be >= 0), default 4.
     * @throws std::invalid_argument if age or numberOfLegs is negative.
     */
    Mammal(const std::string& name, int age, const std::string& species,
           bool isDomesticated, int numberOfLegs = 4);

    /** @brief Copy constructor. */
    Mammal(const Mammal& other);

    /** @brief Destructor. */
    ~Mammal() override;

    /** @brief Polymorphic copy (calls Mammal copy constructor). */
    Animal* clone() const override;

    // ---- Pure virtual overrides ----
    std::string makeSound()     const override;
    std::string getAnimalType() const override;
    std::string getDiet()       const override;

    // ---- Getters ----
    bool getIsDomesticated() const;
    int  getNumberOfLegs()   const;

    // ---- Setters ----
    void setDomesticated(bool isDomesticated);

    /**
     * @brief Sets the number of legs.
     * @throws std::invalid_argument if numberOfLegs is negative.
     */
    void setNumberOfLegs(int numberOfLegs);

private:
    bool isDomesticated_;
    int  numberOfLegs_;
};

} // namespace zoo
