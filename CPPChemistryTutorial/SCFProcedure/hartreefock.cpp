//
//  hartreefock.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/22/20.
//

#include "hartreefock.hpp"
#include <iostream>

unique_ptr<MatrixXf> HartreeFock::get_core_hamiltonian() {
    return make_unique<MatrixXf>(kei + nai);
}

unique_ptr<MatrixXf> HartreeFock::get_ortho_overlap() {
    SelfAdjointEigenSolver<MatrixXf> solver(overlap);
    MatrixXf eigen_vectors = solver.eigenvectors();
    MatrixXf eigen_values = solver.eigenvalues();
    
    MatrixXf eigen_values_diagonal = ((MatrixXf) eigen_values.array().pow(-0.5)).asDiagonal();
    MatrixXf ortho_overlap = eigen_vectors * eigen_values_diagonal * eigen_vectors.transpose();
    
    return make_unique<MatrixXf>(ortho_overlap);
}
