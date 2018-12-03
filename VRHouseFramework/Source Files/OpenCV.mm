//
//  OpenCV.m
//  VRHouseFramework
//

#import "OpenCV.h"
#import "SheetDetection.hpp"

@interface OpenCV ()

@property (nonatomic) SheetDetection sheetDetection;

@end

/**
 An OpenCV wrapper.
 */
@implementation OpenCV

- (id)init {
    if (self = [super init]) {
        self.sheetDetection = *(new SheetDetection);
    }

    return self;
}

/**
 Returns the current OpenCV version string.

 @return The current OpenCV version string.
 */
+ (NSString *)openCVVersionString {
    return [NSString stringWithFormat:@"OpenCV Version %s", CV_VERSION];
}

- (CGRect)findCorners:(UIImage *)image {
    return CGRectMake(0, 0, 0, 0);
}

@end
