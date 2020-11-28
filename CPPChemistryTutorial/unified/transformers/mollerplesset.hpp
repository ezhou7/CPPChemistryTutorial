//
//  mollerplesset.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 11/27/20.
//

#ifndef transformer_mollerplesset_hpp
#define transformer_mollerplesset_hpp

#include <Eigen/Core>

#include "../molecule.hpp"
#include "../utils/index.hpp"

using Eigen::MatrixXf;

class MollerPlessetTransformer {
private:
    int natoms;             // number of atoms
    MatrixXf AOC;           // ao-basis coefficients
    MatrixXf TEI;           // two-electron integrals

public:
    MollerPlessetTransformer(MolecularData& data);
    
    MatrixXf brute();
    MatrixXf optimized();
};

#endif /* transformer_mollerplesset_hpp */
