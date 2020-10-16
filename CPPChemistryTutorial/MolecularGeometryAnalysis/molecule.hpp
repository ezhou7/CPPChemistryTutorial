//
//  molecule.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/14/20.
//

#ifndef molecule_hpp
#define molecule_hpp

#include "atom.hpp"
#include "mathutils.hpp"
#include "matrix.hpp"

class Molecule {
private:
    unique_ptr<vector<unique_ptr<Atom>>> atoms;

public:
    Molecule();
    ~Molecule();
    
    unique_ptr<Matrix<int, int>> get_bond_lengths();
    void get_bond_angles();
    void get_out_of_plane_angles();
    void get_torsion_angles();
    void get_center_of_mass();
    void get_moment_of_inertia();
    void get_rotational_constants();
};

#endif /* molecule_hpp */
