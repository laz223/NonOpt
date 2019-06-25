// Copyright (C) 2019 Frank E. Curtis
//
// This code is published under the MIT License.
//
// Author(s) : Frank E. Curtis

#ifndef __NONOPTSTRATEGIES_HPP__
#define __NONOPTSTRATEGIES_HPP__

#include <memory>
#include <string>

#include "NonOptDirectionComputation.hpp"
#include "NonOptInverseHessianUpdate.hpp"
#include "NonOptLineSearch.hpp"
#include "NonOptPointSetUpdate.hpp"
#include "NonOptQPSolver.hpp"
#include "NonOptSymmetricMatrix.hpp"

namespace NonOpt
{

/**
 * Forward declarations
 */
class DirectionComputation;
class InverseHessianUpdate;
class LineSearch;
class PointSetUpdate;
class QPSolver;
class SymmetricMatrix;

/**
 * Strategies class
 */
class Strategies
{

 public:
  /** @name Constructors */
  //@{
  /**
   * Constructor
   */
  Strategies(){};
  //@}

  /** @name Destructor */
  //@{
  /**
   * Destructor
   */
  ~Strategies(){};
  //@}

  /** @name Options handling methods */
  //@{
  /**
   * Add options
   * \param[in,out] options is pointer to Options object from NonOpt
   * \param[in] reporter is pointer to Reporter object from NonOpt
   */
  void addOptions(Options* options,
                  const Reporter* reporter);
  /**
   * Set options
   * \param[in] options is pointer to Options object from NonOpt
   * \param[in] reporter is pointer to Reporter object from NonOpt
   */
  void setOptions(const Options* options,
                  const Reporter* reporter);
  //@}

  /** @name Initialize method */
  //@{
  /**
   * Initialize strategies
   * \param[in] options is pointer to Options object from NonOpt
   * \param[in,out] quantities is pointer to Quantities object from NonOpt
   * \param[in] reporter is pointer to Reporter object from NonOpt
   */
  void initialize(const Options* options,
                  Quantities* quantities,
                  const Reporter* reporter);
  //@}

  /** @name Get methods */
  //@{
  /**
   * Get pointer to DirectionComputation
   * \return pointer to DirectionComputation object
   */
  inline std::shared_ptr<DirectionComputation> directionComputation() { return direction_computation_; }
  /**
   * Get pointer to InverseHessianUpdate
   * \return pointer to InverseHessianUpdate object
   */
  inline std::shared_ptr<InverseHessianUpdate> inverseHessianUpdate() { return inverse_hessian_update_; }
  /**
   * Get pointer to LineSearch
   * \return pointer to LineSearch object
   */
  inline std::shared_ptr<LineSearch> lineSearch() { return line_search_; }
  /**
   * Get pointer to PointSetUpdate
   * \return pointer to PointSetUpdate object
   */
  inline std::shared_ptr<PointSetUpdate> pointSetUpdate() { return point_set_update_; }
  /**
   * Get pointer to QPSolver
   * \return pointer QPSolver object
   */
  inline std::shared_ptr<QPSolver> qpSolver() { return qp_solver_; }
  /**
   * Get pointer to SymmetricMatrix
   * \return pointer to SymmetricMatrix object
   */
  inline std::shared_ptr<SymmetricMatrix> symmetricMatrix() { return symmetric_matrix_; }
  /**
   * Get iteration header
   * \return iteration header as string
   */
  inline std::string iterationHeader() const { return iteration_header_; }
  //@}

  /** @name Set methods */
  //@{
  /**
   * Set iteration header
   */
  void setIterationHeader();
  //@}

  /** @name Print methods */
  //@{
  /**
   * Print header
   * \param[in] reporter is pointer to Reporter object from NonOpt
   */
  void printHeader(const Reporter* reporter);
  /**
   * Print footer
   * \param[in] reporter is pointer to Reporter object from NonOpt
   */
  void printFooter(const Reporter* reporter);
  //@}

 private:
  /** @name Default compiler generated methods
   * (Hidden to avoid implicit creation/calling.)
   */
  //@{
  /**
   * Copy constructor
   */
  Strategies(const Strategies&);
  /**
   * Overloaded equals operator
   */
  void operator=(const Strategies&);
  //@}

  /** @name * Private members */
  //@{
  std::shared_ptr<DirectionComputation> direction_computation_;
  std::shared_ptr<InverseHessianUpdate> inverse_hessian_update_;
  std::shared_ptr<LineSearch> line_search_;
  std::shared_ptr<PointSetUpdate> point_set_update_;
  std::shared_ptr<QPSolver> qp_solver_;
  std::shared_ptr<SymmetricMatrix> symmetric_matrix_;
  std::string iteration_header_;
  //@}

};  // end Strategies

}  // namespace NonOpt

#endif /* __NONOPTSTRATEGIES_HPP__ */