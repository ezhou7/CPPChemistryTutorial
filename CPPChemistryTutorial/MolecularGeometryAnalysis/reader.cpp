//
//  reader.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/14/20.
//

#include "reader.hpp"

CoordinateDataReader::CoordinateDataReader() {

}

CoordinateDataReader::~CoordinateDataReader() {

}

int CoordinateDataReader::read_array_length(ifstream& instream) {
    string line;
    getline(instream, line);

    return atoi(line.c_str());
}

unique_ptr<vector<unique_ptr<Atom>>> CoordinateDataReader::read(const string& filepath) {
    ifstream instream(filepath);
    
    read_array_length(instream);
    unique_ptr<vector<unique_ptr<Atom>>> atoms = unique_ptr<vector<unique_ptr<Atom>>>(new vector<unique_ptr<Atom>>);
    
    string line;
    while (getline(instream, line)) {
        vector<string> atomic_values;
        boost::split(atomic_values, line, boost::is_any_of(" "));

        int zvalue = atoi(atomic_values[0].c_str());
        double x = atof(atomic_values[1].c_str());
        double y = atof(atomic_values[2].c_str());
        double z = atof(atomic_values[3].c_str());

        unique_ptr<Atom> atom = unique_ptr<Atom>(new Atom(zvalue, x, y, z));
        atoms->push_back(atom);
    }
    
    instream.close();
    
    return atoms;
}
