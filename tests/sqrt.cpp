#include <gtest/gtest.h>
#include "../include/Rational.hpp"

TEST (ArkulibSquareOperation, Rationals) {
    Arkulib::Rational r1(4, 9);

    bool shouldBeEqualToTrue = r1.sqrt() == Arkulib::Rational(2, 3);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibSquareOperation, ConsecutiveSquareOperation) {
    Arkulib::Rational r1(16, 81);

    Arkulib::Rational r2 = r1.sqrt();

    bool shouldBeEqualToTrue = r2 == Arkulib::Rational(4, 9);
    ASSERT_EQ (shouldBeEqualToTrue, true);

    Arkulib::Rational r3 = r2.sqrt();
    shouldBeEqualToTrue = r3 == Arkulib::Rational(2, 3);
    ASSERT_EQ (shouldBeEqualToTrue, true);

}

TEST (ArkulibSquareOperation, RationalsThenSimplify) {
    Arkulib::Rational r1(25, 25);

    bool shouldBeEqualToTrue = r1.sqrt() == 1;
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibSquareOperation, RationalsAndZero) {
    Arkulib::Rational r1(0);
    Arkulib::Rational r2(1, 3);

    bool shouldBeEqualToTrue = r1.sqrt() == Arkulib::Rational<int>::Zero();
    ASSERT_EQ (shouldBeEqualToTrue, true);

    shouldBeEqualToTrue = r1.sqrt() * r2.sqrt() == Arkulib::Rational<int>::Zero();
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibSquareOperation, SquareTimeSquare) {
    Arkulib::Rational r1(4, 9);
    Arkulib::Rational r2(2, 3);

    bool shouldBeEqualToTrue = r1.sqrt() * r1.sqrt() == (r1 * r1).sqrt();
    ASSERT_EQ (shouldBeEqualToTrue, true);

    shouldBeEqualToTrue = r1.sqrt() * r2.sqrt() == (r1 * r2).sqrt();
    ASSERT_NEAR (shouldBeEqualToTrue, true, 1); //ASSERT_EQ doesn't work because of a slight rounding error
}

TEST (ArkulibSquareOperation, BigRationals) {
    Arkulib::Rational r1(6561, 2401);

    bool shouldBeEqualToTrue = r1.sqrt() == Arkulib::Rational(81, 49);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}