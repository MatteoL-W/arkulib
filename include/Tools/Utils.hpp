/**
 * @file      Utils.hpp
 * @author    Elise MASSA
 * @author    Mattéo LECLERCQ
 * @date      2022
 * @copyright WTFPL
 */

#include <cmath>

namespace Arkulib::Tools {
    template <typename FloatingType = double>
    auto roundToWantedPrecision(const FloatingType value, const int precision = 10e4) {
        return std::round(value * precision) / precision;
    }
}