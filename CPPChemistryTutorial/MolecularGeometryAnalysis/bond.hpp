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
    int a1;
    int a2;
    
public:
    double length;
    unique_ptr<Coordinate> unit;
    
    Bond(int a1, int a2, double length, unique_ptr<Coordinate> unit);
    ~Bond();

    bool is_bond_valid(double threshold);
    unique_ptr<Coordinate> get_unit_vector();
};

#endif /* bond_hpp */
