//
//  hessian.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/21/20.
//

#ifndef hessian_hpp
#define hessian_hpp

#include <math.h>
#include <Eigen/Core>
#include <memory>
#include <iostream>

#include "../MolecularGeometryAnalysis/molecule.hpp"

using Eigen::MatrixXf;
using Eigen::SelfAdjointEigenSolver;
using Eigen::VectorXf;
using std::move;
using std::unique_ptr;

class HessianMatrix {
public:
    unique_ptr<MatrixXf> m;
    
    HessianMatrix(unique_ptr<MatrixXf> m);
    
    void mass_weight(Molecule& mol);
    unique_ptr<VectorXf> harmonic_frequencies();
};

#endif /* hessian_hpp */
