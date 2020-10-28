//
//  moleculereader.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/27/20.
//

#include "moleculereader.hpp"

int MoleculeReader::read_array_length(ifstream& instream) {
    string line;
    getline(instream, line);

    return atoi(line.c_str());
}

unique_ptr<Molecule> MoleculeReader::read_file(const string& filepath) {
    if (!filesystem::exists(filepath)) {
        string err_msg = "File does not exist: " + filepath;
        throw invalid_argument(err_msg);
    }

    ifstream instream(filepath);
    
    read_array_length(instream);
    auto atoms = make_unique<vector<unique_ptr<Atom>>>();
    
    string line;
    while (getline(instream, line)) {
        vector<string> atomic_values;
        boost::trim(line);
        boost::split(atomic_values, line, boost::is_any_of(" "), boost::token_compress_on);

        int zvalue = atoi(atomic_values[0].c_str());
        double x = atof(atomic_values[1].c_str());
        double y = atof(atomic_values[2].c_str());
        double z = atof(atomic_values[3].c_str());

        atoms->push_back(unique_ptr<Atom>(new Atom(zvalue, x, y, z)));
    }
    
    instream.close();

    return make_unique<Molecule>(move(atoms));
}
