//
//  TestHartreeFock.m
//  TestCPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/23/20.
//

#import <XCTest/XCTest.h>

#import "aoreader.hpp"
#import "erireader.hpp"
#import "hartreefock.hpp"

@interface TestHartreeFock : XCTestCase

@end

@implementation TestHartreeFock

HartreeFock hartree_fock;

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

@end
