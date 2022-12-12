/**
 * @file      ERational.hpp
 * @author    Elise MASSA
 * @author    Mattéo LECLERCQ
 * @date      2022
 * @warning   The use of ERatio isn't as performant as a simple float type and as Rational.hpp
 * @copyright WTFPL
 */

#include "Rational.hpp"

namespace Arkulib {
    /**
     * @brief This class can be used to express big rationals
     * @tparam IntLikeType
     */
    template<typename IntLikeType = int>
    class ERational : public Rational<IntLikeType> {

    public:

        /************************************************************************************************************
         ****************************************** CONSTRUCTOR / DESTRUCTOR ****************************************
         ************************************************************************************************************/

        /**
         * @brief Default constructor : instantiate an object without parameters.
         */
        inline constexpr explicit ERational() : Rational<IntLikeType>() {};

        /**
         * @brief Classic constructor : create a rational from a numerator and a denominator (set default at 1)
         * @param numerator
         * @param denominator
         */
        inline constexpr explicit ERational(const IntLikeType numerator, const IntLikeType denominator,
                                            const bool willBeReduce = true, const bool willDenominatorBeVerified = true)
                : Rational<IntLikeType>(numerator, denominator, willBeReduce, willDenominatorBeVerified) {};

        /**
         * @brief Copy constructor
         * @param reference
         */
        inline constexpr explicit ERational(const Rational<IntLikeType> &reference) : Rational<IntLikeType>(
                reference) {};

        /**
         * @brief Copy constructor with another int type
         * @tparam AnotherIntLikeType
         * @param copiedRational
         */
        template<typename AnotherIntLikeType>
        inline constexpr explicit
        ERational(Rational<AnotherIntLikeType> &copiedRational) : Rational<IntLikeType>(copiedRational) {}

        /**
         * @brief Create a rational from a floating number
         * @tparam U
         * @param nonRational
         */
        template<typename U>
        inline constexpr explicit ERational(const U &nonRational) : Rational<IntLikeType>(nonRational) {};

        /**
         * @brief Default Destructor
         */
        inline ~ERational() = default;

        /************************************************************************************************************
         ************************************************ GETTERS ***************************************************
         ************************************************************************************************************/

        [[nodiscard]] inline IntLikeType getNumerator() const noexcept {
            return Rational<IntLikeType>::m_numerator * 10;
        }

        [[nodiscard]] inline IntLikeType getDenominator() const noexcept {
            return Rational<IntLikeType>::m_denominator * 15;
        }
    };


};