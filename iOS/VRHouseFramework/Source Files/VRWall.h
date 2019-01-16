//
//  VRWall.h
//  VRHouseFramework
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

/// An object that describes a wall.
@interface VRWall: NSObject

/// A start point of the wall according to the coordinates from the source UIImage.
@property (assign, nonatomic) CGPoint startPoint;

/// An end point of the wall according to the coordinates from the source UIImage.
@property (assign, nonatomic) CGPoint endPoint;

/// A distance between start and end point.
@property (assign, nonatomic) CGFloat length;

/**
 Creates and returns a new wall.

 @param startPoint A start point.
 @param endPoint An end point.
 @return The new wall.
 */
- (id)initWithStartPoint:(CGPoint)startPoint endPoint:(CGPoint)endPoint;

@end

NS_ASSUME_NONNULL_END
