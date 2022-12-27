#include <gtest/gtest.h>
#include "../../include/Tools/ERationalVerif.hpp"

TEST (ArkulibERationalAddition, Simple) {
    Arkulib::ERational r1{2.23, 11, 3.31, 7};
    Arkulib::ERational r2{4.11, 6, 7.08, 4};
    Arkulib::ERational r3 = r1 + r2;

    ASSERT_NEAR(r3.toRealNumber(), Arkulib::Tools::OpApproximation(r1, r2, std::plus<double>{}), 10e-7);
}

TEST (ArkulibERationalAddition, NegativeMultipliers) {
    Arkulib::ERational r1{2.23, 11, -3.31, 7};
    Arkulib::ERational r2{-4.11, 6, -7.08, 4};
    Arkulib::ERational r3 = r1 + r2;

    ASSERT_NEAR(r3.toRealNumber(), Arkulib::Tools::OpApproximation(r1, r2, std::plus<double>{}), 10e-7);
}

TEST (ArkulibERationalAddition, NegativeMultAndExponent) {
    Arkulib::ERational r1{2.23, 11, -3.31, -7};
    Arkulib::ERational r2{-4.11, 6, -7.08, 4};
    Arkulib::ERational r3 = r1 + r2;

    EXPECT_NEAR(r3.toRealNumber(), Arkulib::Tools::OpApproximation(r1, r2, std::plus<double>{}), 1);
    // 1 of precision because OpApproximation is made with the C++ system who isn't that precise with native very bi floating point
}

TEST (ArkulibERationalAddition, BigNumber) {
    Arkulib::ERational r1{2.25352233, 10, -3.31, -7};
    Arkulib::ERational r2{-4.1132523, 31, -7.08, 23};
    Arkulib::ERational r3 = r1 + r2;

    ASSERT_NEAR(r3.toRealNumber(), Arkulib::Tools::OpApproximation(r1, r2, std::plus<double>{}), 10);
    // Large precision because he have very big numbers there.
}
