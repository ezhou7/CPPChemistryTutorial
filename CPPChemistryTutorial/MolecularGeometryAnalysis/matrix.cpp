//
//  matrix.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/14/20.
//

#include "matrix.hpp"

template <typename ...Ints>
Matrix::Matrix(Ints... ds) {
    dims = unique_ptr<vector<int>>(new vector<int>{ds...});
    index_coeffs = cum_multiply(*dims);

    size_t size = (size_t) (*index_coeffs)[index_coeffs->size() - 1];
    array = unique_ptr<int[]>(new int[size]());
}

Matrix::~Matrix() {

}

template <typename ...Ints>
int Matrix::index(Ints... indices) {
    vector<int> idcs{indices...};
    unique_ptr<vector<int>> coeffs = cum_multiply(*dims);

    int converted_idx = idcs[0];
    for (int i = 0; i < coeffs->size() - 1; i++) {
        converted_idx += (*coeffs)[i] * idcs[i + 1];
    }

    return converted_idx;
}

template <typename ...Ints>
int Matrix::get(Ints... indices) {
    int k = index(indices...);
    return array[k];
}

template <typename ...Ints>
void Matrix::set(int value, Ints... indices) {
    int k = index(indices...);
    array[k] = value;

    // TODO: figure out how to set transpose as well
    int k_transpose = index(indices...);
    array[k_transpose] = value;
}
