//
//  reader.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/23/20.
//

#ifndef reader_hpp
#define reader_hpp

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

using std::ifstream;
using std::invalid_argument;
using std::string;

template<class T>
class AbstractReader {
protected:
    virtual T parseFile(ifstream& in) = 0;
    
public:
    T readFile(const string& filepath);
};

#endif /* reader_hpp */
