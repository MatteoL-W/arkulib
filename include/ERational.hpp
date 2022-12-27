/**
 * @file      ERational.hpp
 * @author    Elise MASSA
 * @author    Mattéo LECLERCQ
 * @date      2022
 * @warning   The use of ERatio isn't as performant as a simple float type and as Rational.hpp
 * @copyright WTFPL
 */

#pragma once

#include "Rational.hpp"
#include <iomanip>

namespace Arkulib {
    /**
     * @brief This class can be used to express big rationals
     * @tparam FloatType
     */
    template<typename FloatType = double>
    class ERational {

    public:

        /************************************************************************************************************
         ****************************************** CONSTRUCTOR / DESTRUCTOR ****************************************
         ************************************************************************************************************/

        /**
         * @brief Default constructor : instantiate an object without parameters.
         */
        constexpr explicit ERational();

        /**
         * @brief Classic constructor : create an experimental rational from a numerator and a denominator (set default at 1)
         * @param numerator
         * @param denominator
         * @param willBeReduce
         * @param willDenominatorBeVerified
         */
        template<typename IntType = long long int>
        constexpr explicit ERational(
                IntType numerator,
                IntType denominator,
                bool willBeReduce = false,
                bool willDenominatorBeVerified = true
        );

        /**
        * @brief Create an experimental rational from a floating number
        * @tparam FloatingType
        * @param nonRational
        */
        template<typename FloatingType>
        constexpr explicit ERational(const FloatingType &nonRational);

        /**
         * @brief Copy constructor
         * @tparam IntType
         * @param reference
         */
        inline constexpr ERational(const ERational<FloatType> &reference) = default;

        /**
         * @brief Copy constructor from a Rational
         * @param reference
         */
        template<typename IntType>
        inline constexpr explicit ERational(const Rational<IntType> &reference) {
            *this = ERational<FloatType>(reference.getNumerator(), reference.getDenominator());
        };

        /**
         * @brief Explicit constructor
         * @param numMultiplier
         * @param numExponent
         * @param denMultiplier
         * @param denExponent
         */
        constexpr ERational(
                FloatType numMultiplier,
                short int numExponent,
                FloatType denMultiplier,
                short int denExponent
        );

        /**
         * @brief Default Destructor
         */
        inline ~ERational() = default;

        /************************************************************************************************************
         ************************************************ GETTERS ***************************************************
         ************************************************************************************************************/

        [[nodiscard]] constexpr inline int getNumExponent() const noexcept { return m_numExponent; }

        [[nodiscard]] constexpr inline FloatType getNumMultiplier() const noexcept { return m_numMultiplier; }

        [[nodiscard]] constexpr inline int getDenExponent() const noexcept { return m_denExponent; }

        [[nodiscard]] constexpr inline FloatType getDenMultiplier() const noexcept { return m_denMultiplier; }

        /************************************************************************************************************
         ************************************************ SETTERS ***************************************************
         ************************************************************************************************************/

        inline void setNumExponent(short int newNumExponent) noexcept { m_numExponent = newNumExponent; }

        inline void setNumMultiplier(FloatType newNumMultiplier) noexcept { m_numMultiplier = newNumMultiplier; }

        [[maybe_unused]] inline void setDenExponent(short int newDenExponent) noexcept { m_denExponent = newDenExponent; }

        [[maybe_unused]] inline void setDenMultiplier(FloatType newDenMultiplier) noexcept { m_denMultiplier = newDenMultiplier; }

        /************************************************************************************************************
         *********************************************** OPERATOR + *************************************************
         ************************************************************************************************************/

        /**
         * @brief Sum operation between 2 experimental rationals
         * @param anotherERational
         * @return The sum in ERational
         */
        constexpr ERational<FloatType> operator+(const ERational<FloatType> &anotherERational) const;

        /************************************************************************************************************
         *********************************************** OPERATOR - *************************************************
         ************************************************************************************************************/

        /**
         * @brief Subtraction operation between 2 experimental rationals
         * @param anotherERational
         * @return The result in ERational
         */
        constexpr ERational<FloatType> operator-(const ERational<FloatType> &anotherERational) const;

        /************************************************************************************************************
         *********************************************** OPERATOR * *************************************************
         ************************************************************************************************************/

        /**
         * @brief Multiplication operation between 2 experimental rationals
         * @param anotherERational
         * @return The multiplication in ERational
         */
        constexpr ERational<FloatType> operator*(const ERational<FloatType> &anotherERational) const;

        /************************************************************************************************************
         *********************************************** OPERATOR / *************************************************
         ************************************************************************************************************/

        /**
         * @brief Division operation between 2 experimental rationals
         * @param anotherERational
         * @return The result in ERational
         */
        constexpr ERational<FloatType> operator/(const ERational<FloatType> &anotherERational) const;

