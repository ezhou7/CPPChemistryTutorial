//
//  vectorutils.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/15/20.
//

#include "vectorutils.hpp"

int sum(vector<int>& nums) {
    int total = 0;
    for (int i = 0; i < nums.size(); i++) {
        total += nums[i];
    }
    
    return total;
}

int multiply(vector<int>& nums) {
    if (nums.size() == 0) {
        return 0;
    }
    
    int total = 1;
    for (int i = 0; i < nums.size(); i++) {
        total *= nums[i];
    }
    
    return total;
}

unique_ptr<vector<int>> cum_multiply(vector<int>& nums) {
    if (nums.size() == 0) {
        return NULL;
    }
    
    unique_ptr<vector<int>> v = unique_ptr<vector<int>>(new vector<int>());
    
    int total = 1;
    for (int i = 0; i < nums.size(); i++) {
        total *= nums[i];
        v->push_back(total);
    }
    
    return v;
}

unique_ptr<vector<int>> elem_multiply(vector<int>& nums) {
    return NULL;
}
