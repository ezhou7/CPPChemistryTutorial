//
//  molecule.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/14/20.
//

#include "molecule.hpp"

Molecule::Molecule(unique_ptr<vector<unique_ptr<Atom>>> atoms) {
    this->atoms = move(atoms);
}

Molecule::~Molecule() {

}

unsigned long Molecule::size() {
    return atoms->size();
}

double Molecule::get_bond_length(int i, int j) {
    Coordinate c = *(*atoms)[i]->coord;
    Coordinate d = *(*atoms)[j]->coord;
    
    return euclid_dist(c, d);
}

double Molecule::get_bond_angle(int i, int j, int k) {
    double ij_dist = get_bond_length(i, j);
    double jk_dist = get_bond_length(j, k);
    
    if (ij_dist < bond_threshold && jk_dist < bond_threshold) {
        Coordinate& c = *(*atoms)[i]->coord;
        Coordinate& d = *(*atoms)[j]->coord;
        Coordinate& e = *(*atoms)[k]->coord;

        return angle(c, d, e);
    } else {
        return -1;
    }
}

double Molecule::get_out_of_plane_angle(int i, int j, int k, int l) {
    double ij_dist = get_bond_length(i, j);
    double jk_dist = get_bond_length(j, k);
    double jl_dist = get_bond_length(j, l);
    
    if (ij_dist < bond_threshold && jk_dist < bond_threshold && jl_dist < bond_threshold) {
        Coordinate& c = *(*atoms)[i]->coord;
        Coordinate& d = *(*atoms)[j]->coord;
        Coordinate& e = *(*atoms)[k]->coord;
        Coordinate& f = *(*atoms)[l]->coord;

        unique_ptr<Coordinate> dc_unit = unit_vector(d, c);
        unique_ptr<Coordinate> de_unit = unit_vector(d, e);
        unique_ptr<Coordinate> df_unit = unit_vector(d, f);
        unique_ptr<Coordinate> cross_prod = cross(*dc_unit, *de_unit);
        double dot_prod = dot(*cross_prod, *df_unit);

        double bond_angle = get_bond_angle(i, j, k);
        double h = dot_prod / sin(bond_angle);

        if (h < -1.0) {
            h = -1.0;
        } else if (h > 1.0) {
            h = 1.0;
        }

        return asin(h);
    } else {
        return -1;
    }
}

double Molecule::get_torsion_angle(int i, int j, int k, int l) {
    double ij_dist = get_bond_length(i, j);
    double jk_dist = get_bond_length(j, k);
    double kl_dist = get_bond_length(k, l);
    
    if (ij_dist < bond_threshold && jk_dist < bond_threshold && kl_dist < bond_threshold) {
        Coordinate& c = *(*atoms)[i]->coord;
        Coordinate& d = *(*atoms)[j]->coord;
        Coordinate& e = *(*atoms)[k]->coord;
        Coordinate& f = *(*atoms)[l]->coord;
        
        unique_ptr<Coordinate> ij_unit = unit_vector(c, d);
        unique_ptr<Coordinate> jk_unit = unit_vector(d, e);
        unique_ptr<Coordinate> kl_unit = unit_vector(e, f);

        unique_ptr<Coordinate> ijk_cross = cross(*ij_unit, *jk_unit);
        unique_ptr<Coordinate> jkl_cross = cross(*jk_unit, *kl_unit);
        double dot_prod = dot(*ijk_cross, *jkl_cross);
        
        double ijk_angle = get_bond_angle(i, j, k);
        double jkl_angle = get_bond_angle(j, k, l);
        double torsion = dot_prod / (sin(ijk_angle) * sin(jkl_angle));
        double torsion_angle = acos(torsion);

        return torsion_angle;
    } else {
        return -1;
    }
}

unique_ptr<Vector3f> Molecule::get_center_of_mass() {
    unsigned long size = atoms->size();
    RowVectorXf masses(size);
    MatrixXf coords(size, 3);

    for (int i = 0; i < atoms->size(); i++) {
        int atomic_num = (*atoms)[i]->zvalue;
        masses(i) = atomic_masses[atomic_num];

        coords(i, 0) = (*atoms)[i]->coord->x;
        coords(i, 1) = (*atoms)[i]->coord->y;
        coords(i, 2) = (*atoms)[i]->coord->z;
    }
    
    RowVector3f cm_row = (masses * coords) / masses.sum();
    Vector3f cm = cm_row.transpose();
    
    return make_unique<Vector3f>(cm);
}

unique_ptr<Matrix3f> Molecule::get_moment_of_inertia() {
    unsigned long size = atoms->size();
    MatrixXf inertia(3, 3);
    RowVectorXf masses(size);
    MatrixXf coords(size, 3);
    unique_ptr<Vector3f> cm_ptr = get_center_of_mass();
    Vector3f cm = *cm_ptr;
    for (int i = 0; i < size; i++) {
        int atomic_num = (*atoms)[i]->zvalue;
        masses(i) = atomic_masses[atomic_num];

        coords(i, 0) = (*atoms)[i]->coord->x - cm(0);
        coords(i, 1) = (*atoms)[i]->coord->y - cm(1);
        coords(i, 2) = (*atoms)[i]->coord->z - cm(2);
    }
    
    VectorXf x = coords.col(0);
    VectorXf y = coords.col(1);
    VectorXf z = coords.col(2);
    
    MatrixXf coords_sq = coords.array().square();
    VectorXf x_sq = coords_sq.col(0);
    VectorXf y_sq = coords_sq.col(1);
    VectorXf z_sq = coords_sq.col(2);
    
    // diagonal
    inertia(0, 0) = masses.dot(y_sq + z_sq);
    inertia(1, 1) = masses.dot(x_sq + z_sq);
    inertia(2, 2) = masses.dot(x_sq + y_sq);
    
    // off-diagonal
    inertia(0, 1) = inertia(1, 0) = - masses.transpose().cwiseProduct(x).cwiseProduct(y).sum();
    inertia(0, 2) = inertia(2, 0) = - masses.transpose().cwiseProduct(x).cwiseProduct(z).sum();
    inertia(1, 2) = inertia(2, 1) = - masses.transpose().cwiseProduct(y).cwiseProduct(z).sum();
    
    return make_unique<Matrix3f>(inertia);
}

unique_ptr<Vector3f> Molecule::get_rotational_constants() {
    unique_ptr<Matrix3f> I = get_moment_of_inertia();
    SelfAdjointEigenSolver<Matrix3f> solver(*I);

    Matrix3f eigen_vectors = solver.eigenvectors();
    Vector3f eigen_values = solver.eigenvalues();
    
    // gives rotational constant in cm^-1
    double coeff = 6.6260755E-34/(8.0 * M_PI * M_PI);
    coeff /= 1.6605402E-27 * 0.529177249E-10 * 0.529177249E-10;
    coeff /= 2.99792458E10;

    return make_unique<Vector3f>(coeff / eigen_values.array());
}