        /************************************************************************************************************
         *********************************************** OPERATOR == ************************************************
         ************************************************************************************************************/

        /**
         * @brief Comparison between 2 ERationals
         * @param anotherRational
         * @return True if the first erational is equal to the second
         */
        constexpr inline bool operator==(const ERational<FloatType> &anotherERational) const;

        /************************************************************************************************************
         ********************************************** OPERATOR != *************************************************
         ************************************************************************************************************/

        /**
         * @brief Different comparison between 2 erationals
         * @param anotherRational
         * @return True if the first erational is different to the second
         */
        constexpr inline bool operator!=(const ERational<FloatType> &anotherERational) const;

        /************************************************************************************************************
         ************************************************* STATUS ***************************************************
         ************************************************************************************************************/

        /**
         * @return True if the rational is negative
         */
        [[maybe_unused]] [[nodiscard]] inline bool isNegative() const noexcept {
            return (getNumMultiplier() < 0. && getDenMultiplier() > 0.) || (getNumMultiplier() > 0. && getDenMultiplier() < 0.);
        };

        /**
         * @return True if the rational is an integer
         */
        [[maybe_unused]] [[nodiscard]] inline bool isInteger() const noexcept { return getDenMultiplier() == 1.; };

        /**
         * @return True if the rational is equal to zero
         */
        [[maybe_unused]] [[nodiscard]] inline bool isZero() const noexcept { return getNumMultiplier() == 0.; };

        /************************************************************************************************************
         ************************************************** MATHS ***************************************************
         ************************************************************************************************************/

        /**
         * @brief Apply absolute value on the ERational
         * @return The ERational in absolute value
         */
        [[maybe_unused]] [[nodiscard]] constexpr inline ERational<FloatType> abs() const {
            return ERational<FloatType>(std::abs(getNumMultiplier()), getNumExponent(), std::abs(getDenMultiplier()), getDenExponent());
        };

        /**
         * @brief Get the inverse of an ERational
         * @return The inversed ERational
         */
        [[maybe_unused]] [[nodiscard]] constexpr inline ERational<FloatType> inverse() const {
            return ERational<FloatType>(getDenMultiplier(), getDenExponent(), getNumMultiplier(), getNumExponent());
        }

        /**
         * @brief Simplify the Rational with GCD
         */
        [[maybe_unused]] constexpr ERational<FloatType> simplify() noexcept;

        /************************************************************************************************************
         *********************************************** CONVERSION *************************************************
         ************************************************************************************************************/

        /**
         * @brief Get an approximation floating point number of the experimental ratio
         * @tparam AnotherFloatType
         * @return A floating point number
         */
        template<typename AnotherFloatType = double>
        [[nodiscard]] inline constexpr AnotherFloatType toRealNumber() const noexcept {
            return static_cast<AnotherFloatType>
                (m_numMultiplier * std::pow(10, m_numExponent)) / (m_denMultiplier * std::pow(10, m_denExponent)
            );
        }

        /**
         * @brief Return ( _numerator_ / _denominator_ ) as a string
         * @return std::string
         */
        [[nodiscard]] inline std::string toString() const noexcept {
            return "(" + Tools::toStringWithPrecision(m_numMultiplier) + " * 10^" + Tools::toStringWithPrecision(m_numExponent) + ")"
                   + " / " + "(" + Tools::toStringWithPrecision(m_denMultiplier) + " * 10^" + Tools::toStringWithPrecision(m_denExponent) + ")";
        }

    private:
        /************************************************************************************************************
         ************************************************** METHODS *************************************************
         ************************************************************************************************************/

        /**
         * @brief Set the parameters from a normal numerator and denominator
         * @param numerator
         * @param denominator
         */
        template<typename IntType = long long int>
        constexpr void transformToExperimental(IntType numerator, IntType denominator);

        /**
         * @brief Verify if the denominator is null or negative
         * @param denominator
         * @param checkIfDenominatorIsNull
         */
        constexpr void verifyDenominator(bool checkIfDenominatorIsNull = true);

        /**
         * @brief Verify if the template is correct
         * @return an exception if the template is a floating point
         */
        constexpr inline void verifyTemplateType() const {
            if (std::is_integral<FloatType>()) throw Exceptions::IntTypeGivenException();
        };

        /**
         * @brief Set firstERational and secondERational with the same denominator and the same numerator exponent
         * @param anotherERational
         * @param firstERational
         * @param secondERational
         */
        constexpr void setSameDenominatorAndExponent(
            const ERational<FloatType> &anotherERational,
            ERational<FloatType> &firstERational,
            ERational<FloatType> &secondERational
        ) const;

        /************************************************************************************************************
         ************************************************** MEMBERS *************************************************
         ************************************************************************************************************/

