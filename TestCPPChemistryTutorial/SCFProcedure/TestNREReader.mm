//
//  TestNREReader.m
//  TestCPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/21/20.
//

#import <XCTest/XCTest.h>

#import "TestUtils.h"

#import "nrereader.hpp"

using std::shared_ptr;

@interface TestNREReader : XCTestCase

@end

@implementation TestNREReader

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testReadFile {
    NREReader reader;
    const string project_path([PROJECT_DIR UTF8String]);
    const string relative_path = "/ProgrammingProjects/Project#03/input/h2o/STO-3G/enuc.dat";
    const string filepath = project_path + relative_path;
    
    double nre = reader.read_file(filepath);

    XCTAssertEqualWithAccuracy(nre, 8.002367, 0.0000001);
}

- (void)testReadFileWithInvalidFilePath {
    shared_ptr<NREReader> reader = shared_ptr<NREReader>(new NREReader());
    const string filepath = "";

    XCTAssertCppThrows(reader->read_file(filepath));
}

@end
