//
//  moleculedata.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/21/20.
//

#ifndef moleculedata_hpp
#define moleculedata_hpp

#include <Eigen/Core>
#include <memory>

using Eigen::MatrixXf;
using Eigen::Vector3i;
using Eigen::VectorXf;
using std::unique_ptr;

class MolecularData {
public:
    unique_ptr<Vector3i> zvals;         // atomic numbers
    unique_ptr<VectorXf> weights;       // atomic weights
    unique_ptr<MatrixXf> coords;        // atomic coordinates - centered on center of mass
    unique_ptr<MatrixXf> bondLengths;   // Atomic bond lengths
    unique_ptr<MatrixXf> bondAngles;    // Atomic bond angles
    unique_ptr<MatrixXf> hessian;       // Hessian matrix of energy second derivatives
};

#endif /* moleculedata_hpp */
