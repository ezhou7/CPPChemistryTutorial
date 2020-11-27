//
//  eri.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 11/10/20.
//

#include "eri.hpp"

MatrixXf ERIReader::parseFile(ifstream& in) {
    unique_ptr<vector<string>> lines = readLines(in);

    int max_idx = 0;
    vector<int> is;
    vector<int> js;
    vector<int> ks;
    vector<int> ls;
    vector<double> eris;

    for (string line : *lines) {
        vector<string> values = split(line);
        
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
    
    int size = max_idx * max_idx;
    MatrixXf matrix(size, size);

    for (int a = 0; a < is.size(); a++) {
        int c = calcIndex(is[a], js[a]);
        int r = calcIndex(ks[a], ls[a]);
        matrix(c, r) = matrix(r, c) = eris[a];
    }

    return matrix;
}
