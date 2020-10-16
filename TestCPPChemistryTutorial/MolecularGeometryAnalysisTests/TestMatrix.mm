//
//  TestMatrix.mm
//  TestCPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/15/20.
//

#import <XCTest/XCTest.h>

#include "matrix.hpp"

@interface TestMatrix : XCTestCase

@end

@implementation TestMatrix

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testMatrix0D {
    // TODO: should not be allowed
    Matrix<> matrix();
}

- (void)testMatrix1D {
    Matrix<int> matrix(2);

    XCTAssertEqual(matrix.get(0), 0);
    XCTAssertEqual(matrix.get(1), 0);
}

- (void)testMatrix2D {
    Matrix<int, int> matrix(2, 2);

    XCTAssertEqual(matrix.get(0, 0), 0);
    XCTAssertEqual(matrix.get(0, 1), 0);
    XCTAssertEqual(matrix.get(1, 0), 0);
    XCTAssertEqual(matrix.get(1, 1), 0);
}

- (void)testMatrix3D {
    Matrix<int, int, int> matrix(2, 2, 2);

    XCTAssertEqual(matrix.get(0, 0, 0), 0);
    XCTAssertEqual(matrix.get(0, 0, 1), 0);
    XCTAssertEqual(matrix.get(0, 1, 0), 0);
    XCTAssertEqual(matrix.get(0, 1, 1), 0);
    XCTAssertEqual(matrix.get(1, 0, 0), 0);
    XCTAssertEqual(matrix.get(1, 0, 1), 0);
    XCTAssertEqual(matrix.get(1, 1, 0), 0);
    XCTAssertEqual(matrix.get(1, 1, 1), 0);
}

@end
