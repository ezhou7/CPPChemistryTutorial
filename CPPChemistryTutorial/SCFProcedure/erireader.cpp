//
//  erireader.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/22/20.
//

#include "erireader.hpp"

int calc_index(int i, int j) {
    int idx = 0;
    if (i >= j) {
        idx = (int) (i * (i + 1)) / 2 + j;
    } else if (i < j) {
        idx = (int) (j * (j + 1)) / 2 + i;
    }
    
    return idx;
}

unique_ptr<vector<string>> ERIReader::read_lines(ifstream& instream) {
    auto lines = make_unique<vector<string>>();
    
    string line;
    while (getline(instream, line)) {
        lines->push_back(line);
    }
    
    return lines;
}

unique_ptr<MatrixXf> ERIReader::read_file(const string& filepath) {
    if (!std::filesystem::exists(filepath)) {
        string err_msg = "File does not exist: " + filepath;
        throw invalid_argument(err_msg);
    }
    
    ifstream instream(filepath);
    unique_ptr<vector<string>> lines = read_lines(instream);

    int max_idx = 0;
    vector<int> is;
    vector<int> js;
    vector<int> ks;
    vector<int> ls;
    vector<double> eris;

    for (string line : *lines) {
        vector<string> values;
        boost::trim(line);
        boost::split(values, line, boost::is_any_of(" "), boost::token_compress_on);
        
        assert(values.size() == 5);
        
        int i = atoi(values[0].c_str());
        int j = atoi(values[1].c_str());
        int k = atoi(values[2].c_str());
        int l = atoi(values[3].c_str());
        double eri = atof(values[4].c_str());
        
        is.push_back(i - 1);
        js.push_back(j - 1);
        ks.push_back(k - 1);
        ls.push_back(l - 1);
        eris.push_back(eri);
        
        if (i > max_idx) {
            max_idx = i;
        }
        
        if (j > max_idx) {
            max_idx = j;
        }
        
        if (k > max_idx) {
            max_idx = k;
        }
        
        if (l > max_idx) {
            max_idx = l;
        }
    }
    
    instream.close();
    
    int size = max_idx * max_idx;
    MatrixXf matrix(size, size);

    for (int a = 0; a < is.size(); a++) {
        int c = calc_index(is[a], js[a]);
        int r = calc_index(ks[a], ls[a]);
        matrix(c, r) = matrix(r, c) = eris[a];
    }

    return make_unique<MatrixXf>(matrix);
}
