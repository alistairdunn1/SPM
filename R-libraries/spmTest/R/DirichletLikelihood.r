#' Calculate the Dirichlet likelihood from a set of observed, expected, and error values
#'
#' @author Alistair Dunn
#' @param observed The observed proportions
#' @param expected The expected proportions
#' @param errorValue The error value (total sample size N) of the observed proportions
#' @param processError Additional process error for the likelihood (alpha0)
#' @param delta The robustifying constant to prevent divide by zero errors
#'
#' @export
#'
dirichletLikelihood <- function(observed, expected, errorValue, processError = 0, delta = 1e-11) {
  zeroFun <- function(x, delta = 1e-11) ifelse(x >= delta, x, delta / (2 - (x / delta)))
  if (processError > 0) N <- errorValue * processError
  else N <- errorValue
  alpha <- zeroFun(expected, delta) * N
  x <- observed
  a1 <- lgamma(sum(alpha))
  a2 <- sum(lgamma(alpha))
  a3 <- sum((alpha - 1) * log(x))
  res <- -a1 + a2 - a3
  return(res)
}

dirichletLikelihood2 <- function(observed, expected, errorValue, processError = 0, delta = 1e-11) {
  zeroFun <- function(x, delta = 1e-11) ifelse(x >= delta, x, delta / (2 - (x / delta)))
  if (processError > 0) N <- errorValue * processError
  else N <- errorValue

  initial <- 0
  for (i in 1:length(expected)) {
    initial <- initial + zeroFun(expected[i], delta) * N
  }
  print(initial)

  initial <- -lgamma(initial)

  score <- c()
  for (i in 1:length(expected)) {
    dAlpha = zeroFun(expected[i], delta) * N
    dA2andA3 = lgamma(dAlpha) - ((dAlpha - 1.0) * log(zeroFun(observed[i], delta)));
    score[i] = dA2andA3;
  }

  print(initial)
  print(score)

  res <- sum(score) + initial

  return(res)
}
