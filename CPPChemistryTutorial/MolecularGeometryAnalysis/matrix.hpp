//
//  matrix.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/14/20.
//

#ifndef matrix_hpp
#define matrix_hpp

#include <memory>
#include <vector>

#include "vectorutils.hpp"

#define mMatrix(...) Matrix(__VA_ARGS__, 0)

using namespace std;

class Matrix {
private:
    unique_ptr<vector<int>> dims;
    unique_ptr<vector<int>> index_coeffs;
    unique_ptr<int[]> array;
    
    template <typename ...Ints>
    int index(Ints... indices);
    
public:
    template <typename ...Ints>
    Matrix(Ints... dims);

    ~Matrix();

    template <typename ...Ints>
    int get(Ints... indices);
    
    template <typename ...Ints>
    void set(int value, Ints... indices);
};

#endif /* matrix_hpp */
