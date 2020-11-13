//
//  TestHartreeFock.m
//  TestCPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/23/20.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>

#import <iostream>
#import "nrereader.hpp"
#import "aoreader.hpp"
#import "erireader.hpp"
#import "hartreefock.hpp"

@interface TestHartreeFock : XCTestCase

@end

@implementation TestHartreeFock

HartreeFock hartree_fock;

- (void)readNuclearRepulsionEnergy {
    const string project_path([PROJECT_DIR UTF8String]);
    const string relative_path = "/ProgrammingProjects/Project#03/input/h2o/STO-3G";
    
    const string filepath = project_path + relative_path + "/enuc.dat";

    NREReader nrereader;
    double nre = nrereader.read_file(filepath);
    
    hartree_fock.nre = nre;
}

- (void)readOneElectronAtomicOrbitals {
    const string project_path([PROJECT_DIR UTF8String]);
    const string relative_path = "/ProgrammingProjects/Project#03/input/h2o/STO-3G";

    const string overlap_filepath = project_path + relative_path + "/s.dat";
    const string kei_filepath = project_path + relative_path + "/t.dat";
    const string nai_filepath = project_path + relative_path + "/v.dat";

    AOReader aoreader;
    
    unique_ptr<MatrixXf> s = aoreader.read_file(overlap_filepath);
    hartree_fock.overlap = *s;
    
    unique_ptr<MatrixXf> t = aoreader.read_file(kei_filepath);
    hartree_fock.kei = *t;
    
    unique_ptr<MatrixXf> v = aoreader.read_file(nai_filepath);
    hartree_fock.nai = *v;
}

- (void)setUp {
    [self readOneElectronAtomicOrbitals];
    [self readNuclearRepulsionEnergy];
}

- (void)testGetHamiltonian {
    unique_ptr<MatrixXf> h_ptr = hartree_fock.get_core_hamiltonian();
    MatrixXf h = *h_ptr;
    
    // first column checks
    XCTAssertEqualWithAccuracy(h(0, 0), -32.5773954, 0.000001);
    XCTAssertEqualWithAccuracy(h(1, 0), -7.5788328, 0.000001);
    XCTAssertEqualWithAccuracy(h(2, 0), 0.0, 0.000001);
    XCTAssertEqualWithAccuracy(h(3, 0), -0.0144738, 0.000001);
    XCTAssertEqualWithAccuracy(h(4, 0), 0.0, 0.000001);
    XCTAssertEqualWithAccuracy(h(5, 0), -1.2401023, 0.000001);
    XCTAssertEqualWithAccuracy(h(6, 0), -1.2401023, 0.000001);
    
    // first row checks
    XCTAssertEqualWithAccuracy(h(0, 1), -7.5788328, 0.000001);
    XCTAssertEqualWithAccuracy(h(0, 2), 0.0, 0.000001);
    XCTAssertEqualWithAccuracy(h(0, 3), -0.0144738, 0.000001);
    XCTAssertEqualWithAccuracy(h(0, 4), 0.0, 0.000001);
    XCTAssertEqualWithAccuracy(h(0, 5), -1.2401023, 0.000001);
    XCTAssertEqualWithAccuracy(h(0, 6), -1.2401023, 0.000001);
}

- (void)testGetOrthoOverlap {
    unique_ptr<MatrixXf> oom_ptr = hartree_fock.get_ortho_overlap();
    MatrixXf oom = *oom_ptr;
    
    // first column checks
    XCTAssertEqualWithAccuracy(oom(0, 0), 1.0236346, 0.000001);
    XCTAssertEqualWithAccuracy(oom(1, 0), -0.1368547, 0.000001);
    XCTAssertEqualWithAccuracy(oom(2, 0), 0.0, 0.000001);
    XCTAssertEqualWithAccuracy(oom(3, 0), -0.0074873, 0.000001);
    XCTAssertEqualWithAccuracy(oom(4, 0), 0.0, 0.000001);
    XCTAssertEqualWithAccuracy(oom(5, 0), 0.0190279, 0.000001);
    XCTAssertEqualWithAccuracy(oom(6, 0), 0.0190279, 0.000001);
    
    // first row checks
    XCTAssertEqualWithAccuracy(oom(0, 1), -0.1368547, 0.000001);
    XCTAssertEqualWithAccuracy(oom(0, 2), 0.0, 0.000001);
    XCTAssertEqualWithAccuracy(oom(0, 3), -0.0074873, 0.000001);
    XCTAssertEqualWithAccuracy(oom(0, 4), 0.0, 0.000001);
    XCTAssertEqualWithAccuracy(oom(0, 5), 0.0190279, 0.000001);
    XCTAssertEqualWithAccuracy(oom(0, 6), 0.0190279, 0.000001);
}

