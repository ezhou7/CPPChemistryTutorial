//
//  hessian.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 11/13/20.
//

#ifndef transformer_hessian_hpp
#define transformer_hessian_hpp

#include <math.h>

#include <memory>

#include <Eigen/Core>
#include <unsupported/Eigen/MatrixFunctions>

using Eigen::MatrixXf;
using Eigen::SelfAdjointEigenSolver;
using Eigen::VectorXf;
using std::move;
using std::unique_ptr;

class HessianTransformer {
public:
    void massWeightHessianMatrix(MatrixXf& hessian, const VectorXf& masses);
    VectorXf getHarmonicFrequencies(const MatrixXf& hessian);
};

#endif /* transfomer_hessian_hpp */
