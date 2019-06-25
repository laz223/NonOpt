// Copyright (C) 2019 Frank E. Curtis
//
// This code is published under the MIT License.
//
// Author(s) : Frank E. Curtis

#include <cmath>
#include <limits>
#include <random>

#include "QuadPoly.hpp"

// Constructor
QuadPoly::QuadPoly(int n,
                   int m,
                   int a,
                   double s)
{

  // Set problem size
  number_of_variables_ = n;
  number_of_affine_ = m;
  number_of_active_affine_ = a;

  // Declare scaling factor
  double symmetric_matrix_scaling = s;

  // Declare random number generator
  std::default_random_engine generator;
  std::uniform_real_distribution<double> uniform(0.0, 1.0);
  std::normal_distribution<double> normal(0.0, 1.0);
  generator.seed(0);

  // Declare quantities
  linear_ = new double[number_of_variables_];
  symmetric_matrix_ = new double[number_of_variables_ * number_of_variables_];
  constant_ = new double[number_of_affine_];
  matrix_ = new double[number_of_affine_ * number_of_variables_];

  // Initialize quantities
  for (int i = 0; i < number_of_variables_; i++) {
    linear_[i] = 0.0;
  }
  for (int i = 0; i < number_of_variables_ * number_of_variables_; i++) {
    symmetric_matrix_[i] = 0.0;
  }
  for (int i = 0; i < number_of_affine_; i++) {
    constant_[i] = 0.0;
  }
  for (int i = 0; i < number_of_affine_ * number_of_variables_; i++) {
    matrix_[i] = 0.0;
  }

  // Set random elements of constant
  for (int i = number_of_active_affine_; i < number_of_affine_; i++) {
    constant_[i] = -pow(uniform(generator), 2.0);
  }

  // Initialize and set matrix
  for (int i = 0; i < number_of_affine_ * number_of_variables_; i++) {
    matrix_[i] = normal(generator);
  }

  // Declare weights
  double* weights = new double[number_of_affine_];

  // Set weights and normalize
  double weights_sum = 0.0;
  for (int i = 0; i < number_of_affine_; i++) {
    if (i < number_of_active_affine_) {
      weights[i] = uniform(generator);
      weights_sum += weights[i];
    }
    else {
      weights[i] = 0.0;
    }
  }  // end for
  for (int i = 0; i < number_of_active_affine_; i++) {
    weights[i] /= weights_sum;
  }

  // Set linear
  for (int i = 0; i < number_of_variables_; i++) {
    for (int j = 0; j < number_of_affine_; j++) {
      linear_[i] = linear_[i] - matrix_[j * number_of_variables_ + i] * weights[j];
    }
  }  // end for

  // Declare and set values for symmetric matrix
  double* symmetric_matrix_init = new double[number_of_variables_ * number_of_variables_];
  for (int i = 0; i < number_of_variables_ * number_of_variables_; i++) {
    symmetric_matrix_init[i] = normal(generator);
  }

  // Set symmetric matrix
  for (int i = 0; i < number_of_variables_; i++) {
    for (int j = 0; j < number_of_variables_; j++) {
      for (int k = 0; k < number_of_variables_; k++) {
        symmetric_matrix_[i * number_of_variables_ + j] = symmetric_matrix_[i * number_of_variables_ + j] + symmetric_matrix_init[i * number_of_variables_ + k] * symmetric_matrix_init[j * number_of_variables_ + k];
      }
    }
  }  // end for
  for (int i = 0; i < number_of_variables_ * number_of_variables_; i++) {
    symmetric_matrix_[i] = symmetric_matrix_scaling * symmetric_matrix_[i];
  }

  // Delete temporary quantities
  if (weights != nullptr) {
    delete[] weights;
  }
  if (symmetric_matrix_init != nullptr) {
    delete[] symmetric_matrix_init;
  }

}  // end constructor

