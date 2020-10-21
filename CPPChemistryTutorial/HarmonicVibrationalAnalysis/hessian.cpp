//
//  hessian.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/21/20.
//

#include "hessian.hpp"

HessianMatrix::HessianMatrix(unique_ptr<MatrixXf> m) {
    this->m = move(m);
}

void HessianMatrix::mass_weight(Molecule& mol) {
    vector<unique_ptr<Atom>>& atoms = *mol.atoms;
    int natoms = (int) atoms.size();
    
    vector<double> masses(natoms);

    for (int i = 0; i < natoms; i++) {
        int atomic_num = atoms.at(i)->zvalue;
        masses[i] = (atomic_masses[atomic_num]);
    }
    
    MatrixXf& mat = *m;
    for (int i = 0; i < mat.rows(); i++) {
        double mi = masses[(int) i / 3];

        for (int j = 0; j < mat.cols(); j++) {
            if (mat(i, j) == 0.0) {
                continue;
            } else {
                double mj = masses[(int) j / 3];
                mat(i, j) /= sqrt(mi * mj);
            }
        }
    }
}

unique_ptr<VectorXf> HessianMatrix::harmonic_frequencies() {
    SelfAdjointEigenSolver<MatrixXf> solver(*m);

    MatrixXf eigen_vectors = solver.eigenvectors();
    VectorXf eigen_values = solver.eigenvalues();
    eigen_values = (1E-7 < eigen_values.array().abs()).select(eigen_values, 0.0f);
    std::cout << eigen_values << std::endl;
    
    double scalar = 5140.48;
    return make_unique<VectorXf>(eigen_values.array().sqrt() * scalar);
}
