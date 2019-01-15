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

@end
