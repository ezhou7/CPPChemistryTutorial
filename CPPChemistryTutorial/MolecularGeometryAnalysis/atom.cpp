//
//  atom.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/14/20.
//

#include "atom.hpp"

array<double, 21> atomic_masses = {{
    0.0,
    1.007825,
    4.002602,
    6.015122,
    9.012182,
    10.012936,
    12.000000,
    14.003074,
    15.994914,
    18.998403,
    19.992440,
    22.989769,
    23.985041,
    26.981538,
    27.976926,
    30.973761,
    31.972071,
    34.968852,
    35.967545,
    38.963706,
    39.962590
}};

Atom::Atom(int zvalue, double x, double y, double z) {
    this->zvalue = zvalue;
    this->coord = make_unique<Coordinate>(x, y, z);
}

Atom::~Atom() {

}
