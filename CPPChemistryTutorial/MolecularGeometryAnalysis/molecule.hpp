//
//  molecule.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/14/20.
//

#ifndef molecule_hpp
#define molecule_hpp

#include <Eigen/Core>
#include <unsupported/Eigen/MatrixFunctions>

#include "atom.hpp"
#include "mathutils.hpp"
#include "matrix.hpp"

using Eigen::Matrix3f;
using Eigen::MatrixXf;
using Eigen::RowVector3f;
using Eigen::RowVectorXf;
using Eigen::SelfAdjointEigenSolver;
using Eigen::Vector3f;
using Eigen::VectorXf;

class Molecule {
public:
    double bond_threshold = 4.0;

    unique_ptr<vector<unique_ptr<Atom>>> atoms;
    
    Molecule(unique_ptr<vector<unique_ptr<Atom>>> atoms);
    ~Molecule();
    
    unsigned long size();

    double get_bond_length(int i, int j);
    double get_bond_angle(int i, int j, int k);
    double get_out_of_plane_angle(int i, int j, int k, int l);
    double get_torsion_angle(int i, int j, int k, int l);
    unique_ptr<Vector3f> get_center_of_mass();
    unique_ptr<Matrix3f> get_moment_of_inertia();
    unique_ptr<Vector3f> get_rotational_constants();
};

#endif /* molecule_hpp */
