#include <gtest/gtest.h>
#include "../include/Rational.hpp"

TEST (ArkulibMinusOperation, Rationals) {
    Arkulib::Rational r1(4, 7);
    Arkulib::Rational r2(1, 6);

    ASSERT_EQ (r1 - r2, Arkulib::Rational(17, 42));
}

TEST (ArkulibMinusOperation, ConsecutiveRationalsOperation) {
    Arkulib::Rational r1(12, 7);
    Arkulib::Rational r2(8, 3);
    Arkulib::Rational r3(7, 2);
    Arkulib::Rational r4(13, 5);
    Arkulib::Rational r5 = (r1 - r2);

    ASSERT_EQ (r5, Arkulib::Rational(-20, 21));

    r5 = r5 - r3;
    ASSERT_EQ (r5, Arkulib::Rational(-187, 42));

    r5 = r5 - r4;
    ASSERT_EQ (r5, Arkulib::Rational(-1481, 210));
}

TEST (ArkulibMinusOperation, RationalsThenSimplify) {
    Arkulib::Rational r1(7, 4);
    Arkulib::Rational r2(3, 4);

    ASSERT_TRUE ((r1 - r2) == 1);
}

TEST (ArkulibMinusOperation, RationalsAndZero) {
    Arkulib::Rational r1(0);
    Arkulib::Rational r2(2, 3);

    ASSERT_EQ (r1 - r2, Arkulib::Rational(-2, 3));
    ASSERT_TRUE ((r1 - r1) == 0);
}

TEST (ArkulibMinusOperation, RationalsAndOne) {
    Arkulib::Rational r1(6, 5);
    Arkulib::Rational r2(1);

    ASSERT_EQ (r1 - r2, Arkulib::Rational(1, 5));
}

TEST (ArkulibMinusOperation, BigRationals) {
    Arkulib::Rational r1(5000, 4);
    Arkulib::Rational r2(2000, 1999);

    ASSERT_EQ (r1 - r2, Arkulib::Rational(2496750, 1999));
}


TEST (ArkulibMinusOperation, SubtractionAssignment) {
    Arkulib::Rational r1(1, 6);
    r1 -= Arkulib::Rational(4, 9);

    ASSERT_EQ (r1, Arkulib::Rational(-15, 54));
}

TEST (ArkulibMinusOperation, AdditionAssignment2) {
    Arkulib::Rational r1(6, 7);
    r1 += 1;

    ASSERT_EQ (r1, Arkulib::Rational(13, 7));
}