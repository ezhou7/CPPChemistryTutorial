//
//  hessianreader.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/20/20.
//

#ifndef hessianreader_hpp
#define hessianreader_hpp

#include <boost/algorithm/string.hpp>
#include <Eigen/Core>
#include <filesystem>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include <vector>

using boost::split;
using boost::trim;
using Eigen::MatrixXf;
using std::getline;
using std::ifstream;
using std::invalid_argument;
using std::make_unique;
using std::string;
using std::unique_ptr;
using std::vector;

class HessianReader {
private:
    int read_num_atoms(ifstream& instream);
    
public:
    unique_ptr<MatrixXf> read_file(const string& filepath);
};

#endif /* hessianreader_hpp */
