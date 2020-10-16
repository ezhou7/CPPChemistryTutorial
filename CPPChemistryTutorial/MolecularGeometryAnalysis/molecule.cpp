//
//  molecule.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/14/20.
//

#include "molecule.hpp"

Molecule::Molecule() {
    atoms = unique_ptr<vector<unique_ptr<Atom>>>(new vector<unique_ptr<Atom>>);
}

Molecule::~Molecule() {

}

unique_ptr<Matrix<int, int>> Molecule::get_bond_lengths() {
    int num_atoms = (int) atoms->size();
    unique_ptr<Matrix<int, int>> matrix = unique_ptr<Matrix<int, int>>(new Matrix<int, int>(num_atoms, num_atoms));

    for (int i = 0; i < num_atoms - 1; i++) {
        for (int j = i + 1; j < num_atoms; j++) {
            Coordinate c = *(*atoms)[i]->coord;
            Coordinate d = *(*atoms)[j]->coord;
            
            int dist = euclid_dist(c, d);
            matrix->set(dist, i, j);
        }
    }
    
    return matrix;
}

void Molecule::get_bond_angles() {
    int num_atoms = (int) atoms->size();
    // TODO: calculate angles between all bonds
    unique_ptr<Matrix<int, int, int>> matrix = unique_ptr<Matrix<int, int, int>>(new Matrix<int, int, int>(num_atoms, num_atoms, num_atoms));
}
