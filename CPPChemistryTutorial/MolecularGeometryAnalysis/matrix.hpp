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

template <typename ...Ints>
class Matrix {
private:
    unique_ptr<vector<int>> dims;
    unique_ptr<vector<int>> index_coeffs;
    unique_ptr<int[]> array;

    int index(Ints... indices);
    
public:
    Matrix(Ints... dims);
    ~Matrix();

    int get(Ints... indices);
    void set(int value, Ints... indices);
};

template <typename ...Ints>
Matrix<Ints...>::Matrix(Ints... ds) {
    dims = unique_ptr<vector<int>>(new vector<int>{ds...});
    index_coeffs = cum_multiply(*dims);

    size_t size = (size_t) (*index_coeffs)[index_coeffs->size() - 1];
    array = unique_ptr<int[]>(new int[size]());
}

template <typename ...Ints>
Matrix<Ints...>::~Matrix() {

}

template <typename ...Ints>
int Matrix<Ints...>::index(Ints... indices) {
    vector<int> idcs{indices...};
    unique_ptr<vector<int>> coeffs = cum_multiply(*dims);

    int converted_idx = idcs[0];
    for (int i = 0; i < coeffs->size() - 1; i++) {
        converted_idx += (*coeffs)[i] * idcs[i + 1];
    }

    return  converted_idx;
}

template <typename ...Ints>
int Matrix<Ints...>::get(Ints... indices) {
    int k = index(indices...);
    return array[k];
}

template <typename ...Ints>
void Matrix<Ints...>::set(int value, Ints... indices) {
    int k = index(indices...);
    array[k] = value;

    // TODO: figure out how to set transpose as well
    int k_transpose = index(indices...);
    array[k_transpose] = value;
}

#endif /* matrix_hpp */
