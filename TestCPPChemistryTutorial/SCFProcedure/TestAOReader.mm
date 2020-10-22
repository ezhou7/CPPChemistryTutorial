//
//  TestAOReader.m
//  TestCPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/22/20.
//

#import <XCTest/XCTest.h>

#import "TestUtils.h"

#import "aoreader.hpp"

using std::shared_ptr;

@interface TestAOReader : XCTestCase

@end

@implementation TestAOReader

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testReadFile {
    AOReader reader;
    const string project_path([PROJECT_DIR UTF8String]);
    const string relative_path = "/ProgrammingProjects/Project#03/input/h2o/STO-3G/s.dat";
    const string filepath = project_path + relative_path;
    
    unique_ptr<MatrixXf> m_ptr = reader.read_file(filepath);
    MatrixXf& m = *m_ptr;

    XCTAssertEqual(m.rows(), 7);
    XCTAssertEqual(m.cols(), 7);
    
    XCTAssertEqualWithAccuracy(m(0, 0), 1.0, 0.01);
    XCTAssertEqualWithAccuracy(m(1, 0), 0.236703, 0.000001);
    XCTAssertEqualWithAccuracy(m(1, 1), 1.0, 0.01);
    XCTAssertEqualWithAccuracy(m(2, 0), 0.0, 0.01);
    XCTAssertEqualWithAccuracy(m(2, 1), 0.0, 0.01);
    XCTAssertEqualWithAccuracy(m(2, 2), 1.0, 0.01);
}

- (void)testReadFileWithInvalidFilePath {
    shared_ptr<AOReader> reader = shared_ptr<AOReader>(new AOReader());
    const string filepath = "";

    XCTAssertCppThrows(reader->read_file(filepath));
}

@end
