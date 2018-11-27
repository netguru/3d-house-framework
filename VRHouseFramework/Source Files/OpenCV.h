//
//  OpenCV.h
//  VRHouseFramework
//

#ifdef __cplusplus
#undef NO
#undef YES
#import <opencv2/opencv.hpp>
#import <opencv2/core/core.hpp>
#import <opencv2/imgcodecs/ios.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@interface OpenCV: NSObject

+ (NSString *)openCVVersionString NS_SWIFT_NAME(openCVVersion());

@end

NS_ASSUME_NONNULL_END
