//
//  hartreefock.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 11/13/20.
//

#ifndef transformer_hartreefock_hpp
#define transformer_hartreefock_hpp

#include <vector>

#include <Eigen/Core>

#include "../molecule.hpp"

using Eigen::MatrixXf;
using std::vector;

class HartreeFockSnapshot {
private:
    int iteration;
    double scf;
    MatrixXf D;

public:
    HartreeFockSnapshot(int iteration, double scf, MatrixXf D) :
    iteration(iteration), scf(scf), D(D) {}
    
    int getIteration() {
        return iteration;
    }
    
    double getScf() {
        return scf;
    }
    
    MatrixXf& getDensityMatrix() {
        return D;
    }
};

class HartreeFockIterator {
private:
    int iteration;
    double nre;
    double scf;
    MatrixXf TEI;
    MatrixXf H;
    MatrixXf So;
    MatrixXf F;
    MatrixXf D;
    
    void calcFockMatrix();

public:
    HartreeFockIterator(const double nre, const MatrixXf& So, const MatrixXf& H);
    HartreeFockSnapshot iterate();

    int getIteration() {
        return iteration;
    }
    double getScf() {
        return scf;
    }
};

class HartreeFockHistory {
private:
    vector<HartreeFockSnapshot> history;

public:
    size_t size() {
        return history.size();
    }
    
    void add(HartreeFockSnapshot& snapshot) {
        history.push_back(snapshot);
    }

    double getEnergyDiff(int prevIteration, int iteration);
    double getDensityDiff(int prevIteration, int iteration);
    bool isConvergent(int prevIteration, int iteration, double energyThreshold, double densityThreshold);
};

class HartreeFockTransformer {
private:
    int totalIterations;
    HartreeFockHistory history;
    HartreeFockIterator hartreeFockIterator;

    MatrixXf getOrthoMatrix(const MatrixXf& S);
    
public:
    HartreeFockTransformer(MolecularData& data, const int totalIterations = 100);
    double compute();
};

#endif /* transformer_hartreefock_hpp */
