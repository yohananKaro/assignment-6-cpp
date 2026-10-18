/**
 * @file StudentTest.cpp
 * @brief Student unit tests for the Zoo Management System.
 *        Contains at least 20 original TEST_CASEs not found in test.cpp.
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Animal.hpp"
#include "Mammal.hpp"
#include "Bird.hpp"
#include "Reptile.hpp"
#include "Zoo.hpp"

using namespace zoo;

// ==================== EDGE CASES: AGE BOUNDARY ====================

TEST_CASE("Student - Mammal age zero is valid") {
    Mammal m("NewBorn", 0, "Cat", true, 4);
    CHECK(m.getAge() == 0);
}

TEST_CASE("Student - Bird age zero is valid") {
    Bird b("Chick", 0, "Sparrow", true, 0.3);
    CHECK(b.getAge() == 0);
}

TEST_CASE("Student - Reptile age zero is valid") {
    Reptile r("Hatchling", 0, "Gecko", false, 5.0);
    CHECK(r.getAge() == 0);
}

// ==================== SETTERS VALIDATION ====================

TEST_CASE("Student - Mammal setAge to zero is valid") {
    Mammal m("Leo", 5, "Lion", false);
    m.setAge(0);
    CHECK(m.getAge() == 0);
}

TEST_CASE("Student - Bird setWingspanMeters very small positive is valid") {
    Bird b("Tiny", 1, "Wren", true, 0.1);
    b.setWingspanMeters(0.01);
    CHECK(b.getWingspanMeters() == doctest::Approx(0.01));
}

TEST_CASE("Student - Reptile setBodyLengthCm very small positive is valid") {
    Reptile r("Mini", 1, "Gecko", false, 5.0);
    r.setBodyLengthCm(0.1);
    CHECK(r.getBodyLengthCm() == doctest::Approx(0.1));
}

TEST_CASE("Student - Mammal setName updates name") {
    Mammal m("Old", 3, "Dog", true);
    m.setName("New");
    CHECK(m.getName() == "New");
}

// ==================== getDescription AFTER SETTER CHANGES ====================

TEST_CASE("Student - Mammal getDescription changes after setDomesticated") {
    Mammal m("Leo", 5, "Lion", false, 4);
    CHECK(m.getDescription() == "[Mammal] Leo (Lion), Age: 5, Sound: Roar!, Diet: Meat");
    m.setDomesticated(true);
    CHECK(m.getDescription() == "[Mammal] Leo (Lion), Age: 5, Sound: Purr..., Diet: Meat and plants");
}

TEST_CASE("Student - Bird getDescription changes after setCanFly") {
    Bird b("Pingu", 2, "Penguin", false, 0.5);
    CHECK(b.getDescription() == "[Bird] Pingu (Penguin), Age: 2, Sound: Squawk!, Diet: Seeds and insects");
    b.setCanFly(true);
    CHECK(b.getDescription() == "[Bird] Pingu (Penguin), Age: 2, Sound: Tweet tweet!, Diet: Seeds and insects");
}

TEST_CASE("Student - Reptile getDescription changes after setVenomous") {
    Reptile r("Sly", 3, "Cobra", true, 120.0);
    CHECK(r.getDescription() == "[Reptile] Sly (Cobra), Age: 3, Sound: Hisss!, Diet: Rodents and eggs");
    r.setVenomous(false);
    CHECK(r.getDescription() == "[Reptile] Sly (Cobra), Age: 3, Sound: ..., Diet: Insects and plants");
}

// ==================== ZOO EDGE CASES ====================

TEST_CASE("Student - Zoo findAnimal on empty zoo returns nullptr") {
    Zoo z("Empty Zoo");
    CHECK(z.findAnimal("Nobody") == nullptr);
}

TEST_CASE("Student - Zoo getAnimal throws on empty zoo") {
    Zoo z("Empty Zoo");
    CHECK_THROWS_AS(z.getAnimal(0), std::out_of_range);
}

TEST_CASE("Student - Zoo removeAnimal throws on empty zoo") {
    Zoo z("Empty Zoo");
    CHECK_THROWS_AS(z.removeAnimal(0), std::out_of_range);
}

TEST_CASE("Student - Zoo isEmpty becomes false after addAnimal") {
    Zoo z("Test Zoo");
    CHECK(z.isEmpty());
    Mammal m("Leo", 5, "Lion", false);
    z.addAnimal(m);
    CHECK_FALSE(z.isEmpty());
}

TEST_CASE("Student - Zoo isEmpty becomes true after removing last animal") {
    Zoo z("Test Zoo");
    Mammal m("Leo", 5, "Lion", false);
    z.addAnimal(m);
    CHECK_FALSE(z.isEmpty());
    z.removeAnimal(0);
    CHECK(z.isEmpty());
}

TEST_CASE("Student - Zoo capacity grows correctly after multiple resizes") {
    Zoo z("Grow Zoo", 1);
    Mammal a("A", 1, "Cat", true);
    Mammal b("B", 2, "Dog", true);
    Mammal c("C", 3, "Horse", false);
    Mammal d("D", 4, "Cow", true);

    z.addAnimal(a);  // cap=1, count=1
    CHECK(z.getCapacity() == 1);

    z.addAnimal(b);  // triggers resize → cap=2
    CHECK(z.getCapacity() == 2);

    z.addAnimal(c);  // triggers resize → cap=4
    CHECK(z.getCapacity() == 4);

    z.addAnimal(d);  // cap still 4
    CHECK(z.getCapacity() == 4);
    CHECK(z.getCount() == 4);
}

TEST_CASE("Student - Zoo findAnimal returns correct pointer after resize") {
    Zoo z("Find Zoo", 1);
    Bird b1("Alpha", 1, "Eagle", true, 2.0);
    Bird b2("Beta",  2, "Hawk",  true, 1.5);

    z.addAnimal(b1);
    z.addAnimal(b2);  // triggers resize

    Animal* found = z.findAnimal("Beta");
    CHECK(found != nullptr);
    CHECK(found->getName() == "Beta");
    CHECK(found->getAge() == 2);
}

TEST_CASE("Student - Zoo addAnimal stores independent copy (clone)") {
    Zoo z("Clone Zoo");
    Mammal m("Leo", 5, "Lion", false, 4);
    z.addAnimal(m);

    // Mutate the original — the stored copy should be unaffected
    m.setName("Simba");
    m.setAge(10);

    const Animal& stored = z.getAnimal(0);
    CHECK(stored.getName() == "Leo");
    CHECK(stored.getAge() == 5);
}

TEST_CASE("Student - Zoo preserves order after removeAnimal from middle") {
    Zoo z("Order Zoo");
    Mammal a("First",  1, "Cat",   true);
    Bird   b("Second", 2, "Eagle", true, 2.0);
    Reptile c("Third", 3, "Gecko", false, 20.0);

    z.addAnimal(a);
    z.addAnimal(b);
    z.addAnimal(c);

    z.removeAnimal(1);  // Remove "Second"

    CHECK(z.getCount() == 2);
    CHECK(z.getAnimal(0).getName() == "First");
    CHECK(z.getAnimal(1).getName() == "Third");
}

TEST_CASE("Student - Zoo mixed polymorphism — getAnimalType via base ref") {
    Zoo z("Poly Zoo");
    Mammal m("Leo",  5, "Lion",   false);
    Bird   b("Tweety", 1, "Canary", true, 0.3);
    Reptile r("Rex", 4, "Iguana", false, 60.0);

    z.addAnimal(m);
    z.addAnimal(b);
    z.addAnimal(r);

    CHECK(z.getAnimal(0).getAnimalType() == "Mammal");
    CHECK(z.getAnimal(1).getAnimalType() == "Bird");
    CHECK(z.getAnimal(2).getAnimalType() == "Reptile");
}

// ==================== ANIMAL STATIC COUNT ====================

TEST_CASE("Student - Animal count correct after Zoo destructor") {
    int before = Animal::getAnimalCount();
    Bird b("Tweety", 1, "Canary", true, 0.5);
    {
        Zoo z("Temp Zoo");
        z.addAnimal(b);  // clone stored in Zoo
        // b (stack) + clone in Zoo = +2
        CHECK(Animal::getAnimalCount() == before + 2);
    }
    // Zoo destroyed -> clone deleted; b still on stack -> +1
    CHECK(Animal::getAnimalCount() == before + 1);
}

TEST_CASE("Student - Animal count correct with multiple copies") {
    int before = Animal::getAnimalCount();
    {
        Reptile r1("Sly",   2, "Cobra", true, 150.0);
        Reptile r2(r1);   // copy ctor
        Reptile r3(r2);   // copy ctor
        CHECK(Animal::getAnimalCount() == before + 3);
    }
    CHECK(Animal::getAnimalCount() == before);
}

// ==================== INVALID ARGUMENT COMBINATIONS ====================

TEST_CASE("Student - Bird negative wingspan throws even when canFly is false") {
    CHECK_THROWS_AS(Bird("Tux", 5, "Penguin", false, -0.1), std::invalid_argument);
}

TEST_CASE("Student - Reptile zero body length throws") {
    CHECK_THROWS_AS(Reptile("Sly", 2, "Cobra", true, 0.0), std::invalid_argument);
}

TEST_CASE("Student - Zoo invalid capacity of 0 throws") {
    CHECK_THROWS_AS(Zoo("Bad", 0), std::invalid_argument);
}

TEST_CASE("Student - Zoo invalid negative capacity throws") {
    CHECK_THROWS_AS(Zoo("Bad", -10), std::invalid_argument);
}
