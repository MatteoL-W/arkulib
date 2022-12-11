#include <gtest/gtest.h>
#include "../include/Rational.hpp"

//ToDo Exception on > to INT_MAX
//ToDo Constructor with another type

TEST (ArkulibConstructor, NumeratorAndDenominator) {
    Arkulib::Rational r1(10, 5);
    Arkulib::Rational r2{10, 5};
    Arkulib::Rational r3 = Arkulib::Rational(10, 5);
    Arkulib::Rational r4 = Arkulib::Rational{10, 5};

    ASSERT_EQ (r1, Arkulib::Rational(2));
    ASSERT_EQ (r1, r2);
    ASSERT_EQ (r2, r3);
    ASSERT_EQ (r3, r4);
}

TEST (ArkulibConstructor, NumeratorAndDenominatorWithoutReduceTag) {
    Arkulib::Rational r1(10, 5, false);
    Arkulib::Rational r2{10, 5, false};
    Arkulib::Rational r3 = Arkulib::Rational(10, 5, false);
    Arkulib::Rational r4 = Arkulib::Rational{10, 5, false};

    ASSERT_TRUE (r1 == 2);
    ASSERT_EQ (r1, r2);
    ASSERT_EQ (r2, r3);
    ASSERT_EQ (r3, r4);
}

TEST (ArkulibConstructor, DefaultConstructor) {
    Arkulib::Rational r1{};
    r1.setNumerator(2);
    r1.setDenominator(8);

    ASSERT_TRUE (r1 == 0.25);
}

TEST (ArkulibConstructor, CopyConstructor) {
    Arkulib::Rational r1{2, 8};
    Arkulib::Rational r2{r1};

    ASSERT_TRUE (r1 == r2);
}

TEST (ArkulibConstructor, FromNonRationalConstructor) {
    Arkulib::Rational r1{0.75};
    Arkulib::Rational r2{3, 4};

    ASSERT_TRUE (r1 == r2);
}

TEST (ArkulibConstructor, ConstructorsCoherency) {
    Arkulib::Rational r1{1, 4};
    Arkulib::Rational r2{2, 8, false};
    Arkulib::Rational r3{0.25};
    Arkulib::Rational r4{};
    r4.setNumerator(1);
    r4.setDenominator(4);

    ASSERT_TRUE (r1 == r2);
    ASSERT_TRUE (r1 == r3);
    ASSERT_TRUE (r1 == r4);
}

TEST (ArkulibConstructor, UnwantedTypes) {
    EXPECT_THROW({
                     try {
                         Arkulib::Rational<float> r1;
                     }
                     catch (const Arkulib::Exceptions::FloatTypeGivenException &e) {
                         EXPECT_STREQ("The type given to a rational must not be a floating point.", e.what());
                         throw;
                     }
                 }, Arkulib::Exceptions::FloatTypeGivenException);
}