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
     //ToDo 2 types ?
    template<typename IntType = int>
    class ERational : public Rational<IntType> {

    public:

        /************************************************************************************************************
         ****************************************** CONSTRUCTOR / DESTRUCTOR ****************************************
         ************************************************************************************************************/

        /**
         * @brief Default constructor : instantiate an object without parameters.
         */
        constexpr explicit ERational();

        /**
         * @brief Classic constructor : create a rational from a numerator and a denominator (set default at 1)
         * @param numerator
         * @param denominator
         */
        constexpr explicit ERational(
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
        constexpr explicit ERational(const FloatingType &nonRational);

        //ToDo Copy constructor

        constexpr ERational(
                double numMultiplier,
                IntType numExponent,
                double denMultiplier,
                IntType denExponent
        );

        /**
         * @brief Default Destructor
         */
        inline ~ERational() = default;

        /************************************************************************************************************
         ************************************************ GETTERS ***************************************************
         ************************************************************************************************************/

        [[nodiscard]] virtual inline IntType getNumExponent() const noexcept { return m_numExponent; }
        [[nodiscard]] virtual inline double getNumMultiplier() const noexcept { return m_numMultiplier; }
        [[nodiscard]] virtual inline IntType getDenExponent() const noexcept { return m_denExponent; }
        [[nodiscard]] virtual inline double getDenMultiplier() const noexcept { return m_denMultiplier; }

        /************************************************************************************************************
         *********************************************** CONVERSION *************************************************
         ************************************************************************************************************/

        /**
         * @brief Return ( _numerator_ / _denominator_ ) as a string
         * @return std::string
         */
        [[nodiscard]] inline std::string toString() const noexcept override {
            return "(" + Tools::toStringWithPrecision(m_numMultiplier) + " * 10^" + Tools::toStringWithPrecision(m_numExponent)
            + " / " + Tools::toStringWithPrecision(m_denMultiplier) + " * 10^" + Tools::toStringWithPrecision(m_denExponent) + ")";
        }

    private:
        /************************************************************************************************************
         ************************************************** METHODS *************************************************
         ************************************************************************************************************/

        /**
         * @brief Set the parameter from a normal numerator and denominator
         * @param numerator
         * @param denominator
         */
        void transformToExperimental(IntType numerator, IntType denominator);

        /**
         * @brief Verify if the denominator is null or negative
         * @param denominator
         * @param checkIfDenominatorIsNull
         */
        constexpr void verifyDenominator(bool checkIfDenominatorIsNull = true);

        /************************************************************************************************************
         ************************************************** MEMBERS *************************************************
         ************************************************************************************************************/

        double m_numMultiplier; /*!< The multiplier of the numerator */
        IntType m_numExponent; /*!< The exponent of the numerator */

        double m_denMultiplier; /*!< The multiplier of the denominator */
        IntType m_denExponent; /*!< The exponent of the denominator */
    };

    template<typename IntType>
    constexpr ERational<IntType>::ERational() {
        this->verifyTemplateType();

        m_numExponent = 0;
        m_numMultiplier = 0;
        m_denExponent = 0;
        m_denMultiplier = 1;
    }

    template<typename IntType>
    constexpr ERational<IntType>::ERational(
            const IntType numerator,
            const IntType denominator,
            const bool willBeReduce,
            const bool willDenominatorBeVerified
    ) {
        this->verifyTemplateType();

        transformToExperimental(numerator, denominator);
        this->verifyDenominator(willDenominatorBeVerified);

        //ToDo Simplify ?
    }

    template<typename IntType>
    template<typename FloatingType>
    constexpr ERational<IntType>::ERational(const FloatingType &nonRational) {
        this->verifyTemplateType();

        Rational<long long int> tmpRational = Rational<long long int>::fromFloatingPoint(nonRational);
        if (tmpRational.isZero() && Tools::roundToWantedPrecision(nonRational) != static_cast<FloatingType>(0)) {
            // Because Very large number return 0
            throw Exceptions::NumberTooLargeException();
        }

        ERational<long long int> tmpERational{tmpRational.getNumerator(), tmpRational.getDenominator()};
        m_denMultiplier = tmpERational.getDenMultiplier();
        m_denExponent = tmpERational.getDenExponent();
        m_numMultiplier = tmpERational.getNumMultiplier();
        m_numExponent = tmpERational.getNumExponent();
    }

    template<typename IntType>
    constexpr ERational<IntType>::ERational(
            const double numMultiplier,
            const IntType numExponent,
            const double denMultiplier,
            const IntType denExponent
    ) {
        m_numMultiplier = numMultiplier;
        m_numExponent = numExponent;
        m_denMultiplier = denMultiplier;
        m_denExponent = denExponent;
    }

    /************************************************************************************************************
     ************************************************ METHODS DEF ***********************************************
     ************************************************************************************************************/

    template<typename IntType>
    void ERational<IntType>::transformToExperimental(const IntType numerator, const IntType denominator) {
        const int numeratorLength = trunc(log10(numerator));
        m_numExponent = numeratorLength;
        m_numMultiplier = numerator * std::pow(10, -numeratorLength);

        const int denominatorLength = trunc(log10(denominator));
        m_denExponent = denominatorLength;
        m_denMultiplier = denominator * std::pow(10, -denominatorLength);
    }

    template<typename IntType>
    constexpr void ERational<IntType>::verifyDenominator(bool checkIfDenominatorIsNull) {
        if (m_denMultiplier == 0. && checkIfDenominatorIsNull)
            throw Exceptions::DivideByZeroException();

        if (m_denMultiplier < 0.) {
            m_numMultiplier = -m_numMultiplier;
            m_denMultiplier = -m_denMultiplier;
        }
    }

    /************************************************************************************************************
     ************************************************* STD::COUT ************************************************
     ************************************************************************************************************/

    template<typename IntType>
    std::ostream &operator<<(std::ostream &stream, const ERational<IntType> &rational) {
        return stream << rational.toString();
    }

};