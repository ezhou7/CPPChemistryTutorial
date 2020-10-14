//
//  reader.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/14/20.
//

#ifndef reader_hpp
#define reader_hpp

#include <stdlib.h>

#include <boost/algorithm/string.hpp>

#include <fstream>
#include <string>
#include <vector>

#include "atom.hpp"

using namespace std;

class CoordinateDataReader {
private:
    int read_array_length(ifstream& instream);
    
public:
    CoordinateDataReader();
    ~CoordinateDataReader();
    
    unique_ptr<vector<unique_ptr<Atom>>> read(const string& filepath);
};

#endif /* reader_hpp */
