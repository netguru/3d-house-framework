//
//  OpenCV.h
//  VRHouseFramework
//

#ifdef __cplusplus
#import <opencv2/opencv.hpp>
#endif

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@interface OpenCV: NSObject

+ (NSString *)openCVVersionString NS_SWIFT_NAME(openCVVersion());

- (CGRect)findCorners:(UIImage *)image;

@end

NS_ASSUME_NONNULL_END
