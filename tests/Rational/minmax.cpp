#include <gtest/gtest.h>
#include "../include/Rational.hpp"

TEST (ArkulibMinMax, Min) {
    Arkulib::Rational r0(1,4);
    Arkulib::Rational r1(4,4);
    Arkulib::Rational r2(3,4);
    Arkulib::Rational r3(2,4);
    Arkulib::Rational r4(5,4);

    Arkulib::Rational min = Arkulib::Rational<int>::min(r0, r1, r2, r3, r4);
    ASSERT_EQ(r0, min);
}

TEST (ArkulibMinMax, Max) {
    Arkulib::Rational r0(1,4);
    Arkulib::Rational r1(4,4);
    Arkulib::Rational r2(3,4);
    Arkulib::Rational r3(2,4);
    Arkulib::Rational r4(5,4);

    Arkulib::Rational max = Arkulib::Rational<int>::max(r0, r1, r2, r3, r4);
    ASSERT_EQ(r4, max);
}