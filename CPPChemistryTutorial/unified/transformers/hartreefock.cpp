//
//  hartreefock.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 11/13/20.
//

#include "hartreefock.hpp"

int calcIndex(int i, int j) {
    int idx = 0;
    if (i >= j) {
        idx = (int) (i * (i + 1)) / 2 + j;
    } else if (i < j) {
        idx = (int) (j * (j + 1)) / 2 + i;
    }
    
    return idx;
}

/* ---- Hartree-Fock Iterator ---- */

HartreeFockIterator::HartreeFockIterator(const double nre, const MatrixXf& So, const MatrixXf& H) :
So(So), H(H), D(So.rows(), So.cols()) {
    this->nre = nre;
}

HartreeFockSnapshot HartreeFockIterator::iterate() {
    if (iteration == 0) {
        F = So.transpose() * H * So;
    } else {
        calcFockMatrix();
    }

    // calculate ao basis coefficients
    SelfAdjointEigenSolver<MatrixXf> solver(F);
    MatrixXf evecs = solver.eigenvectors();
    MatrixXf aoBasis = So * evecs;
    
    // calculate density matrix
    for (int i = 0; i < D.rows(); i++) {
        for (int j = 0; j < D.cols(); j++) {
            D(i, j) = aoBasis.col(i).dot(aoBasis.col(j));
        }
    }
    
    // electronic Energy matrix
    MatrixXf E = D.cwiseProduct(H + F);
    scf = E.sum() + nre;
    
    HartreeFockSnapshot snapshot(iteration, scf, D);
    iteration++;
    
    return snapshot;
}

void HartreeFockIterator::calcFockMatrix() {
    F = H;
    for (int i = 0; i < F.rows(); i++) {
        for (int j = 0; j < F.cols(); j++) {
            for (int k = 0; k < F.rows(); k++) {
                for (int l = 0; l < F.cols(); l++) {
                    int ij = calcIndex(i, j);
                    int kl = calcIndex(k, l);
                    int ik = calcIndex(i, k);
                    int jl = calcIndex(j, l);
                    F(i, j) += D(k, l) * (2 * TEI(ij, kl) - TEI(ik, jl));
                }
            }
        }
    }
}

/* ---- Hartree-Fock History ---- */

double HartreeFockHistory::getEnergyDiff(int prevIteration, int iteration) {
    HartreeFockSnapshot prevSnapshot = history[prevIteration];
    HartreeFockSnapshot snapshot = history[iteration];
    
    return snapshot.getScf() - prevSnapshot.getScf();
}

double HartreeFockHistory::getDensityDiff(int prevIteration, int iteration) {
    HartreeFockSnapshot prevSnapshot = history[prevIteration];
    HartreeFockSnapshot snapshot = history[iteration];
    MatrixXf& pD = prevSnapshot.getDensityMatrix();
    MatrixXf& D = snapshot.getDensityMatrix();
    MatrixXf diff = D - pD;
    
    double rms = pow(diff.pow(2).sum(), 0.5);
    return rms;
}

bool HartreeFockHistory::isConvergent(int prevIteration, int iteration, double energyThreshold, double densityThreshold) {
    double energyDiff = getEnergyDiff(prevIteration, iteration);
    double densityDiff = getDensityDiff(prevIteration, iteration);
    
    return energyDiff < energyThreshold && densityDiff < densityThreshold;
}

/* ---- Hartree-Fock Transformer ---- */

HartreeFockTransformer::HartreeFockTransformer(MolecularData& data, const int totalIterations) :
hartreeFockIterator(data.nre, getOrthoMatrix(data.S), data.T + data.V) {
    this->totalIterations = totalIterations;
}

MatrixXf HartreeFockTransformer::getOrthoMatrix(const MatrixXf& S) {
    SelfAdjointEigenSolver<MatrixXf> solver(S);
    MatrixXf evecs = solver.eigenvectors();
    MatrixXf evals = solver.eigenvalues();

    MatrixXf evalsDiagonal = evals.pow(-0.5).asDiagonal();
    MatrixXf So = evecs * evalsDiagonal * evecs.transpose();
    
    return So;
}

double HartreeFockTransformer::compute() {
    while (hartreeFockIterator.getIteration() < totalIterations) {
        auto snapshot = hartreeFockIterator.iterate();
        history.add(snapshot);
    }
    
    return hartreeFockIterator.getScf();
}
