#include <gtest/gtest.h>
#include "../include/Rational.hpp"

TEST (ArkulibPlusOperation, Classic) {
    Arkulib::Rational r1(10, 7);
    Arkulib::Rational r2(7, 7);
    Arkulib::Rational r3(17, 7);

    ASSERT_EQ (r1 + r2, r3);
}

TEST (ArkulibPlusOperation, Negative) {
    Arkulib::Rational r1(10, 7);
    Arkulib::Rational r2(-7, 7);
    Arkulib::Rational r3(3, 7);

    ASSERT_EQ (r1 + r2, r3);
}

TEST (ArkulibPlusOperation, ConsecutiveRationalsOperation) {
    Arkulib::Rational r1(10, 7);
    Arkulib::Rational r2(7, 7);
    Arkulib::Rational r3(14, 2);
    Arkulib::Rational r4(2, 7);

    Arkulib::Rational r5 = (r1 + r2);
    ASSERT_EQ (r5, Arkulib::Rational(17, 7));

    r5 = r5 + r3;
    ASSERT_EQ (r5, Arkulib::Rational(66, 7));

    r5 = r5 + r4;
    ASSERT_EQ (r5, Arkulib::Rational(68, 7));
}

TEST (ArkulibPlusOperation, RationalsThenSimplifyToOne) {
    Arkulib::Rational r1(1, 3);
    Arkulib::Rational r2(2, 3);

    ASSERT_EQ (r1 + r2, Arkulib::Rational<int>::One());
}

TEST (ArkulibPlusOperation, RationalsAndZero) {
    Arkulib::Rational r1(0);
    Arkulib::Rational r2(2, 3);

    ASSERT_EQ (r1 + r2, Arkulib::Rational(2, 3));
    ASSERT_EQ (r1 + r1, Arkulib::Rational<int>::Zero());
}

TEST (ArkulibPlusOperation, RationalsAndOne) {
    Arkulib::Rational r1(1);
    Arkulib::Rational r2(2, 3);

    ASSERT_EQ (r1 + r2, Arkulib::Rational(5, 3));
}

TEST (ArkulibPlusOperation, BigRationals) {
    Arkulib::Rational r1(1000, 3);
    Arkulib::Rational r2(3000, 2999);

    ASSERT_EQ (r1 + r2, Arkulib::Rational(3008000, 8997));
}

TEST (ArkulibPlusOperation, VeryBigRationals) {
    Arkulib::Rational r1(INT_MAX, 2);
    Arkulib::Rational r2(3000, 2999);

    EXPECT_THROW({
         try {
             // This will be > than INT_MAX in numerator
             Arkulib::Rational r3 = r1 + r2;
         }
         catch (const Arkulib::Exceptions::NumberTooLargeException &e) {
             EXPECT_STREQ("The given integer type doesn't have the capacity to store the rational.", e.what());
             throw;
         }
     }, Arkulib::Exceptions::NumberTooLargeException);
}

TEST (ArkulibPlusOperation, VeryBigRationalsNegative) {
    Arkulib::Rational r1(INT_MIN, 2);
    Arkulib::Rational r2(-8, 2999);

    EXPECT_THROW({
        try {
         // This will be > than INT_MAX in numerator
         Arkulib::Rational r3 = r1 + r2;
        }
        catch (const Arkulib::Exceptions::NumberTooLargeException &e) {
         EXPECT_STREQ("The given integer type doesn't have the capacity to store the rational.", e.what());
         throw;
        }
    }, Arkulib::Exceptions::NumberTooLargeException);
}

TEST (ArkulibPlusOperation, AdditionAssignment) {
    Arkulib::Rational r1(1, 4);
    r1 += Arkulib::Rational(2, 3);

    ASSERT_EQ (r1, Arkulib::Rational(11, 12));
}

TEST (ArkulibPlusOperation, AdditionAssignment2) {
    Arkulib::Rational r1(1, 4);
    r1 += 1;

    ASSERT_EQ (r1, Arkulib::Rational(5, 4));
}

TEST (ArkulibPlusOperation, IncrementOperator) {
    Arkulib::Rational r1(1, 4);
    ++r1;

    ASSERT_EQ (r1, Arkulib::Rational(5, 4));
}
