/**
 * @file      Rational.hpp
 * @author    Elise MASSA
 * @author    Mattéo LECLERCQ
 * @date      2022
 * @warning   The use of Ratio isn't as performant as a simple float type
 * @copyright WTFPL
 */

namespace Arkulib {

    /**
     * @brief This class can be used to express rationals
     * @tparam T
     */
    template<typename T = int>
    class Ratio {

    private:
        T numerator; /*!< Rational's numerator */

        T denominator; /*!< Rational's denominator */

    };

}