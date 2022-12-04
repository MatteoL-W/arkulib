#include <gtest/gtest.h>
#include "../include/Rational.hpp"

TEST (ArkulibStatus, IsNegative) {
    Arkulib::Rational r1{-1, 4};
    ASSERT_TRUE (r1.isNegative());

    Arkulib::Rational r2{1, -4};
    ASSERT_TRUE (r2.isNegative());

    Arkulib::Rational r3{1, 4};
    ASSERT_FALSE (r3.isNegative());
}

TEST (ArkulibStatus, IsInteger) {
    Arkulib::Rational r1{-1, 1};
    ASSERT_TRUE (r1.isInteger());

    Arkulib::Rational r2{10000, 1};
    ASSERT_TRUE (r2.isInteger());

    Arkulib::Rational r3{1, 4};
    ASSERT_FALSE (r3.isInteger());
}

TEST (ArkulibStatus, IsZero) {
    Arkulib::Rational r1{0, -1};
    ASSERT_TRUE (r1.isZero());

    Arkulib::Rational r2{0, 1};
    ASSERT_TRUE (r2.isZero());

    Arkulib::Rational r3{1, 4};
    ASSERT_FALSE (r3.isZero());
}
