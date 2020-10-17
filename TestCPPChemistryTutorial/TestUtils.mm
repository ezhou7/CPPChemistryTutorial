//
//  TestUtils.m
//  TestCPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/16/20.
//

#import "TestUtils.h"

@implementation NSCppException

- (id)init: (std::exception) cppException {
    NSString *message = [NSString stringWithUTF8String:cppException.what()];
    return [self initWithName:@"cppException" reason:message userInfo:nil];
}

@end

@implementation TestUtils

+ (void)rethrowNSExceptionForCppException: (void(^)()) action {
    try {
        action();
    } catch (const std::exception& e) {
        @throw [[NSCppException alloc] init:e];
    }
}

@end
