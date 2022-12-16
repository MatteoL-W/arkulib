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
     * @brief An exception to handle a rational who can't be expressed by the given type
     */
    class NumberTooLargeException : public std::overflow_error {
    public:
        inline NumberTooLargeException() : std::overflow_error(
                "The given integer type doesn't have the capacity to store the rational.") {}
    };
}