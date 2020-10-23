//
//  erireader.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/22/20.
//

#ifndef erireader_hpp
#define erireader_hpp

#include <boost/algorithm/string.hpp>
#include <Eigen/Core>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

using Eigen::MatrixXf;
using std::getline;
using std::ifstream;
using std::invalid_argument;
using std::make_unique;
using std::string;
using std::unique_ptr;
using std::vector;

class ERIReader {
private:
    unique_ptr<vector<string>> read_lines(ifstream& instream);
    
public:
    unique_ptr<MatrixXf> read_file(const string& filepath);
};

#endif /* erireader_hpp */
