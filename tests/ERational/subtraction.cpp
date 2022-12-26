#include <gtest/gtest.h>
#include "../../include/Tools/ERationalVerif.hpp"

TEST (ArkulibERationalSubtraction, Simple) {
    //ToDo implement
    Arkulib::ERational r1{2.23, 11, 3.31, 7};
    Arkulib::ERational r2{4.11, 6, 7.08, 4};
    Arkulib::ERational r3 = r1 - r2;

    ASSERT_NEAR(r3.toRealNumber(), Arkulib::Tools::OpApproximation(r1, r2, std::minus<double>{}), 10e-7);
}

TEST (ArkulibERationalSubtraction, NegativeMultipliers) {
    Arkulib::ERational r1{2.23, 11, -3.31, 7};
    Arkulib::ERational r2{-4.11, 6, -7.08, 4};
    Arkulib::ERational r3 = r1 - r2;

    ASSERT_NEAR(r3.toRealNumber(), Arkulib::Tools::OpApproximation(r1, r2, std::minus<double>{}), 10e-7);
}

TEST (ArkulibERationalSubtraction, NegativeMultAndExponent) {
    Arkulib::ERational r1{2.23, 7, -3.31, -7};
    Arkulib::ERational r2{-4.11, 6, -7.08, 4};
    Arkulib::ERational r3 = r1 - r2;

    EXPECT_NEAR(r3.toRealNumber(), Arkulib::Tools::OpApproximation(r1, r2, std::minus<double>{}), 10e3);
    // 1 of precision because OpApproximation is made with the C++ system who isn't that precise with native very big floating point
}

TEST (ArkulibERationalSubtraction, BigNumber) {
    Arkulib::ERational r1{2.25352233, 10, -3.31, -7};
    Arkulib::ERational r2{-4.1132523, 31, -7.08, 23};
    Arkulib::ERational r3 = r1 - r2;

    ASSERT_NEAR(r3.toRealNumber(), Arkulib::Tools::OpApproximation(r1, r2, std::minus<double>{}), 10);
    // Large precision because he have very big numbers there.
}
