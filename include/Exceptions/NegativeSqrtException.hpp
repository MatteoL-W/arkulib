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
    class NegativeSqrtException : public std::runtime_error {
    public:
        inline NegativeSqrtException() : std::runtime_error("The rational must not be negative when calling sqrt().") {}
    };
}