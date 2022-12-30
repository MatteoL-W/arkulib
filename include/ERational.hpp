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
        template<typename IntType = int>
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
                FloatType numMultiplier, short int numExponent,
                FloatType denMultiplier, short int denExponent
        );

        /**
         * @brief Explicit constructor with std::pair
         * @param numerator
         * @param denominator
         */
        constexpr ERational(
                std::pair<FloatType, short int> numerator,
                std::pair<FloatType, short int> denominator
        );

        /**
         * @brief Default Destructor
         */
        inline ~ERational() = default;

        /************************************************************************************************************
         ************************************************ GETTERS ***************************************************
         ************************************************************************************************************/

        [[maybe_unused]] [[nodiscard]] constexpr inline std::pair<FloatType,short int> getNumerator() const noexcept { return m_numerator; }
        [[nodiscard]] constexpr inline FloatType getNumMultiplier() const noexcept { return m_numerator.first; }
        [[nodiscard]] constexpr inline short int getNumExponent() const noexcept { return m_numerator.second; }

        [[maybe_unused]] [[nodiscard]] constexpr inline std::pair<FloatType,short int> getDenominator() const noexcept { return m_denominator; }
        [[nodiscard]] constexpr inline FloatType getDenMultiplier() const noexcept { return m_denominator.first; }
        [[nodiscard]] constexpr inline short int getDenExponent() const noexcept { return m_denominator.second; }

        /************************************************************************************************************
         ************************************************ SETTERS ***************************************************
         ************************************************************************************************************/

        constexpr inline void setNumerator(std::pair<FloatType, short int> numerator) noexcept { m_numerator = numerator; }
        constexpr inline void setNumerator(FloatType newMultiplier, short int newExponent) noexcept { m_numerator = std::make_pair(newMultiplier, newExponent); }
        constexpr inline void setNumMultiplier(FloatType newNumMultiplier) noexcept { m_numerator.first = newNumMultiplier; }
        constexpr inline void setNumExponent(short int newNumExponent) noexcept { m_numerator.second = newNumExponent; }

        constexpr inline void setDenominator(std::pair<FloatType, short int> denominator) noexcept { m_denominator = denominator; }
        constexpr inline void setDenominator(FloatType newMultiplier, short int newExponent) noexcept { m_denominator = std::make_pair(newMultiplier, newExponent); }
        constexpr inline void setDenMultiplier(FloatType newDenMultiplier) noexcept { m_denominator.first = newDenMultiplier; }
        constexpr inline void setDenExponent(short int newDenExponent) noexcept { m_denominator.second = newDenExponent; }

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
            return (getNumMultiplier() < 0. && getDenMultiplier() > 0.)
                    || (getNumMultiplier() > 0. && getDenMultiplier() < 0.);
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
            return ERational<FloatType>(
                    std::abs(getNumMultiplier()), getNumExponent(),
                    std::abs(getDenMultiplier()), getDenExponent()
            );
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
                (getNumMultiplier() * std::pow(10, getNumExponent())) / (getDenMultiplier() * std::pow(10, getDenExponent())
            );
        }

        /**
         * @brief Return ( _numerator_ / _denominator_ ) as a string
         * @return std::string
         */
        [[nodiscard]] inline std::string toString() const noexcept {
            return "(" + Tools::toStringWithPrecision(getNumMultiplier()) + " * 10^" + Tools::toStringWithPrecision(getNumExponent()) + ")"
                   + " / " + "(" + Tools::toStringWithPrecision(getDenMultiplier()) + " * 10^" + Tools::toStringWithPrecision(getDenExponent()) + ")";
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
        template<typename IntType = int>
        constexpr void transformToExperimental(IntType numerator, IntType denominator);

        /**
         * @brief Transform a numerator/denominator into a pair
         * @tparam IntType
         * @param operand
         * @return
         */
        template<typename IntType = int>
        static constexpr std::pair<FloatType, short int> transformOperandToPair(IntType operand);

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
         * @brief Set firstERational and secondERational with the same numerator exponent
         * @param firstERational
         * @param secondERational
         */
        constexpr void setAtSameExponent(
            ERational<FloatType> &firstERational,
            ERational<FloatType> &secondERational
        ) const;

        /**
         * @brief Set firstERational and secondERational with the same denominator exponent
         * @param anotherERational
         * @param firstERational
         * @param secondERational
         */
        constexpr void setAtSameDenominator(
            const ERational <FloatType> &anotherERational,
            ERational <FloatType> &firstERational,
            ERational <FloatType> &secondERational
        ) const;

        /************************************************************************************************************
         ************************************************** MEMBERS *************************************************
         ************************************************************************************************************/

        std::pair<FloatType, short int> m_numerator;

        std::pair<FloatType, short int> m_denominator;
        // We also could have create a struct for this pair to ease some methods
        // (for example, we could have isNegative() in the struct or even operators)
    };




    /************************************************************************************************************
     ************************************************************************************************************/



    /************************************************************************************************************
     ********************************************* CONSTRUCTOR DEF **********************************************
     ************************************************************************************************************/

    template<typename FloatType>
    constexpr ERational<FloatType>::ERational() : m_numerator(0., 0), m_denominator(1., 0) {
        verifyTemplateType();
    }


    template<typename FloatType>
    template<typename IntType>
    constexpr ERational<FloatType>::ERational(
            const IntType numerator,
            const IntType denominator,
            const bool willBeReduce,
            const bool willDenominatorBeVerified
    )   : m_numerator(transformOperandToPair(numerator)),
          m_denominator(transformOperandToPair(denominator))
    {
        verifyTemplateType();
        verifyDenominator(willDenominatorBeVerified);

        if (willBeReduce) {
            const int gcd = std::gcd(numerator, denominator);
            assert(gcd != 0 && "GCD shouldn't be equal to 0");

            transformToExperimental(numerator / gcd, denominator / gcd);
            *this = simplify();
        }
    }

    template<typename FloatType>
    template<typename AnotherFloatType>
    constexpr ERational<FloatType>::ERational(const AnotherFloatType &nonRational) {
        verifyTemplateType();

        Rational<long long int> tmpRational = Rational<long long int>::fromFloatingPoint(nonRational);
        *this = ERational{tmpRational};
    }



    template<typename FloatType>
    constexpr ERational<FloatType>::ERational(
            const FloatType numMultiplier,
            const short int numExponent,
            const FloatType denMultiplier,
            const short int denExponent
    ) {
        m_numerator = std::make_pair(numMultiplier, numExponent);
        m_denominator = std::make_pair(denMultiplier, denExponent);
    }


    template<typename FloatType>
    constexpr ERational<FloatType>::ERational(
            std::pair<FloatType, short int> numerator,
            std::pair<FloatType, short int> denominator
    ) {
        m_numerator = numerator;
        m_denominator = denominator;
    }

    /************************************************************************************************************
     ********************************************* OPERATOR + DEF ***********************************************
     ************************************************************************************************************/

    template<typename FloatType>
    constexpr ERational<FloatType> ERational<FloatType>::operator+(const ERational<FloatType> &anotherERational) const {
        // We create new Rational with the same denominator (we multiply them by denominator / denominator)
        ERational<FloatType> firstERational;
        ERational<FloatType> secondERational;
        setAtSameDenominator(anotherERational, firstERational, secondERational);
        setAtSameExponent(firstERational, secondERational);


        return ERational<FloatType>(
                std::make_pair(
                        firstERational.getNumMultiplier() + secondERational.getNumMultiplier(),
                        firstERational.getNumExponent()
                ),
                firstERational.getDenominator()
        );
    }

    /************************************************************************************************************
 ********************************************* OPERATOR - DEF ***********************************************
 ************************************************************************************************************/

    template<typename FloatType>
    constexpr ERational<FloatType> ERational<FloatType>::operator-(const ERational<FloatType> &anotherERational) const {
        // We create new Rational with the same denominator (we multiply them by denominator / denominator)
        ERational<FloatType> firstERational;
        ERational<FloatType> secondERational;
        setAtSameDenominator(anotherERational, firstERational, secondERational);
        setAtSameExponent(firstERational, secondERational);

        return ERational<FloatType>(
                std::make_pair(
                        firstERational.getNumMultiplier() - secondERational.getNumMultiplier(),
                        firstERational.getNumExponent()
                ),
                firstERational.getDenominator()
        );
    }

    /************************************************************************************************************
     ********************************************* OPERATOR * DEF ***********************************************
     ************************************************************************************************************/

    template<typename FloatType>
    constexpr ERational<FloatType> ERational<FloatType>::operator*(const ERational<FloatType> &anotherERational) const {
        return ERational<FloatType>(
                getNumMultiplier() * anotherERational.getNumMultiplier(),
                getNumExponent() + anotherERational.getNumExponent(),
                getDenMultiplier() * anotherERational.getDenMultiplier(),
                getDenExponent() + anotherERational.getDenExponent()
        );
    }

    /************************************************************************************************************
     ********************************************* OPERATOR / DEF ***********************************************
     ************************************************************************************************************/

    template<typename FloatType>
    constexpr ERational<FloatType> ERational<FloatType>::operator/(const ERational<FloatType> &anotherERational) const {
        return ERational<FloatType>(
                getNumMultiplier() * anotherERational.getDenMultiplier(),
                getNumExponent() + anotherERational.getDenExponent(),
                getDenMultiplier() * anotherERational.getNumMultiplier(),
                getDenExponent() + anotherERational.getNumExponent()
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
            setNumExponent(0);
            setDenExponent(0);
        }

        const int minExponent = std::min(getNumExponent(), getDenExponent());
        if (exponentDifference != 0 && minExponent > 0) {
            setNumExponent(getNumExponent() - minExponent);
            setDenExponent(getDenExponent() - minExponent);
        }

        return *this;
    }

    /************************************************************************************************************
     ************************************************ METHODS DEF ***********************************************
     ************************************************************************************************************/

    template<typename FloatType>
    template<typename IntType>
    constexpr void ERational<FloatType>::transformToExperimental(const IntType numerator, const IntType denominator) {
        setNumerator(transformOperandToPair(numerator));
        setDenominator(transformOperandToPair(denominator));
    }

    template<typename FloatType>
    template<typename IntType>
    constexpr std::pair<FloatType, short> ERational<FloatType>::transformOperandToPair(IntType operand) {
        const int operandLength = Tools::getNumberLength(operand);
        return std::make_pair(
                operand * std::pow(10, -operandLength),
                operandLength
        );
    }

    template<typename FloatType>
    constexpr void ERational<FloatType>::verifyDenominator(bool checkIfDenominatorIsNull) {
        if (getDenMultiplier() == 0. && checkIfDenominatorIsNull)
            throw Exceptions::DivideByZeroException();

        if (getDenMultiplier() < 0.) {
            setNumMultiplier(-getNumMultiplier());
            setDenMultiplier(-getDenMultiplier());
        }
    }

    template<typename FloatType>
    constexpr void ERational<FloatType>::setAtSameExponent(
            ERational<FloatType> &firstERational,
            ERational<FloatType> &secondERational
    ) const {
        const int exponentDifference = firstERational.getNumExponent() - secondERational.getNumExponent();
        secondERational.setNumMultiplier(secondERational.getNumMultiplier() / std::pow(10, exponentDifference));
        secondERational.setNumExponent(secondERational.getNumExponent() + exponentDifference);

        assert(firstERational.getNumExponent() == secondERational.getNumExponent() &&
               "The two numerator exponent should be equal");
    }

    template<typename FloatType>
    constexpr void ERational<FloatType>::setAtSameDenominator(
            const ERational <FloatType> &anotherERational,
            ERational <FloatType> &firstERational,
            ERational <FloatType> &secondERational
    ) const {
        firstERational= *this * ERational(anotherERational.getDenominator(), anotherERational.getDenominator());
        secondERational= anotherERational * ERational(this->getDenominator(), this->getDenominator());
        assert(firstERational.getDenominator() == secondERational.getDenominator() &&
               "The two numerator exponent should be equal");
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