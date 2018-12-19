//
//  OpenCV.m
//  VRHouseFramework
//

#import "OpenCV.h"
#import "SheetDetection.hpp"
#import <opencv2/imgcodecs/ios.h>

@interface OpenCV ()

@property (assign, nonatomic) SheetDetection sheetDetection;

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

/**
 Returns a corners of found piece of paper on the given UIImage in the clockwise order:
 top-left, top-right, bottom-right, and bottom-left.

 @param image The image to be processed.
 @return Four corners of found piece of paper or an empty array if not found.
 */
- (NSArray<NSValue *>*)findCorners:(UIImage *)image {
    if (image == nil) {
        return @[];
    }

    Mat mat;
    UIImageToMat(image, mat);
    vector<cv::Point> corners = self.sheetDetection.findCorners(mat);

    NSMutableArray *array = [NSMutableArray new];
    for (NSUInteger i = 0; i < corners.size(); i++) {
        [array addObject:[NSValue valueWithCGPoint:CGPointMake(corners[i].x, corners[i].y)]];
    }

    return array;
}

/**
 Crops and applies a perspective transformation to the given UIImage.

 @param source The image to be processed.
 @param topLeft The top left corner.
 @param topRight The top right corner.
 @param bottomLeft The bottom left corner.
 @param bottomRight The bottom right corner.
 @return A cropped UIImage with applied a perspective transformation.
 */
- (UIImage *)cropImage:(UIImage *)source topLeft:(CGPoint)topLeft topRight:(CGPoint)topRight bottomLeft:(CGPoint)bottomLeft bottomRight:(CGPoint)bottomRight {
    Mat mat;
    UIImageToMat(source, mat);
    Mat cropped = self.sheetDetection.cropSelectedArea(mat,
                                                       Point2f((float)topLeft.x, (float)topLeft.y),
                                                       Point2f((float)topRight.x, (float)topRight.y),
                                                       Point2f((float)bottomLeft.x, (float)bottomLeft.y),
                                                       Point2f((float)bottomRight.x, (float)bottomRight.y));

    return MatToUIImage(cropped);
}

@end
