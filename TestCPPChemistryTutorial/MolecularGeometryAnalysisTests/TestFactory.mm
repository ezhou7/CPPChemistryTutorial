//
//  TestFactory.m
//  TestCPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/18/20.
//

#import <XCTest/XCTest.h>

#import "factory.hpp"
#import "reader.hpp"

@interface TestMoleculeFactory : XCTestCase

@end

@implementation TestMoleculeFactory

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testAssemble {
//    MoleculeReader reader;
//    const string project_path([PROJECT_DIR UTF8String]);
//    const string relative_path = "/ProgrammingProjects/Project#01/input/acetaldehyde.dat";
//    const string filepath = project_path + relative_path;
//
//    unique_ptr<Molecule> molecule = reader.read_file(filepath);
//
//    MoleculeFactory factory;
//    unique_ptr<Molecule> m = factory.assemble(move(molecule->atoms));
//
//    XCTAssertEqualWithAccuracy(m->bond_lengths->get(1, 0), 2.84511, 0.000005);
}

@end
