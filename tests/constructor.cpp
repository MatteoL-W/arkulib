#include <gtest/gtest.h>
#include "../include/Rational.hpp"

TEST (ArkulibConstructor, NumeratorAndDenominator) {
    Arkulib::Rational r1(10, 5);
    Arkulib::Rational r2{10, 5};
    Arkulib::Rational r3 = Arkulib::Rational(10, 5);
    Arkulib::Rational r4 = Arkulib::Rational{10, 5};

    ASSERT_EQ (true, r1 == 2);
    ASSERT_EQ (true, r1 == r2);
    ASSERT_EQ (true, r2 == r3);
    ASSERT_EQ (true, r3 == r4);
}

TEST (ArkulibConstructor, NumeratorAndDenominatorWithoutReduceTag) {
    Arkulib::Rational r1(10, 5, false);
    Arkulib::Rational r2{10, 5, false};
    Arkulib::Rational r3 = Arkulib::Rational(10, 5, false);
    Arkulib::Rational r4 = Arkulib::Rational{10, 5, false};

    ASSERT_EQ (r1 == 2, true);
    ASSERT_EQ (r1 == r2, true);
    ASSERT_EQ (r2 == r3, true);
    ASSERT_EQ (r3 == r4, true);
}

TEST (ArkulibConstructor, DefaultConstructor) {
    Arkulib::Rational r1{};
    r1.setNumerator(2);
    r1.setDenominator(8);

    ASSERT_EQ (r1 == 0.25, true);
}

TEST (ArkulibConstructor, CopyConstructor) {
    Arkulib::Rational r1{2,8};
    Arkulib::Rational r2{r1};

    ASSERT_EQ (r1 == r2, true);
}

TEST (ArkulibConstructor, FromNonRationalConstructor) {
    Arkulib::Rational r1{0.75};
    Arkulib::Rational r2{3,4};

    ASSERT_EQ (r1 == r2, true);
}

TEST (ArkulibConstructor, ConstructorsCoherency) {
    Arkulib::Rational r1{1,4};
    Arkulib::Rational r2{2,8, false};
    Arkulib::Rational r3{0.25};
    Arkulib::Rational r4{};
    r4.setNumerator(1);
    r4.setDenominator(4);

    //ToDo: Maybe test with some unwanted types?

    ASSERT_EQ (r1 == r2, true);
    ASSERT_EQ (r1 == r3, true);
    ASSERT_EQ (r1 == r4, true);
}