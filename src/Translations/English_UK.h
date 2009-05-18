//============================================================================
// Name        : English.h
// Author      : S.Rasmussen
// Date        : 18/07/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

#ifndef ENGLISH_UK_H_
#define ENGLISH_UK_H_

//**********************************************************************
// ERROR CODES/STRINGS
//
//**********************************************************************
#define ERROR_DUPLICATE                     "Duplicate "
#define ERROR_EQUAL_NOT                     " does not equal "
#define ERROR_EQUAL_TO                      " is equal to "
#define ERROR_GREATER_EQUAL_TO              " is greater than or equal to "
#define ERROR_GREATER_THAN                  " is greater than "
#define ERROR_LESS_EQUAL_TO                 " is less than or equal to "
#define ERROR_LESS_THAN                     " is less than "
#define ERROR_LIST_EQUAL_SIZE               " list must be same size as "
#define ERROR_MISSING                       "Missing "
#define ERROR_MUST_BE_PAIRED                " must be entered as pairs"
#define ERROR_NO_MATCHING                   " has no matching "
#define ERROR_NOT_ENOUGH                    "Not enough "
#define ERROR_SEPARATOR                     ": "
#define ERROR_SUPPORTED                     " not supported"
#define ERROR_TOO_HIGH                      " is too high"
#define ERROR_TOO_MUCH                      "Too much "
#define ERROR_UNKNOWN                       "Unknown "

// Specific Error Codes
#define ERROR_BAD_CAST_WOLD_SQUARE          "Cannot convert to WorldSquare"
#define ERROR_BETWEEN_ZERO_ONE              " must be between 0.0 and 1.0"
#define ERROR_ENABLED_ESTIMATES             "No enabled estimates to use"
#define ERROR_EQUAL_PROPORTION_ONE          " proportions do not sum to 1.0: "
#define ERROR_FORMAT_PARAMETER              "Invalid format, please use  type[label].variable"
#define ERROR_INVALID_FILE_NAME             "Invalid file name: "
#define ERROR_INVALID_FORMAT                "Invalid format: "
#define ERROR_INVALID_IDX                   "Invalid index: "
#define ERROR_INVALID_LAYER_TYPE_NUMERIC    "Layer is not numeric type: "
#define ERROR_INVALID_LAYER_TYPE_STRING     "Layer is not string type: "
#define ERROR_INVALID_TARGET_NULL           "Unknown variable"
#define ERROR_LENGTH_METHOD                 "method is too short"
#define ERROR_MISSING_N_OBS                 "Missing obs for n: "
#define ERROR_NEGATIVE_BASE_LAYER           "Base layer contains a negative value"
#define ERROR_NOT_BOOLEAN                   " is not a valid True/False value for "
#define ERROR_NOT_CONTAIN_EVEN_ELEMENTS     " does not contain an even number of elements"
#define ERROR_OPEN_FILE                     "Failed to open file: "
#define ERROR_QTY_LESS_N                    "Not enough n's: "
#define ERROR_QTY_LESS_PROPORTIONS          "Not enough proportions: "
#define ERROR_QTY_MORE_N                    "Too many n's: "
#define ERROR_QTY_MORE_PARAMETERS           "Too many parameters for "
#define ERROR_QTY_MORE_PROPORTIONS          "Too many proportions: "
#define ERROR_VALID_SQUARES_WITH_LAYER      "No spatial cells are valid with layer applied"


//**********************************************************************
// BASE CONFIGURATION
//
//**********************************************************************
// Configuration File Syntax Strings
#define CONFIG_ARRAY_END                    "]"
#define CONFIG_ARRAY_START                  "["
#define CONFIG_FALSE                        "false"
#define CONFIG_FALSE_SHORT                  "f"
#define CONFIG_INCLUDE                      "@include"
#define CONFIG_MULTI_COMMENT_END            "}"
#define CONFIG_MULTI_COMMENT_START          "{"
#define CONFIG_RATIO_SEPARATOR              ":"
#define CONFIG_SECTION_SYMBOL               "@"
#define CONFIG_SEPERATOR_ESTIMATE_VALUES    ","
#define CONFIG_SINGLE_COMMENT               "#"
#define CONFIG_TRUE                         "true"
#define CONFIG_TRUE_SHORT                   "t"
#define CONFIG_WILDCARD_MULTIPLE            "*"
#define CONFIG_WILDCARD_SINGLE              "?"

