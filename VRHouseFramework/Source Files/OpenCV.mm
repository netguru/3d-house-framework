//
//  OpenCV.m
//  VRHouseFramework
//

#import "OpenCV.h"
#import "SheetDetection.hpp"

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
 Returns a corners of found piece of paper on the given UIImage.

 @param image The image to be processed.
 @return Four corners of founf piece of paper or an empty array if not found.
 */
- (NSArray<NSValue *>*)findCorners:(UIImage *)image {
    if (image == nil) {
        return @[];
    }

    Mat mat = [self cvMatWithImage:image];
    vector<Point2f> corners = self.sheetDetection.findCorners(mat);

    NSMutableArray *array = [NSMutableArray new];
    for (NSUInteger i = 0; i < corners.size(); i++) {
        [array addObject:[NSValue valueWithCGPoint:CGPointMake(corners[i].x, corners[i].y)]];
    }

    return array;
}

/**
 Returns a Mat based on the given UIImage.

 @param image The image to be used to create a Mat.
 @return The Mat object created from the given UIImage.
 */
- (cv::Mat)cvMatWithImage:(UIImage *)image {
    CGColorSpaceRef colorSpace = CGImageGetColorSpace(image.CGImage);
    size_t numberOfComponents = CGColorSpaceGetNumberOfComponents(colorSpace);
    int cols = int(image.size.width);
    int rows = int(image.size.height);

    cv::Mat cvMat(rows, cols, CV_8UC4); // 8 bits per component, 4 channels
    CGBitmapInfo bitmapInfo = kCGImageAlphaNoneSkipLast | kCGBitmapByteOrderDefault;

    // check whether the UIImage is greyscale already
    if (numberOfComponents == 1) {
        cvMat = cv::Mat(rows, cols, CV_8UC1); // 8 bits per component, 1 channels
        bitmapInfo = kCGImageAlphaNone | kCGBitmapByteOrderDefault;
    }

    CGContextRef contextRef = CGBitmapContextCreate(cvMat.data,        // Pointer to backing data
                                                    cols,              // Width of bitmap
                                                    rows,              // Height of bitmap
                                                    8,                 // Bits per component
                                                    cvMat.step[0],     // Bytes per row
                                                    colorSpace,        // Colorspace
                                                    bitmapInfo);       // Bitmap info flags

    CGContextDrawImage(contextRef, CGRectMake(0, 0, cols, rows), image.CGImage);
    CGContextRelease(contextRef);

    return cvMat;
}

@end
