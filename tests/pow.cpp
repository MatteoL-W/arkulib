#include <gtest/gtest.h>
#include "../include/Rational.hpp"

TEST (ArkulibPowOperation, Rationals) {
    Arkulib::Rational r1(2, 7);
    Arkulib::Rational r2(5, 6);

    ASSERT_EQ (r1.pow(2), Arkulib::Rational(4, 49));
    ASSERT_EQ (r2.pow(-3), Arkulib::Rational(216, 125));
}

TEST (ArkulibPowOperation, ConsecutiveRationalsOperation) {
    Arkulib::Rational r1(7, 3);
    Arkulib::Rational r2 = r1.pow(4);

    ASSERT_EQ (r2, Arkulib::Rational(2401, 81));

    Arkulib::Rational r3 = r2.pow(0.75);
    ASSERT_EQ (r3, Arkulib::Rational(343, 27));

    Arkulib::Rational r4 = r3.pow(-1);
    ASSERT_EQ (r4, Arkulib::Rational(27, 343));
}

TEST (ArkulibPowOperation, RationalsThenSimplify) {
    Arkulib::Rational r1(4, 7);
    ASSERT_TRUE (r1 * r1.pow(-1) == 1);
}

TEST (ArkulibPowOperation, PowZeroAndOne) {
    Arkulib::Rational r1(13, 9);
    ASSERT_TRUE (r1.pow(0) == 1);
    ASSERT_EQ (r1.pow(1), r1);
}

TEST (ArkulibPowOperation, PowTimePow) {
    Arkulib::Rational r1(10, 2);
    ASSERT_EQ (r1.pow(4.).pow(2.), r1.pow(2.).pow(4.));
}

TEST (ArkulibPowOperation, BigRationals) {
    Arkulib::Rational r1(124, 7);
    ASSERT_EQ (r1.pow(3), Arkulib::Rational(1906624, 343)); //5558,67055
}
