//
//  factory.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/17/20.
//

#ifndef factory_hpp
#define factory_hpp

#include <array>
#include <memory>

#include "mathutils.hpp"
#include "molecule.hpp"

class MoleculeFactory {
private:
    double bond_threshold = 4.0;
    void set_bonds(Molecule& molecule);
    void set_bond_angles(Molecule& molecule);
    void set_out_of_plane_angles(Molecule& molecule);
    void set_torsion_angles(Molecule& molecule);

public:
    MoleculeFactory();
    ~MoleculeFactory();
    
    unique_ptr<Molecule> assemble(unique_ptr<vector<unique_ptr<Atom>>> atoms);
};

#endif /* factory_hpp */
