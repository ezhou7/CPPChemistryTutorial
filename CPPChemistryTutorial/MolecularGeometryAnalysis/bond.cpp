//
//  bond.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/17/20.
//

#include "bond.hpp"

Bond::Bond(int a1, int a2, double length, unique_ptr<Coordinate> unit) {
    this->a1 = a1;
    this->a2 = a2;
    this->length = length;
    this->unit = move(unit);
}

Bond::~Bond() {

}

bool Bond::is_bond_valid(double threshold) {
    return length < threshold;
}
