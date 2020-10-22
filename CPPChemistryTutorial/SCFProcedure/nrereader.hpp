//
//  nrereader.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/21/20.
//

#ifndef nrereader_hpp
#define nrereader_hpp

#include <boost/algorithm/string.hpp>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <stdlib.h>

using std::getline;
using std::ifstream;
using std::invalid_argument;
using std::string;

class NREReader {
public:
    double read_file(const string& filepath);
};

#endif /* nrereader_hpp */
