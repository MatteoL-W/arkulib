#include <gtest/gtest.h>
#include "Rational.hpp"

TEST (ArkulibPlusOperation, Rationals) {
    Arkulib::Rational r1(10,7);
    Arkulib::Rational r2(7,7);

    bool shouldBeEqualToTrue = (r1 + r2) == Arkulib::Rational(17,7);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibPlusOperation, ConsecutiveRationalsOperation) {
    Arkulib::Rational r1(10,7);
    Arkulib::Rational r2(7,7);
    Arkulib::Rational r3(14,2);
    Arkulib::Rational r4(2,7);
    Arkulib::Rational r5 = (r1 + r2);

    bool shouldBeEqualToTrue = r5 == Arkulib::Rational(17,7);
    ASSERT_EQ (shouldBeEqualToTrue, true);

    r5 = r5 + r3;
    shouldBeEqualToTrue = r5 == Arkulib::Rational(66,7);
    ASSERT_EQ (shouldBeEqualToTrue, true);

    r5 = r5 + r4;
    shouldBeEqualToTrue = r5 == Arkulib::Rational(68,7);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibPlusOperation, RationalsThenSimplify) {
    Arkulib::Rational r1(1,3);
    Arkulib::Rational r2(2,3);

    bool shouldBeEqualToTrue = (r1 + r2) == 1;
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibPlusOperation, RationalsAndZero) {
    Arkulib::Rational r1(0);
    Arkulib::Rational r2(2,3);

    bool shouldBeEqualToTrue = (r1 + r2) == Arkulib::Rational(2,3);
    ASSERT_EQ (shouldBeEqualToTrue, true);

    shouldBeEqualToTrue = (r1 + r1) == Arkulib::Rational<int>::Zero();
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibPlusOperation, RationalsAndOne) {
    Arkulib::Rational r1(1);
    Arkulib::Rational r2(2,3);

    bool shouldBeEqualToTrue = (r1 + r2) == Arkulib::Rational(5,3);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibPlusOperation, BigRationals) {
    Arkulib::Rational r1(1000, 3);
    Arkulib::Rational r2(3000,2999);
    //std::cout << (r1 + r2);

    bool shouldBeEqualToTrue = (r1 + r2) == Arkulib::Rational(3008000,8997);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}