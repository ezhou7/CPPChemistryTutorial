//
//  hartreefock.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/22/20.
//

#include "hartreefock.hpp"

unique_ptr<MatrixXf> HartreeFock::get_core_hamiltonian() {
    return make_unique<MatrixXf>(kei + nai);
}
