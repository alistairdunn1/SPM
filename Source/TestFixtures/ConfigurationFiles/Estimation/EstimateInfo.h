/*
 * EstimateInfo.h
 *
 *  Created on: 25/06/2012
 *      Author: Admin
 */

#ifndef ESTIMATEINFO_H_
#define ESTIMATEINFO_H_

const string basic_estimate_info
    = "@estimation\n"
      "minimiser gammadiff\n"
      "@minimiser gammadiff\n"
      "type numerical_differences\n"
      "tolerance 0.002\n"
      "covariance False\n"
      "@minimiser de\n"
      "type de_solver\n"
      "covariance False\n"
      "@estimate\n"
      "parameter process[category_transition_rate_both].proportions(1)\n"
      "lower_bound 0.1\n"
      "upper_bound 1.0\n"
      "type uniform\n";

const string basic_estimate_info_2_estimates
    = "@estimation\n"
      "minimiser gammadiff\n"
      "@minimiser gammadiff\n"
      "type numerical_differences\n"
      "tolerance 0.002\n"
      "covariance False\n"
      "@minimiser de\n"
      "type de_solver\n"
      "covariance False\n"
      "@estimate\n"
      "parameter process[category_transition_rate_both].proportions(1)\n"
      "lower_bound 0.1\n"
      "upper_bound 1.0\n"
      "type uniform\n"
      "@estimate\n"
      "parameter process[category_transition_rate_both].proportions(2)\n"
      "lower_bound 0.1\n"
      "upper_bound 1.0\n"
      "type uniform\n";

const string basic_estimate_info_vector
    = "@estimation\n"
      "minimiser gammadiff\n"
      "@minimiser gammadiff\n"
      "type numerical_differences\n"
      "tolerance 0.002\n"
      "covariance False\n"
      "@minimiser de\n"
      "type de_solver\n"
      "covariance False\n"
      "@estimate\n"
      "parameter process[category_transition_rate_both].proportions\n"
      "lower_bound 0.1\n"
      "upper_bound 1.0\n"
      "type uniform\n";

#endif /* ESTIMATEINFO_H_ */
