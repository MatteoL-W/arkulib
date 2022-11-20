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

        /************************************************************************************************************
         ****************************************** CONSTRUCTOR / DESTRUCTOR ****************************************
         ************************************************************************************************************/

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
            // ToDo numerator ne doit pas être négatif
        };

        /**
         * @brief Copy constructor
         * @param reference
         */
        inline constexpr Rational(const Rational<T> &reference) = default;

        // ToDo Faire un constructeur à partir d'un float

        /**
         * @brief Default Destructor
         */
        inline ~Rational() = default;

        /************************************************************************************************************
         ************************************************ GETTERS ***************************************************
         ************************************************************************************************************/

        inline T getNumerator() const noexcept { return m_numerator; }

        inline T getDenominator() const noexcept { return m_denominator; }

        /************************************************************************************************************
         *********************************************** OPERATOR + *************************************************
         ************************************************************************************************************/

        /**
         * @brief Addition operation between 2 rationals
         * @param anotherRational
         * @return The sum in Rational
         */
        Rational<T> operator+(const Rational<T> &anotherRational);

        /**
         * @brief Addition operation between a rational and another type. Example: Rational + int
         * @tparam U
         * @param nonRational
         * @return The sum in Rational
         */
        template<typename U>
        inline Rational<T> operator+(const U &nonRational) { return Rational(nonRational) + *this; }

        /**
         * @brief Addition operation between a non-rational and a rational. Example: int + Rational
         * @tparam U
         * @param nonRational
         * @param rational
         * @return The sum in Rational
         */
        template<typename U>
        inline friend Rational<T> operator+(U nonRational, const Rational<T> &rational) {
            return Rational(nonRational) + rational;
        };

        /************************************************************************************************************
         *********************************************** OPERATOR - *************************************************
         ************************************************************************************************************/

        Rational<T> operator-(const Rational<T> &anotherRational);

        /************************************************************************************************************
         *********************************************** OPERATOR * *************************************************
         ************************************************************************************************************/

        Rational<T> operator*(const Rational<T> &anotherRational);

        /************************************************************************************************************
         *********************************************** OPERATOR / *************************************************
         ************************************************************************************************************/

        Rational<T> operator/(const Rational<T> &anotherRational);

        /************************************************************************************************************
         ********************************************** OPERATOR == *************************************************
         ************************************************************************************************************/

        /**
         * @brief Comparison between 2 rationals
         * @param anotherRational
         * @return True if the first rational is equal to the second
         */
        inline bool operator==(const Rational<T> &anotherRational) {
            return (m_numerator * m_denominator) == (anotherRational.m_numerator * anotherRational.m_denominator);
        }

        /**
         * @brief Comparison between a rational and a non-rational. Example: Rational == int
         * @tparam U
         * @param nonRational
         * @return True if the rational is equal to the second operand
         */
        template<typename U>
        inline bool operator==(const U &nonRational) { return Rational(nonRational) == *this; }

        /**
         * @brief Comparison between a non-rational and a rational. Example: int == Rational
         * @tparam U
         * @param nonRational
         * @param rational
         * @return True if the non-rational is equal to the rational
         */
        template<typename U>
        inline friend bool operator==(U nonRational, const Rational<T> &rational) {
            return Rational(nonRational) == rational;
        };

        /************************************************************************************************************
         ************************************************* MATHS ****************************************************
         ************************************************************************************************************/

        Rational<T> inverse();

        Rational<T> sqrt();

        /**
         * @brief Simplify the Rational with GCD (called in constructor)
         */
        void simplify() noexcept;

        /************************************************************************************************************
         ************************************************* STATIC ***************************************************
         ************************************************************************************************************/

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

        /************************************************************************************************************
         *********************************************** CONVERSION *************************************************
         ************************************************************************************************************/

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
         * @brief A method who automatically set numerator and denominator to approach the float parameter
         * @tparam U
         * @param floatingRatio
         * @param iter
         * @return
         */
        template<typename U = float>
        Rational<T> fromFloat(U floatingRatio, size_t iter) const noexcept;

    private:
        /************************************************************************************************************
         ********************************************* MEMBERS ******************************************************
         ************************************************************************************************************/

        T m_numerator; /*!< Rational's numerator */

        T m_denominator; /*!< Rational's denominator */

    };

    /************************************************************************************************************
     ******************************************* STD::COUT OVERRIDE *********************************************
     ************************************************************************************************************/

    template<typename T>
    std::ostream &operator<<(std::ostream &stream, Arkulib::Rational<T> &r) {
        return stream << r.toString();
    }

    /************************************************************************************************************
     ********************************************* OPERATOR + DEF ***********************************************
     ************************************************************************************************************/

    template<typename T>
    Rational<T> Rational<T>::operator+(const Rational<T> &anotherRational) {
        //ToDo Faire pareil pour les autres opérateurs
        return Rational<T>(
                m_numerator * anotherRational.m_denominator + m_denominator * anotherRational.m_numerator,
                m_denominator * anotherRational.m_denominator
        );
    }

    /************************************************************************************************************
     ********************************************* OPERATOR - DEF ***********************************************
     ************************************************************************************************************/

    template<typename T>
    Rational<T> Rational<T>::operator-(const Rational<T> &anotherRational) {
        Rational<T> result;
        result.m_numerator = m_numerator * anotherRational.m_denominator - m_denominator * anotherRational.m_numerator;
        result.m_denominator = m_denominator * anotherRational.m_denominator;
        return result;
    }

    /************************************************************************************************************
     ********************************************* OPERATOR * DEF ***********************************************
     ************************************************************************************************************/

    template<typename T>
    Rational<T> Rational<T>::operator*(const Rational<T> &anotherRational) {
        Rational<T> result;
        result.m_numerator = m_numerator * anotherRational.m_numerator;
        result.m_denominator = m_denominator * anotherRational.m_denominator;
        return result;
    }

    /************************************************************************************************************
     ********************************************* OPERATOR / DEF ***********************************************
     ************************************************************************************************************/

    template<typename T>
    Rational<T> Rational<T>::operator/(const Rational<T> &anotherRational) {
        Rational<T> result;
        result.m_numerator = m_numerator * anotherRational.m_denominator;
        result.m_denominator = m_denominator * anotherRational.m_numerator;
        return result;
    }

    /************************************************************************************************************
     ************************************************ MATHS DEF *************************************************
     ************************************************************************************************************/

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
    void Rational<T>::simplify() noexcept {
        //ToDo: avec std::gcd
    }

    /************************************************************************************************************
     ********************************************** CONVERSION DEF **********************************************
     ************************************************************************************************************/

    template<typename T>
    template<typename U>
    Rational<T> Rational<T>::fromFloat(const U floatingRatio, const size_t iter) const noexcept {
        //ToDo: Trouver un moyen de pas utiliser de paramètres iter
        //ToDo: si c'est négatif

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

}
