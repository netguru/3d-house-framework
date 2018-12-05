//
//  OpenCV.h
//  VRHouseFramework
//

#ifdef __OBJC__
#import <UIKit/UIKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@interface OpenCV: NSObject

+ (NSString *)openCVVersionString NS_SWIFT_NAME(openCVVersion());

- (NSArray<NSValue *>*)findCorners:(UIImage *)image;

@end

NS_ASSUME_NONNULL_END
