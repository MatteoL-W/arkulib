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
#include <numeric>

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

            if (denominator < 0) {
                m_numerator = -m_numerator;
                m_denominator = -m_denominator;
            }

            simplify();
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
        }

        /************************************************************************************************************
         *********************************************** OPERATOR - *************************************************
         ************************************************************************************************************/

        /**
         * @brief Subtraction operation between 2 rationals
         * @param anotherRational
         * @return The subtraction in Rational
         */
        Rational<T> operator-(const Rational<T> &anotherRational);


        /**
         * @brief Subtraction operation between a rational and another type. Example: Rational - int
         * @tparam U
         * @param nonRational
         * @return The subtraction in Rational
         */
        template<typename U>
        inline Rational<T> operator-(const U &nonRational) { return *this - Rational(nonRational); }

        /**
         * @brief Subtraction operation between a non-rational and a rational. Example: int - Rational
         * @tparam U
         * @param nonRational
         * @param rational
         * @return The subtraction in Rational
         */

        template<typename U>
        inline friend Rational<T> operator-(U nonRational, const Rational<T> &rational) {
            return Rational(nonRational) - rational;
        }

        /************************************************************************************************************
         *********************************************** OPERATOR * *************************************************
         ************************************************************************************************************/

        /**
         * @brief Multiplication operation between 2 rationals
         * @param anotherRational
         * @return The multiplication in Rational
         */
        Rational<T> operator*(const Rational<T> &anotherRational);

        /**
         * @brief Multiplication operation between a rational and another type. Example: Rational * int
         * @tparam U
         * @param nonRational
         * @return The multiplication in Rational
         */
        template<typename U>
        inline Rational<T> operator*(const U &nonRational) { return *this * Rational(nonRational); }

        /**
         * @brief Multiplication operation between a non-rational and a rational. Example: int * Rational
         * @tparam U
         * @param nonRational
         * @param rational
         * @return The multiplication in Rational
         */
        template<typename U>
        inline friend Rational<T> operator*(U nonRational, const Rational<T> &rational) {
            return Rational(nonRational) * rational;
        }


        /************************************************************************************************************
         *********************************************** OPERATOR / *************************************************
         ************************************************************************************************************/
        /**
         * @brief Division operation between 2 rationals
         * @param anotherRational
         * @return The division in Rational
         */
        Rational<T> operator/(const Rational<T> &anotherRational);


        /**
         * @brief Division operation between a rational and another type. Example: Rational / int
         * @tparam U
         * @param nonRational
         * @return The division in Rational
         */
        template<typename U>
        inline Rational<T> operator/(const U &nonRational) { return *this / Rational(nonRational); }

        /**
         * @brief Division operation between a non-rational and a rational. Example: int / Rational
         * @tparam U
         * @param nonRational
         * @param rational
         * @return The division in Rational
         */

        template<typename U>
        inline friend Rational<T> operator/(U nonRational, const Rational<T> &rational) {
            return Rational(nonRational) / rational;
        }


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
        }

        /************************************************************************************************************
         ************************************************* MATHS ****************************************************
         ************************************************************************************************************/

        /**
         * @brief Inverse a rationnal : a / b into b / a
         * @return The inverted Rational
         */
        Rational<T> inverse();

        /**
        * @brief Give the square root of a rational
        * @return The the square root as a Rational
        */
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
        return Rational <T>(
                m_denominator,
                m_numerator
        );
    }


    template<typename T>
    Rational<T> Rational<T>::sqrt(){

         /*
        if(m_numerator || m_denominator < 0){
            std::runtime_error("Rational must be positive for sqrt to be applied");
        }*/
         Rational<T> result;

         const size_t iter = 10000;
         result = result.fromFloat(std::sqrt(m_numerator/m_denominator), iter);
         //ToDo correct fromFloat
         return result;

    }

    template<typename T>
    void Rational<T>::simplify() noexcept {
        int gcd = std::gcd(m_numerator, m_denominator);

        m_denominator /= gcd;
        m_numerator /= gcd;
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
            return fromFloat(1. / floatingRatio, iter).inverse();
        }

        if (floatingRatio >= 1) {
            T integerPart = T(floatingRatio);
            return fromFloat(floatingRatio - integerPart, iter - 1) + integerPart;
        }

        //ToDo: Throw exception here
    }


    /************************************************************************************************************
     ******************************************* STD::COUT OVERRIDE *********************************************
     ************************************************************************************************************/

    template<typename T>
    std::ostream &operator<<(std::ostream &stream, const Arkulib::Rational<T> &rational) {
        return stream << rational.toString();
    }

}
