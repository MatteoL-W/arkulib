/**
 * @file      DivideByZeroException.hpp
 * @author    Elise MASSA
 * @author    Mattéo LECLERCQ
 * @date      2022
 * @copyright WTFPL
 */

#pragma once

#include <stdexcept>

namespace Arkulib::Exceptions {
    /**
     * @brief An exception to handle ERational multiplier in a non floating point type
     */
    class IntTypeGivenException : public std::invalid_argument {
    public:
        inline IntTypeGivenException() : std::invalid_argument(
                "The type given to a erational multiplier must not be a floating point.") {}
    };
}