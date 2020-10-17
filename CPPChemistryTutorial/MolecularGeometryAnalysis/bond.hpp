//
//  bond.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/17/20.
//

#ifndef bond_hpp
#define bond_hpp

#include "atom.hpp"
#include "mathutils.hpp"

using namespace std;

class Bond {
private:
    unique_ptr<Atom> a1;
    unique_ptr<Atom> a2;
    
public:
    double length;
    
    Bond(unique_ptr<Atom> atom_1, unique_ptr<Atom> atom_2);
    ~Bond();

    bool is_bond_valid(double threshold);
    unique_ptr<Coordinate> get_unit_vector();
};

#endif /* bond_hpp */
