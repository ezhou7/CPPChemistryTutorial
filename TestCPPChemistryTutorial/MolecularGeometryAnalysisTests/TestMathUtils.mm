//
//  testmathutils.mm
//  TestCPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/15/20.
//

#import <XCTest/XCTest.h>

#include "coordinate.hpp"
#include "mathutils.hpp"

@interface TestMathUtils : XCTestCase

@end

@implementation TestMathUtils

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testEuclidDist {
    Coordinate c(0, 0, 0);
    Coordinate d(3, 0, 0);
    
    double dist = euclid_dist(c, d);
    XCTAssertEqual(dist, 3.0);
}

- (void)testEuclidDistWithNegativeNumbers {
    Coordinate c(0, 0, 0);
    Coordinate d(-3, 0, 0);
    
    double dist = euclid_dist(c, d);
    XCTAssertEqual(dist, 3.0);
}

- (void)testEuclidDistWithZeros {
    Coordinate c(0, 0, 0);
    Coordinate d(0, 0, 0);
    
    double dist = euclid_dist(c, d);
    XCTAssertEqual(dist, 0.0);
}

@end
