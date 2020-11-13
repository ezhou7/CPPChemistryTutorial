//
//  orbital.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 11/10/20.
//

#include "orbital.hpp"

MatrixXf AOReader::parseFile(ifstream& in) {
    unique_ptr<vector<string>> lines = readLines(in);

    int max_idx = 0;
    vector<int> is;
    vector<int> js;
    vector<double> overlaps;

    for (string line : *lines) {
        vector<string> values;
        boost::trim(line);
        boost::split(values, line, boost::is_any_of(" "), boost::token_compress_on);

        assert(values.size() == 3);

        int i = atoi(values[0].c_str());
        int j = atoi(values[1].c_str());
        double overlap = atof(values[2].c_str());
        
        is.push_back(i - 1);
        js.push_back(j - 1);
        overlaps.push_back(overlap);
        
        if (i > max_idx) {
            max_idx = i;
        }
        if (j > max_idx) {
            max_idx = j;
        }
    }
    
    MatrixXf mat(max_idx, max_idx);
    for (int k = 0; k < is.size(); k++) {
        mat(is[k], js[k]) = mat(js[k], is[k]) = overlaps[k];
    }
    
    return mat;
}
