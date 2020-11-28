//
//  mollerplesset.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 11/27/20.
//

#include "mollerplesset.hpp"

MollerPlessetTransformer::MollerPlessetTransformer(MolecularData& data) {
    // TODO: add ao basis coefficients to molecular data and set AOC to coefficients
    this->TEI = data.eri;
}

MatrixXf MollerPlessetTransformer::brute() {
    MatrixXf TEI_MO(TEI.rows(), TEI.cols());
    
    for (int p = 0; p < natoms; p++) {
        for (int q = 0; q < natoms; q++) {
            int pq = calcIndex(p, q);

            for (int r = 0; r < natoms; r++) {
                for (int s = 0; s < natoms; s++) {
                    int rs = calcIndex(r, s);

                    for (int i = 0; i < natoms; i++) {
                        for (int j = 0; j < natoms; j++) {
                            int ij = calcIndex(i, j);

                            for (int k = 0; k < natoms; k++) {
                                for (int l = 0; l < natoms; l++) {
                                    int kl = calcIndex(k, l);
                                    TEI_MO(pq, rs) += AOC(p, i) * AOC(q, j) * AOC(r, k) * AOC(s, l) * TEI(ij, kl);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    return TEI_MO;
}

MatrixXf MollerPlessetTransformer::optimized() {
    MatrixXf TEI_MO(TEI.rows(), TEI.cols());

    // TODO: reduce O(n^8) to O(n^5) - find out why 3 innermost loops are unnecessary
    for (int p = 0; p < natoms; p++) {
        for (int q = 0; q < natoms; q++) {
            int pq = calcIndex(p, q);

            for (int r = 0; r < natoms; r++) {
                for (int s = 0; s < natoms; s++) {
                    int rs = calcIndex(r, s);

                    for (int i = 0; i < natoms; i++) {
                        int mo_i = 0;
                        for (int j = 0; j < natoms; j++) {
                            int ij = calcIndex(i, j);

                            int mo_j = 0;
                            for (int k = 0; k < natoms; k++) {
                                int mo_k = 0;
                                for (int l = 0; l < natoms; l++) {
                                    int kl = calcIndex(k, l);
                                    mo_k += AOC(s, l) * TEI(ij, kl);
                                }
                                mo_j += AOC(r, k) * mo_k;
                            }
                            mo_i += AOC(q, j) * mo_j;
                        }
                        TEI_MO(pq, rs) += AOC(p, i) * mo_i;
                    }
                }
            }
        }
    }
    
    return TEI_MO;
}
