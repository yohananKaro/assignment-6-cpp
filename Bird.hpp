/**
 * @file Bird.hpp
 * @brief Declaration of the Bird class, derived from Animal.
 */

#pragma once

#include "Animal.hpp"
#include <string>

namespace zoo {

/**
 * @class Bird
 * @brief Represents a bird in the zoo.
 *
 * Extends Animal with flight capability and wingspan.
 */
class Bird : public Animal {
public:
    /**
     * @brief Constructs a Bird.
     * @param name           The bird's name.
     * @param age            The bird's age (must be >= 0).
     * @param species        The bird's species.
     * @param canFly         Whether the bird can fly.
     * @param wingspanMeters Wingspan in metres (must be > 0).
     * @throws std::invalid_argument if age is negative or wingspanMeters <= 0.
     */
    Bird(const std::string& name, int age, const std::string& species,
         bool canFly, double wingspanMeters = 1.0);

    /** @brief Copy constructor. */
    Bird(const Bird& other);

    /** @brief Destructor. */
    ~Bird() override;

    /** @brief Polymorphic copy (calls Bird copy constructor). */
    Animal* clone() const override;

    // ---- Pure virtual overrides ----
    std::string makeSound()     const override;
    std::string getAnimalType() const override;
    std::string getDiet()       const override;

    // ---- Getters ----
    bool   getCanFly()          const;
    double getWingspanMeters()  const;

    // ---- Setters ----
    void setCanFly(bool canFly);

    /**
     * @brief Sets the wingspan in metres.
     * @throws std::invalid_argument if wingspanMeters <= 0.
     */
    void setWingspanMeters(double wingspanMeters);

private:
    bool   canFly_;
    double wingspanMeters_;
};

} // namespace zoo
