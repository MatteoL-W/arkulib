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
     * @brief An exception to handle divide by 0
     */
    class DivideByZeroException : public std::runtime_error {
    public:
        inline DivideByZeroException() : std::runtime_error("Denominator must not be null") {}
    };
}
