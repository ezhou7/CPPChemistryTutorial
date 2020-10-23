//
//  hartreefock.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/22/20.
//

#ifndef hartreefock_hpp
#define hartreefock_hpp

#include <Eigen/Core>
#include <memory>

using Eigen::MatrixXf;
using std::make_unique;
using std::unique_ptr;

class HartreeFock {
public:
    MatrixXf overlap;
    MatrixXf kei;
    MatrixXf nai;
    
    unique_ptr<MatrixXf> get_core_hamiltonian();
};

#endif /* hartreefock_hpp */
