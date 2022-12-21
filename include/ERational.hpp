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
    template<typename IntType = int, typename FloatType = double>
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
                FloatType numMultiplier,
                IntType numExponent,
                FloatType denMultiplier,
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
        [[nodiscard]] virtual inline FloatType getNumMultiplier() const noexcept { return m_numMultiplier; }
        [[nodiscard]] virtual inline IntType getDenExponent() const noexcept { return m_denExponent; }
        [[nodiscard]] virtual inline FloatType getDenMultiplier() const noexcept { return m_denMultiplier; }

        /************************************************************************************************************
         ************************************************ SETTERS ***************************************************
         ************************************************************************************************************/

        virtual inline void setNumExponent(IntType newNumExponent) noexcept { m_numExponent = newNumExponent; }
        virtual inline void setNumMultiplier(FloatType newNumMultiplier) noexcept { m_numMultiplier = newNumMultiplier; }
        virtual inline void setDenExponent(IntType newDenExponent) noexcept { m_denExponent = newDenExponent; }
        virtual inline void setDenMultiplier(FloatType newDenMultiplier) noexcept { m_denMultiplier = newDenMultiplier; }

        /************************************************************************************************************
         *********************************************** OPERATOR + *************************************************
         ************************************************************************************************************/

        /**
         * @brief Sum operation between 2 experimental rationals
         * @param anotherERational
         * @return The sum in ERational
         */
        ERational<IntType> operator+(const ERational<IntType> &anotherERational);

        /************************************************************************************************************
         *********************************************** OPERATOR - *************************************************
         ************************************************************************************************************/

        /**
         * @brief Sum operation between 2 experimental rationals
         * @param anotherERational
         * @return The sum in ERational
         */
        ERational<IntType> operator-(const ERational<IntType> &anotherERational);

        /************************************************************************************************************
         *********************************************** OPERATOR * *************************************************
         ************************************************************************************************************/

        /**
         * @brief Multiplication operation between 2 experimental rationals
         * @param anotherERational
         * @return The multiplication in ERational
         */
        ERational<IntType> operator*(const ERational<IntType> &anotherERational);

        /************************************************************************************************************
         *********************************************** CONVERSION *************************************************
         ************************************************************************************************************/

        /**
         * @brief Return ( _numerator_ / _denominator_ ) as a string
         * @return std::string
         */
        [[nodiscard]] inline std::string toString() const noexcept override {
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
        inline void verifyTemplateType() const override {
            if (!std::is_integral<IntType>()) throw Exceptions::FloatTypeGivenException();
            if (std::is_integral<FloatType>()) throw Exceptions::IntTypeGivenException();
        };

        void setSameDenominatorAndExponent(const ERational <IntType> &anotherERational,
                                           ERational <IntType> &firstERational,
                                           ERational <IntType> &secondERational);

        /************************************************************************************************************
         ************************************************** MEMBERS *************************************************
         ************************************************************************************************************/

        //ToDO Suppr denom/num
        FloatType m_numMultiplier; /*!< The multiplier of the numerator */
        IntType m_numExponent; /*!< The exponent of the numerator */

        FloatType m_denMultiplier; /*!< The multiplier of the denominator */
        IntType m_denExponent; /*!< The exponent of the denominator */
    };




    /************************************************************************************************************
     ************************************************************************************************************/



    /************************************************************************************************************
     ********************************************* CONSTRUCTOR DEF **********************************************
     ************************************************************************************************************/

    template<typename IntType, typename FloatType>
    constexpr ERational<IntType, FloatType>::ERational() {
        this->verifyTemplateType();

        m_numExponent = 0;
        m_numMultiplier = 0.;
        m_denExponent = 0;
        m_denMultiplier = 1.;
    }

    template<typename IntType, typename FloatType>
    constexpr ERational<IntType, FloatType>::ERational(
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

    template<typename IntType, typename FloatType>
    template<typename AnotherFloatType>
    constexpr ERational<IntType, FloatType>::ERational(const AnotherFloatType &nonRational) {
        this->verifyTemplateType();

        Rational<long long int> tmpRational = Rational<long long int>::fromFloatingPoint(nonRational);
        if (tmpRational.isZero() && Tools::roundToWantedPrecision(nonRational) != static_cast<AnotherFloatType>(0)) {
            // Because Very large number return 0
            throw Exceptions::NumberTooLargeException();
        }

        ERational<long long int> tmpERational{tmpRational.getNumerator(), tmpRational.getDenominator()};
        m_denMultiplier = tmpERational.getDenMultiplier();
        m_denExponent = tmpERational.getDenExponent();
        m_numMultiplier = tmpERational.getNumMultiplier();
        m_numExponent = tmpERational.getNumExponent();
    }

    template<typename IntType, typename FloatType>
    constexpr ERational<IntType, FloatType>::ERational(
            const FloatType numMultiplier,
            const IntType numExponent,
            const FloatType denMultiplier,
            const IntType denExponent
    ) {
        m_numMultiplier = numMultiplier;
        m_numExponent = numExponent;
        m_denMultiplier = denMultiplier;
        m_denExponent = denExponent;
    }

    /************************************************************************************************************
     ********************************************* OPERATOR + DEF ***********************************************
     ************************************************************************************************************/

    template<typename IntType, typename FloatType>
    ERational<IntType> ERational<IntType, FloatType>::operator+(const ERational<IntType> &anotherERational) {
        ERational<IntType> firstERational;
        ERational<IntType> secondERational;
        setSameDenominatorAndExponent(anotherERational, firstERational, secondERational);

        assert(firstERational.getNumExponent() == secondERational.getNumExponent() && "The two numerator exponent should be equal");
        return ERational<IntType>(
            firstERational.getNumMultiplier() + secondERational.getNumMultiplier(),
            firstERational.getNumExponent(),
            firstERational.getDenMultiplier(),
            firstERational.getDenExponent()
        );
    }

    /************************************************************************************************************
 ********************************************* OPERATOR - DEF ***********************************************
 ************************************************************************************************************/

    template<typename IntType, typename FloatType>
    ERational<IntType> ERational<IntType, FloatType>::operator-(const ERational<IntType> &anotherERational) {
        ERational<IntType> firstERational;
        ERational<IntType> secondERational;
        setSameDenominatorAndExponent(anotherERational, firstERational, secondERational);

        assert(firstERational.getNumExponent() == secondERational.getNumExponent() && "The two numerator exponent should be equal");
        return ERational<IntType>(
                firstERational.getNumMultiplier() - secondERational.getNumMultiplier(),
                firstERational.getNumExponent(),
                firstERational.getDenMultiplier(),
                firstERational.getDenExponent()
        );
    }


    /************************************************************************************************************
     ********************************************* OPERATOR * DEF ***********************************************
     ************************************************************************************************************/

    template<typename IntType, typename FloatType>
    ERational<IntType> ERational<IntType, FloatType>::operator*(const ERational<IntType> &anotherERational) {
        return ERational<IntType>(
                m_numMultiplier * anotherERational.getNumMultiplier(),// Num Multiplier
                m_numExponent + anotherERational.getNumExponent(),    // Num Exponent
                m_denMultiplier * anotherERational.getDenMultiplier(),    // Den Multiplier
                m_denExponent + anotherERational.getDenExponent()    // Den Exponent
        );
    }

    /************************************************************************************************************
     ************************************************ METHODS DEF ***********************************************
     ************************************************************************************************************/

    template<typename IntType, typename FloatType>
    constexpr void ERational<IntType, FloatType>::transformToExperimental(const IntType numerator, const IntType denominator) {
        const int numeratorLength = trunc(log10(numerator));
        m_numExponent = numeratorLength;
        m_numMultiplier = numerator * std::pow(10, -numeratorLength);

        const int denominatorLength = trunc(log10(denominator));
        m_denExponent = denominatorLength;
        m_denMultiplier = denominator * std::pow(10, -denominatorLength);
    }

    template<typename IntType, typename FloatType>
    constexpr void ERational<IntType, FloatType>::verifyDenominator(bool checkIfDenominatorIsNull) {
        if (m_denMultiplier == 0. && checkIfDenominatorIsNull)
            throw Exceptions::DivideByZeroException();

        if (m_denMultiplier < 0.) {
            m_numMultiplier = -m_numMultiplier;
            m_denMultiplier = -m_denMultiplier;
        }
    }

    template<typename IntType, typename FloatType>
    void ERational<IntType, FloatType>::setSameDenominatorAndExponent(const ERational <IntType> &anotherERational,
                                                                      ERational <IntType> &firstERational,
                                                                      ERational <IntType> &secondERational) {
        firstERational = *this * ERational(anotherERational.getDenMultiplier(),
                                           anotherERational.getDenExponent(),
                                           anotherERational.getDenMultiplier(),
                                           anotherERational.getDenExponent());

        secondERational = (ERational)anotherERational * ERational(m_denMultiplier,
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

    template<typename IntType, typename FloatType>
    std::ostream &operator<<(std::ostream &stream, const ERational<IntType, FloatType> &rational) {
        return stream << rational.toString();
    }

};