#include <gtest/gtest.h>
#include "../include/Rational.hpp"

TEST (ArkulibSetter, DefaultSetter) {
    Arkulib::Rational r1{};
    r1.setNumerator(3);
    r1.setDenominator(4);

    ASSERT_EQ (3 == r1.getNumerator(), true);
    ASSERT_EQ (4 == r1.getDenominator(), true);
}

TEST (ArkulibSetter, HookSetter) {
    Arkulib::Rational r1{};
    r1[0] = 3;
    r1[1] = 4;

    ASSERT_EQ (3 == r1.getNumerator(), true);
    ASSERT_EQ (4 == r1.getDenominator(), true);
}

TEST (ArkulibGetter, ErrorSetter) {
    Arkulib::Rational r1{0.75};

    EXPECT_THROW({
         try {
             r1[2] = 3;
         }
         catch (const Arkulib::Exceptions::InvalidAccessArgument &e) {
             EXPECT_STREQ("The parameter must be 0 (numerator) or 1 (denominator).", e.what());
             throw;
         }
     }, Arkulib::Exceptions::InvalidAccessArgument);
}