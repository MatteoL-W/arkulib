#include <gtest/gtest.h>
#include "../../include/Rational.hpp"

TEST (ArkulibGetter, DefaultGetter) {
    Arkulib::Rational r1{0.75};
    ASSERT_EQ (3, r1.getNumerator());
    ASSERT_EQ (4, r1.getDenominator());
}

TEST (ArkulibGetter, HookGetter) {
    Arkulib::Rational r1{0.75};
    ASSERT_EQ (3, r1[0]);
    ASSERT_EQ (4, r1[1]);
}

TEST (ArkulibGetter, ErrorGetter) {
    Arkulib::Rational r1{0.75};

    EXPECT_THROW({
         try {
             r1[2];
         }
         catch (const Arkulib::Exceptions::InvalidAccessArgument &e) {
             EXPECT_STREQ("The parameter must be 0 (numerator) or 1 (denominator).", e.what());
             throw;
         }
     }, Arkulib::Exceptions::InvalidAccessArgument);
}
