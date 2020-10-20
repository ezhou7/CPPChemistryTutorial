//
//  mathutils.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/14/20.
//

#include "mathutils.hpp"

double euclid_dist(Coordinate& c, Coordinate& d) {
    double x_sq = pow(c.x - d.x, 2);
    double y_sq = pow(c.y - d.y, 2);
    double z_sq = pow(c.z - d.z, 2);

    double total = x_sq + y_sq + z_sq;

    return sqrt(total);
}

unique_ptr<Coordinate> unit_vector(Coordinate& c, Coordinate& d) {
    double dist = euclid_dist(c, d);
    if (dist <= 0) {
        return NULL;
    }

    double e_x = (d.x - c.x) / dist;
    double e_y = (d.y - c.y) / dist;
    double e_z = (d.z - c.z) / dist;
    
    return unique_ptr<Coordinate>(new Coordinate(e_x, e_y, e_z));
}

double dot(Coordinate& c, Coordinate& d) {
    return c.x * d.x + c.y * d.y + c.z * d.z;
}

double angle(Coordinate& c, Coordinate& d, Coordinate& e) {
    unique_ptr<Coordinate> dc_unit = unit_vector(d, c);
    unique_ptr<Coordinate> de_unit = unit_vector(d, e);
    
    double dot_prod = dot(*dc_unit, *de_unit);
    return acos(dot_prod);
}

unique_ptr<Coordinate> multiply(double scalar, Coordinate& c) {
    double x = scalar * c.x;
    double y = scalar * c.y;
    double z = scalar * c.z;
    
    return make_unique<Coordinate>(x, y, z);
}

unique_ptr<Coordinate> divide(double scalar, Coordinate& c) {
    return multiply(1 / scalar, c);
}

unique_ptr<Coordinate> cross(Coordinate& u, Coordinate& v) {
    double s_x = u.y * v.z - u.z * v.y;
    double s_y = u.z * v.x - u.x * v.z;
    double s_z = u.x * v.y - u.y * v.x;

    return make_unique<Coordinate>(s_x, s_y, s_z);
}
