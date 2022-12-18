/**
 * @file      Constant.hpp
 * @author    Elise MASSA
 * @author    Mattéo LECLERCQ
 * @date      2022
 * @copyright WTFPL
 */

namespace Arkulib::Constant {
    const unsigned int DEFAULT_ITERATIONS_FROM_FP = 10; /*!< Default iterations used in the fromFloatingPoint recursive algorithm */
    const unsigned int DEFAULT_MAX_DIGITS_APPROXIMATE = 7; /*!< The max digits handled by the method toApproximation */
    const unsigned int DEFAULT_KEPT_DIGITS_APPROXIMATE = 3; /*!< The default precision set for toApproximation. The approximation will be set for 3 digits by default. */
}