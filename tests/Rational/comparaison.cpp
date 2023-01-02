#include <climits>
#include <gtest/gtest.h>
#include "../../include/Rational.hpp"

TEST (ArkulibComparaison, Equal) {
    Arkulib::Rational r1(1, 2);
    Arkulib::Rational r2(2, 4);
    Arkulib::Rational r3{2, 4};
    Arkulib::Rational r4(988, 1976);
    Arkulib::Rational r5(0.5);

    ASSERT_TRUE(r1 == r2);
    ASSERT_TRUE(r2 == r3);
    ASSERT_TRUE(r1 == r4);
    ASSERT_TRUE(r1 == r5);
}

TEST (ArkulibComparaison, Different) {
    Arkulib::Rational r1(1, 2);
    Arkulib::Rational r2(1, 3);
    Arkulib::Rational r3(0.2);
    Arkulib::Rational r4(200000, 1);

    ASSERT_TRUE(r1 != r2);
    ASSERT_TRUE(r1 != r3);
    ASSERT_TRUE(r1 != r4);
}

TEST (ArkulibComparaison, Inferior) {
    Arkulib::Rational r1(1, 3);
    Arkulib::Rational r2(1, 2);
    Arkulib::Rational r3(1.5);
    Arkulib::Rational r4(200000, 1);

    ASSERT_TRUE(r1 < r2);
    ASSERT_TRUE(r1 < r3);
    ASSERT_TRUE(r1 < r4);
}

TEST (ArkulibComparaison, Superior) {
    Arkulib::Rational r1(1, 3);
    Arkulib::Rational r2(1, 2);
    Arkulib::Rational r3(1.5);
    Arkulib::Rational r4(200000, 1);

    ASSERT_TRUE(r4 > r3);
    ASSERT_TRUE(r3 > r2);
    ASSERT_TRUE(r2 > r1);
}

TEST (ArkulibComparaison, InferiorOrEqual) {
    Arkulib::Rational r1(1, 3);
    Arkulib::Rational r2(2, 6);
    Arkulib::Rational r3(0.2);
    Arkulib::Rational r4(1, 5);

    ASSERT_TRUE(r1 <= r2);
    ASSERT_TRUE(r1 == r2);

    ASSERT_TRUE(r3 <= r2);
    ASSERT_TRUE(r3 < r2);

    ASSERT_TRUE(r4 <= r3);
    ASSERT_TRUE(r4 == r3);
}

TEST (ArkulibComparaison, SuperiorOrEqual) {
    Arkulib::Rational r1(1, 3);
    Arkulib::Rational r2(2, 6);
    Arkulib::Rational r3(0.2);
    Arkulib::Rational r4(1, 5);

    ASSERT_TRUE(r3 >= r4);
    ASSERT_TRUE(r3 == r4);

    ASSERT_TRUE(r2 > r3);
    ASSERT_TRUE(r2 >= r3);

    ASSERT_TRUE(r1 >= r2);
    ASSERT_TRUE(r1 == r2);
}