//
//  TestUtils.h
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/16/20.
//

#ifndef TestUtils_h
#define TestUtils_h

#import <Foundation/Foundation.h>

#import <stdexcept>

#define XCTAssertCppThrows(expression, ...) \
XCTAssertThrows([TestUtils rethrowNSExceptionForCppException: ^{expression;}], __VA_ARGS__)

@interface NSCppException : NSException

@end

@interface TestUtils : NSObject

+ (void)rethrowNSExceptionForCppException: (void(^)()) action;

@end

#endif /* TestUtils_h */
