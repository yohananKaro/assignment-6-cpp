/**
 * @file Zoo.hpp
 * @brief Declaration of the Zoo class for managing a collection of animals.
 */

#pragma once

#include "Animal.hpp"
#include "Mammal.hpp"
#include "Bird.hpp"
#include "Reptile.hpp"
#include <string>

namespace zoo {

/**
 * @class Zoo
 * @brief Manages a dynamically-sized array of polymorphic Animal objects.
 *
 * Animals are stored by pointer (heap-allocated via Animal::clone()) so that
 * polymorphism is preserved.  The array doubles in capacity whenever it is full.
 */
class Zoo {
public:
    /**
     * @brief Default constructor.
     * Creates an "Unnamed Zoo" with initial capacity of 4.
     */
    Zoo();

    /**
     * @brief Parameterised constructor.
     * @param name     Name of the zoo.
     * @param capacity Initial capacity (must be > 0).
     * @throws std::invalid_argument if capacity <= 0.
     */
    explicit Zoo(const std::string& name, int capacity = 4);

    /** @brief Destructor – frees all cloned animals. */
    ~Zoo();

    // ---- Animal management ----

    /**
     * @brief Adds a copy of the given animal to the zoo.
     * Doubles the capacity if the zoo is full.
     * @param animal The animal to copy and store.
     */
    void addAnimal(const Animal& animal);

    /**
     * @brief Removes the animal at the given index.
     * Shifts remaining animals left to fill the gap.
     * @throws std::out_of_range if index is out of bounds.
     */
    void removeAnimal(int index);

    /**
     * @brief Finds an animal by name.
     * @return Pointer to the animal, or nullptr if not found.
     */
    Animal* findAnimal(const std::string& name) const;

    /**
     * @brief Returns a const reference to the animal at the given index.
     * @throws std::out_of_range if index is out of bounds.
     */
    const Animal& getAnimal(int index) const;

    // ---- Display ----

    /** @brief Prints all animals with numbered list and descriptions. */
    void printAllAnimals() const;

    /** @brief Prints each animal's sound. */
    void makeAllSounds() const;

    // ---- Getters ----
    std::string getZooName()  const;
    int         getCapacity() const;
    int         getCount()    const;
    bool        isEmpty()     const;

    // ---- Setters ----
    void setZooName(const std::string& name);

    // ---- Static counter ----
    /** @brief Returns the total number of Zoo instances ever created (never decremented). */
    static int getTotalZoosCreated();

private:
    std::string  name_;
    Animal**     animals_;   ///< Heap-allocated array of polymorphic Animal pointers
    int          capacity_;
    int          count_;

    /** @brief Doubles the capacity of the internal array. */
    void resize();

    static int totalZoosCreated_;
};

} // namespace zoo
