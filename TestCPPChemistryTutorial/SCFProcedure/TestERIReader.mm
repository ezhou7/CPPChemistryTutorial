//
//  TestERIReader.m
//  TestCPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/23/20.
//

#import <XCTest/XCTest.h>

#import "TestUtils.h"

#import "erireader.hpp"

using std::shared_ptr;

@interface TestERIReader : XCTestCase

@end

@implementation TestERIReader

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testReadFile {
    ERIReader reader;
    const string project_path([PROJECT_DIR UTF8String]);
    const string relative_path = "/ProgrammingProjects/Project#03/input/h2o/STO-3G/eri.dat";
    const string filepath = project_path + relative_path;
    
    unique_ptr<MatrixXf> m_ptr = reader.read_file(filepath);
    MatrixXf& m = *m_ptr;

    XCTAssertEqual(m.rows(), 49);
    XCTAssertEqual(m.cols(), 49);
    
    XCTAssertEqualWithAccuracy(m(0, 0), 4.785065, 0.000001);
    XCTAssertEqualWithAccuracy(m(1, 0), 0.741380, 0.000001);
    XCTAssertEqualWithAccuracy(m(1, 1), 0.136873, 0.000001);
    XCTAssertEqualWithAccuracy(m(2, 0), 1.118946, 0.000001);
    XCTAssertEqualWithAccuracy(m(2, 1), 0.256633, 0.000001);
    XCTAssertEqualWithAccuracy(m(2, 2), 0.817206, 0.000001);
}

- (void)testReadFileWithInvalidFilePath {
    shared_ptr<ERIReader> reader = shared_ptr<ERIReader>(new ERIReader());
    const string filepath = "";

    XCTAssertCppThrows(reader->read_file(filepath));
}

@end
