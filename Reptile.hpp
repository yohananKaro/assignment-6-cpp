/**
 * @file Reptile.hpp
 * @brief Declaration of the Reptile class, derived from Animal.
 */

#pragma once

#include "Animal.hpp"
#include <string>

namespace zoo {

/**
 * @class Reptile
 * @brief Represents a reptile in the zoo.
 *
 * Extends Animal with venomous status and body length.
 */
class Reptile : public Animal {
public:
    /**
     * @brief Constructs a Reptile.
     * @param name          The reptile's name.
     * @param age           The reptile's age (must be >= 0).
     * @param species       The reptile's species.
     * @param isVenomous    Whether the reptile is venomous.
     * @param bodyLengthCm  Body length in centimetres (must be > 0).
     * @throws std::invalid_argument if age is negative or bodyLengthCm <= 0.
     */
    Reptile(const std::string& name, int age, const std::string& species,
            bool isVenomous, double bodyLengthCm = 50.0);

    /** @brief Copy constructor. */
    Reptile(const Reptile& other);

    /** @brief Destructor. */
    ~Reptile() override;

    /** @brief Polymorphic copy (calls Reptile copy constructor). */
    Animal* clone() const override;

    // ---- Pure virtual overrides ----
    std::string makeSound()     const override;
    std::string getAnimalType() const override;
    std::string getDiet()       const override;

    // ---- Getters ----
    bool   getIsVenomous()   const;
    double getBodyLengthCm() const;

    // ---- Setters ----
    void setVenomous(bool isVenomous);

    /**
     * @brief Sets the body length in centimetres.
     * @throws std::invalid_argument if bodyLengthCm <= 0.
     */
    void setBodyLengthCm(double bodyLengthCm);

private:
    bool   isVenomous_;
    double bodyLengthCm_;
};

} // namespace zoo
