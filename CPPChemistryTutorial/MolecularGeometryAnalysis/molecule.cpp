//
//  molecule.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/14/20.
//

#include "molecule.hpp"

Molecule::Molecule(unique_ptr<vector<unique_ptr<Atom>>> atoms) {
    this->atoms = move(atoms);
}

Molecule::~Molecule() {

}

unique_ptr<Matrix<int, int>> Molecule::get_bond_lengths() {
    int num_atoms = (int) atoms->size();
    auto matrix = make_unique<Matrix<int, int>>(num_atoms, num_atoms);

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
    auto matrix = make_unique<Matrix<int, int, int>>(num_atoms, num_atoms, num_atoms);
    
    for (int i = 0; i < num_atoms - 1; i++) {
        for (int j = i + 1; j < num_atoms; j++) {
            for (int k = j + 1; k < num_atoms; k++) {
                Coordinate c = *(*atoms)[i]->coord;
                Coordinate d = *(*atoms)[j]->coord;
                Coordinate e = *(*atoms)[k]->coord;
                
                int cd_dist = euclid_dist(c, d);
                int de_dist = euclid_dist(d, e);
                
                if (cd_dist < 4.0 && de_dist < 4.0) {
                    double bond_angle = angle(c, d, e);
                    matrix->set(bond_angle, i, j, k);
                }
            }
        }
    }
}