//**********************************************************************
// FMM
//
//**********************************************************************
#define FMM_MANY_FUNCTION_EVALUATIONS             "Numerical_differences: Too many function evaluations"
#define FMM_MANY_LOOPS_LINEAR_SEARCH              "Numerical_differences: Too many loops in this linear search"
#define FMM_SMALL_LINEAR_STEP_SIZE                "Numerical_differences: Linear step size too small"
#define FMM_MANY_QUASI_NEWTON_ITERATIONS          "Numerical_differences: Too many quasi-newton iterations"
#define FMM_ITERATION                             "Numerical_differences: Iteration = "
#define FMM_FUNCTION_VALUE                        "Numerical_differences: Function value = "
#define FMM_CURRENT_PARAMETER_ESTIMATES           "Numerical_differences: Current parameter estimates = "
#define FMM_MAX_NEWTON_STEP_FIVE                  "Numerical_differences: The max newton step has been taken 5 times, see D&S p 348"
#define FMM_CONVERGENCE_CHECK                     "Numerical_differences: Convergence check value = "
#define FMM_CONVERGENCE_THRESHOLD                 "Numerical_differences: Convergence tolerance   = "
#define FMM_CONVERGENCE                           "Numerical_differences: Convergence = "
#define FMM_FUNCTION_SCORE                        "Numerical_differences: Function score = "
#define FMM_GRADIENT_VALUE                        "Numerical_differences: Gradient value = "
#define FMM_SMALL_STEP_SIZE_CONVERGENCE           "Numerical_differences: Step size too small. Indicates successful convergence, but this is not a textbook ideal convergence"
#define FMM_CONVERGENCE_NOT_TEXTBOOK              "Numerical_differences: "

//**********************************************************************
// GAMMADIFF
//
//**********************************************************************
#define GAMMADIFF_SIZE_LOWER_BOUND_START_VALUE    "Lower bound vector is not same size as start value"
#define GAMMADIFF_SIZE_UPPER_BOUND_START_VALUE    "Upper bound vector is not same size as start value"
#define GAMMADIFF_CONVERGENCE_UNCLEAR             "Unclear convergence, maybe local minimum"
#define GAMMADIFF_EVALUATIONS_MAX                 "Maximum evaluations/iterations with no convergence"
#define GAMMADIFF_CONVERGENCE                     "Convergence was successful"
#define GAMMADIFF_RETURN_VALUE_UNKNOWN            "Fatal error, unknown return value = "
#define GAMMADIFF_LESS_START_LOWER_BOUND          "Start value is less than lower bound"
#define GAMMADIFF_GREATER_START_UPPER_BOUND       "Start value is greater than upper bound"

