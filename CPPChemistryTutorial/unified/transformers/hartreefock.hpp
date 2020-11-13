//
//  hartreefock.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 11/13/20.
//

#ifndef transformer_hartreefock_hpp
#define transformer_hartreefock_hpp

#include <Eigen/Core>

#include "../molecule.hpp"

using Eigen::MatrixXf;

class HartreeFockTransformer {
private:
    MatrixXf getFockMatrix(MolecularData& data);
    MatrixXf getDensityMatrix(MolecularData& data);
    MatrixXf getSCFEnergy(MolecularData& data);
    
public:
    double compute(MolecularData& data);
};

#endif /* transformer_hartreefock_hpp */
