/**
 * @file      Rational.hpp
 * @author    Elise MASSA
 * @author    Mattéo LECLERCQ
 * @date      2022
 * @warning   The use of Ratio isn't as performant as a simple float type
 * @copyright WTFPL
 */

#include "Exceptions/DivideByZeroException.hpp"

namespace Arkulib {
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
            // numerator ne doit pas être négatif
        };

        /**
         * @brief Return a zero constant rational
         * @return Rational<T>
         */
        inline constexpr Rational<T> Zero() noexcept { return Rational<T>(0, 1); };

        /**
         * @brief Return infinite constant rational
         * @return Rational<T>
         */
        inline constexpr Rational<T> Infinite() noexcept { return Rational<T>(1, 0); };

        /**
         * @brief [WIP->Is It Useful?] Get the integer of the ratio
         * @return An int (type T)
         */
        inline constexpr T toInteger() noexcept {
            return T(m_numerator / m_denominator);
        }

        /**
         * @brief [WIP] Get an approximation floating point number of the ratio
         * @tparam U
         * @return A floating point number (type U)
         */
        template<typename U = float>
        inline constexpr U toFloat() noexcept {
            return U(m_numerator / m_denominator);
        }

        /**
         * @brief A method who automatically set numerator / denominator to approach the parameter float
         * @tparam U
         * @param floatingRatio
         */
        template<typename U = float>
        void fromFloat(U floatingRatio, unsigned int iter);

        /**
         * @brief Simplify the Rational with GCD (called in constructor)
         * @param ratio
         */
        void simplify();

    private:
        T m_numerator; /*!< Rational's numerator */

        T m_denominator; /*!< Rational's denominator */

    };

    template<typename T>
    template<typename U>
    void Rational<T>::fromFloat(U floatingRatio, unsigned int) {
        //ToDo
    }

    template<typename T>
    void Rational<T>::simplify() {
        //ToDo
    }

}