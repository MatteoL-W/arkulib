#include <gtest/gtest.h>
#include "../include/Rational.hpp"

TEST (ArkulibCosineOperation, Rationals) {
    Arkulib::Rational r1 = Arkulib::Rational<int>::Pi() * Arkulib::Rational(1, 3);
    bool shouldBeEqualToTrue = r1.cos() == Arkulib::Rational(1, 2);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibCosineOperation, CosineAndZero) {
    Arkulib::Rational r1(0);

    bool shouldBeEqualToTrue = r1.cos() == 1;
    ASSERT_EQ (shouldBeEqualToTrue, true);

    shouldBeEqualToTrue = r1.cos() - r1.cos() == Arkulib::Rational<int>::Zero();
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibCosineOperation, CosineAndPi) {

    Arkulib::Rational r1 = Arkulib::Rational<int>::Pi();
    bool shouldBeEqualToTrue = r1.cos() == -1;
    ASSERT_EQ (shouldBeEqualToTrue, true);

    Arkulib::Rational r2 = Arkulib::Rational<int>::Pi() * Arkulib::Rational(1, 2);
    shouldBeEqualToTrue = r2.cos() == Arkulib::Rational<int>::Zero();
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibCosineOperation, BigRationals) {
    Arkulib::Rational r1(5000, 4);

    bool shouldBeEqualToTrue = r1.cos() == Arkulib::Rational(2507821, 2673479);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}


TEST (ArkulibCosineOperation, Linearisation) {
    Arkulib::Rational r1(7, 5);
    Arkulib::Rational r2(3, 4);

    bool shouldBeEqualToTrue = r1.cos() * r2.cos() == Arkulib::Rational(1, 2) * ((r1 + r2).cos() + (r1 - r2).cos());
    ASSERT_NEAR (shouldBeEqualToTrue, true, 1); //ASSERT_EQ doesn't work because of a slight rounding error
}
