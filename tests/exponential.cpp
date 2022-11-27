#include <gtest/gtest.h>
#include "../include/Rational.hpp"

TEST (ArkulibExpOperation, RationalsOfOne) {
    Arkulib::Rational r1(1,1);
    Arkulib::Rational r2(2,3);
    Arkulib::Rational r3(-4);

    bool shouldBeEqualToTrue = r1.exp() == Arkulib::Rational(1457,536); // 2,71828
    ASSERT_EQ (shouldBeEqualToTrue, true);

    std::cout << r3.exp() << std::endl;
    shouldBeEqualToTrue = r2.exp() == Arkulib::Rational(5420575,2783016); // 1,94773
    ASSERT_EQ (shouldBeEqualToTrue, true);

    shouldBeEqualToTrue = r3.exp() == Arkulib::Rational(112975,6168226); // 0.0183156
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

TEST (ArkulibExpOperation, ExponentialInverted) {
    Arkulib::Rational r1(7, 13);

    std::cout << r1.exp() << std::endl;

    bool shouldBeEqualToTrue = (-r1).exp() == 1 / r1.exp();
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibExpOperation, ExponentialTimeExponential) {
    // We don't use int because the numerator is actually superior to INT_MAX
    Arkulib::Rational<long long int> r1(1, 3);
    Arkulib::Rational<long long int> r2(9,4);
    Arkulib::Rational<long long int> r3 = r1.exp() * r2.exp();
    Arkulib::Rational<long long int> r4 = (r1 + r2).exp();


    bool shouldBeEqualToTrue = (r4 - r3).abs() < 0.1;
    ASSERT_EQ (shouldBeEqualToTrue, true);
}


TEST (ArkulibExpOperation, ExponentialDivideExponential) {
    Arkulib::Rational r1(5, 4);
    Arkulib::Rational r2(-1,6);
    Arkulib::Rational r3 = r1.exp() / r2.exp();
    Arkulib::Rational r4 = (r1 - r2).exp();

    bool shouldBeEqualToTrue = (r4 - r3).abs() < 0.1;
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibExpOperation, ExponentialPowN) {
    Arkulib::Rational r1(8, 5);

    std::cout << r1.exp() << std::endl;

    bool shouldBeEqualToTrue = (r1.exp()).pow(3) == (3*r1).exp();
    ASSERT_EQ (shouldBeEqualToTrue, true);
}

TEST (ArkulibExpOperation, BigRationals) {
    Arkulib::Rational r1(568, 134);

    bool shouldBeEqualToTrue = r1.exp() == Arkulib::Rational(3235191,46667); //69,32503
    ASSERT_EQ (shouldBeEqualToTrue, true);
}
