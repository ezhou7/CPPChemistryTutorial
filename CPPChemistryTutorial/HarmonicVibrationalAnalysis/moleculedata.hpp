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
#include <unsupported/Eigen/MatrixFunctions>

using Eigen::Dynamic;
using Eigen::Matrix;
using Eigen::Matrix3f;
using Eigen::MatrixXf;
using Eigen::RowVector3f;
using Eigen::SelfAdjointEigenSolver;
using Eigen::Vector3f;
using Eigen::Vector3i;
using Eigen::VectorXf;
using std::make_unique;
using std::unique_ptr;

class MolecularData {
public:
    // ---- Molecular Geometry ---- //
    const double bondThreshold = 4.0;
    
    Vector3i zvals;                               // atomic numbers
    VectorXf masses;                              // atomic masses
    MatrixXf coords;                              // atomic coordinates - centered on center of mass
    MatrixXf bondLengths;                         // Atomic bond lengths
    Matrix<MatrixXf, Dynamic, 1> bondAngles;      // Atomic bond angles
    
    double getOutOfPlaneAngle(int i, int j, int k, int l);
    double getTorsionAngle(int i, int j, int k, int l);
    unique_ptr<Vector3f> getCenterOfMass();
    unique_ptr<Matrix3f> getMomentOfInertia();
    unique_ptr<Vector3f> getRotationalConstants();
    
    // ---- Harmonic Vibrational Frequency ---- //
    MatrixXf hessian;       // Hessian matrix of energy second derivatives
    
    unique_ptr<MatrixXf> getMassWeightedHessian();
    unique_ptr<VectorXf> getHarmonicFrequencies();
    
    // ---- Hartree-Fock SCF ---- //
    MatrixXf S;             // pre-computed one-electron atomic orbital overlap matrix
    MatrixXf T;             // pre-computed one-electron kinetic energy matrix
    MatrixXf V;             // pre-computed one-electron nuclear attraction integrals
    MatrixXf eri;           // pre-computed two-electron repulsion integrals
    
    unique_ptr<MatrixXf> getCoreHamiltonian();
};

#endif /* moleculedata_hpp */
