//
//  bond.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/17/20.
//

#include "bond.hpp"

Bond::Bond(unique_ptr<Atom> a1, unique_ptr<Atom> a2) {
    length = euclid_dist(*a1->coord, *a2->coord);
    this->a1 = move(a1);
    this->a2 = move(a2);
}

Bond::~Bond() {

}

bool Bond::is_bond_valid(double threshold) {
    return length < threshold;
}

unique_ptr<Coordinate> Bond::get_unit_vector() {
    return unit_vector(*a1->coord, *a2->coord);
}
