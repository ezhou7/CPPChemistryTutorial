//
//  aoreader.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/22/20.
//

#ifndef aoreader_hpp
#define aoreader_hpp

#include <assert.h>
#include <stdlib.h>

#include <boost/algorithm/string.hpp>
#include <Eigen/Core>
#include <fstream>
#include <filesystem>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

using Eigen::MatrixXf;
using Eigen::VectorXf;
using std::ifstream;
using std::invalid_argument;
using std::make_unique;
using std::string;
using std::unique_ptr;
using std::vector;

class AOReader {
private:
    unique_ptr<vector<string>> read_lines(ifstream& instream);
    
public:
    unique_ptr<MatrixXf> read_file(const string& filepath);
};

#endif /* aoreader_hpp */
