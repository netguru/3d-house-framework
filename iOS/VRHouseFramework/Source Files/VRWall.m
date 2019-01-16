//
//  VRWall.m
//  VRHouseFramework
//

#import "VRWall.h"

@implementation VRWall

- (id)initWithStartPoint:(CGPoint)startPoint endPoint:(CGPoint)endPoint {
    if (self = [super init]) {
        self.startPoint = startPoint;
        self.endPoint = endPoint;
    }

    return self;
}

- (CGFloat)length {
    return (CGFloat)(hypot(self.startPoint.x - self.endPoint.x, self.startPoint.y - self.endPoint.y));
}

@end
