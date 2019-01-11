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
    XCTAssertEqual(point1.x, 606);
    XCTAssertEqual(point1.y, 364);

    CGPoint point2 = array[1].CGPointValue;
    XCTAssertEqual(point2.x, 2635);
    XCTAssertEqual(point2.y, 400);

    CGPoint point3 = array[2].CGPointValue;
    XCTAssertEqual(point3.x, 2727);
    XCTAssertEqual(point3.y, 3506);

    CGPoint point4 = array[3].CGPointValue;
    XCTAssertEqual(point4.x, 283);
    XCTAssertEqual(point4.y, 3373);
}

- (void)testFindCornersFailureNil {
    UIImage *image = nil;
    NSArray<NSValue *>*array = [self.sut findCorners:image];

    XCTAssertEqual(array.count, 0);
}

- (void)testCrop {
    UIImage *image = [UIImage imageNamed:@"paper.jpg"
                                inBundle:[NSBundle bundleForClass:[self class]]
           compatibleWithTraitCollection:nil];

    CGPoint topLeft = CGPointMake(606, 364);
    CGPoint topRight = CGPointMake(2635, 400);
    CGPoint bottomLeft = CGPointMake(283, 3373);
    CGPoint bottomRight = CGPointMake(2727, 3506);

    UIImage *croppedImage = [self.sut cropImage:image topLeft:topLeft topRight:topRight bottomLeft:bottomLeft bottomRight:bottomRight];

    XCTAssertNotNil(croppedImage);
    XCTAssertEqual(croppedImage.size.width, 2614);
    XCTAssertEqual(croppedImage.size.height, 3226);
}

@end
