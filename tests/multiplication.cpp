#include <gtest/gtest.h>
#include "Rational.hpp"

TEST (ArkulibTimeOperation, Rationals) {
    Arkulib::Rational r1(1,2);
    Arkulib::Rational r2(7,8);

    bool shouldBeEqualToTrue = (r1 * r2) == Arkulib::Rational(7,16);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibTimeOperation, ConsecutiveRationalsOperation) {
    Arkulib::Rational r1(4,3);
    Arkulib::Rational r2(2,5);
    Arkulib::Rational r3(-1,9);
    Arkulib::Rational r4(6,7);
    Arkulib::Rational r5 = (r1 * r2);

    bool shouldBeEqualToTrue = r5 == Arkulib::Rational(8,15);
    ASSERT_EQ (shouldBeEqualToTrue, true);

    r5 = r5 * r3;
    shouldBeEqualToTrue = r5 == Arkulib::Rational(-8,135);
    ASSERT_EQ (shouldBeEqualToTrue, true);

    r5 = r5 * r4;
    shouldBeEqualToTrue = r5 == Arkulib::Rational(-16,315);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibTimeOperation, RationalsThenSimplify) {
    Arkulib::Rational r1(4,7);
    Arkulib::Rational r2(7,4);

    bool shouldBeEqualToTrue = (r1 * r2) == 1;
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibTimeOperation, RationalsAndZero) {
    Arkulib::Rational r1(0);
    Arkulib::Rational r2(1,3);

    bool shouldBeEqualToTrue = (r1 * r2) == Arkulib::Rational<int>::Zero();
    ASSERT_EQ (shouldBeEqualToTrue, true);

    shouldBeEqualToTrue = (r1 * r1) == Arkulib::Rational<int>::Zero();
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibTimeOperation, RationalsAndOne) {
    Arkulib::Rational r1(1);
    Arkulib::Rational r2(14,4);

    bool shouldBeEqualToTrue = (r1 * r2) == Arkulib::Rational(14,4);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibTimeOperation, BigRationals) {
    Arkulib::Rational r1(1450, 2);
    Arkulib::Rational r2(305,2869);

    bool shouldBeEqualToTrue = (r1 * r2) == Arkulib::Rational(221125,2869);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}
