//
//  nre.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/23/20.
//

#ifndef nre_hpp
#define nre_hpp

#include <stdlib.h>

#include <boost/algorithm/string.hpp>
#include <string>

#include "reader.hpp";

using std::getline;
using std::string;

class NREReader : public AbstractReader<double> {
public:
    double parseFile(ifstream& in);
};

#endif /* nre_hpp */
