//
//  mathutils.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/14/20.
//

#include "mathutils.hpp"

double euclid_dist(Coordinate& c, Coordinate& d) {
    double x_sq = pow(c.x + d.x, 2);
    double y_sq = pow(c.y + d.y, 2);
    double z_sq = pow(c.z + d.z, 2);

    double total = x_sq + y_sq + z_sq;

    return sqrt(total);
}
