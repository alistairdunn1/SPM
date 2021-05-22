//============================================================================
// Name        : TwoSex_NoEstimates.h
// Author      : S.Rasmussen
// Date        : 11/09/2014
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
// Description :
//============================================================================
#ifndef TESTFIXTURES_MODELS_TWOSEX_NOESTIMATES_H_
#define TESTFIXTURES_MODELS_TWOSEX_NOESTIMATES_H_

#include <string>

const std::string two_sex_no_estimates =
    R"(
@model
nrows 1
ncols 1
layer Base
categories immature-male mature-male immature-female mature-female
min_age 1
max_age 50
age_plus_group True
initialisation_phases Phase1 Phase2
cell_length 1
time_steps step_one step_two
initial_year 1994
current_year 2008
age_size none none none none

@age_size none
type none
size_weight none

@size_weight none
type none

@initialisation_phase Phase1
years 200
time_steps Phase1

@time_step Phase1
processes Recruitment Maturation-male Maturation-female halfM halfM Ageing

@initialisation_phase Phase2
years 1
time_steps Phase2

@time_step Phase2
processes Recruitment Maturation-male Maturation-female halfM halfM Ageing

@time_step step_one
processes Recruitment Maturation-male Maturation-female halfM Fishing halfM

@time_step step_two
processes Ageing

@process Ageing
type ageing
categories immature-male mature-male immature-female mature-female

@process Recruitment
type constant_recruitment
categories immature-male immature-female
proportions 0.5 0.5
R0 997386
age 1

@process halfM
type constant_mortality_rate
categories immature-male mature-male immature-female mature-female
M 0.065 0.065 0.065 0.065
selectivities One One One One

@process Fishing
type event_mortality
categories immature-male mature-male immature-female mature-female
years 1998 1999 2000 2001 2002 2003 2004 2005 2006 2007
layers Fishing_1998 Fishing_1999 Fishing_2000 Fishing_2001 Fishing_2002 Fishing_2003 Fishing_2004 Fishing_2005 Fishing_2006 Fishing_2007
U_max 0.99
selectivities FishingSel FishingSel FishingSel FishingSel
penalty event_mortality_penalty

@process Maturation-male
type category_transition_rate
from immature-male
to mature-male
proportions 1.0
selectivities Maturation

@process Maturation-female
type category_transition_rate
from immature-female
to mature-female
proportions 1.0
selectivities Maturation

@layer Base
type numeric
data 1

@layer constant
type numeric
data 1

@layer SSRU
type categorical
data All

@layer Fishing_1998
type numeric
data 1849.153714

@layer Fishing_1999
type numeric
data 14442.000000

@layer Fishing_2000
type numeric
data 28323.203463

@layer Fishing_2001
type numeric
data 24207.464203

@layer Fishing_2002
type numeric
data 47279.000000

@layer Fishing_2003
type numeric
data 58350.943094

@layer Fishing_2004
type numeric
data 82875.872790

@layer Fishing_2005
type numeric
data 115974.547730

@layer Fishing_2006
type numeric
data 113852.472257

@layer Fishing_2007
type numeric
data 119739.517172

@selectivity One
type constant
c 1

@selectivity Maturation
type logistic_producing
L 5
H 30
a50 8
ato95 3

@selectivity FishingSel
type logistic
a50 8
ato95 3

@estimation
minimiser gammadiff

@minimiser gammadiff
type numerical_differences
iterations 1000
evaluations 4000
stepsize 1e-7
tolerance 0.002 
covariance True

@MCMC
start 1
length 1500000
keep 1000
adaptive_stepsize True
adapt_at 100000 200000 400000
proposal_t True
df 4

@observation CAA-year-1998
type proportions_at_age
year 1998
time_step step_one
categories immature-male + mature-male + immature-female + mature-female
selectivities FishingSel FishingSel FishingSel FishingSel
min_age 1
max_age 35
age_plus_group True
layer SSRU
obs All 0.00000 0.00000 0.01382 0.03178 0.08416 0.03859 0.06588 0.08455 0.05462 0.07629 0.03963 0.07307 0.07535 0.07065 0.04555 0.06775 0.02900 0.02156 0.02174 0.01617 0.01136 0.01653 0.00646 0.01327 0.00948 0.00838 0.00959 0.00189 0.00414 0.00518 0.00000 0.00000 0.00058 0.00068 0.00230
error_value All 343
likelihood multinomial
delta 1e-11

@observation CAA-year-1999
type proportions_at_age
year 1999
time_step step_one
categories immature-male + mature-male + immature-female + mature-female
selectivities FishingSel FishingSel FishingSel FishingSel
min_age 1
max_age 35
age_plus_group True
layer SSRU
obs All 0.00000 0.00000 0.00086 0.00244 0.00448 0.03929 0.10549 0.11334 0.10784 0.09378 0.08746 0.10926 0.07183 0.07593 0.06111 0.03952 0.01718 0.01463 0.01281 0.00675 0.01591 0.00337 0.00814 0.00000 0.00051 0.00000 0.00391 0.00090 0.00138 0.00000 0.00000 0.00000 0.00000 0.00097 0.00090
error_value All 564
likelihood multinomial
delta 1e-11

