#include <gtest/gtest.h>
#include "../include/Rational.hpp"

TEST (ArkulibStatus, IsNegative) {
    Arkulib::Rational r1{-1, 4};
    ASSERT_EQ (r1.isNegative(), true);

    Arkulib::Rational r2{1, -4};
    ASSERT_EQ (r2.isNegative(), true);

    Arkulib::Rational r3{1, 4};
    ASSERT_EQ (r3.isNegative(), false);
}

TEST (ArkulibStatus, IsInteger) {
    Arkulib::Rational r1{-1, 1};
    ASSERT_EQ (r1.isInteger(), true);

    Arkulib::Rational r2{10000, 1};
    ASSERT_EQ (r2.isInteger(), true);

    Arkulib::Rational r3{1, 4};
    ASSERT_EQ (r3.isInteger(), false);
}

TEST (ArkulibStatus, IsZero) {
    Arkulib::Rational r1{0, -1};
    ASSERT_EQ (r1.isZero(), true);

    Arkulib::Rational r2{0, 1};
    ASSERT_EQ (r2.isZero(), true);

    Arkulib::Rational r3{1, 4};
    ASSERT_EQ (r3.isZero(), false);
}
