/**
 * @file      Rational.hpp
 * @author    Elise MASSA
 * @author    Mattéo LECLERCQ
 * @date      2022
 * @warning   The use of Ratio isn't as performant as a simple float type
 * @copyright WTFPL
 */

#include <cmath>
#include <fstream>
#include <iostream>
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
         * @brief Default constructor : instantiate an object without parameters.
         */
        Rational() = default;

        /**
         * @brief Classic constructor : create a rational from a numerator and a denominator (set default at 1)
         * @param numerator
         * @param denominator
         */
        inline constexpr explicit Rational(const T numerator, const T denominator = 1)
                : m_numerator(numerator), m_denominator(denominator) {
            if (denominator == 0) {
                throw DivideByZeroException();
            }

            simplify();
            // numerator ne doit pas être négatif
        };

        /**
         * @brief Copy constructor
         * @param reference
         */
        inline constexpr Rational(const Rational<T> &reference) = default;

        /**
         * @brief Default Destructor
         */
        inline ~Rational() = default;

        template<typename U>
        Rational<T> operator+(const U &f);

        Rational<T> operator+(const Rational<T> &r);

        Rational<T> operator-(const Rational<T> &r);

        Rational<T> operator*(const Rational<T> &r);

        Rational<T> operator/(const Rational<T> &r);

        Rational<T> inverse();

        Rational<T> sqrt();

        /**
         * @brief Return a zero constant rational
         * @return Rational<T>
         */
        inline constexpr static Rational<T> Zero() noexcept { return Rational<T>(0, 1); }

        /**
         * @brief Return infinite constant rational
         * @return Rational<T>
         */
        inline constexpr static Rational<T> Infinite() noexcept { return Rational<T>(1, 0); }

        inline T getNumerator() const noexcept { return m_numerator; }

        inline T getDenominator() const noexcept { return m_denominator; }

        /**
         * @brief Get the integer part of the ratio
         * @return An int (type T)
         */
        inline constexpr T toInteger() const noexcept { return T(m_numerator / m_denominator); }

        /**
         * @brief Get an approximation floating point number of the ratio
         * @tparam U
         * @return A floating point number (type U)
         */
        template<typename U = float>
        inline constexpr U toFloat() const noexcept { return m_numerator / U(m_denominator); }

        /**
         * @brief Return ( _numerator_ / _denominator_ ) as a string
         * @return std::string
         */
        [[nodiscard]] inline std::string toString() const noexcept {
            return "(" + std::to_string(getNumerator()) + " / " + std::to_string(getDenominator()) + ")";
        }

        /**
         * @brief A method who automatically set numerator and denominator to approach the parameter float
         * @tparam U
         * @param floatingRatio
         * @param iter
         * @return
         */
        template<typename U = float>
        Rational<T> fromFloat(U floatingRatio, size_t iter) const noexcept;

        /**
         * @brief Simplify the Rational with GCD (called in constructor)
         */
        void simplify() noexcept;

    private:
        T m_numerator; /*!< Rational's numerator */

        T m_denominator; /*!< Rational's denominator */

    };

    template<typename T>
    std::ostream &operator<<(std::ostream &stream, Arkulib::Rational<T> &r) {
        return stream << r.toString();
    }

    template<typename T>
    Rational<T> Rational<T>::operator+(const Rational<T> &r) {
        //ToDo Faire pareil pour les autres opérateurs
        return Rational<T>(
                m_numerator * r.m_denominator + m_denominator * r.m_numerator,
                m_denominator * r.m_denominator
        );
    }

    template<typename T>
    template<typename U>
    Rational<T> Rational<T>::operator+(const U &f) {
        //ToDo Faire pareil pour les autres opérateurs mais pas tout de suite :)
        return Rational(f) + *this;
    }

    template<typename T>
    Rational<T> Rational<T>::operator-(const Rational<T> &r) {
        Rational<T> result;
        result.m_numerator = m_numerator * r.m_denominator - m_denominator * r.m_numerator;
        result.m_denominator = m_denominator * r.m_denominator;
        return result;
    }

    template<typename T>
    Rational<T> Rational<T>::operator*(const Rational<T> &r) {
        Rational<T> result;
        result.m_numerator = m_numerator * r.m_numerator;
        result.m_denominator = m_denominator * r.m_denominator;
        return result;
    }

    template<typename T>
    Rational<T> Rational<T>::operator/(const Rational<T> &r) {
        Rational<T> result;
        result.m_numerator = m_numerator * r.m_denominator;
        result.m_denominator = m_denominator * r.m_numerator;
        return result;
    }

    template<typename T>
    Rational<T> Rational<T>::inverse() {
        Rational<T> result;
        result.m_numerator = m_denominator;
        result.m_denominator = m_numerator;
        return result;
    }

    /*
    template<typename T>
    Rational<T> Rational<T>::sqrt(){
        Rational<T> result;
        //ToDo exception if f is negative
    }*/

    template<typename T>
    template<typename U>
    Rational<T> Rational<T>::fromFloat(const U floatingRatio, const size_t iter) const noexcept {
        //ToDo: Trouver un moyen de pas utiliser de paramètres iter

        const float threshold = 0.01;
        if (floatingRatio <= 0 + threshold || iter == 0) {
            return Rational::Zero();
        }

        if (floatingRatio < 1) {
            return fromFloat(1 / floatingRatio, iter).inverse();
        }

        if (floatingRatio >= 1) {
            T integerPart = T(floatingRatio);
            return fromFloat(floatingRatio - integerPart, iter - 1) + integerPart;
        }

        //ToDo: Throw exception here
    }

    template<typename T>
    void Rational<T>::simplify() noexcept {
        //ToDo: avec std::gcd
    }

}
