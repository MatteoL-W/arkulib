#include <gtest/gtest.h>
#include "../include/Rational.hpp"

TEST (ArkulibDivideOperation, Classic) {
    Arkulib::Rational r1(1, 7);
    Arkulib::Rational r2(6, 13);

    ASSERT_EQ (r1 / r2, Arkulib::Rational(13, 42));
}

TEST (ArkulibDivideOperation, Negative) {
    Arkulib::Rational r1(1, 7);
    Arkulib::Rational r2(-6, 13);

    ASSERT_EQ (r1 / r2, Arkulib::Rational(-13, 42));
}

TEST (ArkulibDivideOperation, ConsecutiveRationalsOperation) {
    Arkulib::Rational r1(4, 5);
    Arkulib::Rational r2(8, 3);
    Arkulib::Rational r3(17, 21);
    Arkulib::Rational r4(2, 3);
    Arkulib::Rational r5 = (r1 / r2);
    ASSERT_EQ (r1 / r2, r5);

    r5 = r5 / r3;
    ASSERT_EQ (r5, Arkulib::Rational(63, 170));

    r5 = r5 / r4;
    ASSERT_EQ (r5, Arkulib::Rational(189, 340));
}

TEST (ArkulibDivideOperation, RationalsThenSimplify) {
    Arkulib::Rational r1(1, 2);
    Arkulib::Rational r2(1, 2);

    ASSERT_TRUE ((r1 / r2) == 1);
}

TEST (ArkulibDivideOperation, RationalsAndZero) {
    Arkulib::Rational r1(0);
    Arkulib::Rational r2(5, 4);
    ASSERT_TRUE (r1 / r2 == 0);

    EXPECT_THROW({
         try {
             r1 / r1;
         }
         catch (const Arkulib::Exceptions::DivideByZeroException &e) {
             EXPECT_STREQ("Denominator must not be null", e.what());
             throw;
         }
     }, Arkulib::Exceptions::DivideByZeroException);
}

TEST (ArkulibDivideOperation, RationalsAndOne) {
    Arkulib::Rational r1(1);
    Arkulib::Rational r2(3, 4);

    ASSERT_EQ (r1 / r2, Arkulib::Rational(4, 3));
}

TEST (ArkulibDivideOperation, BigRationals) {
    Arkulib::Rational r1(4560, 9);
    Arkulib::Rational r2(256, 900);

    ASSERT_EQ (r1 / r2, Arkulib::Rational(342000, 192));
}


TEST (ArkulibDivideOperation, VeryBigRationals) {
    Arkulib::Rational r1(INT_MAX, 2);
    Arkulib::Rational r2(3000, 2999);

    EXPECT_THROW({
                     try {
                         // This will be > than INT_MAX in numerator
                         Arkulib::Rational r3 = r1 / r2;
                     }
                     catch (const Arkulib::Exceptions::NumberTooLargeException &e) {
                         EXPECT_STREQ("The given integer type doesn't have the capacity to store the rational.", e.what());
                         throw;
                     }
                 }, Arkulib::Exceptions::NumberTooLargeException);
}

TEST (ArkulibDivideOperation, VeryBigRationalsNegative) {
    Arkulib::Rational r1(INT_MIN, 2);
    Arkulib::Rational r2(-8, 2999);

    EXPECT_THROW({
                     try {
                         Arkulib::Rational r3 = r1 / r2;
                     }
                     catch (const Arkulib::Exceptions::NumberTooLargeException &e) {
                         EXPECT_STREQ("The given integer type doesn't have the capacity to store the rational.", e.what());
                         throw;
                     }
                 }, Arkulib::Exceptions::NumberTooLargeException);
}

TEST (ArkulibDivisionOperation, DivisionAssignment) {
    Arkulib::Rational r1(1, 2);
    r1 /= Arkulib::Rational(3, 4);

    ASSERT_EQ (r1, Arkulib::Rational(2, 3));
}

TEST (ArkulibDivisionOperation, DivisionAssignment2) {
    Arkulib::Rational r1(6, 5);
    r1 /= 1;

    ASSERT_EQ (r1, Arkulib::Rational(6, 5));
}