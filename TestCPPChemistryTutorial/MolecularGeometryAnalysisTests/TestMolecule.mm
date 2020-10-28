//
//  TestMolecule.m
//  TestCPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/19/20.
//

#import <XCTest/XCTest.h>

#import <iostream>
#import "moleculereader.hpp"

@interface TestMolecule : XCTestCase

@end

@implementation TestMolecule

unique_ptr<Molecule> molecule;

- (void)setUp {
    MoleculeReader reader;
    const string project_path([PROJECT_DIR UTF8String]);
    const string relative_path = "/ProgrammingProjects/Project#01/input/acetaldehyde.dat";
    const string filepath = project_path + relative_path;

    molecule = reader.read_file(filepath);
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testGetBondLength {
    double bond_length = molecule->get_bond_length(1, 0);
    XCTAssertEqualWithAccuracy(bond_length, 2.84511, 0.000005);
}

- (double)radianToDegrees: (double) angle {
    return 180 * (angle / M_PI);
}

- (void)testGetBondAngle {
    double a1 = molecule->get_bond_angle(2, 1, 0);
    double a2 = molecule->get_bond_angle(3, 1, 0);
    double a3 = molecule->get_bond_angle(3, 2, 1);
    double a4 = molecule->get_bond_angle(5, 4, 0);
    double a5 = molecule->get_bond_angle(6, 4, 0);
    double a6 = molecule->get_bond_angle(6, 5, 0);
    double a7 = molecule->get_bond_angle(6, 5, 4);

    XCTAssertEqualWithAccuracy([self radianToDegrees: a1], 124.268308, 0.0000005);
    XCTAssertEqualWithAccuracy([self radianToDegrees: a2], 115.479341, 0.0000005);
    XCTAssertEqualWithAccuracy([self radianToDegrees: a3], 28.377448, 0.0000005);
    XCTAssertEqualWithAccuracy([self radianToDegrees: a4], 35.109529, 0.0000005);
    XCTAssertEqualWithAccuracy([self radianToDegrees: a5], 35.109529, 0.0000005);
    XCTAssertEqualWithAccuracy([self radianToDegrees: a6], 36.373677, 0.0000005);
    XCTAssertEqualWithAccuracy([self radianToDegrees: a7], 60.484476, 0.0000005);
}

- (void)testGetOutOfPlaneAngle {
    double a1 = molecule->get_out_of_plane_angle(3, 1, 2, 0);
    double a2 = molecule->get_out_of_plane_angle(6, 4, 5, 0);
    double a3 = molecule->get_out_of_plane_angle(6, 5, 4, 0);
    double a4 = molecule->get_out_of_plane_angle(5, 6, 4, 0);

    XCTAssertEqualWithAccuracy([self radianToDegrees: a1], 0.0, 0.0000005);
    XCTAssertEqualWithAccuracy([self radianToDegrees: a2], 19.939726, 0.0000005);
    XCTAssertEqualWithAccuracy([self radianToDegrees: a3], -19.850523, 0.0000005);
    XCTAssertEqualWithAccuracy([self radianToDegrees: a4], 19.850523, 0.0000005);
}

- (void)testGetTorsionAngle {
    double a1 = molecule->get_torsion_angle(3, 2, 1, 0);
    double a2 = molecule->get_torsion_angle(6, 5, 4, 0);

    XCTAssertEqualWithAccuracy([self radianToDegrees: a1], 180.000000, 0.0000005);
    XCTAssertEqualWithAccuracy([self radianToDegrees: a2], 36.366799, 0.0000005);
}

- (void)testGetCenterOfMass {
    unique_ptr<Vector3f> cm_ptr = molecule->get_center_of_mass();
    Vector3f cm = *cm_ptr;

    XCTAssertEqualWithAccuracy(cm(0), 0.64494926, 0.0000005);
    XCTAssertEqualWithAccuracy(cm(1), 0.00000000, 0.0000005);
    XCTAssertEqualWithAccuracy(cm(2), 2.31663792, 0.0000005);
}

- (void)testGetMomentOfInertia {
    unique_ptr<Matrix3f> I_ptr = molecule->get_moment_of_inertia();
    Matrix3f I = *I_ptr;
    
    XCTAssertEqualWithAccuracy(I(0, 0), 156.154, 0.001);
    XCTAssertEqualWithAccuracy(I(1, 1), 199.371, 0.001);
    XCTAssertEqualWithAccuracy(I(2, 2), 54.459, 0.001);

    XCTAssertEqualWithAccuracy(I(1, 0), 0.0, 0.001);
    XCTAssertEqualWithAccuracy(I(0, 1), 0.0, 0.001);
    XCTAssertEqualWithAccuracy(I(1, 2), 0.0, 0.001);
    XCTAssertEqualWithAccuracy(I(2, 1), 0.0, 0.001);
    XCTAssertEqualWithAccuracy(I(0, 2), -52.855, 0.001);
    XCTAssertEqualWithAccuracy(I(2, 0), -52.855, 0.001);
}

- (void)testGetRotationalConstants {
    unique_ptr<Vector3f> rc_ptr = molecule->get_rotational_constants();
    Vector3f rc = *rc_ptr;
    
    XCTAssertEqualWithAccuracy(rc(0), 1.8834, 0.0001);
    XCTAssertEqualWithAccuracy(rc(1), 0.3370, 0.0001);
    XCTAssertEqualWithAccuracy(rc(2), 0.3019, 0.0001);
}

@end
