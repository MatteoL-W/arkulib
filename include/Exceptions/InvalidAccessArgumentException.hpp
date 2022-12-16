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
     * @brief An exception to handle call of sqrt() when the rational is negative
     */
    class InvalidAccessArgument : public std::invalid_argument {
    public:
        inline InvalidAccessArgument() : std::invalid_argument(
                "The parameter must be 0 (numerator) or 1 (denominator).") {}
    };
}