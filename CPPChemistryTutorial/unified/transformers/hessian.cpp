//
//  hessian.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 11/13/20.
//

#include "hessian.hpp"

void HessianTransformer::massWeightHessianMatrix(MatrixXf& hessian, const VectorXf& masses) {
    for (int i = 0; i < hessian.rows(); i++) {
        double mi = masses((int) i / 3);

        for (int j = 0; j < hessian.cols(); j++) {
            if (hessian(i, j) != 0.0) {
                double mj = masses((int) j / 3);
                hessian(i, j) /= sqrt(mi * mj);
            }
        }
    }
}

VectorXf HessianTransformer::getHarmonicFrequencies(const MatrixXf& hessian) {
    SelfAdjointEigenSolver<MatrixXf> solver(hessian);

    MatrixXf eigen_vectors = solver.eigenvectors();
    VectorXf eigen_values = solver.eigenvalues();
    eigen_values = (1E-7 < eigen_values.array().abs()).select(eigen_values, 0.0f);
    
    double scalar = 5140.48;
    return eigen_values.array().sqrt() * scalar;
}
