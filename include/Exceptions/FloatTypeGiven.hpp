/**
 * @file      DivideByZeroException.hpp
 * @author    Elise MASSA
 * @author    Mattéo LECLERCQ
 * @date      2022
 * @copyright WTFPL
 */

#include <stdexcept>

namespace Arkulib::Exceptions {
    /**
     * @brief An exception to handle Rational expressed in a non integer type
     */
    class FloatTypeGiven : public std::invalid_argument {
    public:
        inline FloatTypeGiven() : std::invalid_argument("The type given to a rational must not be a floating point.") {}
    };
}