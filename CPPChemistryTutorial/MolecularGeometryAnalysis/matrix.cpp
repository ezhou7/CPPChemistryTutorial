//
//  matrix.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/14/20.
//

#include "matrix.hpp"

Matrix::Matrix(int r, int c) {
    rows = r;
    cols = c;
    array = unique_ptr<int[]>(new int[r * c]());
}

Matrix::~Matrix() {

}

int Matrix::num_rows() {
    return rows;
}

int Matrix::num_cols() {
    return cols;
}

int Matrix::index(int i, int j) {
    return rows * i + j;
}

int Matrix::get(int i, int j) {
    int k = index(i, j);
    return array[k];
}

void Matrix::set(int i, int j, int value) {
    int k = index(i, j);
    int k_transpose = index(j, i);
    array[k] = value;
    array[k_transpose] = value;
}
