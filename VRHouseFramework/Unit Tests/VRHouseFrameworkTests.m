//
//  VRHouseFrameworkTests.m
//  VRHouseFrameworkTests
//

@import XCTest;
#import <VRHouseFramework/OpenCV.h>

@interface VRHouseFrameworkTests: XCTestCase

@property (strong, nonatomic) OpenCV *sut;

@end

@implementation VRHouseFrameworkTests

- (void)setUp {
    [super setUp];
    self.sut = [OpenCV new];
}

- (void)tearDown {
    [super tearDown];
    self.sut = nil;
}

- (void)testVersionString {
    NSString *version = [OpenCV openCVVersionString];
    NSString *prefix = [version substringToIndex:14];
    NSString *number = [version substringFromIndex:15];
    XCTAssert([prefix isEqualToString:@"OpenCV Version"]);

    NSCharacterSet *notAllowedCharactersInVersionNumber = [[NSCharacterSet characterSetWithCharactersInString:@"1234567890."] invertedSet];
    XCTAssertEqual([number rangeOfCharacterFromSet:notAllowedCharactersInVersionNumber].location, NSNotFound);
}

- (void)testFindCornersSuccess {
    UIImage *image = [UIImage imageNamed:@"paper.jpg"
                                inBundle:[NSBundle bundleForClass:[self class]]
           compatibleWithTraitCollection:nil];

    NSArray<NSValue *>*array = [self.sut findCorners:image];

    XCTAssertEqual(array.count, 4);

    CGPoint point1 = array[0].CGPointValue;
    XCTAssertEqualWithAccuracy(point1.x, 2728, 1.0);
    XCTAssertEqualWithAccuracy(point1.y, 3507, 1.0);

    CGPoint point2 = array[1].CGPointValue;
    XCTAssertEqualWithAccuracy(point2.x, 287, 1.0);
    XCTAssertEqualWithAccuracy(point2.y, 3376, 1.0);

    CGPoint point3 = array[2].CGPointValue;
    XCTAssertEqualWithAccuracy(point3.x, 452, 1.0);
    XCTAssertEqualWithAccuracy(point3.y, 287, 1.0);

    CGPoint point4 = array[3].CGPointValue;
    XCTAssertEqualWithAccuracy(point4.x, 2894, 1.0);
    XCTAssertEqualWithAccuracy(point4.y, 417, 1.0);
}

- (void)testFindCornersFailureNil {
    UIImage *image = nil;
    NSArray<NSValue *>*array = [self.sut findCorners:image];

    XCTAssertEqual(array.count, 0);
}

@end