- (void)testGetFockMatrix {
    unique_ptr<MatrixXf> fock_ptr = hartree_fock.get_fock_matrix();
    MatrixXf fock = *fock_ptr;
    
    // first col
    XCTAssertEqualWithAccuracy(fock(0, 0), -32.254586, 0.000015);
    XCTAssertEqualWithAccuracy(fock(0, 1), -2.7914909, 0.000015);
    XCTAssertEqualWithAccuracy(fock(0, 2), 0, 0.000015);
    XCTAssertEqualWithAccuracy(fock(0, 3), 0.0086110, 0.000015);
    XCTAssertEqualWithAccuracy(fock(0, 4), 0, 0.000015);
    XCTAssertEqualWithAccuracy(fock(0, 5), -0.1812967, 0.000015);
    XCTAssertEqualWithAccuracy(fock(0, 6), -0.1812967, 0.000015);

    // first row
    XCTAssertEqualWithAccuracy(fock(1, 0), fock(0, 1), 0.000015);
    XCTAssertEqualWithAccuracy(fock(2, 0), fock(0, 2), 0.000015);
    XCTAssertEqualWithAccuracy(fock(3, 0), fock(0, 3), 0.000015);
    XCTAssertEqualWithAccuracy(fock(4, 0), fock(0, 4), 0.000015);
    XCTAssertEqualWithAccuracy(fock(5, 0), fock(0, 5), 0.000015);
    XCTAssertEqualWithAccuracy(fock(6, 0), fock(0, 6), 0.000015);
    
    // diagonal
    XCTAssertEqualWithAccuracy(fock(1, 1), -8.2368891, 0.000015);
    XCTAssertEqualWithAccuracy(fock(2, 2), -7.5428890, 0.000015);
    XCTAssertEqualWithAccuracy(fock(3, 3), -7.4570295, 0.000015);
    XCTAssertEqualWithAccuracy(fock(4, 4), -7.3471449, 0.000015);
    XCTAssertEqualWithAccuracy(fock(5, 5), -4.0329547, 0.000015);
    XCTAssertEqualWithAccuracy(fock(6, 6), -4.0329547, 0.000015);
}

- (unique_ptr<MatrixXf>)getCoeffsMatrix {
    NSString* string = @"-1.0015436   0.2336245   0.0000000   0.0856842   0.0000000  -0.0482226  -0.0000000 \
    0.0071893  -1.0579388  -0.0000000  -0.3601105  -0.0000000   0.4631213   0.0000000 \
    -0.0000000  -0.0000000   1.0610702   0.0000000  -0.0000000  -0.0000000   0.2965071 \
    0.0002671  -0.4272843  -0.0000000   0.9399425   0.0000000   0.2129401   0.0000000 \
    0.0000000   0.0000000  -0.0000000   0.0000000  -1.0000000  -0.0000000  -0.0000000 \
    -0.0018213   0.1492533  -0.1377210  -0.0378579   0.0000000  -0.7807003  -0.8501403 \
    -0.0018213   0.1492533   0.1377210  -0.0378579  -0.0000000  -0.7807003   0.8501403";
    
    NSArray* stringifiedNums = [string componentsSeparatedByCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    stringifiedNums = [stringifiedNums filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"length > 0"]];
    vector<float> nums;
    for (NSString* stringifiedNum in stringifiedNums) {
        float num = [stringifiedNum floatValue];
        nums.push_back(num);
    }
    
    MatrixXf m = Eigen::Map<Eigen::Matrix<float, 7, 7>>(nums.data());

    return make_unique<MatrixXf>(m.transpose());
}

- (void)testGetAOBasisCoefficients {
    unique_ptr<MatrixXf> cmptr = [self getCoeffsMatrix];
    MatrixXf cm = *cmptr;
    unique_ptr<MatrixXf> oomptr = hartree_fock.get_ortho_overlap();
    MatrixXf oom = *oomptr;
    unique_ptr<MatrixXf> fock_ptr = hartree_fock.get_fock_matrix();
    MatrixXf fock = *fock_ptr;
    MatrixXf evecs = oom.inverse() * cm;
    MatrixXf evals = evecs.inverse() * fock * evecs;
    std::cout << evals << std::endl << std::endl;
    
    unique_ptr<MatrixXf> ao_basis_ptr = hartree_fock.get_ao_basis_coefficients();
    MatrixXf ao_basis = *ao_basis_ptr;
    std::cout << ao_basis << std::endl;
    
    XCTAssertEqualWithAccuracy(ao_basis(0, 0), -1.0015436, 0.000001);
}

- (void)testGetInitialGuessDensity {
    unique_ptr<MatrixXf> density_ptr = hartree_fock.get_initial_guess_density();
    MatrixXf density = *density_ptr;
    std::cout << density << std::endl;
    
    XCTAssertEqualWithAccuracy(density(0, 0), 1.0650117, 0.000001);
}

- (void)testGetInitialSCFEnergy {
    double scf = hartree_fock.get_initial_scf_energy();
    XCTAssertEqualWithAccuracy(scf, -125.842077437699, 0.000001);
}

@end