        FloatType m_numMultiplier; /*!< The multiplier of the numerator */
        short int m_numExponent; /*!< The exponent of the numerator */

        FloatType m_denMultiplier; /*!< The multiplier of the denominator */
        short int m_denExponent; /*!< The exponent of the denominator */
    };




    /************************************************************************************************************
     ************************************************************************************************************/



    /************************************************************************************************************
     ********************************************* CONSTRUCTOR DEF **********************************************
     ************************************************************************************************************/

    template<typename FloatType>
    constexpr ERational<FloatType>::ERational()
            : m_numExponent(0), m_numMultiplier(0.), m_denExponent(0), m_denMultiplier(1.) {
        this->verifyTemplateType();
    }


    template<typename FloatType>
    template<typename IntType>
    constexpr ERational<FloatType>::ERational(
            const IntType numerator,
            const IntType denominator,
            const bool willBeReduce,
            const bool willDenominatorBeVerified
    ) {
        this->verifyTemplateType();

        const int gcd = std::gcd(numerator, denominator);
        assert(gcd != 0 && "GCD shouldn't be equal to 0");

        if (willBeReduce) transformToExperimental(numerator / gcd, denominator / gcd);
        else transformToExperimental(numerator, denominator);

        this->verifyDenominator(willDenominatorBeVerified);

        if (willBeReduce) *this = simplify();
    }



    template<typename FloatType>
    template<typename AnotherFloatType>
    constexpr ERational<FloatType>::ERational(const AnotherFloatType &nonRational) {
        this->verifyTemplateType();

        Rational<long long int> tmpRational = Rational<long long int>::fromFloatingPoint(nonRational);
        if (tmpRational.isZero() && Tools::roundToWantedPrecision(nonRational) != static_cast<AnotherFloatType>(0)) {
            // Because Very large number return 0
            throw Exceptions::NumberTooLargeException();
        }

        *this = ERational{tmpRational};
    }



    template<typename FloatType>
    constexpr ERational<FloatType>::ERational(
            const FloatType numMultiplier,
            const short int numExponent,
            const FloatType denMultiplier,
            const short int denExponent
    ) {
        m_numMultiplier = numMultiplier;
        m_numExponent = numExponent;
        m_denMultiplier = denMultiplier;
        m_denExponent = denExponent;
    }

    /************************************************************************************************************
     ********************************************* OPERATOR + DEF ***********************************************
     ************************************************************************************************************/

    template<typename FloatType>
    constexpr ERational<FloatType> ERational<FloatType>::operator+(const ERational<FloatType> &anotherERational) const {
        ERational<FloatType> firstERational;
        ERational<FloatType> secondERational;
        setSameDenominatorAndExponent(anotherERational, firstERational, secondERational);

        assert(firstERational.getNumExponent() == secondERational.getNumExponent() &&
               "The two numerator exponent should be equal");
        return ERational<FloatType>(
                firstERational.getNumMultiplier() + secondERational.getNumMultiplier(),
                firstERational.getNumExponent(),
                firstERational.getDenMultiplier(),
                firstERational.getDenExponent()
        );
    }

    /************************************************************************************************************
 ********************************************* OPERATOR - DEF ***********************************************
 ************************************************************************************************************/

    template<typename FloatType>
    constexpr ERational<FloatType> ERational<FloatType>::operator-(const ERational<FloatType> &anotherERational) const {
        ERational<FloatType> firstERational;
        ERational<FloatType> secondERational;
        setSameDenominatorAndExponent(anotherERational, firstERational, secondERational);

        assert(firstERational.getNumExponent() == secondERational.getNumExponent() &&
               "The two numerator exponent should be equal");
        return ERational<FloatType>(
                firstERational.getNumMultiplier() - secondERational.getNumMultiplier(),
                firstERational.getNumExponent(),
                firstERational.getDenMultiplier(),
                firstERational.getDenExponent()
        );
    }

    /************************************************************************************************************
     ********************************************* OPERATOR * DEF ***********************************************
     ************************************************************************************************************/

    template<typename FloatType>
    constexpr ERational<FloatType> ERational<FloatType>::operator*(const ERational<FloatType> &anotherERational) const {
        return ERational<FloatType>(
                m_numMultiplier * anotherERational.getNumMultiplier(),// Num Multiplier
                m_numExponent + anotherERational.getNumExponent(),    // Num Exponent
                m_denMultiplier * anotherERational.getDenMultiplier(),    // Den Multiplier
                m_denExponent + anotherERational.getDenExponent()    // Den Exponent
        );
    }

    /************************************************************************************************************
     ********************************************* OPERATOR / DEF ***********************************************
     ************************************************************************************************************/

