//
//  mathutils.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/14/20.
//

#ifndef mathutils_hpp
#define mathutils_hpp

#include <cmath>
#include <vector>

#include "coordinate.hpp"

using namespace std;

double euclid_dist(Coordinate& c, Coordinate& d);
double angle(Coordinate& c, Coordinate& d, Coordinate& e);
double dot(Coordinate& c, Coordinate& d);

unique_ptr<Coordinate> unit_vector(Coordinate& c, Coordinate& d);
unique_ptr<Coordinate> multiply(int scalar, Coordinate& c);
unique_ptr<Coordinate> divide(int scalar, Coordinate& c);
unique_ptr<Coordinate> cross(Coordinate& c, Coordinate& d, Coordinate& e);

#endif /* mathutils_hpp */
