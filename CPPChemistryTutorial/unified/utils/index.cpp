//
//  index.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 11/27/20.
//

#include "index.hpp"

int calcIndex(int i, int j) {
    int idx = 0;
    if (i >= j) {
        idx = (int) (i * (i + 1)) / 2 + j;
    } else if (i < j) {
        idx = (int) (j * (j + 1)) / 2 + i;
    }
    
    return idx;
}
