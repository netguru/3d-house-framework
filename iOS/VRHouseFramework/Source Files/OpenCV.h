//
//  OpenCV.h
//  VRHouseFramework
//

#ifdef __OBJC__
#import <UIKit/UIKit.h>
#import "VRWall.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/**
 An OpenCV wrapper.
 */
@interface OpenCV: NSObject

/**
 Returns the current OpenCV version string.

 @return The current OpenCV version string.
 */
+ (NSString *)openCVVersionString NS_SWIFT_NAME(openCVVersion());

/**
 Returns a corners of found piece of paper on the given UIImage in the clockwise order:
 top-left, top-right, bottom-right, and bottom-left.

 @param image The image to be processed.
 @return Four corners of found piece of paper or an empty array if not found.
 */
- (NSArray<NSValue *>*)findCorners:(UIImage *)image;

/**
 Crops and applies a perspective transformation to the given UIImage.

 @param source The image to be processed.
 @param topLeft The top left corner.
 @param topRight The top right corner.
 @param bottomLeft The bottom left corner.
 @param bottomRight The bottom right corner.
 @return A cropped UIImage with applied a perspective transformation.
 */
- (UIImage *)cropImage:(UIImage *)source topLeft:(CGPoint)topLeft topRight:(CGPoint)topRight bottomLeft:(CGPoint)bottomLeft bottomRight:(CGPoint)bottomRight;

/**
 Returns walls found on the given UIImage.

 @param image The image to be processed.
 @return Found walls or an empty array if not found.
 */
- (NSArray<VRWall *>*)findWalls:(UIImage *)image;

@end

NS_ASSUME_NONNULL_END
