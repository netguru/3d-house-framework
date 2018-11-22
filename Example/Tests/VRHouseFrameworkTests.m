//
//  VRHouseFrameworkTests.m
//  VRHouseFrameworkTests
//

@import XCTest;
#import "OpenCV.h"

@interface VRHouseFrameworkTests: XCTestCase

@end

@implementation VRHouseFrameworkTests

- (void)testVersionString {
    NSString *version = [OpenCV openCVVersionString];
    NSString *prefix = [version substringToIndex:14];
    NSString *number = [version substringFromIndex:15];
    XCTAssert([prefix isEqualToString:@"OpenCV Version"]);

    NSCharacterSet *notAllowedCharactersInVersionNumber = [[NSCharacterSet characterSetWithCharactersInString:@"1234567890."] invertedSet];
    XCTAssertEqual([number rangeOfCharacterFromSet:notAllowedCharactersInVersionNumber].location, NSNotFound);
}

@end
