//
//  matrix.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/14/20.
//

#ifndef matrix_hpp
#define matrix_hpp

#include <memory>
#include <stdexcept>
#include <vector>

#include "vectorutils.hpp"

using namespace std;

template <typename ...Ints>
class Matrix {
private:
    unique_ptr<vector<int>> dims;
    unique_ptr<vector<int>> index_coeffs;
    unique_ptr<double[]> array;

    bool are_indices_valid(vector<int>& indices);
    int index(Ints... indices);
    
public:
    Matrix(Ints... dims);
    ~Matrix();

    double get(Ints... indices);
    void set(double value, Ints... indices);
};

template <typename ...Ints>
Matrix<Ints...>::Matrix(Ints... ds) {
    dims = unique_ptr<vector<int>>(new vector<int>{ds...});
    index_coeffs = cum_multiply(*dims);

    size_t size = (size_t) (*index_coeffs)[index_coeffs->size() - 1];
    array = unique_ptr<double[]>(new double[size]());
}

template <typename ...Ints>
Matrix<Ints...>::~Matrix() {

}

template <typename ...Ints>
bool Matrix<Ints...>::are_indices_valid(vector<int>& indices) {
    for (int i = 0; i < indices.size(); i++) {
        int index = indices[i];
        int dim = (*dims)[i];
        
        if (index < 0 || index >= dim) {
            return false;
        }
    }
    
    return true;
}

template <typename ...Ints>
int Matrix<Ints...>::index(Ints... indices) {
    vector<int> idcs{indices...};

    if (!are_indices_valid(idcs)) {
        throw invalid_argument("Indices out of bounds.");
    }

    int converted_idx = idcs[0];
    for (int i = 0; i < index_coeffs->size() - 1; i++) {
        converted_idx += (*index_coeffs)[i] * idcs[i + 1];
    }

    return  converted_idx;
}

template <typename ...Ints>
double Matrix<Ints...>::get(Ints... indices) {
    int idx = index(indices...);
    return array[idx];
}

template <typename ...Ints>
void Matrix<Ints...>::set(double value, Ints... indices) {
    int idx = index(indices...);
    array[idx] = value;
}

#endif /* matrix_hpp */
