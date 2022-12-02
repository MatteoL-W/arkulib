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

#include "Exceptions/Exceptions.hpp"

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
        inline constexpr Rational() : m_numerator(0), m_denominator(1) { verifyTemplateType(); }

        /**
         * @brief Classic constructor : create a rational from a numerator and a denominator (set default at 1)
         * @param numerator
         * @param denominator
         */
        inline constexpr Rational(const IntLikeType numerator, const IntLikeType denominator,
                                  const bool willBeReduce = true)
                : m_numerator(numerator), m_denominator(denominator) {
            verifyTemplateType();
            verifyDenominator(denominator);
            if (willBeReduce) *this = simplify();
        }

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
            verifyTemplateType();
            *this = fromFloatingPoint(nonRational, 10);
        }

        /**
         * @brief Default Destructor
         */
        inline ~Rational() = default;

        /************************************************************************************************************
         ************************************************ GETTERS ***************************************************
         ************************************************************************************************************/

        [[nodiscard]] inline IntLikeType getNumerator() const noexcept { return m_numerator; }

        [[nodiscard]] inline IntLikeType getDenominator() const noexcept { return m_denominator; }

        /**
         * @brief Getter with [] operator
         * @param id
         * @return If id == 0 => return numerator; if id == 1 => return denominator
         */
        inline const IntLikeType &operator[](const size_t &id) const {
            if (id == 0) { return m_numerator; }
            else if (id == 1) { return m_denominator; }
            else { throw Arkulib::Exceptions::InvalidAccessArgument(); }
        }

        /************************************************************************************************************
         ************************************************ SETTERS ***************************************************
         ************************************************************************************************************/

        inline void setNumerator(IntLikeType numerator) { m_numerator = numerator; };

        inline void setDenominator(IntLikeType denominator) {
            verifyDenominator(denominator);
            m_denominator = denominator;
        };

        /**
         * @brief Setter with [] operator. Example: rational[0] = 1 and rational[1] = 2 => (1/2)
         * @param id
         */
        inline IntLikeType &operator[](const size_t &id) {
            if (id == 0) { return m_numerator; }
            else if (id == 1) { return m_denominator; }
            else { throw Arkulib::Exceptions::InvalidAccessArgument(); }
        }

        /************************************************************************************************************
         ************************************************* STATUS ***************************************************
         ************************************************************************************************************/

        /**
         * @return True if the rational is negative
         */
        [[maybe_unused]] [[nodiscard]] inline bool isNegative() const { return m_numerator < 0; };

        /**
         * @return True if the rational is an integer
         */
        [[maybe_unused]] [[nodiscard]] inline bool isInteger() const { return m_denominator == 1; };

        /**
         * @return True if the rational is equal to zero
         */
        [[maybe_unused]] [[nodiscard]] inline bool isZero() const { return m_numerator == 0; };

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
        inline Rational<IntLikeType> operator+(const U &nonRational) {
            return Rational<IntLikeType>(nonRational) + *this;
        }

        /**
         * @brief Addition operation between a non-rational and a rational. Example: int + Rational
         * @tparam U
         * @param nonRational
         * @param rational
         * @return The sum in Rational
         */
        template<typename U>
        inline friend Rational<IntLikeType> operator+(U nonRational, const Rational<IntLikeType> &rational) {
            return Rational<IntLikeType>(nonRational) + rational;
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
        inline Rational<IntLikeType> operator-(const U &nonRational) {
            return *this - Rational<IntLikeType>(nonRational);
        }

        /**
         * @brief Subtraction operation between a non-rational and a rational. Example: int - Rational
         * @tparam U
         * @param nonRational
         * @param rational
         * @return The subtraction in Rational
         */
        template<typename U>
        inline friend Rational<IntLikeType> operator-(U nonRational, const Rational<IntLikeType> &rational) {
            return Rational<IntLikeType>(nonRational) - rational;
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
        inline Rational<IntLikeType> operator*(const U &nonRational) {
            return *this * Rational<IntLikeType>(nonRational);
        }

        /**
         * @brief Multiplication operation between a non-rational and a rational. Example: int * Rational
         * @tparam U
         * @param nonRational
         * @param rational
         * @return The multiplication in Rational
         */
        template<typename U>
        inline friend Rational<IntLikeType> operator*(U nonRational, const Rational<IntLikeType> &rational) {
            return Rational<IntLikeType>(nonRational) * rational;
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
        inline Rational<IntLikeType> operator/(const U &nonRational) {
            return *this / Rational<IntLikeType>(nonRational);
        }

        /**
         * @brief Division operation between a non-rational and a rational. Example: int / Rational
         * @tparam U
         * @param nonRational
         * @param rational
         * @return The division in Rational
         */
        template<typename U>
        inline friend Rational<IntLikeType> operator/(U nonRational, const Rational<IntLikeType> &rational) {
            return Rational<IntLikeType>(nonRational) / rational;
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
            Rational<IntLikeType> leftRational = simplify();
            Rational<IntLikeType> rightRational = anotherRational.simplify();

            return (leftRational.getNumerator() == rightRational.getNumerator() &&
                    leftRational.getDenominator() == rightRational.getDenominator());
        }

        /**
         * @brief Comparison between a rational and a non-rational. Example: Rational == int
         * @tparam U
         * @param nonRational
         * @return True if the rational is equal to the second operand
         */
        template<typename U>
        inline bool operator==(const U &nonRational) { return Rational<IntLikeType>(nonRational) == *this; }

        /**
         * @brief Comparison between a non-rational and a rational. Example: int == Rational
         * @tparam U
         * @param nonRational
         * @param rational
         * @return True if the non-rational is equal to the rational
         */
        template<typename U>
        inline friend bool operator==(U nonRational, const Rational<IntLikeType> &rational) {
            return Rational<IntLikeType>(nonRational) == rational;
        }

        /************************************************************************************************************
         ********************************************** OPERATOR != *************************************************
         ************************************************************************************************************/

        //ToDo Test
        /**
         * @brief Different comparison between 2 rationals
         * @param anotherRational
         * @return True if the first rational is different to the second
         */
        inline bool operator!=(const Rational<IntLikeType> &anotherRational) {
            Rational<IntLikeType> leftRational = simplify();
            Rational<IntLikeType> rightRational = anotherRational.simplify();

            return (leftRational.getNumerator() != rightRational.getNumerator() ||
                    leftRational.getDenominator() != rightRational.getDenominator());
        }

        /**
        * @brief Different comparison between a rational and a non-rational. Example: Rational != int
        * @tparam U
        * @param nonRational
        * @return True if the rational is different to the second operand
        */
        template<typename U>
        inline bool operator!=(const U &nonRational) { return Rational<IntLikeType>(nonRational) != *this; }

        /**
         * @brief Different comparison between a non-rational and a rational. Example: int != Rational
         * @tparam U
         * @param nonRational
         * @param rational
         * @return True if the non-rational is different to the rational
         */
        template<typename U>
        inline friend bool operator!=(U nonRational, const Rational<IntLikeType> &rational) {
            return Rational<IntLikeType>(nonRational) != rational;
        }

        /************************************************************************************************************
         *********************************************** OPERATOR < *************************************************
         ************************************************************************************************************/

        /**
         * @brief < Comparison between 2 rationals
         * @param anotherRational
         * @return True if the first rational is inferior to the second
         */
        inline bool operator<(const Rational<IntLikeType> &anotherRational) {
            //ToDo Passer par autre chose qu'un double?
            double firstRatio = (double) getNumerator() / getDenominator();
            double secondRatio = (double) anotherRational.getNumerator() / anotherRational.getDenominator();
            return (firstRatio < secondRatio);
        }

        /**
         * @brief < Comparison between a rational and a non-rational. Example: Rational < int
         * @tparam U
         * @param nonRational
         * @return True if the rational is inferior to the second operand
         */
        template<typename U>
        inline bool operator<(const U &nonRational) { return *this < Rational<IntLikeType>(nonRational); }

        /**
         * @brief < Comparison between a non-rational and a rational. Example: int < Rational
         * @tparam U
         * @param nonRational
         * @param rational
         * @return True if the non-rational is inferior to the rational
         */
        template<typename U>
        inline friend bool operator<(U nonRational, const Rational<IntLikeType> &rational) {
            return Rational<IntLikeType>(nonRational) < rational;
        }

        /************************************************************************************************************
         *********************************************** OPERATOR <= *************************************************
         ************************************************************************************************************/

        /**
         * @brief <= Comparison between 2 rationals
         * @param anotherRational
         * @return True if the first rational is inferior to the second
         */
        inline bool operator<=(const Rational<IntLikeType> &anotherRational) {
            //ToDo Passer par autre chose qu'un double?
            double firstRatio = (double) getNumerator() / getDenominator();
            double secondRatio = (double) anotherRational.getNumerator() / anotherRational.getDenominator();
            return (firstRatio <= secondRatio);
        }

        /**
         * @brief <= Comparison between a rational and a non-rational. Example: Rational <= int
         * @tparam U
         * @param nonRational
         * @return True if the rational is inferior to the second operand
         */
        template<typename U>
        inline bool operator<=(const U &nonRational) { return *this <= Rational<IntLikeType>(nonRational); }

        /**
         * @brief <= Comparison between a non-rational and a rational. Example: int <= Rational
         * @tparam U
         * @param nonRational
         * @param rational
         * @return True if the non-rational is inferior to the rational
         */
        template<typename U>
        inline friend bool operator<=(U nonRational, const Rational<IntLikeType> &rational) {
            return Rational<IntLikeType>(nonRational) <= rational;
        }

        /************************************************************************************************************
         *********************************************** OPERATOR > *************************************************
         ************************************************************************************************************/

        /**
         * @brief > Comparison between 2 rationals
         * @param anotherRational
         * @return True if the first rational is inferior to the second
         */
        inline bool operator>(const Rational<IntLikeType> &anotherRational) {
            double firstRatio = (double) getNumerator() / getDenominator();
            double secondRatio = (double) anotherRational.getNumerator() / anotherRational.getDenominator();
            return (firstRatio > secondRatio);
        }

        /**
         * @brief > Comparison between a rational and a non-rational. Example: Rational > int
         * @tparam U
         * @param nonRational
         * @return True if the rational is inferior to the second operand
         */
        template<typename U>
        inline bool operator>(const U &nonRational) { return *this > Rational<IntLikeType>(nonRational); }

        /**
         * @brief < Comparison between a non-rational and a rational. Example: int > Rational
         * @tparam U
         * @param nonRational
         * @param rational
         * @return True if the non-rational is superior to the rational
         */
        template<typename U>
        inline friend bool operator>(U nonRational, const Rational<IntLikeType> &rational) {
            return Rational<IntLikeType>(nonRational) > rational;
        }

        /************************************************************************************************************
         *********************************************** OPERATOR >= *************************************************
         ************************************************************************************************************/

        /**
         * @brief >= Comparison between 2 rationals
         * @param anotherRational
         * @return True if the first rational is inferior to the second
         */
        inline bool operator>=(const Rational<IntLikeType> &anotherRational) {
            double firstRatio = (double) getNumerator() / getDenominator();
            double secondRatio = (double) anotherRational.getNumerator() / anotherRational.getDenominator();
            return (firstRatio >= secondRatio);
        }

        /**
         * @brief >= Comparison between a rational and a non-rational. Example: Rational >= int
         * @tparam U
         * @param nonRational
         * @return True if the rational is inferior to the second operand
         */
        template<typename U>
        inline bool operator>=(const U &nonRational) { return *this >= Rational<IntLikeType>(nonRational); }

        /**
         * @brief < Comparison between a non-rational and a rational. Example: int >= Rational
         * @tparam U
         * @param nonRational
         * @param rational
         * @return True if the non-rational is superior to the rational
         */
        template<typename U>
        inline friend bool operator>=(U nonRational, const Rational<IntLikeType> &rational) {
            return Rational<IntLikeType>(nonRational) >= rational;
        }

        /************************************************************************************************************
         *********************************************** OPERATOR += ************************************************
         ************************************************************************************************************/

        /**
         * @brief Addition assignment operation between 2 rationals
         * @param anotherRational
         * @return The sum in Rational
         */
        Rational<IntLikeType> operator+=(const Rational<IntLikeType> &anotherRational) {
            *this = *this + anotherRational;
            return *this;
        }

        /**
         * @brief Addition assignment operation between a rational and another type. Example: Rational + int
         * @tparam U
         * @param nonRational
         * @return The sum assigment in Rational
         */
        template<typename U>
        inline Rational<IntLikeType> operator+=(const U &nonRational) {
            *this = *this + Rational<IntLikeType>(nonRational);
            return *this;
        }

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
        [[maybe_unused]] constexpr inline Rational<IntLikeType> inverse() const {
            return Rational<IntLikeType>(m_denominator, m_numerator);
        }

        /**
        * @brief Give the square root of a rational
        * @return The square root as a Rational
        */
        [[maybe_unused]] constexpr Rational<IntLikeType> sqrt() const;

        /**
        * @brief Give the cosine of a rational
        * @return The cosine as a Rational
        */
        [[maybe_unused]] constexpr Rational<IntLikeType> cos() const;

        /**
        * @brief Give the exponential of a rational
        * @return The exponential as a Rational
        */
        [[maybe_unused]] constexpr Rational<IntLikeType> exp() const;

        /**
        * @brief Give the power of a rational
        * @return The power as a Rational
        */
        [[maybe_unused]] constexpr Rational<IntLikeType> pow(double k) const;

        /**
         * @brief Give the abs of a rational
         * @return The Rational in absolute value
         */
        [[maybe_unused]] constexpr inline Rational<IntLikeType> abs() const {
            return Rational<IntLikeType>(std::abs(m_numerator), std::abs(m_denominator));
        };

        //ToDo: Peut-être une fonction qui permet de simplifier le rationnel ? Si c'est faisable, genre qui renvoie une approximation plus simple
        //ToDo: ...

        /**
         * @brief Simplify the Rational with GCD (called in constructor)
         */
        [[maybe_unused]] [[nodiscard]] constexpr Rational<IntLikeType> simplify() const noexcept;

        /************************************************************************************************************
         ************************************************* STATIC ***************************************************
         ************************************************************************************************************/

        /**
         * @brief Return zero in Rational Type
         * @return Rational with 0 as numerator and 1 as denominator
         */
        inline constexpr static Rational<IntLikeType> Zero() noexcept { return Rational<IntLikeType>(0, 1); }

        /**
         * @brief Return one in Rational Type
         * @return Rational with 1 as numerator and 1 as denominator
         */
        inline constexpr static Rational<IntLikeType> One() noexcept { return Rational<IntLikeType>(1, 1); }

        /**
         * @brief Return Pi in Rational Type
         * @return An approximation of Pi
         */
        inline constexpr static Rational<IntLikeType> Pi() noexcept { return Rational<IntLikeType>(355, 113); }

        /**
         * @brief Return an approximation of +infinite in Rational Type
         * @return 1 as numerator and 0 as denominator
         */
        [[maybe_unused]] inline constexpr static Rational<IntLikeType>
        Infinite() noexcept { return Rational<IntLikeType>(1, 0); }

        /************************************************************************************************************
         *********************************************** CONVERSION *************************************************
         ************************************************************************************************************/

        /**
         * @brief Get the integer part of the ratio
         * @return An int (type IntLikeType)
         */
        [[nodiscard]] inline constexpr IntLikeType toInteger() const noexcept {
            return IntLikeType(m_numerator / m_denominator);
        }

        /**
         * @brief Get an approximation floating point number of the ratio
         * @tparam U
         * @return A floating point number (type U)
         */
        template<typename U = float>
        [[nodiscard]] inline constexpr U toRealNumber() const noexcept { return m_numerator / U(m_denominator); }

        /**
         * @brief Return ( _numerator_ / _denominator_ ) as a string
         * @return std::string
         */
        [[nodiscard]] inline std::string toString() const noexcept {
            return "(" + std::to_string(getNumerator()) + " / " + std::to_string(getDenominator()) + ")";
        }

        /**
         * @brief A method who automatically set numerator and denominator to approach the float parameter
         * @tparam FloatLikeType
         * @param floatingRatio
         * @param iter
         * @return
         */
        template<typename FloatLikeType = double>
        [[nodiscard]] constexpr Rational<IntLikeType> fromFloatingPoint(FloatLikeType floatingRatio, size_t iter) const;

    private:
        /************************************************************************************************************
         ********************************************* MEMBERS ******************************************************
         ************************************************************************************************************/

        IntLikeType m_numerator; /*!< Rational's numerator */

        IntLikeType m_denominator; /*!< Rational's denominator */

        /************************************************************************************************************
         ********************************************* METHODS ******************************************************
         ************************************************************************************************************/

        constexpr inline void verifyTemplateType() const {
            if (!std::is_integral<IntLikeType>()) throw Exceptions::FloatTypeGiven();
        };

        constexpr inline void verifyDenominator(const IntLikeType denominator) {
            if (denominator == static_cast<IntLikeType>(0)) throw Exceptions::DivideByZeroException();

            if (denominator < static_cast<IntLikeType>(0)) {
                m_numerator = -m_numerator;
                m_denominator = -denominator;
            }
        }
    };

    /************************************************************************************************************
     ********************************************* OPERATOR + DEF ***********************************************
     ************************************************************************************************************/

    template<typename IntLikeType>
    Rational<IntLikeType> Rational<IntLikeType>::operator+(const Rational<IntLikeType> &anotherRational) {
        return Rational<IntLikeType>(
                m_numerator * anotherRational.m_denominator + m_denominator * anotherRational.m_numerator,
                m_denominator * anotherRational.m_denominator
        );
    }

    /************************************************************************************************************
     ********************************************* OPERATOR - DEF ***********************************************
     ************************************************************************************************************/

    template<typename IntLikeType>
    Rational<IntLikeType> Rational<IntLikeType>::operator-(const Rational<IntLikeType> &anotherRational) {
        return Rational<IntLikeType>(
                m_numerator * anotherRational.m_denominator - m_denominator * anotherRational.m_numerator,
                m_denominator * anotherRational.m_denominator
        );
    }

    /************************************************************************************************************
     ********************************************* OPERATOR * DEF ***********************************************
     ************************************************************************************************************/

    template<typename IntLikeType>
    Rational<IntLikeType> Rational<IntLikeType>::operator*(const Rational<IntLikeType> &anotherRational) {
        return Rational<IntLikeType>(
                m_numerator * anotherRational.m_numerator,
                m_denominator * anotherRational.m_denominator
        );
    }

    /************************************************************************************************************
     ********************************************* OPERATOR / DEF ***********************************************
     ************************************************************************************************************/

    template<typename IntLikeType>
    Rational<IntLikeType> Rational<IntLikeType>::operator/(const Rational<IntLikeType> &anotherRational) {
        return Rational<IntLikeType>(
                m_numerator * anotherRational.m_denominator,
                m_denominator * anotherRational.m_numerator
        );
    }

    /************************************************************************************************************
     ************************************************ MATHS DEF *************************************************
     ************************************************************************************************************/

    template<typename IntLikeType>
    constexpr Rational<IntLikeType> Rational<IntLikeType>::sqrt() const {
        // ToDo : Do a take !
        // Do we (keep the precision) or (simplify the operations in order to ease the operations)
        if (isNegative()) throw Arkulib::Exceptions::NegativeSqrtException();
        return Rational<IntLikeType>(
                std::sqrt(double(m_numerator) / m_denominator)
        );
    }

    template<typename IntLikeType>
    Rational<IntLikeType> constexpr Rational<IntLikeType>::cos() const {
        return Rational<IntLikeType>(
                std::cos(double(m_numerator) / m_denominator)
        );
    }

    template<typename IntLikeType>
    Rational<IntLikeType> constexpr Rational<IntLikeType>::exp() const {
        return Rational<IntLikeType>(
                std::exp(double(m_numerator) / m_denominator)
        );
    }

    template<typename IntLikeType>
    //ToDo: May be optimised !!!!!!!! + Remove integer() function
    Rational<IntLikeType> constexpr Rational<IntLikeType>::pow(const double k) const {
        return Rational<IntLikeType>(
                std::pow(double(m_numerator) / m_denominator, k)
        );
    }

    template<typename IntLikeType>
    Rational<IntLikeType> constexpr Rational<IntLikeType>::simplify() const noexcept {
        const int gcd = std::gcd(m_numerator, m_denominator);
        assert(gcd != 0 && "GCD shouldn't be equal to 0");

        return Rational<IntLikeType>(
                m_numerator / gcd,
                m_denominator / gcd,
                false
        );
    }

    /************************************************************************************************************
     ********************************************** CONVERSION DEF **********************************************
     ************************************************************************************************************/

    template<typename IntLikeType>
    template<typename FloatLikeType>
    Rational<IntLikeType> constexpr
    Rational<IntLikeType>::fromFloatingPoint(const FloatLikeType floatingRatio, size_t iter) const {
        //ToDo: Throw une except si n ou d supérieur à max
        //ToDo: Trouver un moyen de pas utiliser de paramètres iter
        if (floatingRatio < static_cast<FloatLikeType>(0)) {
            return -fromFloatingPoint(-floatingRatio, iter);
        }

        const auto THRESHOLD = static_cast<FloatLikeType>(0.01);
        if (floatingRatio <= 0 + THRESHOLD || iter == 0) {
            return Rational<IntLikeType>::Zero();
        }

        if (floatingRatio < static_cast<FloatLikeType>(1)) {
            return fromFloatingPoint(static_cast<FloatLikeType>(1) / floatingRatio, iter).inverse();
        }

        IntLikeType integerPart = IntLikeType(floatingRatio);
        return fromFloatingPoint(floatingRatio - integerPart, iter - 1)
               + Arkulib::Rational<IntLikeType>(integerPart, static_cast<IntLikeType>(1));
    }

    /************************************************************************************************************
     ******************************************* STD::COUT OVERRIDE *********************************************
     ************************************************************************************************************/

    template<typename IntLikeType>
    std::ostream &operator<<(std::ostream &stream, const Arkulib::Rational<IntLikeType> &rational) {
        return stream << rational.toString();
    }

}
