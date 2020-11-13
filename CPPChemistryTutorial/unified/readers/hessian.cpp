//
//  hessian.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 11/13/20.
//

#include "hessian.hpp"

int HessianReader::readNumAtoms(ifstream& in) {
    string line;
    getline(in, line);

    return atoi(line.c_str());
}

MatrixXf HessianReader::parseFile(ifstream& in) {
    int num_atoms = readNumAtoms(in);
    int size = num_atoms * 3;
    MatrixXf matrix(size, size);

    int i = 0, j = 0;
    string line;
    while (getline(in, line)) {
        if (j == size) {
            i++;
            j = 0;
        }
        
        vector<string> values = split(line);

        matrix(i, j) = atof(values[0].c_str());
        matrix(i, j + 1) = atof(values[1].c_str());
        matrix(i, j + 2) = atof(values[2].c_str());
        
        j += 3;
    }
    
    return matrix;
}