//**********************************************************************
// PARAMETERS
//
//**********************************************************************
#define PARAM_A                                   "a"
#define PARAM_A50                                 "a50"
#define PARAM_ABUNDANCE                           "abundance"
#define PARAM_ABUNDANCE_DENSITY                   "abundance_density"
#define PARAM_AGE                                 "age"
#define PARAM_AGE_INDEX                           "age_index"
#define PARAM_AGE_PLUS_GROUP                      "age_plus_group"
#define PARAM_AGEING                              "ageing"
#define PARAM_AGEING_ERROR                        "ageing_error"
#define PARAM_AGES                                "ages"
#define PARAM_ALL_VALUES_BOUNDED                  "all_values_bounded"
#define PARAM_ALL_VALUES                          "all_values"
#define PARAM_ALPHA                               "alpha"
#define PARAM_ANNUAL_MORTALITY_RATE               "annual_mortality_rate"
#define PARAM_AREA                                "area"
#define PARAM_ATO95                               "ato95"
#define PARAM_B                                   "b"
#define PARAM_BETA                                "beta"
#define PARAM_BH_RECRUITMENT                      "bh_recruitment"
#define PARAM_BINOMIAL                            "binomial"
#define PARAM_BINOMIAL_APPROX                     "binomial_approx"
#define PARAM_BIOMASS                             "biomass"
#define PARAM_BIOMASS_DENSITY                     "biomass_density"
#define PARAM_C                                   "c"
#define PARAM_CATCHABILITY                        "catchability"
#define PARAM_CATEGORIES                          "categories"
#define PARAM_CATEGORY                            "category"
#define PARAM_CATEGORY_INDEX                      "category_index"
#define PARAM_CATEGORY_TRANSITION                 "category_transition"
#define PARAM_CATEGORY_TRANSITION_RATE            "category_transition_rate"
#define PARAM_CELL_LENGTH                         "cell_length"
#define PARAM_COLUMN                              "column"
#define PARAM_COLUMN_INDEX                        "column_index"
#define PARAM_CONSTANT                            "constant"
#define PARAM_CONSTANT_MORTALITY_RATE             "constant_mortality_rate"
#define PARAM_CONSTANT_RECRUITMENT                "constant_recruitment"
#define PARAM_COVARIANCE                          "covariance"
#define PARAM_CROSSOVER_PROBABILITY               "crossover_probability"
#define PARAM_CURRENT_YEAR                        "current_year"
#define PARAM_CV                                  "cv"
#define PARAM_DATA                                "data"
#define PARAM_DE_SOLVER                           "de_solver"
#define PARAM_DELTA                               "delta"
#define PARAM_DERIVED_QUANTITY                    "derived_quantity"
#define PARAM_DIFFERENCE_SCALE                    "difference_scale"
#define PARAM_DISTANCE                            "distance"
#define PARAM_DOUBLE                              "numeric"
#define PARAM_DOUBLE_EXPONENTIAL                  "double_exponential"
#define PARAM_DOUBLE_NORMAL                       "double_normal"
#define PARAM_E                                   "e"
#define PARAM_ENABLED_ESTIMATES                   "enabled_estimates"
#define PARAM_ERROR_VALUE                         "error_value"
#define PARAM_ESTIMABLE                           "estimable"
#define PARAM_ESTIMATE                            "estimate"
#define PARAM_ESTIMATE_SUMMARY                    "estimate_summary"
#define PARAM_ESTIMATES                           "estimates"
#define PARAM_ESTIMATE_VALUE                      "estimate_value"
#define PARAM_ESTIMATION                          "estimation"
#define PARAM_EVENT_MORTALITY                     "event_mortality"
#define PARAM_EXPONENTIAL                         "exponential"
#define PARAM_FILE_NAME                           "file_name"
#define PARAM_FINAL_YEAR                          "final_year"
#define PARAM_FLAGGED_PENALTIES                   "flagged_penalties"
#define PARAM_FROM                                "from"
#define PARAM_FUNCTION                            "function"
#define PARAM_GAMMADIFF                           "numerical_differences"
#define PARAM_H                                   "h"
#define PARAM_HEIGHT                              "height"
#define PARAM_HEX                                 "hex"
#define PARAM_HEX_UNIFORM                         "hex_uniform"
#define PARAM_INCREASING                          "increasing"
#define PARAM_INDEX                               "index"
#define PARAM_INITIAL_YEAR                        "initial_year"
#define PARAM_INITIALIZATION                      "initialisation"
#define PARAM_INITIALIZATION_PHASE                "initialisation_phase"
#define PARAM_INITIALIZATION_PHASES               "initialisation_phases"
#define PARAM_INVERSE_LOGISTIC                    "inverse_logistic"
#define PARAM_KNIFE_EDGE                          "knife_edge"
#define PARAM_L                                   "l"
#define PARAM_LABEL                               "label"
#define PARAM_LAMBDA                              "lambda"
#define PARAM_LAYER                               "layer"
#define PARAM_LAYER_DERIVED_WORLD_VIEW            "layer_derived_view"
#define PARAM_LAYER_HEIGHT                        "layer_height"
#define PARAM_LAYER_WIDTH                         "layer_width"
#define PARAM_LAYERS                              "layers"
#define PARAM_LENGTH                              "length"
#define PARAM_LIKELIHOOD                          "likelihood"
#define PARAM_LOG_SCALE                           "log_scale"
#define PARAM_LOGISTIC                            "logistic"
#define PARAM_LOGISTIC_PRODUCING                  "logistic_producing"
#define PARAM_LOGNORMAL                           "lognormal"
#define PARAM_LOWER_BOUND                         "lower_bound"
#define PARAM_M                                   "m"
#define PARAM_MAX_AGE                             "max_age"
#define PARAM_MAX_EVALUATIONS                     "evaluations"
#define PARAM_MAX_GENERATIONS                     "max_generations"
#define PARAM_MAX_ITERATIONS                      "iterations"
#define PARAM_MCMC                                "mcmc"
#define PARAM_META                                "meta"
#define PARAM_METHOD                              "method"
#define PARAM_MIN_AGE                             "min_age"
#define PARAM_MINIMIZER                           "minimiser"
#define PARAM_MODEL                               "model"
#define PARAM_MU                                  "mu"
#define PARAM_MULTINOMIAL                         "multinomial"
#define PARAM_MULTIPLIER                          "multiplier"
#define PARAM_N                                   "n"
#define PARAM_NCOLS                               "ncols"
#define PARAM_NONE                                "none"
#define PARAM_NORMAL                              "normal"
#define PARAM_NORMAL_BY_STDEV                     "normal_by_stdev"
#define PARAM_NORMAL_LOG                          "normal_log"
#define PARAM_NROWS                               "nrows"
#define PARAM_OBJECTIVE                           "objective"
#define PARAM_OBJECTIVE_FUNCTION                  "objective_function"
#define PARAM_OBS                                 "obs"
#define PARAM_OBSERVATION                         "observation"
#define PARAM_OBSERVATION_DEFINITION              "observation_definition"
#define PARAM_OFF_BY_ONE                          "off_by_one"
#define PARAM_ONE                                 "1 (one)"
#define PARAM_ONE_THOUSAND                        "1,000"
#define PARAM_OVERWRITE                           "overwrite"
#define PARAM_PARAMETER                           "parameter"
#define PARAM_PARTITION                           "partition"
#define PARAM_PENALTY                             "penalty"
#define PARAM_POPULATION_SIZE                     "population_size"
#define PARAM_PREFERENCE                          "preference"
#define PARAM_PREFERENCE_FUNCTION                 "preference_function"
#define PARAM_PREFERENCE_FUNCTIONS                "preference_functions"
#define PARAM_PRIOR                               "prior"
#define PARAM_PROCESS                             "process"
#define PARAM_PROCESS_ERROR                       "process_error"
#define PARAM_PROCESSES                           "processes"
#define PARAM_PROFILE                             "profile"
#define PARAM_PROFILES                            "profiles"
#define PARAM_PROPORTION                          "proportion"
#define PARAM_PROPORTIONS                         "proportions"
#define PARAM_PROPORTIONS_AT_AGE                  "proportions_at_age"
#define PARAM_PROPORTIONS_BY_CATEGORY             "proportions_by_category"
#define PARAM_PROPORTION_TIME_STEP                "proportion_time-step"
#define PARAM_PSEUDO                              "none"
#define PARAM_Q                                   "q"
#define PARAM_R0                                  "r0"
#define PARAM_RANDOM_NUMBER_SEED                  "random_number_seed"
#define PARAM_REPORT                              "report"
#define PARAM_RESCALE                             "rescale"
#define PARAM_RHO                                 "rho"
#define PARAM_ROW                                 "row"
#define PARAM_ROW_INDEX                           "row_index"
#define PARAM_RUN_MODE                            "run_mode"
#define PARAM_SAME                                "same"
#define PARAM_SCORES_INDEX                        "scores_index"
#define PARAM_SECTION                             "command"
#define PARAM_SELECTIVITIES                       "selectivities"
#define PARAM_SELECTIVITY                         "selectivity"
#define PARAM_SIGMA                               "sigma"
#define PARAM_SIGMA_L                             "sigma_l"
#define PARAM_SIGMA_R                             "sigma_r"
#define PARAM_SIMULATE                            "simulate"
#define PARAM_SIZE_WEIGHT                         "size_weight"
#define PARAM_SIZE_WEIGHTS                        "size_weights"
#define PARAM_SPATIAL_MAP                         "spatial_map"
#define PARAM_STANDARDISE_YCS_YEAR_RANGE          "standardise_ycs_year_range"
#define PARAM_SQUARE_UNIFORM                      "square_uniform"
#define PARAM_SSB                                 "ssb"
#define PARAM_SSB_OFFSET                          "ssb_offset"
#define PARAM_STEP_SIZE                           "step_size"
#define PARAM_STEEPNESS                           "steepness"
#define PARAM_STRING                              "categorical"
#define PARAM_TARGET_CATEGORIES                   "categories2"
#define PARAM_TARGET_SELECTIVITIES                "selectivities2"
#define PARAM_THRESHOLD                           "threshold"
#define PARAM_THRESHOLD_BIOMASS                   "threshold_biomass"
#define PARAM_TIME_STEP                           "time_step"
#define PARAM_TIME_STEPS                          "time_steps"
#define PARAM_TO                                  "to"
#define PARAM_TOLERANCE                           "tolerance"
#define PARAM_TOTAL_SCORE                         "total_score"
#define PARAM_TYPE                                "type"
#define PARAM_U_MAX                               "u_max"
#define PARAM_UNIFORM                             "uniform"
#define PARAM_UNIFORM_LOG                         "uniform_log"
#define PARAM_UPPER_BOUND                         "upper_bound"
#define PARAM_V                                   "v"
#define PARAM_VALUE                               "value"
#define PARAM_WIDTH                               "width"
#define PARAM_X0                                  "x0"
#define PARAM_X1                                  "x1"
#define PARAM_X2                                  "x2"
#define PARAM_Y0                                  "y0"
#define PARAM_Y1                                  "y1"
#define PARAM_Y2                                  "y2"
#define PARAM_YCS_VALUES                          "ycs_values"
#define PARAM_YCS_YEARS                           "ycs_years"
#define PARAM_YEAR                                "year"
#define PARAM_YEARS                               "years"
#define PARAM_ZERO                                "0 (zero)"

#endif /* ENGLISH_H_ */
