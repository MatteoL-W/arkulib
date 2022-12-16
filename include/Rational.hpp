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
     * @tparam IntType
     */
    template<typename IntType = int>
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
        constexpr Rational(
                IntType numerator,
                IntType denominator,
                bool willBeReduce = true,
                bool willDenominatorBeVerified = true
        );

        /**
         * @brief Create a rational from a floating number
         * @tparam FloatingType
         * @param nonRational
         */
        template<typename FloatingType>
        constexpr explicit Rational(const FloatingType &nonRational);

        /**
         * @brief Copy constructor
         * @param reference
         */
        inline constexpr Rational(const Rational<IntType> &reference) = default;

        /**
         * @brief Copy constructor with another int type
         * @tparam AnotherIntType
         * @param copiedRational
         */
        template<typename AnotherIntType>
        constexpr explicit Rational(Rational<AnotherIntType> &copiedRational);

        /**
         * @brief Default Destructor
         */
        inline ~Rational() = default;

        /************************************************************************************************************
         ************************************************ GETTERS ***************************************************
         ************************************************************************************************************/

        [[nodiscard]] inline IntType getNumerator() const noexcept { return m_numerator; }

        [[nodiscard]] inline IntType getDenominator() const noexcept { return m_denominator; }

        /**
         * @brief Getter with [] operator
         * @param id
         * @return If id == 0 => return numerator; if id == 1 => return denominator
         */
        inline const IntType &operator[](const size_t &id) const;

        /**
         * @return The numerator if numerator > denominator. Return denominator else.
         */
        [[maybe_unused]] [[nodiscard]] constexpr inline IntType getLargerOperand() { return std::max(m_numerator, m_denominator); }

        /**
         * @return The denominator if numerator > denominator. Return numerator else.
         */
        [[maybe_unused]] [[nodiscard]] constexpr inline IntType getLowerOperand() { return std::min(m_numerator, m_denominator); }

        /************************************************************************************************************
         ************************************************ SETTERS ***************************************************
         ************************************************************************************************************/

        inline void setNumerator(IntType numerator) { m_numerator = numerator; };

        inline void setDenominator(IntType denominator) {
            verifyDenominator(denominator);
            m_denominator = denominator;
        };

        /**
         * @brief Setter with [] operator. Example: rational[0] = 1 and rational[1] = 2 => (1/2)
         * @param id
         */
        inline IntType &operator[](const size_t &id);

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
        Rational<IntType> operator+(const Rational<IntType> &anotherRational);

        /**
         * @brief Addition operation between a rational and another type. Example: Rational + int
         * @tparam NonRationalType
         * @param nonRational
         * @return The sum in Rational
         */
        template<typename NonRationalType>
        inline Rational<IntType> operator+(const NonRationalType &nonRational) {
            return Rational<IntType>(nonRational) + *this;
        }

        /**
         * @brief Addition operation between a non-rational and a rational. Example: int + Rational
         * @tparam NonRationalType
         * @param nonRational
         * @param rational
         * @return The sum in Rational
         */
        template<typename NonRationalType>
        inline friend Rational<IntType> operator+(
                NonRationalType nonRational,
                const Rational<IntType> &rational
        ) {
            return Rational<IntType>(nonRational) + rational;
        }

        /************************************************************************************************************
         *********************************************** OPERATOR - *************************************************
         ************************************************************************************************************/

        /**
         * @brief Subtraction operation between 2 rationals
         * @param anotherRational
         * @return The subtraction in Rational
         */
        Rational<IntType> operator-(const Rational<IntType> &anotherRational);

        /**
         * @brief Subtraction operation between a rational and another type. Example: Rational - int
         * @tparam NonRationalType
         * @param nonRational
         * @return The subtraction in Rational
         */
        template<typename NonRationalType>
        inline Rational<IntType> operator-(const NonRationalType &nonRational) {
            return *this - Rational<IntType>(nonRational);
        }

        /**
         * @brief Subtraction operation between a non-rational and a rational. Example: int - Rational
         * @tparam NonRationalType
         * @param nonRational
         * @param rational
         * @return The subtraction in Rational
         */
        template<typename NonRationalType>
        inline friend Rational<IntType>
        operator-(NonRationalType nonRational, const Rational<IntType> &rational) {
            return Rational<IntType>(nonRational) - rational;
        }

        /**
         * @brief Unary operator, allow to do -Rational
         * @param rational
         * @return The rational in negative
         */
        inline friend Rational operator-(const Rational &rational) {
            return Rational<IntType>(-rational.getNumerator(), rational.getDenominator());
        }

        /************************************************************************************************************
         *********************************************** OPERATOR * *************************************************
         ************************************************************************************************************/

        /**
         * @brief Multiplication operation between 2 rationals
         * @param anotherRational
         * @return The multiplication in Rational
         */
        Rational<IntType> operator*(const Rational<IntType> &anotherRational);

        /**
         * @brief Multiplication operation between a rational and another type. Example: Rational * int
         * @tparam NonRationalType
         * @param nonRational
         * @return The multiplication in Rational
         */
        template<typename NonRationalType>
        inline Rational<IntType> operator*(const NonRationalType &nonRational) {
            return *this * Rational<IntType>(nonRational);
        }

        /**
         * @brief Multiplication operation between a non-rational and a rational. Example: int * Rational
         * @tparam NonRationalType
         * @param nonRational
         * @param rational
         * @return The multiplication in Rational
         */
        template<typename NonRationalType>
        inline friend Rational<IntType>
        operator*(NonRationalType nonRational, const Rational<IntType> &rational) {
            return Rational<IntType>(nonRational) * rational;
        }

        /************************************************************************************************************
         *********************************************** OPERATOR / *************************************************
         ************************************************************************************************************/

        /**
         * @brief Division operation between 2 rationals
         * @param anotherRational
         * @return The division in Rational
         */
        Rational<IntType> operator/(const Rational<IntType> &anotherRational);

        /**
         * @brief Division operation between a rational and another type. Example: Rational / int
         * @tparam NonRationalType
         * @param nonRational
         * @return The division in Rational
         */
        template<typename NonRationalType>
        inline Rational<IntType> operator/(const NonRationalType &nonRational) {
            return *this / Rational<IntType>(nonRational);
        }

        /**
         * @brief Division operation between a non-rational and a rational. Example: int / Rational
         * @tparam NonRationalType
         * @param nonRational
         * @param rational
         * @return The division in Rational
         */
        template<typename NonRationalType>
        inline friend Rational<IntType>
        operator/(NonRationalType nonRational, const Rational<IntType> &rational) {
            return Rational<IntType>(nonRational) / rational;
        }

        /************************************************************************************************************
         ********************************************** OPERATOR == *************************************************
         ************************************************************************************************************/

        /**
         * @brief Comparison between 2 rationals
         * @param anotherRational
         * @return True if the first rational is equal to the second
         */
        inline bool operator==(const Rational<IntType> &anotherRational) {
            Rational<IntType> leftRational = simplify();
            Rational<IntType> rightRational = anotherRational.simplify();

            return (leftRational.getNumerator() == rightRational.getNumerator() &&
                    leftRational.getDenominator() == rightRational.getDenominator());
        }

        /**
         * @brief Comparison between a rational and a non-rational. Example: Rational == int
         * @tparam NonRationalType
         * @param nonRational
         * @return True if the rational is equal to the second operand
         */
        template<typename NonRationalType>
        inline bool operator==(const NonRationalType &nonRational) {
            return Rational<IntType>(nonRational) == *this;
        }

        /**
         * @brief Comparison between a non-rational and a rational. Example: int == Rational
         * @tparam NonRationalType
         * @param nonRational
         * @param rational
         * @return True if the non-rational is equal to the rational
         */
        template<typename NonRationalType>
        inline friend bool operator==(NonRationalType nonRational, const Rational<IntType> &rational) {
            return Rational<IntType>(nonRational) == rational;
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
        inline bool operator!=(const Rational<IntType> &anotherRational) {
            Rational<IntType> leftRational = simplify();
            Rational<IntType> rightRational = anotherRational.simplify();

            return (leftRational.getNumerator() != rightRational.getNumerator() ||
                    leftRational.getDenominator() != rightRational.getDenominator());
        }

        /**
        * @brief Different comparison between a rational and a non-rational. Example: Rational != int
        * @tparam NonRationalType
        * @param nonRational
        * @return True if the rational is different to the second operand
        */
        template<typename NonRationalType>
        inline bool operator!=(const NonRationalType &nonRational) {
            return Rational<IntType>(nonRational) != *this;
        }

        /**
         * @brief Different comparison between a non-rational and a rational. Example: int != Rational
         * @tparam NonRationalType
         * @param nonRational
         * @param rational
         * @return True if the non-rational is different to the rational
         */
        template<typename NonRationalType>
        inline friend bool operator!=(NonRationalType nonRational, const Rational<IntType> &rational) {
            return Rational<IntType>(nonRational) != rational;
        }

        /************************************************************************************************************
         *********************************************** OPERATOR < *************************************************
         ************************************************************************************************************/

        /**
         * @brief < Comparison between 2 rationals
         * @param anotherRational
         * @return True if the first rational is inferior to the second
         */
        inline bool operator<(const Rational<IntType> &anotherRational) {
            //ToDo Passer par autre chose qu'un double?
            double firstRatio = (double) getNumerator() / getDenominator();
            double secondRatio = (double) anotherRational.getNumerator() / anotherRational.getDenominator();
            return (firstRatio < secondRatio);
        }

        /**
         * @brief < Comparison between a rational and a non-rational. Example: Rational < int
         * @tparam NonRationalType
         * @param nonRational
         * @return True if the rational is inferior to the second operand
         */
        template<typename NonRationalType>
        inline bool operator<(const NonRationalType &nonRational) { return *this < Rational<IntType>(nonRational); }

        /**
         * @brief < Comparison between a non-rational and a rational. Example: int < Rational
         * @tparam NonRationalType
         * @param nonRational
         * @param rational
         * @return True if the non-rational is inferior to the rational
         */
        template<typename NonRationalType>
        inline friend bool operator<(NonRationalType nonRational, const Rational<IntType> &rational) {
            return Rational<IntType>(nonRational) < rational;
        }

        /************************************************************************************************************
         *********************************************** OPERATOR <= *************************************************
         ************************************************************************************************************/

        /**
         * @brief <= Comparison between 2 rationals
         * @param anotherRational
         * @return True if the first rational is inferior to the second
         */
        inline bool operator<=(const Rational<IntType> &anotherRational) {
            //ToDo Passer par autre chose qu'un double?
            double firstRatio = (double) getNumerator() / getDenominator();
            double secondRatio = (double) anotherRational.getNumerator() / anotherRational.getDenominator();
            return (firstRatio <= secondRatio);
        }

        /**
         * @brief <= Comparison between a rational and a non-rational. Example: Rational <= int
         * @tparam NonRationalType
         * @param nonRational
         * @return True if the rational is inferior to the second operand
         */
        template<typename NonRationalType>
        inline bool operator<=(const NonRationalType &nonRational) {
            return *this <= Rational<IntType>(nonRational);
        }

        /**
         * @brief <= Comparison between a non-rational and a rational. Example: int <= Rational
         * @tparam NonRationalType
         * @param nonRational
         * @param rational
         * @return True if the non-rational is inferior to the rational
         */
        template<typename NonRationalType>
        inline friend bool operator<=(NonRationalType nonRational, const Rational<IntType> &rational) {
            return Rational<IntType>(nonRational) <= rational;
        }

        /************************************************************************************************************
         *********************************************** OPERATOR > *************************************************
         ************************************************************************************************************/

        /**
         * @brief > Comparison between 2 rationals
         * @param anotherRational
         * @return True if the first rational is inferior to the second
         */
        inline bool operator>(const Rational<IntType> &anotherRational) {
            double firstRatio = (double) getNumerator() / getDenominator();
            double secondRatio = (double) anotherRational.getNumerator() / anotherRational.getDenominator();
            return (firstRatio > secondRatio);
        }

        /**
         * @brief > Comparison between a rational and a non-rational. Example: Rational > int
         * @tparam NonRationalType
         * @param nonRational
         * @return True if the rational is inferior to the second operand
         */
        template<typename NonRationalType>
        inline bool operator>(const NonRationalType &nonRational) { return *this > Rational<IntType>(nonRational); }

        /**
         * @brief < Comparison between a non-rational and a rational. Example: int > Rational
         * @tparam NonRationalType
         * @param nonRational
         * @param rational
         * @return True if the non-rational is superior to the rational
         */
        template<typename NonRationalType>
        inline friend bool operator>(NonRationalType nonRational, const Rational<IntType> &rational) {
            return Rational<IntType>(nonRational) > rational;
        }

        /************************************************************************************************************
         *********************************************** OPERATOR >= *************************************************
         ************************************************************************************************************/

        /**
         * @brief >= Comparison between 2 rationals
         * @param anotherRational
         * @return True if the first rational is inferior to the second
         */
        inline bool operator>=(const Rational<IntType> &anotherRational) {
            double firstRatio = (double) getNumerator() / getDenominator();
            double secondRatio = (double) anotherRational.getNumerator() / anotherRational.getDenominator();
            return (firstRatio >= secondRatio);
        }

        /**
         * @brief >= Comparison between a rational and a non-rational. Example: Rational >= int
         * @tparam NonRationalType
         * @param nonRational
         * @return True if the rational is inferior to the second operand
         */
        template<typename NonRationalType>
        inline bool operator>=(const NonRationalType &nonRational) {
            return *this >= Rational<IntType>(nonRational);
        }

        /**
         * @brief < Comparison between a non-rational and a rational. Example: int >= Rational
         * @tparam NonRationalType
         * @param nonRational
         * @param rational
         * @return True if the non-rational is superior to the rational
         */
        template<typename NonRationalType>
        inline friend bool operator>=(NonRationalType nonRational, const Rational<IntType> &rational) {
            return Rational<IntType>(nonRational) >= rational;
        }

        /************************************************************************************************************
         *********************************************** OPERATOR += ************************************************
         ************************************************************************************************************/

        /**
         * @brief Addition assignment operation between 2 rationals
         * @param anotherRational
         * @return The sum assignment in Rational
         */
        Rational<IntType> operator+=(const Rational<IntType> &anotherRational) {
            *this = *this + anotherRational;
            return *this;
        }

        /**
         * @brief Addition assignment operation between a rational and another type. Example: Rational += int
         * @tparam NonRationalType
         * @param nonRational
         * @return The sum assigment in Rational
         */
        template<typename NonRationalType>
        inline Rational<IntType> operator+=(const NonRationalType &nonRational) {
            *this = *this + Rational<IntType>(nonRational);
            return *this;
        }

        /************************************************************************************************************
         *********************************************** OPERATOR -= ************************************************
         ************************************************************************************************************/

        /**
         * @brief
         * @param anotherRational
         * @return The subtraction in Rational
         */
        Rational<IntType> operator-=(const Rational<IntType> &anotherRational) {
            *this = *this - anotherRational;
            return *this;
        }

        /**
         * @brief Subtraction assignment operation between a rational and another type. Example: Rational - int
         * @tparam NonRationalType
         * @param nonRational
         * @return The subtraction assigment in Rational
         */
        template<typename NonRationalType>
        inline Rational<IntType> operator-=(const NonRationalType &nonRational) {
            *this = *this - Rational<IntType>(nonRational);
            return *this;
        }

        /************************************************************************************************************
         *********************************************** OPERATOR *= ************************************************
         ************************************************************************************************************/

        /**
         * @brief Multiplication assignment operation between 2 rationals
         * @param anotherRational
         * @return The multiplication in Rational
         */
        Rational<IntType> operator*=(const Rational<IntType> &anotherRational) {
            *this = *this * anotherRational;
            return *this;
        }

        /**
         * @brief Multiplication assignment operation between a rational and another type. Example: Rational * int
         * @tparam NonRationalType
         * @param nonRational
         * @return The multiplication assigment in Rational
         */
        template<typename NonRationalType>
        inline Rational<IntType> operator*=(const NonRationalType &nonRational) {
            *this = *this * Rational<IntType>(nonRational);
            return *this;
        }

        /************************************************************************************************************
         *********************************************** OPERATOR /= ************************************************
         ************************************************************************************************************/


        /**
         * @brief Division assignment operation between 2 rationals
         * @param anotherRational
         * @return The division in Rational
         */
        Rational<IntType> operator/=(const Rational<IntType> &anotherRational) {
            *this = *this / anotherRational;
            return *this;
        }

        /**
         * @brief Multiplication assignment operation between a rational and another type. Example: Rational * int
         * @tparam NonRationalType
         * @param nonRational
         * @return The multiplication assigment in Rational
         */
        template<typename NonRationalType>
        inline Rational<IntType> operator/=(const NonRationalType &nonRational) {
            *this = *this / Rational<IntType>(nonRational);
            return *this;
        }


        /************************************************************************************************************
         ************************************************* MATHS ****************************************************
         ************************************************************************************************************/

        /**
         * @brief Inverse a rational : a / b into b / a
         * @return The inverted Rational
         */
        [[maybe_unused]] [[nodiscard]] constexpr inline Rational<IntType> inverse() const {
            return Rational<IntType>(m_denominator, m_numerator);
        }

        /**
        * @brief Give the square root of a rational
        * @return The square root as a Rational
        */
        [[maybe_unused]] [[nodiscard]] constexpr Rational<IntType> sqrt() const;

        /**
        * @brief Give the cosine of a rational
        * @return The cosine as a Rational
        */
        [[maybe_unused]] [[nodiscard]] constexpr Rational<IntType> cos() const;

        /**
        * @brief Give the exponential of a rational
        * @return The exponential as a Rational
        */
        [[maybe_unused]] [[nodiscard]] constexpr Rational<IntType> exp() const;

        /**
        * @brief Give the power of a rational
        * @return The power as a Rational
        */

        template<typename FloatingType>
        [[maybe_unused]] [[nodiscard]] constexpr Rational<IntType> pow(const FloatingType &k) const;

        /**
         * @brief Give the abs of a rational
         * @return The Rational in absolute value
         */
        [[maybe_unused]] [[nodiscard]] constexpr inline Rational<IntType> abs() const {
            return Rational<IntType>(std::abs(m_numerator), std::abs(m_denominator));
        };

        //ToDo: Peut-être une fonction qui permet de simplifier le rationnel ? Si c'est faisable, genre qui renvoie une approximation plus simple
        //ToDo: ...

        /**
         * @brief Simplify the Rational with GCD (called in constructor)
         */
        [[maybe_unused]] [[nodiscard]] constexpr Rational<IntType> simplify() const noexcept;

        /************************************************************************************************************
         ************************************************* STATIC ***************************************************
         ************************************************************************************************************/

        /**
         * @brief Return zero in Rational Type
         * @return Rational with 0 as numerator and 1 as denominator
         */
        inline constexpr static Rational<IntType> Zero() noexcept { return Rational<IntType>(0, 1); }

        /**
         * @brief Return one in Rational Type
         * @return Rational with 1 as numerator and 1 as denominator
         */
        inline constexpr static Rational<IntType> One() noexcept { return Rational<IntType>(1, 1); }

        /**
         * @brief Return Pi in Rational Type
         * @return An approximation of Pi
         */
        inline constexpr static Rational<IntType> Pi() noexcept { return Rational<IntType>(355, 113, false); }

        /**
         * @brief Return an approximation of +infinite in Rational Type
         * @return 1 as numerator and 0 as denominator
         */
        [[maybe_unused]] inline constexpr static Rational<IntType>
        Infinite() noexcept { return Rational<IntType>(1, 0, false, false); }

        /************************************************************************************************************
         *********************************************** CONVERSION *************************************************
         ************************************************************************************************************/

        /**
         * @brief Get the integer part of the ratio
         * @return An int (type IntType)
         */
        [[nodiscard]] inline constexpr IntType toInteger() const noexcept {
            return IntType(m_numerator / m_denominator);
        }

        /**
         * @brief Get an approximation floating point number of the ratio
         * @tparam FloatingType
         * @return A floating point number (type FloatingType)
         */
        template<typename FloatingType = float>
        [[nodiscard]] inline constexpr FloatingType toRealNumber() const noexcept {
            return m_numerator / FloatingType(m_denominator);
        }

        /**
         * @brief Return ( _numerator_ / _denominator_ ) as a string
         * @return std::string
         */
        [[nodiscard]] inline std::string toString() const noexcept {
            return "(" + std::to_string(getNumerator()) + " / " + std::to_string(getDenominator()) + ")";
        }

        /**
         * @brief A method who automatically set numerator and denominator to approach the float parameter
         * @tparam FloatingType
         * @param floatingRatio
         * @param iter
         * @return The rational wanted
         */
        template<typename FloatingType = double>
        [[nodiscard]] constexpr Rational<IntType> fromFloatingPoint(FloatingType floatingRatio, size_t iter) const;

    private:
        /************************************************************************************************************
         ********************************************* MEMBERS ******************************************************
         ************************************************************************************************************/

        IntType m_numerator; /*!< Rational's numerator */

        IntType m_denominator; /*!< Rational's denominator */

        /************************************************************************************************************
         ********************************************* METHODS ******************************************************
         ************************************************************************************************************/

        constexpr inline void verifyTemplateType() const {
            if (!std::is_integral<IntType>()) throw Exceptions::FloatTypeGivenException();
        };

        constexpr inline void verifyDenominator(
                const IntType denominator,
                const bool checkIfDenominatorIsNull = true
        );

        /**
         * @brief Verify if the operands are superior to the limit of IntType
         * @tparam AnotherIntType
         * @param anotherRational
         */
        template<typename AnotherIntType>
        constexpr void verifyNumberLargeness(Rational<AnotherIntType> &anotherRational);
    };




    /************************************************************************************************************
     ************************************************************************************************************/



    /************************************************************************************************************
     ********************************************* CONSTRUCTOR DEF **********************************************
     ************************************************************************************************************/

    template<typename IntType>
    constexpr Rational<IntType>::Rational(
            const IntType numerator,
            const IntType denominator,
            const bool willBeReduce,
            const bool willDenominatorBeVerified
    ) : m_numerator(numerator), m_denominator(denominator)
    {
        verifyTemplateType();
        verifyDenominator(denominator, willDenominatorBeVerified);
        if (willBeReduce) *this = simplify();
    }

    /************************************************************************************************************/

    template<typename IntType>
    template<typename FloatingType>
    constexpr Rational<IntType>::Rational(const FloatingType &nonRational) {
        verifyTemplateType();
        Rational<long long int> tmpRational = Rational<long long int>::Zero();
        tmpRational = tmpRational.fromFloatingPoint(nonRational, 10);

        // ToDo Fonction arrondir ?
        // Can't be handled by long long int
        if (tmpRational.isZero() && std::round(nonRational * 10e4) / 10e4 != static_cast<FloatingType>(0)) {
            // Because Very large number return 0
            throw Exceptions::NumberTooLargeException();
        }

        *this = Rational<IntType>(tmpRational);
    }

    /************************************************************************************************************/

    template<typename IntType>
    template<typename AnotherIntType>
    constexpr Rational<IntType>::Rational(Rational<AnotherIntType> &copiedRational) {
        verifyNumberLargeness(copiedRational);
        m_numerator = copiedRational.getNumerator();
        m_denominator = copiedRational.getDenominator();
    }

    /************************************************************************************************************
     ********************************************* OPERATORS[] DEF **********************************************
     ************************************************************************************************************/

    template<typename IntType>
    const IntType &Rational<IntType>::operator[](const size_t &id) const {
        if (id == 0) return m_numerator;
        else if (id == 1) return m_denominator;
        else throw Exceptions::InvalidAccessArgument();
    }

    template<typename IntType>
    IntType &Rational<IntType>::operator[](const size_t &id) {
        if (id == 0) return m_numerator;
        else if (id == 1) return m_denominator;
        else throw Exceptions::InvalidAccessArgument();
    }

    /************************************************************************************************************
     ********************************************* OPERATOR + DEF ***********************************************
     ************************************************************************************************************/

    template<typename IntType>
    Rational<IntType> Rational<IntType>::operator+(const Rational<IntType> &anotherRational) {
        return Rational<IntType>(
                m_numerator * anotherRational.m_denominator + m_denominator * anotherRational.m_numerator,
                m_denominator * anotherRational.m_denominator
        );
    }

    /************************************************************************************************************
     ********************************************* OPERATOR - DEF ***********************************************
     ************************************************************************************************************/

    template<typename IntType>
    Rational<IntType> Rational<IntType>::operator-(const Rational<IntType> &anotherRational) {
        return Rational<IntType>(
                m_numerator * anotherRational.m_denominator - m_denominator * anotherRational.m_numerator,
                m_denominator * anotherRational.m_denominator
        );
    }

    /************************************************************************************************************
     ********************************************* OPERATOR * DEF ***********************************************
     ************************************************************************************************************/

    template<typename IntType>
    Rational<IntType> Rational<IntType>::operator*(const Rational<IntType> &anotherRational) {
        return Rational<IntType>(
                m_numerator * anotherRational.m_numerator,
                m_denominator * anotherRational.m_denominator
        );
    }

    /************************************************************************************************************
     ********************************************* OPERATOR / DEF ***********************************************
     ************************************************************************************************************/

    template<typename IntType>
    Rational<IntType> Rational<IntType>::operator/(const Rational<IntType> &anotherRational) {
        return Rational<IntType>(
                m_numerator * anotherRational.m_denominator,
                m_denominator * anotherRational.m_numerator
        );
    }

    /************************************************************************************************************
     ************************************************ MATHS DEF *************************************************
     ************************************************************************************************************/

    // ToDo : Do a take !
    // Do we (keep the precision) or (simplify the operations in order to ease the operations)
    template<typename IntType>
    constexpr Rational<IntType> Rational<IntType>::sqrt() const {
        if (isNegative()) throw Exceptions::NegativeSqrtException();
        return Rational<IntType>(
                std::sqrt(double(m_numerator) / m_denominator)
        );
    }

    template<typename IntType>
    Rational<IntType> constexpr Rational<IntType>::cos() const {
        return Rational<IntType>(
                std::cos(double(m_numerator) / m_denominator)
        );
    }

    template<typename IntType>
    Rational<IntType> constexpr Rational<IntType>::exp() const {
        return Rational<IntType>(
                std::exp(double(m_numerator) / m_denominator)
        );
    }

    template<typename IntType>
    template<typename FloatingType>
    Rational<IntType> constexpr Rational<IntType>::pow(const FloatingType &k) const {
        return Rational<IntType>(
                std::pow(double(m_numerator) / m_denominator, k)
        );
    }

    template<typename IntType>
    Rational<IntType> constexpr Rational<IntType>::simplify() const noexcept {
        const int gcd = std::gcd(m_numerator, m_denominator);
        assert(gcd != 0 && "GCD shouldn't be equal to 0");

        return Rational<IntType>(
                m_numerator / gcd,
                m_denominator / gcd,
                false
        );
    }

    /************************************************************************************************************
     ********************************************** CONVERSION DEF **********************************************
     ************************************************************************************************************/

    template<typename IntType>
    template<typename FloatingType>
    Rational<IntType> constexpr
    Rational<IntType>::fromFloatingPoint(const FloatingType floatingRatio, size_t iter) const {
        //ToDo: Throw une except si n ou d supérieur à max
        //ToDo: Trouver un moyen de pas utiliser de paramètres iter
        constexpr FloatingType ZERO = 0;
        constexpr FloatingType ONE = 1;

        if (floatingRatio < ZERO) {
            return -fromFloatingPoint(-floatingRatio, iter);
        }

        if (floatingRatio <= ZERO + static_cast<FloatingType>(0.01) || iter == 0) {
            return Rational<IntType>::Zero();
        }

        if (floatingRatio < static_cast<FloatingType>(1)) {
            return fromFloatingPoint(ONE / floatingRatio, iter).inverse();
        }

        IntType integerPart = IntType(floatingRatio);
        return fromFloatingPoint(floatingRatio - integerPart, iter - 1)
               + Rational<IntType>(integerPart, ONE);
    }

    /************************************************************************************************************
     ************************************************ METHODS DEF ***********************************************
     ************************************************************************************************************/

    template<typename IntType>
    template<typename AnotherIntType>
    constexpr void Rational<IntType>::verifyNumberLargeness(
            Rational<AnotherIntType> &anotherRational
    ) {
        // If the value of the other rational is above the limits of IntType
        if ((std::numeric_limits<IntType>::max() < anotherRational.getLargerOperand() ||
             std::numeric_limits<IntType>::lowest() > anotherRational.getLowerOperand())) {
            throw Exceptions::NumberTooLargeException();
        }
    }

    template<typename IntType>
    constexpr void
    Rational<IntType>::verifyDenominator(
            const IntType denominator,
            const bool checkIfDenominatorIsNull
    ) {
        constexpr IntType ZERO = 0;
        if (denominator == ZERO && checkIfDenominatorIsNull)
            throw Exceptions::DivideByZeroException();

        if (denominator < ZERO) {
            m_numerator = -m_numerator;
            m_denominator = -denominator;
        }
    }

    /************************************************************************************************************
     ******************************************* STD::COUT OVERRIDE *********************************************
     ************************************************************************************************************/

    template<typename IntType>
    std::ostream &operator<<(std::ostream &stream, const Rational<IntType> &rational) {
        return stream << rational.toString();
    }
}
