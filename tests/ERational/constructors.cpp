#include <gtest/gtest.h>
#include "../../include/ERational.hpp"

TEST (ArkulibERationalConstructor, Classic) {
    Arkulib::ERational r1{};
    ASSERT_EQ(r1.toRealNumber(), 0);
}

TEST (ArkulibERationalConstructor, NumAndDen) {
    Arkulib::ERational r2{12, 24};
    ASSERT_EQ(r2.toRealNumber(), 0.5);

    Arkulib::ERational r3{(long long int) 4342434324432, 314347483689};
    ASSERT_NEAR(r3.getNumMultiplier(), 4.342434324432, 10e-12);
    ASSERT_EQ(r3.getNumExponent(), 12);

    ASSERT_NEAR(r3.getDenMultiplier(), 3.14347483689, 10e-11);
    ASSERT_EQ(r3.getDenExponent(), 11);

    // We create the same rational as before but reduced this time.
    Arkulib::ERational r4{(long long int) 4342434324432, 314347483689, true};
    ASSERT_NEAR(r4.toRealNumber(), r3.toRealNumber(), 10e-7);
    ASSERT_EQ(r4.getNumExponent(), 1);
    ASSERT_EQ(r4.getDenExponent(), 0);
}

TEST (ArkulibERationalConstructor, CopyRational) {
    Arkulib::Rational rational{363443, 24342};
    Arkulib::ERational r4{rational};
    ASSERT_NEAR(r4.getNumMultiplier(), 3.63443, 10e-5);
    ASSERT_EQ(r4.getNumExponent(), 5);

    ASSERT_NEAR(r4.getDenMultiplier(), 2.4342, 10e-4);
    ASSERT_EQ(r4.getDenExponent(), 4);
}

TEST (ArkulibERationalConstructor, Copy) {
    Arkulib::ERational r1{12, 24};
    Arkulib::ERational r2{r1};
    ASSERT_EQ(r1.toRealNumber(), r2.toRealNumber());
}

TEST (ArkulibERationalConstructor, FullConstructor) {
    Arkulib::ERational r1{2.2, 11, 3.3, 12};
    ASSERT_NEAR(r1.toRealNumber(), (2.2 * std::pow(10, 11)) / (3.3 * std::pow(10, 12)), 10e-7);
}

//ToDO Fix les 10e4