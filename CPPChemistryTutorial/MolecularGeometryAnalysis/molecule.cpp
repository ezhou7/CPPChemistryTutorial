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
        
        double bond_angle = get_bond_angle(i, j, k);

        unique_ptr<Coordinate> cross_prod = cross(c, d, e);
        unique_ptr<Coordinate> h = divide(bond_angle, *cross_prod);
        unique_ptr<Coordinate> df_unit = unit_vector(d, f);

        double dot_prod = dot(*h, *df_unit);
        if (dot_prod < -1.0) {
            dot_prod = -1.0;
        } else if (dot_prod > 1.0) {
            dot_prod = 1.0;
        }
        
        return asin(dot_prod);
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

        unique_ptr<Coordinate> ijk_cross = cross(c, d, e);
        unique_ptr<Coordinate> jkl_cross = cross(d, e, f);
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
    VectorXf masses(size);
    MatrixXf coords(size, 3);

    for (int i = 0; i < atoms->size(); i++) {
        masses(i) = (*atoms)[i]->zvalue;
        coords(i, 0) = (*atoms)[i]->coord->x;
        coords(i, 1) = (*atoms)[i]->coord->y;
        coords(i, 2) = (*atoms)[i]->coord->z;
    }
    
    RowVector3f cm_row = masses * coords;
    Vector3f cm = cm_row.transpose();
    
    return make_unique<Vector3f>(cm);
}

unique_ptr<MatrixXf> Molecule::get_moment_of_inertia() {
    unsigned long size = atoms->size();
    MatrixXf inertia(3, 3);
    VectorXf masses(size);
    MatrixXf coords(size, 3);
    for (int i = 0; i < atoms->size(); i++) {
        masses(i) = (*atoms)[i]->zvalue;
        coords(i, 0) = (*atoms)[i]->coord->x;
        coords(i, 1) = (*atoms)[i]->coord->y;
        coords(i, 2) = (*atoms)[i]->coord->z;
    }
    
    VectorXf x = coords.col(0);
    VectorXf y = coords.col(1);
    VectorXf z = coords.col(2);
    
    VectorXf x_sq = x.pow(2);
    VectorXf y_sq = y.pow(2);
    VectorXf z_sq = z.pow(2);
    
    // diagonals
    inertia(0, 0) = (masses * (y_sq + z_sq)).sum();
    inertia(1, 1) = (masses * (y_sq + z_sq)).sum();
    inertia(2, 2) = (masses * (y_sq + z_sq)).sum();
    
    // off-diagonals
    inertia(0, 1) = inertia(1, 0) = (masses * x * y).sum();
    inertia(0, 2) = inertia(2, 0) = (masses * x * z).sum();
    inertia(1, 2) = inertia(2, 1) = (masses * y * z).sum();
    
    return make_unique<MatrixXf>(inertia);
}
