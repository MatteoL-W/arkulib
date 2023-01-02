#include <climits>
#include <gtest/gtest.h>
#include "../../include/Rational.hpp"

TEST (ArkulibTimeOperation, Rationals) {
    Arkulib::Rational r1(1, 2);
    Arkulib::Rational r2(7, 8);

    ASSERT_EQ (r1 * r2, Arkulib::Rational(7, 16));
}

TEST (ArkulibTimeOperation, ConsecutiveRationalsOperation) {
    Arkulib::Rational r1(4, 3);
    Arkulib::Rational r2(2, 5);
    Arkulib::Rational r3(-1, 9);
    Arkulib::Rational r4(6, 7);
    Arkulib::Rational r5 = (r1 * r2);

    ASSERT_EQ (r5, Arkulib::Rational(8, 15));

    r5 = r5 * r3;
    ASSERT_EQ (r5, Arkulib::Rational(-8, 135));

    r5 = r5 * r4;
    ASSERT_EQ (r5, Arkulib::Rational(-16, 315));
}

TEST (ArkulibTimeOperation, RationalsThenSimplify) {
    Arkulib::Rational r1(4, 7);
    Arkulib::Rational r2(7, 4);

    ASSERT_TRUE ((r1 * r2) == 1);
}

TEST (ArkulibTimeOperation, RationalsAndZero) {
    Arkulib::Rational r1(0);
    Arkulib::Rational r2(1, 3);

    ASSERT_TRUE ((r1 * r2) == 0);
    ASSERT_TRUE ((r1 * r1) == 0);
}

TEST (ArkulibTimeOperation, RationalsAndOne) {
    Arkulib::Rational r1(1);
    Arkulib::Rational r2(14, 4);

    ASSERT_EQ (r1 * r2, Arkulib::Rational(14, 4));
}

TEST (ArkulibTimeOperation, BigRationals) {
    Arkulib::Rational r1(1450, 2);
    Arkulib::Rational r2(305, 2869);

    ASSERT_EQ (r1 * r2, Arkulib::Rational(221125, 2869));
}


TEST (ArkulibTimeOperation, VeryBigRationals) {
    Arkulib::Rational r1(INT_MAX, 2);
    Arkulib::Rational r2(3000, 2999);

    EXPECT_THROW({
                     try {
                         // This will be > than INT_MAX in numerator
                         Arkulib::Rational r3 = r1 * r2;
                     }
                     catch (const Arkulib::Exceptions::NumberTooLargeException &e) {
                         EXPECT_STREQ("The given integer type doesn't have the capacity to store the rational.", e.what());
                         throw;
                     }
                 }, Arkulib::Exceptions::NumberTooLargeException);
}

TEST (ArkulibTimeOperation, VeryBigRationalsNegative) {
    Arkulib::Rational r1(INT_MIN, 2);
    Arkulib::Rational r2(-8, 2999);

    EXPECT_THROW({
                     try {
                         // This will be > than INT_MAX in numerator
                         Arkulib::Rational r3 = r1 * r2;
                     }
                     catch (const Arkulib::Exceptions::NumberTooLargeException &e) {
                         EXPECT_STREQ("The given integer type doesn't have the capacity to store the rational.", e.what());
                         throw;
                     }
                 }, Arkulib::Exceptions::NumberTooLargeException);
}

TEST (ArkulibTimeOperation, MultiplicationAssignment) {
    Arkulib::Rational r1(2, 5);
    r1 *= Arkulib::Rational(11, 3);

    ASSERT_EQ (r1, Arkulib::Rational(22, 15));
}

TEST (ArkulibTimeOperation, MultiplicationAssignment2) {
    Arkulib::Rational r1(7, 8);
    r1 *= 1;

    ASSERT_EQ (r1, Arkulib::Rational(7, 8));
}