@observation CAA-year-2000
type proportions_at_age
year 2000
time_step step_one
categories immature-male + mature-male + immature-female + mature-female
selectivities FishingSel FishingSel FishingSel FishingSel
min_age 1
max_age 35
age_plus_group True
layer SSRU
obs All 0.00000 0.00000 0.00000 0.00037 0.00415 0.00640 0.01976 0.07120 0.08222 0.07515 0.08747 0.05801 0.10737 0.08080 0.08953 0.09575 0.06014 0.06322 0.02783 0.02057 0.02040 0.00738 0.00755 0.00536 0.00203 0.00438 0.00000 0.00242 0.00000 0.00045 0.00000 0.00000 0.00008 0.00000 0.00000
error_value All 651
likelihood multinomial
delta 1e-11

@observation CAA-year-2001
type proportions_at_age
year 2001
time_step step_one
categories immature-male + mature-male + immature-female + mature-female
selectivities FishingSel FishingSel FishingSel FishingSel
min_age 1
max_age 35
age_plus_group True
layer SSRU
obs All 0.00000 0.00000 0.00000 0.00200 0.00350 0.03549 0.06725 0.09951 0.08653 0.04724 0.05347 0.04106 0.03943 0.05259 0.05045 0.06034 0.04739 0.04569 0.04445 0.03272 0.03233 0.02405 0.02646 0.02949 0.01345 0.01439 0.01173 0.01423 0.00349 0.00762 0.00389 0.00477 0.00227 0.00073 0.00126
error_value All 840
likelihood multinomial
delta 1e-11

@observation CAA-year-2002
type proportions_at_age
year 2002
time_step step_one
categories immature-male + mature-male + immature-female + mature-female
selectivities FishingSel FishingSel FishingSel FishingSel
min_age 1
age_plus_group True
layer SSRU
max_age 35
obs All 0.00000 0.00000 0.00900 0.00021 0.00166 0.00281 0.00261 0.01229 0.04306 0.03154 0.05151 0.06312 0.06697 0.09535 0.05892 0.07222 0.07539 0.04725 0.04795 0.02844 0.04516 0.04174 0.02689 0.03357 0.01697 0.03698 0.02749 0.01893 0.01425 0.01098 0.00479 0.00452 0.00247 0.00324 0.00215
error_value All 598
likelihood multinomial
delta 1e-11

@observation CAA-year-2003
type proportions_at_age
year 2003
time_step step_one
categories immature-male + mature-male + immature-female + mature-female
selectivities FishingSel FishingSel FishingSel FishingSel
min_age 1
max_age 35
age_plus_group True
layer SSRU
obs All 0.00000 0.00000 0.00000 0.00000 0.01000 0.00065 0.00066 0.00345 0.00887 0.00748 0.01729 0.03141 0.03914 0.05192 0.03888 0.05965 0.06126 0.05314 0.06201 0.06782 0.04751 0.05956 0.08472 0.05216 0.05335 0.05356 0.02539 0.02896 0.03062 0.01596 0.01437 0.00435 0.00976 0.00364 0.00162
error_value All 456
likelihood multinomial
delta 1e-11

@observation CAA-year-2004
type proportions_at_age
year 2004
time_step step_one
categories immature-male + mature-male + immature-female + mature-female
selectivities FishingSel FishingSel FishingSel FishingSel
min_age 1
max_age 35
age_plus_group True
layer SSRU
obs All 0.00000 0.00000 0.00300 0.00090 0.00223 0.01645 0.01668 0.01642 0.01872 0.03421 0.02997 0.04186 0.06070 0.08973 0.08342 0.06299 0.09181 0.05329 0.06977 0.03387 0.04415 0.04125 0.02680 0.02912 0.01770 0.03041 0.01543 0.01909 0.01444 0.01296 0.00816 0.00938 0.00159 0.00235 0.00135
error_value All 538
likelihood multinomial
delta 1e-11

@observation CAA-year-2005
type proportions_at_age
year 2005
time_step step_one
categories immature-male + mature-male + immature-female + mature-female
selectivities FishingSel FishingSel FishingSel FishingSel
min_age 1
max_age 35
age_plus_group True
layer SSRU
obs All 0.00000 0.00000 0.01722 0.00581 0.01447 0.01395 0.00875 0.01650 0.01843 0.01546 0.03134 0.03891 0.06389 0.07664 0.08851 0.07702 0.08848 0.07067 0.05496 0.06758 0.03703 0.03704 0.03964 0.01325 0.02080 0.00893 0.00995 0.02363 0.01265 0.00666 0.00688 0.00301 0.00223 0.01005 0.00065
error_value All 438
likelihood multinomial
delta 1e-11

