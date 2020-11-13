//
//  hessian.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 11/13/20.
//

#ifndef reader_hessian_hpp
#define reader_hessian_hpp

#include <Eigen/Core>

#include "reader.hpp"

using Eigen::MatrixXf;

class HessianReader : public AbstractReader<MatrixXf> {
protected:
    int readNumAtoms(ifstream& in);
    MatrixXf parseFile(ifstream& in);
};

#endif /* reader_hessian_hpp */
