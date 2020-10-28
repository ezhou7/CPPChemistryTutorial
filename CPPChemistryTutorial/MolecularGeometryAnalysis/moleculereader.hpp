//
//  moleculereader.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/27/20.
//

#ifndef moleculereader_hpp
#define moleculereader_hpp

#include <stdlib.h>

#include <boost/algorithm/string.hpp>

#include <filesystem>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>

#include "molecule.hpp"

using namespace std;

class MoleculeReader {
private:
    int read_array_length(ifstream& instream);

public:
    unique_ptr<Molecule> read_file(const string& filepath);
};

#endif /* moleculereader_hpp */
