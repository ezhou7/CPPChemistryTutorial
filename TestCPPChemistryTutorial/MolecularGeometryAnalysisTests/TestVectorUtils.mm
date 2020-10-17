//
//  TestVectorUtils.m
//  TestCPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/17/20.
//

#import <XCTest/XCTest.h>

#import "TestUtils.h"

#import "vectorutils.hpp"

@interface TestVectorUtils : XCTestCase

@end

@implementation TestVectorUtils

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testMultiply {
    vector<int> v{1, 2, 3, 4, 5};
    int total = multiply(v);
    XCTAssertEqual(total, 120);
}

- (void)testCumulativeMultiply {
    vector<int> v{1, 2, 3, 4, 5};
    unique_ptr<vector<int>> cum_v = cum_multiply(v);

    XCTAssertEqual((*cum_v)[0], 1);
    XCTAssertEqual((*cum_v)[1], 2);
    XCTAssertEqual((*cum_v)[2], 6);
    XCTAssertEqual((*cum_v)[3], 24);
    XCTAssertEqual((*cum_v)[4], 120);
}

@end
