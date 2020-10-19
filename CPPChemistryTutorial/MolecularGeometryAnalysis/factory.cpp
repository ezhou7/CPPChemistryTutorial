//
//  factory.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/17/20.
//

#include "factory.hpp"

MoleculeFactory::MoleculeFactory() {

}

MoleculeFactory::~MoleculeFactory() {

}

//unique_ptr<Molecule> MoleculeFactory::assemble(unique_ptr<vector<unique_ptr<Atom>>> atoms) {
//    unique_ptr<Molecule> molecule = make_unique<Molecule>(move(atoms));
//    set_bonds(*molecule);
////    set_bond_angles(*molecule);
//    // TODO: calculate out of plane angles
//
//    return molecule;
//}
//
//void MoleculeFactory::set_bonds(Molecule& molecule) {
//    vector<unique_ptr<Atom>>& atoms = *molecule.atoms;
//
//    int n = (int) molecule.size();
//    auto matrix = make_unique<SparseMatrix<double>>(n, n);
//
//    for (int i = 1; i < n; i++) {
//        for (int j = 0; j < i; j++) {
//            Coordinate& c = *atoms[i]->coord;
//            Coordinate& d = *atoms[j]->coord;
//            printf("c: %f %f %f\n", c.x, c.y, c.z);
//            printf("d: %f %f %f\n", d.x, d.y, d.z);
//
//            double dist = euclid_dist(c, d);
//            matrix->insert(i, j);
//            matrix->insert(j, i);
//            printf("dist: %f\n\n", dist);
//        }
//    }
//
//    molecule.bond_lengths = move(matrix);
//}
//
//void MoleculeFactory::set_bond_angles(Molecule& molecule) {
//    vector<unique_ptr<Atom>>& atoms = *molecule.atoms;
//    Matrix<int, int>& bond_lengths = *molecule.bond_lengths;
//
//    int n = (int) molecule.size();
//    auto matrix = new Matrix<int, int, int>(n, n, n);
//
//    for (int i = 0; i < n - 2; i++) {
//        for (int j = i + 1; j < n - 1; j++) {
//            for (int k = j + 1; k < n; k++) {
//                double ij_dist = bond_lengths.get(i, j);
//                double jk_dist = bond_lengths.get(j, k);
//
//                if (ij_dist < bond_threshold && jk_dist < bond_threshold) {
//                    Coordinate& c = *atoms[i]->coord;
//                    Coordinate& d = *atoms[j]->coord;
//                    Coordinate& e = *atoms[k]->coord;
//
//                    double bond_angle = angle(c, d, e);
//                    matrix->set(bond_angle, i, j, k);
//                }
//            }
//        }
//    }
//
//    molecule.bond_angles = unique_ptr<Matrix<int, int, int>>(matrix);
//}
//
//void MoleculeFactory::set_out_of_plane_angles(Molecule& molecule) {
//    vector<unique_ptr<Atom>>& atoms = *molecule.atoms;
//    Matrix<int, int>& bond_lengths = *molecule.bond_lengths;
//    Matrix<int, int, int>& bond_angles = *molecule.bond_angles;
//
//    int n = (int) molecule.size();
//    auto matrix = new Matrix<int, int, int, int>(n, n, n, n);
//
//    for (int i = 0; i < n - 3; i++) {
//        for (int j = i + 1; j < n - 2; j++) {
//            for (int k = j + 1; k < n - 1; k++) {
//                for (int l = k + 1; l < n; l++) {
//                    double ij_dist = bond_lengths.get(i, j);
//                    double jk_dist = bond_lengths.get(j, k);
//                    double jl_dist = bond_lengths.get(j, l);
//
//                    if (ij_dist < bond_threshold && jk_dist < bond_threshold && jl_dist < bond_threshold) {
//                        Coordinate& c = *atoms[i]->coord;
//                        Coordinate& d = *atoms[j]->coord;
//                        Coordinate& e = *atoms[k]->coord;
//                        Coordinate& f = *atoms[l]->coord;
//
//                        double bond_angle = bond_angles.get(i, j, k);
//
//                        unique_ptr<Coordinate> cross_prod = cross(c, d, e);
//                        unique_ptr<Coordinate> h = divide(bond_angle, *cross_prod);
//                        unique_ptr<Coordinate> df_unit = unit_vector(d, f);
//
//                        double dot_prod = dot(*h, *df_unit);
//                        if (dot_prod < -1.0) {
//                            dot_prod = -1.0;
//                        } else if (dot_prod > 1.0) {
//                            dot_prod = 1.0;
//                        }
//
//                        matrix->set(asin(dot_prod), i, j, k, l);
//                    }
//                }
//            }
//        }
//    }
//
//    molecule.out_of_plane_angles = unique_ptr<Matrix<int, int, int, int>>(matrix);
//}
//
//void MoleculeFactory::set_torsion_angles(Molecule& molecule) {
//    vector<unique_ptr<Atom>>& atoms = *molecule.atoms;
//    Matrix<int, int>& bond_lengths = *molecule.bond_lengths;
//    Matrix<int, int, int>& bond_angles = *molecule.bond_angles;
//
//    int n = (int) molecule.size();
//    auto matrix = new Matrix<int, int, int, int>(n, n, n, n);
//
//    for (int i = 0; i < n - 3; i++) {
//        for (int j = i + 1; j < n - 2; j++) {
//            for (int k = j + 1; k < n - 1; k++) {
//                for (int l = k + 1; l < n; l++) {
//                    double ij_dist = bond_lengths.get(i, j);
//                    double jk_dist = bond_lengths.get(j, k);
//                    double kl_dist = bond_lengths.get(k, l);
//
//                    if (ij_dist < bond_threshold && jk_dist < bond_threshold && kl_dist < bond_threshold) {
//                        Coordinate& c = *atoms[i]->coord;
//                        Coordinate& d = *atoms[j]->coord;
//                        Coordinate& e = *atoms[k]->coord;
//                        Coordinate& f = *atoms[l]->coord;
//
//                        unique_ptr<Coordinate> ijk_cross = cross(c, d, e);
//                        unique_ptr<Coordinate> jkl_cross = cross(d, e, f);
//                        double dot_prod = dot(*ijk_cross, *jkl_cross);
//
//                        double ijk_angle = bond_angles.get(i, j, k);
//                        double jkl_angle = bond_angles.get(j, k, l);
//                        double torsion = dot_prod / (sin(ijk_angle) * sin(jkl_angle));
//                        double torsion_angle = acos(torsion);
//
//                        matrix->set(torsion_angle, i, j, k, l);
//                    }
//                }
//            }
//        }
//    }
//}
