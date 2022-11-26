/**
 * @file      Rational.hpp
 * @author    Elise MASSA
 * @author    Mattéo LECLERCQ
 * @date      2022
 * @warning   The use of Ratio isn't as performant as a simple float type
 * @copyright WTFPL
 */

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>

#include "Exceptions/DivideByZeroException.hpp"
#include "Exceptions/NegativeSqrtException.hpp"

namespace Arkulib {
    /**
     * @brief This class can be used to express rationals
     * @tparam IntLikeType
     */
    template<typename IntLikeType = int>
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
        inline constexpr Rational(const IntLikeType numerator, const IntLikeType denominator)
                : m_numerator(numerator), m_denominator(denominator) {
            if (denominator == 0) throw Arkulib::Exceptions::DivideByZeroException();

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
        inline constexpr Rational(const Rational<IntLikeType> &reference) = default;

        /**
         * @brief Create a rational from a floating number
         * @tparam U
         * @param nonRational
         */
        template<typename U>
        inline constexpr explicit Rational(const U &nonRational) {
            *this = fromFloat(nonRational, 10);
        }

        /**
         * @brief Default Destructor
         */
        inline ~Rational() = default;

        /************************************************************************************************************
         ************************************************ GETTERS ***************************************************
         ************************************************************************************************************/

        inline IntLikeType getNumerator() const noexcept { return m_numerator; }

        inline IntLikeType getDenominator() const noexcept { return m_denominator; }

        /************************************************************************************************************
         ************************************************* STATUS ***************************************************
         ************************************************************************************************************/

        /**
         * @return True if the rational is negative
         */
        inline bool isNegative() { return m_numerator < 0; };

        /**
         * @return True if the rational is an integer
         */
        inline bool isInteger() { return m_denominator == 1; };

        /**
         * @return True if the rational is equal to zero
         */
        inline bool isZero() { return m_denominator == 0; };

        /************************************************************************************************************
         *********************************************** OPERATOR + *************************************************
         ************************************************************************************************************/

        /**
         * @brief Addition operation between 2 rationals
         * @param anotherRational
         * @return The sum in Rational
         */
        Rational<IntLikeType> operator+(const Rational<IntLikeType> &anotherRational);

        /**
         * @brief Addition operation between a rational and another type. Example: Rational + int
         * @tparam U
         * @param nonRational
         * @return The sum in Rational
         */
        template<typename U>
        inline Rational<IntLikeType> operator+(const U &nonRational) { return Rational(nonRational) + *this; }

        /**
         * @brief Addition operation between a non-rational and a rational. Example: int + Rational
         * @tparam U
         * @param nonRational
         * @param rational
         * @return The sum in Rational
         */
        template<typename U>
        inline friend Rational<IntLikeType> operator+(U nonRational, const Rational<IntLikeType> &rational) {
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
        Rational<IntLikeType> operator-(const Rational<IntLikeType> &anotherRational);

        /**
         * @brief Subtraction operation between a rational and another type. Example: Rational - int
         * @tparam U
         * @param nonRational
         * @return The subtraction in Rational
         */
        template<typename U>
        inline Rational<IntLikeType> operator-(const U &nonRational) { return *this - Rational(nonRational); }

        /**
         * @brief Subtraction operation between a non-rational and a rational. Example: int - Rational
         * @tparam U
         * @param nonRational
         * @param rational
         * @return The subtraction in Rational
         */
        template<typename U>
        inline friend Rational<IntLikeType> operator-(U nonRational, const Rational<IntLikeType> &rational) {
            return Rational(nonRational) - rational;
        }

        /**
         * @brief Unary operator, allow to do -Rational
         * @param rational
         * @return The rational in negative
         */
        inline friend Rational operator-(const Rational &rational) {
            return Rational<IntLikeType>(-rational.getNumerator(), rational.getDenominator());
        }

        /************************************************************************************************************
         *********************************************** OPERATOR * *************************************************
         ************************************************************************************************************/

        /**
         * @brief Multiplication operation between 2 rationals
         * @param anotherRational
         * @return The multiplication in Rational
         */
        Rational<IntLikeType> operator*(const Rational<IntLikeType> &anotherRational);

        /**
         * @brief Multiplication operation between a rational and another type. Example: Rational * int
         * @tparam U
         * @param nonRational
         * @return The multiplication in Rational
         */
        template<typename U>
        inline Rational<IntLikeType> operator*(const U &nonRational) { return *this * Rational(nonRational); }

        /**
         * @brief Multiplication operation between a non-rational and a rational. Example: int * Rational
         * @tparam U
         * @param nonRational
         * @param rational
         * @return The multiplication in Rational
         */
        template<typename U>
        inline friend Rational<IntLikeType> operator*(U nonRational, const Rational<IntLikeType> &rational) {
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
        Rational<IntLikeType> operator/(const Rational<IntLikeType> &anotherRational);

        /**
         * @brief Division operation between a rational and another type. Example: Rational / int
         * @tparam U
         * @param nonRational
         * @return The division in Rational
         */
        template<typename U>
        inline Rational<IntLikeType> operator/(const U &nonRational) { return *this / Rational(nonRational); }

        /**
         * @brief Division operation between a non-rational and a rational. Example: int / Rational
         * @tparam U
         * @param nonRational
         * @param rational
         * @return The division in Rational
         */
        template<typename U>
        inline friend Rational<IntLikeType> operator/(U nonRational, const Rational<IntLikeType> &rational) {
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
        inline bool operator==(const Rational<IntLikeType> &anotherRational) {
            // ToDo: Gérer les multiples ?
            // + ToDo: Là (1/2) == (2/1) donc c'est grave faux
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
        inline friend bool operator==(U nonRational, const Rational<IntLikeType> &rational) {
            return Rational(nonRational) == rational;
        }

        /************************************************************************************************************
         ********************************************** OPERATOR != *************************************************
         ************************************************************************************************************/

        /************************************************************************************************************
         *********************************************** OPERATOR < *************************************************
         ************************************************************************************************************/

        /************************************************************************************************************
         *********************************************** OPERATOR <= *************************************************
         ************************************************************************************************************/

        /************************************************************************************************************
         *********************************************** OPERATOR > *************************************************
         ************************************************************************************************************/

        /************************************************************************************************************
         *********************************************** OPERATOR >= *************************************************
         ************************************************************************************************************/

        /************************************************************************************************************
         *********************************************** OPERATOR += ************************************************
         ************************************************************************************************************/

        /************************************************************************************************************
         *********************************************** OPERATOR -= ************************************************
         ************************************************************************************************************/

        /************************************************************************************************************
         *********************************************** OPERATOR *= ************************************************
         ************************************************************************************************************/

        /************************************************************************************************************
         *********************************************** OPERATOR /= ************************************************
         ************************************************************************************************************/

        /************************************************************************************************************
         ************************************************* MATHS ****************************************************
         ************************************************************************************************************/

        /**
         * @brief Inverse a rational : a / b into b / a
         * @return The inverted Rational
         */
        inline Rational<IntLikeType> inverse() { return Rational<IntLikeType>(m_denominator, m_numerator); }

        /**
        * @brief Give the square root of a rational
        * @return The square root as a Rational
        */
        Rational<IntLikeType> sqrt();

        /**
        * @brief Give the cosine of a rational
        * @return The cosine as a Rational
        */
        Rational<IntLikeType> cos();

        /**
        * @brief Give the exponential of a rational
        * @return The exponential as a Rational
        */
        Rational<IntLikeType> exp();

        /**
        * @brief Give the power of a rational
        * @return The power as a Rational
        */
        Rational<IntLikeType> pow(const double k);


        //ToDo: abs
        //ToDo: Peut-être une fonction qui permet de simplifier le rationel ? Si c'est faisable, genre qui renvoie une approximation plus simple
        //ToDo: ...

        /**
         * @brief Simplify the Rational with GCD (called in constructor)
         */
        void simplify() noexcept;

        /************************************************************************************************************
         ************************************************* STATIC ***************************************************
         ************************************************************************************************************/

        /**
         * @brief Return zero
         * @return Rational<IntLikeType>
         */
        inline constexpr static Rational<IntLikeType> Zero() noexcept { return Rational<IntLikeType>(0, 1); }

        /**
         * @brief Return one
         * @return Rational<IntLikeType>
         */
        inline constexpr static Rational<IntLikeType> One() noexcept { return Rational<IntLikeType>(1, 1); }

        /**
         * @brief Return an approximation of pi
         * @return Rational<IntLikeType>
         */
        inline constexpr static Rational<IntLikeType> Pi() noexcept { return Rational<IntLikeType>(355, 113); }

        /**
         * @brief Return infinite constant rational
         * @return Rational<IntLikeType>
         */
        inline constexpr static Rational<IntLikeType> Infinite() noexcept { return Rational<IntLikeType>(1, 0); }

        /************************************************************************************************************
         *********************************************** CONVERSION *************************************************
         ************************************************************************************************************/

        /**
         * @brief Get the integer part of the ratio
         * @return An int (type IntLikeType)
         */
        inline constexpr IntLikeType toInteger() const noexcept { return IntLikeType(m_numerator / m_denominator); }

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
        template<typename U = double>
        Rational<IntLikeType> fromFloat(U floatingRatio, size_t iter) const;

    private:
        /************************************************************************************************************
         ********************************************* MEMBERS ******************************************************
         ************************************************************************************************************/

        IntLikeType m_numerator; /*!< Rational's numerator */

        IntLikeType m_denominator; /*!< Rational's denominator */

    };

    /************************************************************************************************************
     ********************************************* OPERATOR + DEF ***********************************************
     ************************************************************************************************************/

    template<typename T>
    Rational<T> Rational<T>::operator+(const Rational<T> &anotherRational) {
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
        return Rational<T>(
                m_numerator * anotherRational.m_denominator - m_denominator * anotherRational.m_numerator,
                m_denominator * anotherRational.m_denominator
        );
    }

    /************************************************************************************************************
     ********************************************* OPERATOR * DEF ***********************************************
     ************************************************************************************************************/

    template<typename T>
    Rational<T> Rational<T>::operator*(const Rational<T> &anotherRational) {
        return Rational<T>(
                m_numerator * anotherRational.m_numerator,
                m_denominator * anotherRational.m_denominator
        );
    }

    /************************************************************************************************************
     ********************************************* OPERATOR / DEF ***********************************************
     ************************************************************************************************************/

    template<typename T>
    Rational<T> Rational<T>::operator/(const Rational<T> &anotherRational) {
        return Rational<T>(
                m_numerator * anotherRational.m_denominator,
                m_denominator * anotherRational.m_numerator
        );
    }

    /************************************************************************************************************
     ************************************************ MATHS DEF *************************************************
     ************************************************************************************************************/

    template<typename IntLikeType>
    Rational<IntLikeType> Rational<IntLikeType>::sqrt() {
        // ToDo : Do a take !
        // Do we (keep the precision) or (simplify the operations in order to ease the operations)
        if (isNegative()) throw Arkulib::Exceptions::NegativeSqrtException();
        return Rational<IntLikeType>(
                std::sqrt(double(m_numerator) / m_denominator)
        );
    }

    template<typename IntLikeType>
    Rational<IntLikeType> Rational<IntLikeType>::cos() {
        return Rational<IntLikeType>(
                std::cos(double(m_numerator) / m_denominator)
        );
    }

    template<typename IntLikeType>
    Rational<IntLikeType> Rational<IntLikeType>::exp() {
        return Rational<IntLikeType>(
                std::exp(double(m_numerator) / m_denominator)
        );
    }



    template<typename T>
    void Rational<T>::simplify() noexcept {
        const int gcd = std::gcd(m_numerator, m_denominator);
        assert(gcd != 0 && "GCD shouldn't be equal to 0");

        m_denominator /= gcd;
        m_numerator /= gcd;
    }

    /************************************************************************************************************
     ********************************************** CONVERSION DEF **********************************************
     ************************************************************************************************************/

    template<typename T>
    template<typename U>
    Rational<T> Rational<T>::fromFloat(const U floatingRatio, const size_t iter) const {
        //ToDo: Trouver un moyen de pas utiliser de paramètres iter
        if (floatingRatio < 0) {
            return -fromFloat(-floatingRatio, iter);
        }

        const double threshold = 0.01;
        if (floatingRatio <= 0 + threshold || iter == 0) {
            return Rational::Zero();
        }

        if (floatingRatio < 1) {
            return fromFloat(1. / floatingRatio, iter).inverse();
        }

        T integerPart = T(floatingRatio);
        return fromFloat(floatingRatio - integerPart, iter - 1) + Arkulib::Rational(integerPart, 1);
    }

    /************************************************************************************************************
     ******************************************* STD::COUT OVERRIDE *********************************************
     ************************************************************************************************************/

    template<typename T>
    std::ostream &operator<<(std::ostream &stream, const Arkulib::Rational<T> &rational) {
        return stream << rational.toString();
    }

}
