//
//  TestHessian.m
//  TestCPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/21/20.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>

#import "reader.hpp"
#import "hessianreader.hpp"
#import "hessian.hpp"

using std::move;
using std::shared_ptr;

@interface TestHessian : XCTestCase

@end

@implementation TestHessian

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (unique_ptr<Molecule>)readMoleculeFile {
    MoleculeReader reader;
    const string project_path([PROJECT_DIR UTF8String]);
    const string relative_path = "/ProgrammingProjects/Project#02/input/h2o_geom.txt";
    const string filepath = project_path + relative_path;
    
    return reader.read_file(filepath);
}

- (unique_ptr<MatrixXf>)readHessianFile {
    HessianReader reader;
    const string project_path([PROJECT_DIR UTF8String]);
    const string relative_path = "/ProgrammingProjects/Project#02/input/h2o_hessian.txt";
    const string filepath = project_path + relative_path;

    return reader.read_file(filepath);
}

- (void)testMassWeight {
    unique_ptr<Molecule> mol = [self readMoleculeFile];
    unique_ptr<MatrixXf> m_ptr = [self readHessianFile];
    HessianMatrix hm(move(m_ptr));
    MatrixXf& m = *hm.m;
    
    hm.mass_weight(*mol);

    XCTAssertEqualWithAccuracy(m(0, 0), 0.0057996, 0.00001);
    XCTAssertEqualWithAccuracy(m(0, 2), 0.0, 0.00001);
    XCTAssertEqualWithAccuracy(m(0, 3), -0.0115523, 0.00001);
    XCTAssertEqualWithAccuracy(m(0, 6), -0.0115523, 0.00001);
    XCTAssertEqualWithAccuracy(m(1, 1), 0.0198271, 0.00001);
    XCTAssertEqualWithAccuracy(m(1, 4), -0.0394937, 0.00001);
    XCTAssertEqualWithAccuracy(m(1, 5), 0.0199304, 0.00001);
    XCTAssertEqualWithAccuracy(m(1, 7), -0.0394937, 0.00001);
    XCTAssertEqualWithAccuracy(m(1, 8), -0.0199304, 0.00001);
    XCTAssertEqualWithAccuracy(m(2, 2), 0.0175112, 0.00001);
    XCTAssertEqualWithAccuracy(m(2, 4), 0.0086617, 0.00001);
    XCTAssertEqualWithAccuracy(m(2, 5), -0.0348807, 0.00001);
    XCTAssertEqualWithAccuracy(m(2, 7), -0.0086617, 0.00001);
    XCTAssertEqualWithAccuracy(m(2, 8), -0.0348807, 0.00001);
    XCTAssertEqualWithAccuracy(m(3, 0), -0.0115523, 0.00001);
}

- (void)testHarmonicFrequencies {
    unique_ptr<Molecule> mol = [self readMoleculeFile];
    unique_ptr<MatrixXf> m_ptr = [self readHessianFile];
    HessianMatrix hm(move(m_ptr));
    
    hm.mass_weight(*mol);
    
    unique_ptr<VectorXf> hf_ptr = hm.harmonic_frequencies();
    VectorXf hf = *hf_ptr;

    XCTAssertEqual(hf.rows(), 9);
    
    XCTAssertEqualWithAccuracy(hf(0), 0.0, 0.01);
    XCTAssertEqualWithAccuracy(hf(1), 0.0, 0.01);
    XCTAssertEqualWithAccuracy(hf(2), 0.0, 0.01);
    XCTAssertEqualWithAccuracy(hf(3), 1170.1990, 0.01);
    XCTAssertEqualWithAccuracy(hf(4), 1202.8640, 0.01);
    XCTAssertEqualWithAccuracy(hf(5), 1217.6808, 0.01);
    XCTAssertEqualWithAccuracy(hf(6), 1865.8704, 0.01);
    XCTAssertEqualWithAccuracy(hf(7), 2359.6522, 0.01);
    XCTAssertEqualWithAccuracy(hf(8), 2492.7600, 0.01);
}

@end