@observation CAA-year-2006
type proportions_at_age
year 2006
time_step step_one
categories immature-male + mature-male + immature-female + mature-female
selectivities FishingSel FishingSel FishingSel FishingSel
min_age 1
max_age 35
age_plus_group True
layer SSRU
obs All 0.00000 0.00000 0.00000 0.00100 0.00434 0.00278 0.02499 0.02925 0.02513 0.02217 0.05581 0.06836 0.06633 0.10862 0.10592 0.10892 0.08496 0.06597 0.05506 0.02521 0.03047 0.02841 0.01219 0.01519 0.00872 0.01126 0.01303 0.00897 0.00162 0.00294 0.00305 0.00629 0.00269 0.00003 0.00000
error_value All 817
likelihood multinomial
delta 1e-11

@observation CAA-year-2007
type proportions_at_age
year 2007
time_step step_one
categories immature-male + mature-male + immature-female + mature-female
selectivities FishingSel FishingSel FishingSel FishingSel
min_age 1
max_age 35
age_plus_group True
layer SSRU
obs All 0.00000 0.00000 0.00000 0.00095 0.00970 0.01689 0.02675 0.03727 0.03764 0.03621 0.05253 0.04765 0.04557 0.06458 0.09280 0.08854 0.09656 0.07813 0.06467 0.03323 0.03816 0.02401 0.02313 0.02351 0.01130 0.01114 0.01160 0.00656 0.00294 0.00491 0.00302 0.00557 0.00097 0.00319 0.00000
error_value All 915
likelihood multinomial
delta 1e-11

@observation CPUE-1998
type abundance
catchability CPUEq
year 1998
time_step step_one
categories immature-male mature-male immature-female mature-female
selectivities FishingSel FishingSel FishingSel FishingSel
layer SSRU
obs All 22.55065505
error_value All 0.2
likelihood lognormal

@observation CPUE-1999
type abundance
catchability CPUEq
year 1999
time_step step_one
categories immature-male mature-male immature-female mature-female
selectivities FishingSel FishingSel FishingSel FishingSel
layer SSRU
obs All 57.30952381
error_value  All 0.2
likelihood lognormal

@observation CPUE-2000
type abundance
catchability CPUEq
year 2000
time_step step_one
categories immature-male mature-male immature-female mature-female
selectivities FishingSel FishingSel FishingSel FishingSel
layer SSRU
obs All 57.92066148
error_value  All 0.2
likelihood lognormal

@observation CPUE-2001
type abundance
catchability CPUEq
year 2001
time_step step_one
categories immature-male mature-male immature-female mature-female
selectivities FishingSel FishingSel FishingSel FishingSel
layer SSRU
obs All 33.52834377
error_value  All 0.2
likelihood lognormal

@observation CPUE-2002
type abundance
catchability CPUEq
year 2002
time_step step_one
categories immature-male mature-male immature-female mature-female
selectivities FishingSel FishingSel FishingSel FishingSel
layer SSRU
obs All 108.4380734
error_value  All 0.2
likelihood lognormal

@observation CPUE-2003
type abundance
catchability CPUEq
year 2003
time_step step_one
categories immature-male mature-male immature-female mature-female
selectivities FishingSel FishingSel FishingSel FishingSel
layer SSRU
obs All 72.84761934
error_value  All 0.2
likelihood lognormal

@observation CPUE-2004
type abundance
catchability CPUEq
year 2004
time_step step_one
categories immature-male mature-male immature-female mature-female
selectivities FishingSel FishingSel FishingSel FishingSel
layer SSRU
obs All 38.29753826
error_value  All 0.2
likelihood lognormal

@observation CPUE-2005
type abundance
catchability CPUEq
year 2005
time_step step_one
categories immature-male mature-male immature-female mature-female
selectivities FishingSel FishingSel FishingSel FishingSel
layer SSRU
obs All 75.84993311
error_value  All 0.2
likelihood lognormal

@observation CPUE-2006
type abundance
catchability CPUEq
year 2006
time_step step_one
categories immature-male mature-male immature-female mature-female
selectivities FishingSel FishingSel FishingSel FishingSel
layer SSRU
obs All 109.47353102
error_value  All 0.2
likelihood lognormal

@observation CPUE-2007
type abundance
catchability CPUEq
year 2007
time_step step_one
categories immature-male mature-male immature-female mature-female
selectivities FishingSel FishingSel FishingSel FishingSel
layer SSRU
obs All 85.7732931
error_value  All 0.2
likelihood lognormal

@catchability CPUEq
q 0.000153139

@penalty event_mortality_penalty
log_scale False
multiplier 10
)";

#endif /* TESTFIXTURES_MODELS_TWOSEX_NOESTIMATES_H_ */
