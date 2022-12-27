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
     * @brief An exception to handle call of unwanted argument offset
     */
    class InvalidAccessArgument : public std::invalid_argument {
    public:
        inline InvalidAccessArgument() : std::invalid_argument(
                "The parameter must be 0 (numerator) or 1 (denominator).") {}
    };
}