//
//  nre.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/23/20.
//

#include "nre.hpp"

double NREReader::parseFile(ifstream& in) {
    string line;
    getline(in, line);
    boost::trim(line);

    return atof(line.c_str());
}

