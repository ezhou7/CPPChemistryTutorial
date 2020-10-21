//
//  hessianreader.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/20/20.
//

#include "hessianreader.hpp"

int HessianReader::read_num_atoms(ifstream& instream) {
    string line;
    getline(instream, line);

    return atoi(line.c_str());
}

unique_ptr<MatrixXf> HessianReader::read_file(const string& filepath) {
    if (!std::filesystem::exists(filepath)) {
        string err_msg = "File does not exist: " + filepath;
        throw invalid_argument(err_msg);
    }
    
    ifstream instream(filepath);

    int num_atoms = read_num_atoms(instream);
    int size = num_atoms * 3;
    MatrixXf matrix(size, size);

    int i = 0, j = 0;
    string line;
    while (getline(instream, line)) {
        if (j == size) {
            i++;
            j = 0;
        }

        vector<string> values;

        trim(line);
        split(values, line, boost::is_any_of(" "), boost::token_compress_on);

        matrix(i, j) = atof(values[0].c_str());
        matrix(i, j + 1) = atof(values[1].c_str());
        matrix(i, j + 2) = atof(values[2].c_str());
        
        j += 3;
    }
    
    return make_unique<MatrixXf>(matrix);
}
