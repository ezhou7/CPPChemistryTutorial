//
//  TestHessianReader.m
//  TestCPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/20/20.
//

#import <XCTest/XCTest.h>

#import "TestUtils.h"

#import "hessianreader.hpp"

using std::shared_ptr;

@interface TestHessianReader : XCTestCase

@end

@implementation TestHessianReader

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testReadFile {
    HessianReader reader;
    const string project_path([PROJECT_DIR UTF8String]);
    const string relative_path = "/ProgrammingProjects/Project#02/input/h2o_hessian.txt";
    const string filepath = project_path + relative_path;
    
    unique_ptr<MatrixXf> m_ptr = reader.read_file(filepath);
    MatrixXf m = *m_ptr;

    XCTAssertEqual(m.rows(), 9);
    XCTAssertEqual(m.cols(), 9);

    XCTAssertEqualWithAccuracy(m(0, 0), 0.0927643390, 0.00001);
    XCTAssertEqualWithAccuracy(m(0, 1), 0.0, 0.00001);
    XCTAssertEqualWithAccuracy(m(0, 2), 0.0, 0.00001);
    XCTAssertEqualWithAccuracy(m(0, 3), -0.0463821695, 0.00001);
    XCTAssertEqualWithAccuracy(m(0, 4), 0.0, 0.00001);
    XCTAssertEqualWithAccuracy(m(0, 5), 0.0, 0.00001);
    XCTAssertEqualWithAccuracy(m(0, 6), -0.0463821695, 0.00001);
    XCTAssertEqualWithAccuracy(m(0, 7), 0.0, 0.00001);
    XCTAssertEqualWithAccuracy(m(0, 8), 0.0, 0.00001);
    XCTAssertEqualWithAccuracy(m(1, 1), 0.3171327134, 0.00001);
    XCTAssertEqualWithAccuracy(m(1, 4), -0.1585663567, 0.00001);
    XCTAssertEqualWithAccuracy(m(1, 5), 0.0800202030, 0.00001);
}

- (void)testReadFileWithInvalidFilePath {
    shared_ptr<HessianReader> reader = shared_ptr<HessianReader>(new HessianReader());
    const string filepath = "";

    XCTAssertCppThrows(reader->read_file(filepath));
}

@end
