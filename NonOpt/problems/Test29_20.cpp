// Copyright (C) 2019 Frank E. Curtis
//
// This code is published under the MIT License.
//
// Author(s) : Frank E. Curtis and Minhan Li

#include <cmath>

#include "Test29_20.hpp"

// Constructor
Test29_20::Test29_20(int n)
  : number_of_variables_(n) {}

// Destructor
Test29_20::~Test29_20() {}

// Number of variables
bool Test29_20::numberOfVariables(int& n)
{

  // Set number of variables
  n = number_of_variables_;

  // Return
  return true;

} // end numberOfVariables

// Initial point
bool Test29_20::initialPoint(int n,
                             double* x)
{

  // Set initial point
  for (int i = 0; i < n; i++) {
    x[i] = -1.0;
  }

  // Return
  return true;

} // end initialPoint

// Objective value
bool Test29_20::evaluateObjective(int n,
                                  const double* x,
                                  double& f)
{

  // Evaluate maximum value
  f = fabs((0.5 * x[0] - 3.0) * x[0] - 1.0 + 2.0 * x[1]);
  for (int i = 1; i < n - 1; i++) {
    f = fmax(f, fabs((0.5 * x[i] - 3.0) * x[i] - 1.0 + x[i - 1] + 2.0 * x[i + 1]));
  }
  f = fmax(f, fabs((0.5 * x[n - 1] - 3.0) * x[n - 1] - 1.0 + x[n - 2]));

  // Return
  return true;

} // end evaluateObjective

// Gradient value
bool Test29_20::evaluateGradient(int n,
                                 const double* x,
                                 double* g)
{

  // Initialize gradient and evaluate maximum value
  int max_ind = 0;
  double term = (0.5 * x[0] - 3.0) * x[0] - 1.0 + 2.0 * x[1];
  double max_term = term;
  double max_val = fabs(term);
  g[0] = 0.0;
  for (int i = 1; i < n - 1; i++) {
    term = (0.5 * x[i] - 3.0) * x[i] - 1.0 + x[i - 1] + 2.0 * x[i + 1];
    if (fabs(term) > max_val) {
      max_ind = i;
      max_term = term;
      max_val = fabs(term);
    } // end if
    g[i] = 0.0;
  } // end for
  term = (0.5 * x[n - 1] - 3.0) * x[n - 1] - 1.0 + x[n - 2];
  if (fabs(term) > max_val) {
    max_ind = n - 1;
    max_term = term;
    max_val = fabs(term);
  } // end if
  g[n - 1] = 0.0;

  // Evaluate gradient
  double sign = ((max_term >= 0.0) ? 1.0 : -1.0);
  g[max_ind] = sign * (x[max_ind] - 3.0);
  if (max_ind > 0) {
    g[max_ind - 1] = sign * (1.0);
  }
  if (max_ind < n - 1) {
    g[max_ind + 1] = sign * (2.0);
  }

  // Return
  return true;

} // end evaluateGradient

// Finalize solution
bool Test29_20::finalizeSolution(int n,
                                 const double* x,
                                 double f,
                                 const double* g)
{
  return true;
}