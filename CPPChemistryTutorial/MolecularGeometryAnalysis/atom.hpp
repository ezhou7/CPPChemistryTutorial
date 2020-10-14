//
//  atom.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/14/20.
//

#ifndef atom_hpp
#define atom_hpp

#include <memory>

#include "coordinate.hpp"

using namespace std;

class Atom {
public:
    int zvalue;
    unique_ptr<Coordinate> coord;
    
    Atom(int zvalue, double x, double y, double z);
    ~Atom();
};

#endif /* atom_hpp */
