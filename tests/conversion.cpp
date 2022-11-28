#include <gtest/gtest.h>
#include "../include/Rational.hpp"

TEST (ArkulibConversion, ToInteger) {
    Arkulib::Rational r1{0.75};
    ASSERT_EQ (0 == r1.toInteger(), true);

    Arkulib::Rational r2{1.5};
    ASSERT_EQ (1 == r2.toInteger(), true);

    Arkulib::Rational r3{2.7};
    ASSERT_EQ (2 == r3.toInteger(), true);

    Arkulib::Rational r4{1000000.8};
    ASSERT_EQ (1000000 == r4.toInteger(), true);
}

TEST (ArkulibConversion, ToRealNumber) {
    Arkulib::Rational r1{1, 4};
    ASSERT_EQ (float(0.25) == r1.toRealNumber(), true);

    Arkulib::Rational r2{10, 100};
    ASSERT_EQ (double(0.1) == r2.toRealNumber<double>(), true);
}

TEST (ArkulibConversion, ToString) {
    Arkulib::Rational r1{1, 4};
    std::string expectedResult = "(1 / 4)";

    ASSERT_EQ (expectedResult == r1.toString(), true);
}