    template<typename FloatType>
    constexpr ERational<FloatType> ERational<FloatType>::operator/(const ERational<FloatType> &anotherERational) const {
        return ERational<FloatType>(
                m_numMultiplier * anotherERational.getDenMultiplier(),
                m_numExponent + anotherERational.getDenExponent(),
                m_denMultiplier * anotherERational.getNumMultiplier(),
                m_denExponent + anotherERational.getNumExponent()
        );
    }

    /************************************************************************************************************
     ********************************************* OPERATOR == DEF **********************************************
     ************************************************************************************************************/

    template<typename FloatType>
    constexpr bool ERational<FloatType>::operator==(const ERational<FloatType> &anotherERational) const {
        ERational<FloatType> leftRational = this->simplify();
        ERational<FloatType> rightRational = anotherERational->simplify();

        if (leftRational.getNumExponent() != rightRational.getNumExponent()
            || leftRational.getDenExponent() != rightRational.getDenExponent()
            || leftRational.toRealNumber() != rightRational.toRealNumber()) {
            return false;
        }

        return true;
    }

    /************************************************************************************************************
     ********************************************* OPERATOR != DEF **********************************************
     ************************************************************************************************************/

    template<typename FloatType>
    constexpr bool ERational<FloatType>::operator!=(const ERational<FloatType> &anotherERational) const {
        return (*this == anotherERational) == false;
    }

    /************************************************************************************************************
     ************************************************ MATHS DEF *************************************************
     ************************************************************************************************************/

    template<typename FloatType>
    constexpr ERational<FloatType> ERational<FloatType>::simplify() noexcept {
        const int exponentDifference = std::abs(getNumExponent() - getDenExponent());

        if (exponentDifference == 0 && getNumExponent() != 0) {
            m_numExponent = 0;
            m_denExponent = 0;
        }

        const int minExponent = std::min(getNumExponent(), getDenExponent());
        if (exponentDifference != 0 && minExponent > 0) {
            m_numExponent = m_numExponent - minExponent;
            m_denExponent = m_denExponent - minExponent;
        }

        return *this;
    }

    /************************************************************************************************************
     ************************************************ METHODS DEF ***********************************************
     ************************************************************************************************************/

    template<typename FloatType>
    template<typename IntType>
    constexpr void ERational<FloatType>::transformToExperimental(const IntType numerator, const IntType denominator) {
        const int numeratorLength = Tools::getNumberLength(numerator);
        m_numExponent = numeratorLength;
        m_numMultiplier = numerator * std::pow(10, -numeratorLength);

        const int denominatorLength = Tools::getNumberLength(denominator);
        m_denExponent = denominatorLength;
        m_denMultiplier = denominator * std::pow(10, -denominatorLength);
    }

    template<typename FloatType>
    constexpr void ERational<FloatType>::verifyDenominator(bool checkIfDenominatorIsNull) {
        if (m_denMultiplier == 0. && checkIfDenominatorIsNull)
            throw Exceptions::DivideByZeroException();

        if (m_denMultiplier < 0.) {
            m_numMultiplier = -m_numMultiplier;
            m_denMultiplier = -m_denMultiplier;
        }
    }

    template<typename FloatType>
    constexpr void ERational<FloatType>::setSameDenominatorAndExponent(
            const ERational<FloatType> &anotherERational,
            ERational<FloatType> &firstERational,
            ERational<FloatType> &secondERational
    ) const {
        firstERational = *this * ERational(anotherERational.getDenMultiplier(),
                                           anotherERational.getDenExponent(),
                                           anotherERational.getDenMultiplier(),
                                           anotherERational.getDenExponent());

        secondERational = (ERational) anotherERational * ERational(m_denMultiplier,
                                                                   m_denExponent,
                                                                   m_denMultiplier,
                                                                   m_denExponent);

        const int exponentDifference = firstERational.getNumExponent() - secondERational.getNumExponent();

        if (exponentDifference > 0) {
            secondERational.setNumMultiplier(secondERational.getNumMultiplier() / std::pow(10, exponentDifference));
            secondERational.setNumExponent(secondERational.getNumExponent() + exponentDifference);
        }

        if (exponentDifference < 0) {
            firstERational.setNumMultiplier(firstERational.getNumMultiplier() / std::pow(10, -exponentDifference));
            firstERational.setNumExponent(firstERational.getNumExponent() - exponentDifference);
        }
    }

    /************************************************************************************************************
     ************************************************* STD::COUT ************************************************
     ************************************************************************************************************/

    /**
     * @brief << operator override to allow std::cout
     * @tparam FloatType
     * @param stream
     * @param rational
     * @return The stream with the rational to string.
     */
    template<typename FloatType>
    std::ostream &operator<<(std::ostream &stream, const ERational<FloatType> &rational) {
        return stream << rational.toString();
    }

};