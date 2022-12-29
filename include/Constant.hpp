/**
 * @file      Constant.hpp
 * @author    Elise MASSA
 * @author    Mattéo LECLERCQ
 * @date      2022
 * @brief     Customize the library by changing default values
 * @copyright WTFPL
 */

#pragma once

namespace Arkulib::Constant {
    const unsigned int DEFAULT_ITERATIONS_FROM_FP = 10; /*!< Default iterations used in the fromFloatingPoint recursive algorithm */
    const double DEFAULT_THRESHOLD_FROM_FP = 0.01; /*!< Default iterations used in the fromFloatingPoint recursive algorithm */
    const unsigned int DEFAULT_MAX_DIGITS_APPROXIMATE = 7; /*!< The max digits handled by the method toApproximation */
    const unsigned int DEFAULT_KEPT_DIGITS_APPROXIMATE = 3; /*!< The default precision set for toApproximation. The approximation will be set for 3 digits by default. */
    const unsigned int DEFAULT_COUT_ERATIONAL_DIGITS = 10; /*!< The default precision set for ERational std::cout */
}