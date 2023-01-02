#include <gtest/gtest.h>
#include "../../include/Rational.hpp"

TEST (ArkulibConversion, ToApproximation) {
    Arkulib::Rational r1{319871312, 9788787};

    unsigned int precision = 3;
    Arkulib::Rational r2 = r1.toApproximation(precision);
    ASSERT_NEAR (r1.toRealNumber(), r2.toRealNumber(), precision);

    // Excess
    precision = 7;
    Arkulib::Rational r3 = r1.toApproximation(precision);
    ASSERT_NEAR (r1.toRealNumber(), r3.toRealNumber(), precision);

    precision = 1;
    Arkulib::Rational r5 = r1.toApproximation(precision);
    ASSERT_NEAR (r1.toRealNumber(), r5.toRealNumber(), precision);

    precision = 0;
    Arkulib::Rational r6 = r1.toApproximation(precision);
    ASSERT_NEAR (r1.toRealNumber(), r6.toRealNumber(), 1);

    EXPECT_THROW({
         try {
             r1 = r1.toApproximation(15);
         }
         catch (const Arkulib::Exceptions::DigitsTooLargeException &e) {
             EXPECT_STREQ("The given precision seems to large to be wanted. You should reduce it.",
                          e.what());
             throw;
         }
     }, Arkulib::Exceptions::DigitsTooLargeException);
}

TEST (ArkulibConversion, ToInteger) {
    Arkulib::Rational r1{0.75};
    ASSERT_EQ (r1.toInteger(), Arkulib::Rational<int>::Zero());

    Arkulib::Rational r2{1.5};
    ASSERT_EQ (r2.toInteger(), Arkulib::Rational<int>::One());

    Arkulib::Rational r3{2.7};
    ASSERT_EQ (r3.toInteger(), Arkulib::Rational(2));

    Arkulib::Rational r4{1000000.8};
    ASSERT_EQ (r4.toInteger(), 1000000);
}

TEST (ArkulibConversion, ToRealNumber) {
    Arkulib::Rational r1{1, 4};
    ASSERT_EQ (float(0.25), r1.toRealNumber());

    Arkulib::Rational r2{10, 100};
    ASSERT_EQ (double(0.1), r2.toRealNumber<double>());
}

TEST (ArkulibConversion, ToString) {
    Arkulib::Rational r1{1, 4};
    std::string expectedResult = "(1 / 4)";

    ASSERT_EQ (expectedResult, r1.toString());
}