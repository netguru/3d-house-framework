//
//  OpenCV.h
//  VRHouseFramework
//

#ifdef __OBJC__
#import <UIKit/UIKit.h>
#endif

@class Wall;

NS_ASSUME_NONNULL_BEGIN

@interface OpenCV: NSObject

+ (NSString *)openCVVersionString NS_SWIFT_NAME(openCVVersion());

- (NSArray<NSValue *>*)findCorners:(UIImage *)image;

- (UIImage *)cropImage:(UIImage *)source topLeft:(CGPoint)topLeft topRight:(CGPoint)topRight bottomLeft:(CGPoint)bottomLeft bottomRight:(CGPoint)bottomRight;

- (NSArray<Wall *> *)findWalls:(UIImage *)image;

@end

NS_ASSUME_NONNULL_END
