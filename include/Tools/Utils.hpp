/**
 * @file      Utils.hpp
 * @author    Elise MASSA
 * @author    Mattéo LECLERCQ
 * @date      2022
 * @copyright WTFPL
 */

#include <cmath>
#include <sstream>
#include "Constant.hpp"

namespace Arkulib::Tools {
    /**
     * @brief Round a number for a wanted precision (the digits)
     * @tparam FloatingType
     * @param value
     * @param precision
     * @return A rounded value
     */
    template <typename FloatingType = double>
    auto roundToWantedPrecision(const FloatingType value, const int precision = 10e4) {
        return std::round(value * precision) / precision;
    }

    /**
     * @brief Let the user set the precision while transforming a floating point to a string
     * @tparam Type
     * @param value
     * @param precision
     * @return A string
     */
    template <typename Type>
    std::string toStringWithPrecision(const Type value, const int precision = Arkulib::Constant::DEFAULT_COUT_ERATIONAL_DIGITS)
    {
        std::ostringstream out;
        out.precision(precision);
        out << std::fixed << value;
        return out.str();
    }
}