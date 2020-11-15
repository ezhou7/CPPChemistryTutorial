//
//  hartreefock.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/22/20.
//

#include "hartreefock.hpp"
#include <iostream>

int calc_index_1(int i, int j) {
    int idx = 0;
    if (i >= j) {
        idx = (int) (i * (i + 1)) / 2 + j;
    } else if (i < j) {
        idx = (int) (j * (j + 1)) / 2 + i;
    }
    
    return idx;
}

unique_ptr<MatrixXf> HartreeFock::get_core_hamiltonian() {
    return make_unique<MatrixXf>(kei + nai);
}

unique_ptr<MatrixXf> HartreeFock::get_ortho_overlap() {
    SelfAdjointEigenSolver<MatrixXf> solver(overlap);
    MatrixXf eigen_vectors = solver.eigenvectors();
    MatrixXf eigen_values = solver.eigenvalues();
    
    MatrixXf eigen_values_diagonal = ((MatrixXf) eigen_values.array().pow(-0.5)).asDiagonal();
    MatrixXf ortho_overlap = eigen_vectors * eigen_values_diagonal * eigen_vectors.transpose();
    
    return make_unique<MatrixXf>(ortho_overlap);
}

unique_ptr<MatrixXf> HartreeFock::get_fock_matrix() {
    unique_ptr<MatrixXf> hptr = get_core_hamiltonian();
    MatrixXf& h = *hptr;

    unique_ptr<MatrixXf> s_ptr = get_ortho_overlap();
    MatrixXf& s = *s_ptr;
    MatrixXf st = s.transpose();
    MatrixXf fock = st * h * s;
    
    return make_unique<MatrixXf>(fock);
}

unique_ptr<MatrixXf> HartreeFock::get_ao_basis_coefficients() {
    unique_ptr<MatrixXf> s_ptr = get_ortho_overlap();
    MatrixXf& s = *s_ptr;
    unique_ptr<MatrixXf> fock_ptr = get_fock_matrix();
    MatrixXf& fock = *fock_ptr;
    SelfAdjointEigenSolver<MatrixXf> solver(fock);
    
    MatrixXf eigen_vectors = solver.eigenvectors();
//    std::cout << "Eigen values" << std::endl;
//    std::cout << solver.eigenvalues() << std::endl << std::endl;
//    std::cout << "Eigen vectors" << std::endl;
//    std::cout << eigen_vectors << std::endl << std::endl;
//    std::cout << s << std::endl << std::endl;
    MatrixXf ao_basis = s * eigen_vectors;
    
    return make_unique<MatrixXf>(ao_basis);
}

unique_ptr<MatrixXf> HartreeFock::get_initial_guess_density() {
    unique_ptr<MatrixXf> hptr = get_core_hamiltonian();
    MatrixXf& h = *hptr;

    unique_ptr<MatrixXf> s_ptr = get_ortho_overlap();
    MatrixXf& s = *s_ptr;
    MatrixXf st = s.transpose();
    MatrixXf fock = st * h * s;
    
    SelfAdjointEigenSolver<MatrixXf> solver(fock);
    
    MatrixXf eigen_vectors = solver.eigenvectors();
    MatrixXf ao_basis = s * eigen_vectors;
    
    MatrixXf density(ao_basis.cols(), ao_basis.cols());
    for (int i = 0; i < density.rows(); i++) {
        for (int j = 0; j < density.cols(); j++) {
            density(i, j) = ao_basis.col(i).dot(ao_basis.col(j));
        }
    }

    return make_unique<MatrixXf>(density);
}

double HartreeFock::get_initial_scf_energy() {
    unique_ptr<MatrixXf> fock_ptr = get_fock_matrix();
    unique_ptr<MatrixXf> hamilton_ptr = get_core_hamiltonian();
    unique_ptr<MatrixXf> density_ptr = get_initial_guess_density();
    
    MatrixXf& fock = *fock_ptr;
    MatrixXf& hamilton = *hamilton_ptr;
    MatrixXf& density = *density_ptr;
    
    MatrixXf electronic_matrix = density.cwiseProduct(hamilton + fock);
    double scf = electronic_matrix.sum();
    
    return scf + nre;
}

unique_ptr<MatrixXf> HartreeFock::get_new_fock_matrix() {
    unique_ptr<MatrixXf> chptr = get_core_hamiltonian();
    MatrixXf& ch = *chptr;
    unique_ptr<MatrixXf> density_ptr = get_initial_guess_density();
    MatrixXf& density = *density_ptr;
    
    MatrixXf nf = ch;
    for (int i = 0; i < nf.rows(); i++) {
        for (int j = 0; j < nf.cols(); j++) {
            for (int k = 0; k < nf.rows(); k++) {
                for (int l = 0; l < nf.cols(); l++) {
                    int ij = calc_index_1(i, j);
                    int kl = calc_index_1(k, l);
                    int ik = calc_index_1(i, k);
                    int jl = calc_index_1(j, l);
                    nf(i, j) += density(k, l) * (2 * eri(ij, kl) - eri(ik, jl));
                }
            }
        }
    }
    
    return make_unique<MatrixXf>(nf);
}

unique_ptr<MatrixXf> HartreeFock::get_new_density_matrix() {
    unique_ptr<MatrixXf> fptr = get_new_fock_matrix();
    MatrixXf& f = *fptr;

    unique_ptr<MatrixXf> s_ptr = get_ortho_overlap();
    MatrixXf& s = *s_ptr;
    MatrixXf st = s.transpose();
    MatrixXf fock = st * f * s;
    
    SelfAdjointEigenSolver<MatrixXf> solver(fock);
    
    MatrixXf eigen_vectors = solver.eigenvectors();
    MatrixXf ao_basis = s * eigen_vectors;
    
    MatrixXf density(ao_basis.cols(), ao_basis.cols());
    for (int i = 0; i < density.rows(); i++) {
        for (int j = 0; j < density.cols(); j++) {
            density(i, j) = ao_basis.col(i).dot(ao_basis.col(j));
        }
    }

    return make_unique<MatrixXf>(density);
}

double HartreeFock::get_new_scf_energy() {
    unique_ptr<MatrixXf> fock_ptr = get_new_fock_matrix();
    unique_ptr<MatrixXf> hamilton_ptr = get_core_hamiltonian();
    unique_ptr<MatrixXf> density_ptr = get_new_density_matrix();
    
    MatrixXf& fock = *fock_ptr;
    MatrixXf& hamilton = *hamilton_ptr;
    MatrixXf& density = *density_ptr;
    
    MatrixXf electronic_matrix = density.cwiseProduct(hamilton + fock);
    double scf = electronic_matrix.sum();
    
    return scf + nre;
}

bool HartreeFock::is_convergent(double energy_threshold, double density_threshold) {
    double energy_diff = get_new_scf_energy() - get_initial_scf_energy();

    unique_ptr<MatrixXf> init_density_ptr = get_initial_guess_density();
    unique_ptr<MatrixXf> density_ptr = get_new_density_matrix();
    MatrixXf& init_density = *init_density_ptr;
    MatrixXf& density = *density_ptr;
    MatrixXf density_diff = density - init_density;
    double rms = pow(density_diff.pow(2).sum(), 0.5);
    
    return energy_diff < energy_threshold && rms < density_threshold;
}
