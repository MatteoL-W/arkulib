#include <gtest/gtest.h>
#include "../include/Rational.hpp"

TEST (ArkulibCosineOperation, Rationals) {
    Arkulib::Rational r1 = Arkulib::Rational<int>::Pi() * Arkulib::Rational(1, 3);
    Arkulib::Rational r2 = Arkulib::Rational(1, 2);

    ASSERT_EQ (r1.cos(), r2);
}

TEST (ArkulibCosineOperation, CosineAndZero) {
    Arkulib::Rational r1(0);
    ASSERT_TRUE (r1.cos() == 1);
    ASSERT_TRUE (r1.cos() - r1.cos() == 0);
}

TEST (ArkulibCosineOperation, CosineAndPi) {
    Arkulib::Rational r1 = Arkulib::Rational<int>::Pi();
    ASSERT_TRUE (r1.cos() == -1);

    Arkulib::Rational r2 = r1 * Arkulib::Rational(1, 2);
    ASSERT_NEAR (r2.cos().toRealNumber(), 0, 10e4);
}

TEST (ArkulibCosineOperation, BigRationals) {
    Arkulib::Rational r1(5000, 4);
    ASSERT_EQ (r1.cos(), Arkulib::Rational(2507821, 2673479));
}


TEST (ArkulibCosineOperation, Linearisation) {
    Arkulib::Rational r1(7, 5);
    Arkulib::Rational r2(3, 4);
    Arkulib::Rational linearisation = r1.cos() * r2.cos();
    Arkulib::Rational linearisationTest = Arkulib::Rational(1, 2) * ((r1 + r2).cos() + (r1 - r2).cos());
    ASSERT_NEAR (linearisation.toRealNumber(), linearisationTest.toRealNumber(), 10e4);
}
