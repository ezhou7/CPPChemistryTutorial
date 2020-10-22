//
//  nrereader.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/21/20.
//

#include "nrereader.hpp"

double NREReader::read_file(const string& filepath) {
    if (!std::filesystem::exists(filepath)) {
        string err_msg = "File does not exist: " + filepath;
        throw invalid_argument(err_msg);
    }
    
    ifstream instream(filepath);

    string line;
    getline(instream, line);
    boost::trim(line);

    return atof(line.c_str());
}
