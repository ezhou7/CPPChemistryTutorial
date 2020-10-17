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

unique_ptr<Coordinate> unit_vector(Coordinate& c, Coordinate& d) {
    double dist = euclid_dist(c, d);
    if (dist <= 0) {
        return NULL;
    }

    double e_x = -(c.x - d.x) / dist;
    double e_y = -(c.y - d.y) / dist;
    double e_z = -(c.z - d.z) / dist;
    
    return unique_ptr<Coordinate>(new Coordinate(e_x, e_y, e_z));
}

double dot(Coordinate& c, Coordinate& d) {
    return c.x * d.x + c.y * d.y + c.z * d.z;
}

double angle(Coordinate& c, Coordinate& d, Coordinate& e) {
    unique_ptr<Coordinate> cd_unit = unit_vector(c, d);
    unique_ptr<Coordinate> de_unit = unit_vector(d, e);
    
    double dot_prod = dot(*cd_unit, *de_unit);
    return acos(dot_prod);
}
