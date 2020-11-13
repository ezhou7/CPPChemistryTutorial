//
//  molecule.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/23/20.
//

#include "molecule.hpp"

double MolecularData::getOutOfPlaneAngle(int i, int j, int k, int l) {
    double ijDist = bondLengths(i, j);
    double jkDist = bondLengths(j, k);
    double jlDist = bondLengths(j, l);
    
    if (ijDist < bondThreshold && jkDist < bondThreshold && jlDist < bondThreshold) {
        Vector3f jiUnit = (coords.col(j) - coords.col(i)).normalized();
        Vector3f jkUnit = (coords.col(j) - coords.col(k)).normalized();
        Vector3f jlUnit = (coords.col(j) - coords.col(l)).normalized();
        Vector3f crossProd = jiUnit.cross(jkUnit);
        double dotProd = crossProd.dot(jlUnit);

        double bondAngle = bondAngles(i)(j, k);
        double h = dotProd / sin(bondAngle);

        if (h < -1.0) {
            h = -1.0;
        } else if (h > 1.0) {
            h = 1.0;
        }

        return asin(h);
    } else {
        return -1;
    }
}

double MolecularData::getTorsionAngle(int i, int j, int k, int l) {
    double ijDist = bondLengths(i, j);
    double jkDist = bondLengths(j, k);
    double klDist = bondLengths(k, l);
    
    if (ijDist < bondThreshold && jkDist < bondThreshold && klDist < bondThreshold) {
        Vector3f ijUnit = (coords.col(i) - coords.col(j)).normalized();
        Vector3f jkUnit = (coords.col(j) - coords.col(k)).normalized();
        Vector3f klUnit = (coords.col(k) - coords.col(l)).normalized();

        Vector3f ijkCross = ijUnit.cross(jkUnit);
        Vector3f jklCross = jkUnit.cross(klUnit);
        double dotProd = ijkCross.dot(jklCross);
        
        double ijkAngle = bondAngles(i)(j, k);
        double jklAngle = bondAngles(j)(k, l);
        double torsion = dotProd / (sin(ijkAngle) * sin(jklAngle));

        return acos(torsion);
    } else {
        return -1;
    }
}

unique_ptr<Vector3f> MolecularData::getCenterOfMass() {
    RowVector3f cm_row = (masses * coords) / masses.sum();
    Vector3f cm = cm_row.transpose();
    
    return make_unique<Vector3f>(cm);
}

unique_ptr<Matrix3f> MolecularData::getMomentOfInertia() {
    MatrixXf inertia(3, 3);

    unique_ptr<Vector3f> cm_ptr = getCenterOfMass();
    Vector3f cm = *cm_ptr;
    
    MatrixXf translatedCoords = coords.colwise() - cm;

    VectorXf x = translatedCoords.col(0);
    VectorXf y = translatedCoords.col(1);
    VectorXf z = translatedCoords.col(2);
    
    MatrixXf coords_sq = translatedCoords.array().square();
    VectorXf x_sq = coords_sq.col(0);
    VectorXf y_sq = coords_sq.col(1);
    VectorXf z_sq = coords_sq.col(2);
    
    // diagonal
    inertia(0, 0) = masses.dot(y_sq + z_sq);
    inertia(1, 1) = masses.dot(x_sq + z_sq);
    inertia(2, 2) = masses.dot(x_sq + y_sq);
    
    // off-diagonal
    inertia(0, 1) = inertia(1, 0) = -masses.transpose().cwiseProduct(x).cwiseProduct(y).sum();
    inertia(0, 2) = inertia(2, 0) = -masses.transpose().cwiseProduct(x).cwiseProduct(z).sum();
    inertia(1, 2) = inertia(2, 1) = -masses.transpose().cwiseProduct(y).cwiseProduct(z).sum();
    
    return make_unique<Matrix3f>(inertia);
}

unique_ptr<Vector3f> MolecularData::getRotationalConstants() {
    unique_ptr<Matrix3f> I = getMomentOfInertia();
    SelfAdjointEigenSolver<Matrix3f> solver(*I);

    Matrix3f eigen_vectors = solver.eigenvectors();
    Vector3f eigen_values = solver.eigenvalues();
    
    // gives rotational constant in cm^-1
    double coeff = 6.6260755E-34/(8.0 * M_PI * M_PI);
    coeff /= 1.6605402E-27 * 0.529177249E-10 * 0.529177249E-10;
    coeff /= 2.99792458E10;

    return make_unique<Vector3f>(coeff / eigen_values.array());
}

unique_ptr<MatrixXf> MolecularData::getMassWeightedHessian() {
    unique_ptr<MatrixXf> matPtr = make_unique<MatrixXf>(hessian);
    MatrixXf& mat = *matPtr;

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
    
    return matPtr;
}

unique_ptr<VectorXf> MolecularData::getHarmonicFrequencies() {
    SelfAdjointEigenSolver<MatrixXf> solver(hessian);

    MatrixXf eigen_vectors = solver.eigenvectors();
    VectorXf eigen_values = solver.eigenvalues();
    eigen_values = (1E-7 < eigen_values.array().abs()).select(eigen_values, 0.0f);
    
    double scalar = 5140.48;
    return make_unique<VectorXf>(eigen_values.array().sqrt() * scalar);
}

unique_ptr<MatrixXf> MolecularData::getCoreHamiltonian() {
    return make_unique<MatrixXf>(T + V);
}
