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

unique_ptr<Matrix> Molecule::get_bond_lengths() {
    int num_atoms = (int) atoms->size();
    unique_ptr<Matrix> matrix = unique_ptr<Matrix>(new Matrix(num_atoms, num_atoms));

    for (int i = 0; i < num_atoms - 1; i++) {
        for (int j = i + 1; j < num_atoms; j++) {
            Coordinate c = *(*atoms)[i]->coord;
            Coordinate d = *(*atoms)[i]->coord;
            
            int dist = euclid_dist(c, d);
            matrix->set(i, j, dist);
        }
    }
    
    return matrix;
}
