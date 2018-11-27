//
//  OpenCV.m
//  VRHouseFramework
//

#import "OpenCV.h"

/**
 An OpenCV wrapper.
 */
@implementation OpenCV

/**
 Returns the current OpenCV version string.

 @return The current OpenCV version string.
 */
+ (NSString *)openCVVersionString {
    return [NSString stringWithFormat:@"OpenCV Version %s", CV_VERSION];
}

@end
