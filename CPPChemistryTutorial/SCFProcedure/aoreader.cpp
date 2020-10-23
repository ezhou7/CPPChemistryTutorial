//
//  aoreader.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/22/20.
//

#include "aoreader.hpp"

unique_ptr<vector<string>> AOReader::read_lines(ifstream& instream) {
    auto lines = make_unique<vector<string>>();
    
    string line;
    while (getline(instream, line)) {
        lines->push_back(line);
    }
    
    return lines;
}

unique_ptr<MatrixXf> AOReader::read_file(const string& filepath) {
    if (!std::filesystem::exists(filepath)) {
        string err_msg = "File does not exist: " + filepath;
        throw invalid_argument(err_msg);
    }
    
    ifstream instream(filepath);
    unique_ptr<vector<string>> lines = read_lines(instream);

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
    
    instream.close();
    
    MatrixXf mat(max_idx, max_idx);
    for (int k = 0; k < is.size(); k++) {
        mat(is[k], js[k]) = overlaps[k];
    }
    
    return make_unique<MatrixXf>(mat);
}
