//
//  matrix.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/14/20.
//

#ifndef matrix_hpp
#define matrix_hpp

#include <memory>

using namespace std;

class Matrix {
private:
    int rows;
    int cols;
    unique_ptr<int[]> array;
    
    int index(int i, int j);
    
public:
    Matrix(int r, int c);
    ~Matrix();
    
    int num_rows();
    int num_cols();
    int get(int i, int j);
    void set(int i, int j, int value);
};

#endif /* matrix_hpp */
