//
//  TestMatrix.mm
//  TestCPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/15/20.
//

#import <XCTest/XCTest.h>

#include <stdexcept>

#include "matrix.hpp"

#define XCTAssertCppThrows(expression, ...) \
XCTAssertThrows([self rethrowNSExceptionForCppException: ^{expression;}], __VA_ARGS__)

@interface IndexOutOfBoundsException : NSException

@end

@implementation IndexOutOfBoundsException

- (id)init: (std::exception) cppException {
    NSString *message = [NSString stringWithUTF8String:cppException.what()];
    return [self initWithName:@"cppException" reason:message userInfo:nil];
}

@end

@interface TestMatrix : XCTestCase

@end

@implementation TestMatrix

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)rethrowNSExceptionForCppException: (void(^)()) action {
    try {
        action();
    } catch (const std::exception& e) {
        @throw [[IndexOutOfBoundsException alloc] init:e];
    }
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

- (void)testMatrixGetAndSet {
    Matrix<int, int> matrix(2, 2);
    matrix.set(-1, 0, 0);
    matrix.set(-2, 0, 1);
    matrix.set(-3, 1, 0);
    matrix.set(-4, 1, 1);
    
    XCTAssertEqual(matrix.get(0, 0), -1);
    XCTAssertEqual(matrix.get(0, 1), -2);
    XCTAssertEqual(matrix.get(1, 0), -3);
    XCTAssertEqual(matrix.get(1, 1), -4);
}

- (void)testMatrixIndexOutOfBounds {
    auto matrix = shared_ptr<Matrix<int, int>>(new Matrix<int, int>(2, 2));
    XCTAssertCppThrows(matrix->get(-1, -1));
}

@end
