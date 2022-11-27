#include <gtest/gtest.h>
#include "../include/Rational.hpp"

TEST (ArkulibExpOperation, RationalsOfOne) {
    Arkulib::Rational r1(1,1);
    Arkulib::Rational r2(2,3);
    Arkulib::Rational r3(-4);

    bool shouldBeEqualToTrue = r1.exp() == Arkulib::Rational(1457,536); //valeur
    ASSERT_EQ (shouldBeEqualToTrue, true);
}


TEST (ArkulibExpOperation, RationalsThenSimplify) {
    Arkulib::Rational r1(4,7);
    Arkulib::Rational r2(-4,7);

    bool shouldBeEqualToTrue = r1.exp()*r2.exp() == 1;
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibExpOperation, ExponantialOfZero) {
    Arkulib::Rational r1(0);

    bool shouldBeEqualToTrue = r1.exp() == 1;
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibExpOperation, ExponentialTimeExponential) {
    Arkulib::Rational r1(1, 3);
    Arkulib::Rational r2(9,4);
    std::cout << (r1 + r2).exp() << std::endl; // 13,2412
    std::cout << r1.exp() << std::endl; //  1,39561
    std::cout << r2.exp() << std::endl; // 9,48774

    bool shouldBeEqualToTrue = (r1 + r2).exp() == r1.exp() * r2.exp();
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibExpOperation, BigRationals) {
    Arkulib::Rational r1(1450, 2);
    Arkulib::Rational r2(305,2869);

    bool shouldBeEqualToTrue = (r1 * r2) == Arkulib::Rational(221125,2869);
    ASSERT_EQ (shouldBeEqualToTrue, true);
}