// Destructor
QuadPoly::~QuadPoly()
{

  // Delete quantities
  if (linear_ != nullptr) {
    delete[] linear_;
  }
  if (symmetric_matrix_ != nullptr) {
    delete[] symmetric_matrix_;
  }
  if (constant_ != nullptr) {
    delete[] constant_;
  }
  if (matrix_ != nullptr) {
    delete[] matrix_;
  }

}  // end destructor

// Number of variables
bool QuadPoly::numberOfVariables(int& n)
{

  // Set number of variables
  n = number_of_variables_;

  // Return
  return true;

}  // end numberOfVariables

// Initial point
bool QuadPoly::initialPoint(int n,
                            double* x)
{

  // Declare random number generator
  std::default_random_engine generator;
  std::normal_distribution<double> normal(0.0, 1.0);
  generator.seed(1);

  // Set initial point
  for (int i = 0; i < n; i++) {
    x[i] = normal(generator);
  }

  // Return
  return true;

}  // end initialPoint

// Objective value
bool QuadPoly::evaluateObjective(int n,
                                 const double* x,
                                 double& f)
{

  // Initialize objective value
  f = 0.0;

  // Evaluate linear term
  for (int i = 0; i < number_of_variables_; i++) {
    f += linear_[i] * x[i];
  }

  // Add quadratic term
  for (int i = 0; i < number_of_variables_; i++) {
    for (int j = 0; j < number_of_variables_; j++) {
      f += 0.5 * symmetric_matrix_[i * number_of_variables_ + j] * x[i] * x[j];
    }
  }  // end for

  // Declare affine term
  double* affine = new double[number_of_affine_];

  // Initialize affine term
  for (int i = 0; i < number_of_affine_; i++) {
    affine[i] = 0.0;
  }

  // Evaluate affine term
  double affine_max = -std::numeric_limits<double>::infinity();
  for (int i = 0; i < number_of_affine_; i++) {
    affine[i] += constant_[i];
    for (int j = 0; j < number_of_variables_; j++) {
      affine[i] += matrix_[i * number_of_variables_ + j] * x[j];
    }
    if (affine[i] > affine_max) {
      affine_max = affine[i];
    }
  }  // end for
  f += affine_max;

  // Delete affine
  if (affine != nullptr) {
    delete[] affine;
  }

  // Return
  return true;

}  // end evaluateObjective

// Gradient value
bool QuadPoly::evaluateGradient(int n,
                                const double* x,
                                double* g)
{

  // Initialize gradient value
  for (int i = 0; i < number_of_variables_; i++) {
    g[i] = linear_[i];
  }

  // Add gradient of quadratic term
  for (int i = 0; i < number_of_variables_; i++) {
    for (int j = 0; j < number_of_variables_; j++) {
      g[i] += symmetric_matrix_[i * number_of_variables_ + j] * x[j];
    }
  }  // end for

  // Declare affine term
  double* affine = new double[number_of_affine_];

  // Initialize affine term
  for (int i = 0; i < number_of_affine_; i++) {
    affine[i] = 0.0;
  }

  // Evaluate affine term
  double affine_max = -std::numeric_limits<double>::infinity();
  int affine_ind = -1;
  for (int i = 0; i < number_of_affine_; i++) {
    affine[i] += constant_[i];
    for (int j = 0; j < number_of_variables_; j++) {
      affine[i] += matrix_[i * number_of_variables_ + j] * x[j];
    }
    if (affine[i] > affine_max) {
      affine_max = affine[i];
      affine_ind = i;
    }
  }  // end for

  // Add gradient of max term
  for (int i = 0; i < number_of_variables_; i++) {
    g[i] += matrix_[affine_ind * number_of_variables_ + i];
  }

  // Delete affine
  if (affine != nullptr) {
    delete[] affine;
  }

  // Return
  return true;

}  // end evaluateGradient

// Finalize solution
bool QuadPoly::finalizeSolution(int n,
                                const double* x,
                                double f,
                                const double* g)
{
  return true;
}