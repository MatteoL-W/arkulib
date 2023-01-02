/**
 * @file      ERationalVerif.hpp
 * @author    Elise MASSA
 * @author    Mattéo LECLERCQ
 * @date      2022
 * @copyright WTFPL
 */

#pragma once

#include <cmath>
#include <functional>
#include "../ERational.hpp"

namespace Arkulib::Tools {
    template <typename OperatorType>
    double OpApproximation(
            Arkulib::ERational<> r1,
            Arkulib::ERational<> r2,
            OperatorType operatorFunc
    ) {
        return operatorFunc(
            (r1.getNumMultiplier() * std::pow(10, r1.getNumExponent())) / (r1.getDenMultiplier() * std::pow(10, r1.getDenExponent())),
            (r2.getNumMultiplier() * std::pow(10, r2.getNumExponent())) / (r2.getDenMultiplier() * std::pow(10, r2.getDenExponent()))
        );
    }
}