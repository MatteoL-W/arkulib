#include <gtest/gtest.h>
#include "../include/Rational.hpp"

TEST (ArkulibSquareOperation, Rationals) {
    Arkulib::Rational r1(4, 9);
    ASSERT_EQ (r1.sqrt(), Arkulib::Rational(2, 3));
}

TEST (ArkulibSquareOperation, ConsecutiveSquareOperation) {
    Arkulib::Rational r1(16, 81);
    ASSERT_EQ (r1.sqrt(), Arkulib::Rational(4, 9));
    ASSERT_EQ (r1.sqrt().sqrt(), Arkulib::Rational(2, 3));
}

TEST (ArkulibSquareOperation, RationalsThenSimplify) {
    Arkulib::Rational r1(25, 25);
    ASSERT_TRUE (r1.sqrt() == 1);
}

TEST (ArkulibSquareOperation, RationalsAndZero) {
    Arkulib::Rational r1(0);
    Arkulib::Rational r2(1, 3);

    ASSERT_TRUE (r1.sqrt() == 0);
    ASSERT_TRUE (r1.sqrt() * r2.sqrt() == 0);
}

TEST (ArkulibSquareOperation, SquareTimeSquare) {
    Arkulib::Rational r1(4, 9);
    Arkulib::Rational r2(2, 3);

    ASSERT_EQ (r1.sqrt() * r1.sqrt(), (r1 * r1).sqrt());
    ASSERT_NEAR ((r1.sqrt() * r2.sqrt()).toRealNumber(), (r1 * r2).sqrt().toRealNumber(), 10e4);
}

TEST (ArkulibSquareOperation, BigRationals) {
    Arkulib::Rational r1(6561, 2401);
    ASSERT_EQ (r1.sqrt(), Arkulib::Rational(81, 49));
}