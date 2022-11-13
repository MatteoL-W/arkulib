/**
 * @file      Rational.hpp
 * @author    Elise MASSA
 * @author    Mattéo LECLERCQ
 * @date      2022
 * @warning   The use of Ratio isn't as performant as a simple float type
 * @copyright WTFPL
 */

#include <stdexcept>

namespace Arkulib {
    /**
     * @brief An exception to handle divide by 0
     */
    class DivideByZeroException : public std::runtime_error {
    public:
        inline DivideByZeroException() : std::runtime_error("Denominator must not be null") {}
    };

    /**
     * @brief This class can be used to express rationals
     * @tparam T
     */
    template<typename T = int>
    class Rational {

    public:
        /**
         * @brief Default constructor : create a rational from a numerator and a denominator (set default at 1)
         * @param numerator
         * @param denominator
         */
        inline constexpr explicit Rational(const T numerator, const T denominator = 1)
                : m_numerator(numerator), m_denominator(denominator) {
            if (denominator == 0) {
                throw DivideByZeroException();
            }
            // Faire pgcd
        };

        /**
         * @defgroup constant_methods Methods which returns constants
         * @brief Return a zero constant rational
         * @return Rational<T>
         */
        inline constexpr Rational<T> Zero() { return Rational<T>(0, 1); };

        /**
         * @brief Return infinite constant rational
         * @return Rational<T>
         */
        inline constexpr Rational<T> Infinite() { return Rational<T>(1, 0); };

    private:
        T m_numerator; /*!< Rational's numerator */

        T m_denominator; /*!< Rational's denominator */

    };

}