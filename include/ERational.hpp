/**
 * @file      ERational.hpp
 * @author    Elise MASSA
 * @author    Mattéo LECLERCQ
 * @date      2022
 * @warning   The use of ERatio isn't as performant as a simple float type and as Rational.hpp
 * @copyright WTFPL
 */

#include "Rational.hpp"
#include <iomanip>

namespace Arkulib {
    /**
     * @brief This class can be used to express big rationals
     * @tparam IntType
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
        [[maybe_unused]] inline constexpr explicit ERational(const Rational<IntType> &reference) {
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
                int numExponent,
                FloatType denMultiplier,
                int denExponent
        );

        /**
         * @brief Default Destructor
         */
        inline ~ERational() = default;

        /************************************************************************************************************
         ************************************************ GETTERS ***************************************************
         ************************************************************************************************************/

        [[nodiscard]] virtual inline int getNumExponent() const noexcept { return m_numExponent; }

        [[nodiscard]] virtual inline FloatType getNumMultiplier() const noexcept { return m_numMultiplier; }

        [[nodiscard]] virtual inline int getDenExponent() const noexcept { return m_denExponent; }

        [[nodiscard]] virtual inline FloatType getDenMultiplier() const noexcept { return m_denMultiplier; }

        /************************************************************************************************************
         ************************************************ SETTERS ***************************************************
         ************************************************************************************************************/

        virtual inline void setNumExponent(int newNumExponent) noexcept { m_numExponent = newNumExponent; }

        virtual inline void setNumMultiplier(FloatType newNumMultiplier) noexcept { m_numMultiplier = newNumMultiplier; }

        virtual inline void setDenExponent(int newDenExponent) noexcept { m_denExponent = newDenExponent; }

        virtual inline void setDenMultiplier(FloatType newDenMultiplier) noexcept { m_denMultiplier = newDenMultiplier; }

        /************************************************************************************************************
         *********************************************** OPERATOR + *************************************************
         ************************************************************************************************************/

        /**
         * @brief Sum operation between 2 experimental rationals
         * @param anotherERational
         * @return The sum in ERational
         */
        ERational<FloatType> operator+(const ERational<FloatType> &anotherERational);

        /************************************************************************************************************
         *********************************************** OPERATOR - *************************************************
         ************************************************************************************************************/

        /**
         * @brief Subtraction operation between 2 experimental rationals
         * @param anotherERational
         * @return The result in ERational
         */
        ERational<FloatType> operator-(const ERational<FloatType> &anotherERational);

        /************************************************************************************************************
         *********************************************** OPERATOR * *************************************************
         ************************************************************************************************************/

        /**
         * @brief Multiplication operation between 2 experimental rationals
         * @param anotherERational
         * @return The multiplication in ERational
         */
        ERational<FloatType> operator*(const ERational<FloatType> &anotherERational);

        /************************************************************************************************************
         *********************************************** OPERATOR / *************************************************
         ************************************************************************************************************/

        /**
         * @brief Division operation between 2 experimental rationals
         * @param anotherERational
         * @return The result in ERational
         */
        ERational<FloatType> operator/(const ERational<FloatType> &anotherERational);

        /************************************************************************************************************
         *********************************************** OPERATOR == ************************************************
         ************************************************************************************************************/

        /**
         * @brief Comparison between 2 ERationals
         * @param anotherRational
         * @return True if the first erational is equal to the second
         */
        inline bool operator==(const ERational<FloatType> &anotherERational);

        /************************************************************************************************************
         ********************************************** OPERATOR != *************************************************
         ************************************************************************************************************/

        /**
         * @brief Different comparison between 2 erationals
         * @param anotherRational
         * @return True if the first erational is different to the second
         */
        inline bool operator!=(const ERational<FloatType> &anotherERational);

        /************************************************************************************************************
         ************************************************** MATHS ***************************************************
         ************************************************************************************************************/

        /**
         * @brief Simplify the Rational with GCD (called in constructor)
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
        inline void verifyTemplateType() const {
            if (std::is_integral<FloatType>()) throw Exceptions::IntTypeGivenException();
        };

        /**
         * @brief Set firstERational and secondERational with the same denominator and the same numerator exponent
         * @param anotherERational
         * @param firstERational
         * @param secondERational
         */
        void setSameDenominatorAndExponent(
            const ERational<FloatType> &anotherERational,
            ERational<FloatType> &firstERational,
            ERational<FloatType> &secondERational
        );

        /************************************************************************************************************
         ************************************************** MEMBERS *************************************************
         ************************************************************************************************************/

        FloatType m_numMultiplier; /*!< The multiplier of the numerator */
        int m_numExponent; /*!< The exponent of the numerator */

        FloatType m_denMultiplier; /*!< The multiplier of the denominator */
        int m_denExponent; /*!< The exponent of the denominator */
    };




    /************************************************************************************************************
     ************************************************************************************************************/



    /************************************************************************************************************
     ********************************************* CONSTRUCTOR DEF **********************************************
     ************************************************************************************************************/

    template<typename FloatType>
    constexpr ERational<FloatType>::ERational() {
        this->verifyTemplateType();

        m_numExponent = 0;
        m_numMultiplier = 0.;
        m_denExponent = 0;
        m_denMultiplier = 1.;
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

        ERational tmpERational{tmpRational.getNumerator(), tmpRational.getDenominator()};
        m_denMultiplier = tmpERational.getDenMultiplier();
        m_denExponent = tmpERational.getDenExponent();
        m_numMultiplier = tmpERational.getNumMultiplier();
        m_numExponent = tmpERational.getNumExponent();
    }



    template<typename FloatType>
    constexpr ERational<FloatType>::ERational(
            const FloatType numMultiplier,
            const int numExponent,
            const FloatType denMultiplier,
            const int denExponent
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
    ERational<FloatType> ERational<FloatType>::operator+(const ERational<FloatType> &anotherERational) {
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
    ERational<FloatType> ERational<FloatType>::operator-(const ERational<FloatType> &anotherERational) {
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
    ERational<FloatType> ERational<FloatType>::operator*(const ERational<FloatType> &anotherERational) {
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
    ERational<FloatType> ERational<FloatType>::operator/(const ERational<FloatType> &anotherERational) {
        return ERational<FloatType>(
                m_numMultiplier * anotherERational.getDenMultiplier(),// Num Multiplier
                m_numExponent + anotherERational.getDenExponent(),    // Num Exponent
                m_denMultiplier * anotherERational.getNumMultiplier(),    // Den Multiplier
                m_denExponent + anotherERational.getNumExponent()    // Den Exponent
        );
    }

    /************************************************************************************************************
     ********************************************* OPERATOR == DEF **********************************************
     ************************************************************************************************************/

    template<typename FloatType>
    bool ERational<FloatType>::operator==(const ERational<FloatType> &anotherERational) {
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
    bool ERational<FloatType>::operator!=(const ERational<FloatType> &anotherERational) {
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
        const int numeratorLength = trunc(log10(numerator));
        m_numExponent = numeratorLength;
        m_numMultiplier = numerator * std::pow(10, -numeratorLength);

        const int denominatorLength = trunc(log10(denominator));
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
    void ERational<FloatType>::setSameDenominatorAndExponent(
            const ERational<FloatType> &anotherERational,
            ERational<FloatType> &firstERational,
            ERational<FloatType> &secondERational
    ) {
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

    template<typename FloatType>
    std::ostream &operator<<(std::ostream &stream, const ERational<FloatType> &rational) {
        return stream << rational.toString();
    }

};