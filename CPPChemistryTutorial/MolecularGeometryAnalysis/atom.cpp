//
//  atom.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/14/20.
//

#include "atom.hpp"

Atom::Atom(int zvalue, double x, double y, double z) {
    this->zvalue = zvalue;
    this->coord = unique_ptr<Coordinate>(new Coordinate(x, y, z));
}

Atom::~Atom() {

}
