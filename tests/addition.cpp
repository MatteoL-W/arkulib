#include <gtest/gtest.h>
#include "Rational.hpp"

TEST (ArkulibPlusOperation, simpleRationalsOperation) {
    Arkulib::Rational r1(1,2);
    Arkulib::Rational r2(1,2);
    Arkulib::Rational r3 = r1+r2;

    ASSERT_EQ (r3, r3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}