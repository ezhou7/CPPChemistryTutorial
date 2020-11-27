//
//  eri.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 11/10/20.
//

#ifndef eri_hpp
#define eri_hpp

#include <Eigen/Core>

#include "../utils/index.hpp"
#include "reader.hpp"

using Eigen::MatrixXf;

class ERIReader : public AbstractReader<MatrixXf> {
protected:
    MatrixXf parseFile(ifstream& in);
};

#endif /* eri_hpp */
