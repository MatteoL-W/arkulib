#include <gtest/gtest.h>
#include "../include/Rational.hpp"

TEST (ArkulibMinusOperation, Rationals) {
    Arkulib::Rational r1(4,7);
    Arkulib::Rational r2(1,6);

    bool shouldBeEqualToTrue = (r1 - r2) == Arkulib::Rational(17,42);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibMinusOperation, ConsecutiveRationalsOperation) {
    Arkulib::Rational r1(12,7);
    Arkulib::Rational r2(8,3);
    Arkulib::Rational r3(7,2);
    Arkulib::Rational r4(13,5);
    Arkulib::Rational r5 = (r1 - r2);

    bool shouldBeEqualToTrue = r5 == Arkulib::Rational(-20,21);
    ASSERT_EQ (shouldBeEqualToTrue, true);

    r5 = r5 - r3;
    shouldBeEqualToTrue = r5 == Arkulib::Rational(-187,42);
    ASSERT_EQ (shouldBeEqualToTrue, true);

    r5 = r5 - r4;
    shouldBeEqualToTrue = r5 == Arkulib::Rational(-1481,210);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibMinusOperation, RationalsThenSimplify) {
    Arkulib::Rational r1(7,4);
    Arkulib::Rational r2(3,4);

    bool shouldBeEqualToTrue = (r1 - r2) == 1;
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibMinusOperation, RationalsAndZero) {
    Arkulib::Rational r1(0);
    Arkulib::Rational r2(2,3);

    bool shouldBeEqualToTrue = (r1 - r2) == Arkulib::Rational(-2,3);
    ASSERT_EQ (shouldBeEqualToTrue, true);

    shouldBeEqualToTrue = (r1 - r1) == Arkulib::Rational<int>::Zero();
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibMinusOperation, RationalsAndOne) {
    Arkulib::Rational r1(6,5);
    Arkulib::Rational r2(1);


    bool shouldBeEqualToTrue = (r1 - r2) == Arkulib::Rational(1,5);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibMinusOperation, BigRationals) {
    Arkulib::Rational r1(5000, 4);
    Arkulib::Rational r2(2000,1999);

    bool shouldBeEqualToTrue = (r1 - r2) == Arkulib::Rational(2496750,1999);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}
