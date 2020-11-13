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
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

using std::ifstream;
using std::invalid_argument;
using std::make_unique;
using std::string;
using std::unique_ptr;
using std::vector;

template<class T>
class AbstractReader {
protected:
    vector<string> split(string& line);
    virtual T parseFile(ifstream& in) = 0;
    
public:
    unique_ptr<vector<string>> readLines(ifstream& in);
    T readFile(const string& filepath);
};

template<class T>
unique_ptr<vector<string>> AbstractReader<T>::readLines(ifstream& in) {
    auto lines = make_unique<vector<string>>();
    
    string line;
    while (getline(in, line)) {
        lines->push_back(line);
    }
    
    return lines;
}

template<class T>
vector<string> AbstractReader<T>::split(string& line) {
    vector<string> values;
    boost::trim(line);
    boost::split(values, line, boost::is_any_of(" "), boost::token_compress_on);
    
    return values;
}

template<class T>
T AbstractReader<T>::readFile(const string& filepath) {
    if (!std::filesystem::exists(filepath)) {
        string errMsg = "File does not exist: " + filepath;
        throw invalid_argument(errMsg);
    }
    
    ifstream in(filepath);
    T obj = parseFile(in);
    in.close();
    
    return obj;
}

#endif /* reader_hpp */
