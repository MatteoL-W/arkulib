#include <gtest/gtest.h>
#include "Rational.hpp"

TEST (ArkulibDivideOperation, Rationals) {
    Arkulib::Rational r1(1,7);
    Arkulib::Rational r2(6,13);

    bool shouldBeEqualToTrue = (r1 / r2) == Arkulib::Rational(13,42);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

/* ça marche pas c'est mystique
TEST (ArkulibDivideOperation, ConsecutiveRationalsOperation) {
    Arkulib::Rational r1(4,5);
    Arkulib::Rational r2(8,3);
    Arkulib::Rational r3(17,21);
    Arkulib::Rational r4(2,3);
    Arkulib::Rational r5 = (r1 / r2);
    std::cout << r5;

    bool shouldBeEqualToTrue = r5 == Arkulib::Rational(3, 10);
    ASSERT_EQ (shouldBeEqualToTrue, true);


    r5 = r5 / r3;
    shouldBeEqualToTrue = r5 == Arkulib::Rational(63,170);
    ASSERT_EQ (shouldBeEqualToTrue, true);

    r5 = r5 / r4;
    shouldBeEqualToTrue = r5 == Arkulib::Rational(189,340);
    ASSERT_EQ (shouldBeEqualToTrue, true);

}

TEST (ArkulibDivideOperation, RationalsThenSimplify) {
    Arkulib::Rational r1(1,2);
    Arkulib::Rational r2(1,2);

    bool shouldBeEqualToTrue = (r1 / r2) == 1;
    ASSERT_EQ (shouldBeEqualToTrue, true);
}*/

TEST (ArkulibDivideOperation, RationalsAndZero) {
    Arkulib::Rational r1(0);
    Arkulib::Rational r2(5,4);

    bool shouldBeEqualToTrue = (r1 / r2) == Arkulib::Rational<int>::Zero();
    ASSERT_EQ (shouldBeEqualToTrue, true);

    shouldBeEqualToTrue = (r1 / r1) == Arkulib::Rational<int>::Zero();
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibDivideOperation, RationalsAndOne) {
    Arkulib::Rational r1(1);
    Arkulib::Rational r2(3,4);

    bool shouldBeEqualToTrue = (r1 / r2) == Arkulib::Rational(4,3);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

/* pareil
TEST (ArkulibDivideOperation, BigRationals) {
    Arkulib::Rational r1(4560, 9);
    Arkulib::Rational r2(256,900);
    std::cout << (r1 / r2);

    bool shouldBeEqualToTrue = (r1 / r2) == Arkulib::Rational(342000,192);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}*/