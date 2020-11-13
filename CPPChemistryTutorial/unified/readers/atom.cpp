//
//  atom.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 11/10/20.
//

#include "atom.hpp"

int AtomReader::readNumAtoms(ifstream& in) {
    string line;
    getline(in, line);

    return atoi(line.c_str());
}

MatrixXf AtomReader::parseFile(ifstream& in) {
    int natoms = readNumAtoms(in);
    MatrixXf m(natoms, 4);
    
    int i = 0;
    string line;
    while (getline(in, line)) {
        vector<string> atomic_values;
        boost::trim(line);
        boost::split(atomic_values, line, boost::is_any_of(" "), boost::token_compress_on);
        
        assert(atomic_values.size() == 4);

        m(i, 0) = atoi(atomic_values[0].c_str());   // z-value (num protons in atom)
        m(i, 1) = atof(atomic_values[1].c_str());   // x-coordinate
        m(i, 2) = atof(atomic_values[2].c_str());   // y-coordinate
        m(i, 3) = atof(atomic_values[3].c_str());   // z-coordinate
        
        i++;
    }

    return m;
}
