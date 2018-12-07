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
    XCTAssertEqual(point1.x, 611);
    XCTAssertEqual(point1.y, 374);

    CGPoint point2 = array[1].CGPointValue;
    XCTAssertEqual(point2.x, 2628);
    XCTAssertEqual(point2.y, 406);

    CGPoint point3 = array[2].CGPointValue;
    XCTAssertEqual(point3.x, 2723);
    XCTAssertEqual(point3.y, 3501);

    CGPoint point4 = array[3].CGPointValue;
    XCTAssertEqual(point4.x, 291);
    XCTAssertEqual(point4.y, 3366);
}

- (void)testFindCornersFailureNil {
    UIImage *image = nil;
    NSArray<NSValue *>*array = [self.sut findCorners:image];

    XCTAssertEqual(array.count, 0);
}

@end
