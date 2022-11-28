#include <gtest/gtest.h>
#include "../include/Rational.hpp"

TEST (ArkulibPowOperation, Rationals) {
    Arkulib::Rational r1(2, 7);
    Arkulib::Rational r2(5, 6);

    bool shouldBeEqualToTrue = r1.pow(2) == Arkulib::Rational(4, 49);
    ASSERT_EQ (shouldBeEqualToTrue, true);

    shouldBeEqualToTrue = r2.pow(-3) == Arkulib::Rational(216, 125);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibPowOperation, ConsecutiveRationalsOperation) {
    Arkulib::Rational r1(7, 3);

    Arkulib::Rational r2 = r1.pow(4);

    bool shouldBeEqualToTrue = r2 == Arkulib::Rational(2401, 81);
    ASSERT_EQ (shouldBeEqualToTrue, true);

    Arkulib::Rational r3 = r2.pow(0.75);
    shouldBeEqualToTrue = r3 == Arkulib::Rational(343, 27);
    ASSERT_EQ (shouldBeEqualToTrue, true);

    Arkulib::Rational r4 = r3.pow(-1);
    shouldBeEqualToTrue = r4 == Arkulib::Rational(27, 343);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibPowOperation, RationalsThenSimplify) {
    Arkulib::Rational r1(4, 7);

    bool shouldBeEqualToTrue = r1 * r1.pow(-1) == 1;
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibPowOperation, PowZeroAndOne) {
    Arkulib::Rational r1(13, 9);

    bool shouldBeEqualToTrue = r1.pow(0) == 1;
    ASSERT_EQ (shouldBeEqualToTrue, true);

    shouldBeEqualToTrue = r1.pow(1) == r1;
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibPowOperation, PowTiemPow) {
    Arkulib::Rational r1(1, 5);

    bool shouldBeEqualToTrue = r1.pow(4).pow(2) == r1.pow(2).pow(4);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibPowOperation, BigRationals) {
    Arkulib::Rational r1(124, 7);

    bool shouldBeEqualToTrue = r1.pow(3) == Arkulib::Rational(1906624, 343); //5558,67055
    ASSERT_EQ (shouldBeEqualToTrue, true);
}
