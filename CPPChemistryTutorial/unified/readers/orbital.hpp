//
//  orbital.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 11/10/20.
//

#ifndef orbital_hpp
#define orbital_hpp

#include <Eigen/Core>
#include <boost/algorithm/string.hpp>

#include "reader.hpp"

using Eigen::MatrixXf;
using std::make_unique;

class AOReader : public AbstractReader<MatrixXf> {
protected:
    MatrixXf parseFile(ifstream& in);
};

#endif /* orbital_hpp */
