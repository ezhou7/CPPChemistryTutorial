//
//  hartreefock.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/22/20.
//

#ifndef hartreefock_hpp
#define hartreefock_hpp

#include <Eigen/Core>
#include <unsupported/Eigen/MatrixFunctions>
#include <memory>

using Eigen::MatrixXf;
using Eigen::SelfAdjointEigenSolver;
using std::make_unique;
using std::unique_ptr;

class HartreeFock {
public:
    double nre;
    
    MatrixXf overlap;
    MatrixXf kei;
    MatrixXf nai;
    MatrixXf eri;
    
    unique_ptr<MatrixXf> get_core_hamiltonian();
    unique_ptr<MatrixXf> get_ortho_overlap();
    unique_ptr<MatrixXf> get_fock_matrix();
    unique_ptr<MatrixXf> get_ao_basis_coefficients();
    unique_ptr<MatrixXf> get_initial_guess_density();
    double get_initial_scf_energy();
    unique_ptr<MatrixXf> get_new_fock_matrix();
    unique_ptr<MatrixXf> get_new_density_matrix();
    double get_new_scf_energy();
};

#endif /* hartreefock_hpp */
