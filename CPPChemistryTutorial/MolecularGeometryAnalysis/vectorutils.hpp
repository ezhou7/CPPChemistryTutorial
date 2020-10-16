//
//  vectorutils.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/15/20.
//

#ifndef vectorutils_hpp
#define vectorutils_hpp

#include <vector>

using namespace std;

int multiply(vector<int>& nums);
unique_ptr<vector<int>> cum_multiply(vector<int>& nums);

#endif /* vectorutils_hpp */
