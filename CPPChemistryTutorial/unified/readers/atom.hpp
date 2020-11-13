//
//  atom.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 11/10/20.
//

#ifndef atom_hpp
#define atom_hpp

#include <assert.h>

#include <vector>

#include <Eigen/Core>
#include <boost/algorithm/string.hpp>

#include "reader.hpp"

using Eigen::MatrixXf;
using std::vector;

class AtomReader : public AbstractReader<MatrixXf> {
protected:
    int readNumAtoms(ifstream& in);
    MatrixXf parseFile(ifstream& in);
};

#endif /* atom_hpp */
