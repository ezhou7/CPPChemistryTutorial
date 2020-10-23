//
//  reader.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/23/20.
//

#include "reader.hpp"

template<class T>
T AbstractReader<T>::readFile(const string& filepath) {
    if (!std::filesystem::exists(filepath)) {
        string err_msg = "File does not exist: " + filepath;
        throw invalid_argument(err_msg);
    }
    
    ifstream in(filepath);
    T obj = parseFile(in);
    in.close();
    
    return obj;
}
