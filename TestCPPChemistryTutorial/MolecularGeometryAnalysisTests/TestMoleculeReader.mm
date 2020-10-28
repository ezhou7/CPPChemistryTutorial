//
//  TestMoleculeReader.m
//  TestCPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/16/20.
//

#import <XCTest/XCTest.h>

#import "TestUtils.h"

#import "moleculereader.hpp"

@interface TestMoleculeReader : XCTestCase

@end

@implementation TestMoleculeReader

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testReadFile {
    MoleculeReader reader;
    const string project_path([PROJECT_DIR UTF8String]);
    const string relative_path = "/ProgrammingProjects/Project#01/input/acetaldehyde.dat";
    const string filepath = project_path + relative_path;
    
    unique_ptr<Molecule> molecule = reader.read_file(filepath);

    XCTAssertEqual(molecule->atoms->size(), 7);
}

- (void)testReadFileWithInvalidFilePath {
    shared_ptr<MoleculeReader> reader = shared_ptr<MoleculeReader>(new MoleculeReader());
    const string filepath = "";

    XCTAssertCppThrows(reader->read_file(filepath));
}

@end
