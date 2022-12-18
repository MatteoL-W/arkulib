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
     * @brief An exception to handle too large precision
     */
    class DigitsTooLargeException : public std::overflow_error {
    public:
        inline DigitsTooLargeException() : std::overflow_error(
                "The given precision seems to large to be wanted. You should reduce it.") {}
    };
}