// Copyright (C) 2019 Frank E. Curtis
//
// This code is published under the MIT License.
//
// Author(s) : Frank E. Curtis and Minhan Li

#include <cmath>

#include "Test29_19.hpp"

// Constructor
Test29_19::Test29_19(int n)
  : number_of_variables_(n) {}

// Destructor
Test29_19::~Test29_19() {}

// Number of variables
bool Test29_19::numberOfVariables(int& n)
{

  // Set number of variables
  n = number_of_variables_;

  // Return
  return true;

} // end numberOfVariables

// Initial point
bool Test29_19::initialPoint(int n,
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
bool Test29_19::evaluateObjective(int n,
                                  const double* x,
                                  double& f)
{

  // Evaluate maximum value
  f = pow((3.0 - 2.0 * x[0]) * x[0] - 2.0 * x[1] + 1.0, 2.0);
  for (int i = 1; i < n - 1; i++) {
    f = fmax(f, pow((3.0 - 2.0 * x[i]) * x[i] - x[i - 1] - 2.0 * x[i + 1] + 1.0, 2.0));
  }
  f = fmax(f, pow((3.0 - 2.0 * x[n - 1]) * x[n - 1] - x[n - 2] + 1.0, 2.0));

  // Return
  return !isnan(f);

} // end evaluateObjective

// Objective and gradient value
bool Test29_19::evaluateObjectiveAndGradient(int n,
                                             const double* x,
                                             double& f,
                                             double* g)
{

  // Declare success
  bool success = true;

  // Initialize gradient and evaluate maximum value
  int index = 0;
  double term = (3.0 - 2.0 * x[0]) * x[0] - 2.0 * x[1] + 1.0;
  double maximum = term;
  f = pow(term, 2.0);
  double temp;
  g[0] = 0.0;
  for (int i = 1; i < n - 1; i++) {
    term = (3.0 - 2.0 * x[i]) * x[i] - x[i - 1] - 2.0 * x[i + 1] + 1.0;
    temp = pow(term, 2.0);
    if (temp > f) {
      index = i;
      maximum = term;
      f = temp;
    } // end if
    g[i] = 0.0;
  } // end for
  term = (3.0 - 2.0 * x[n - 1]) * x[n - 1] - x[n - 2] + 1.0;
  temp = pow(term, 2.0);
  if (temp > f) {
    index = n - 1;
    maximum = term;
    f = temp;
  } // end if
  g[n - 1] = 0.0;

  // Check index of maximum value
  double sign = ((f >= 0.0) ? 1.0 : -1.0);
  g[index] = sign * (2.0 * maximum * (3.0 - 4.0 * x[index]));
  if (isnan(g[index])) {
    success = false;
  }
  if (index > 0) {
    g[index - 1] = sign * (2.0 * maximum * (-1.0));
    if (isnan(g[index-1])) {
      success = false;
    }
  }
  if (index < n - 1) {
    g[index + 1] = sign * (2.0 * maximum * (-2.0));
    if (isnan(g[index+1])) {
      success = false;
    }
  }

  // Return
  return !isnan(f) && success;

} // end evaluateObjective

// Gradient value
bool Test29_19::evaluateGradient(int n,
                                 const double* x,
                                 double* g)
{

  // Declare success
  bool success = true;

  // Initialize gradient and evaluate maximum value
  int index = 0;
  double term = (3.0 - 2.0 * x[0]) * x[0] - 2.0 * x[1] + 1.0;
  double maximum = term;
  double f = pow(term, 2.0);
  double temp;
  g[0] = 0.0;
  for (int i = 1; i < n - 1; i++) {
    term = (3.0 - 2.0 * x[i]) * x[i] - x[i - 1] - 2.0 * x[i + 1] + 1.0;
    temp = pow(term, 2.0);
    if (temp > f) {
      index = i;
      maximum = term;
      f = temp;
    } // end if
    g[i] = 0.0;
  } // end for
  term = (3.0 - 2.0 * x[n - 1]) * x[n - 1] - x[n - 2] + 1.0;
  temp = pow(term, 2.0);
  if (temp > f) {
    index = n - 1;
    maximum = term;
    f = temp;
  } // end if
  g[n - 1] = 0.0;

  // Check index of maximum value
  double sign = ((f >= 0.0) ? 1.0 : -1.0);
  g[index] = sign * (2.0 * maximum * (3.0 - 4.0 * x[index]));
  if (isnan(g[index])) {
    success = false;
  }
  if (index > 0) {
    g[index - 1] = sign * (2.0 * maximum * (-1.0));
    if (isnan(g[index-1])) {
      success = false;
    }
  }
  if (index < n - 1) {
    g[index + 1] = sign * (2.0 * maximum * (-2.0));
    if (isnan(g[index+1])) {
      success = false;
    }
  }

  // Return
  return success;

} // end evaluateGradient

// Finalize solution
bool Test29_19::finalizeSolution(int n,
                                 const double* x,
                                 double f,
                                 const double* g)
{
  return true;
}
