//
//  Wall.m
//  VRHouseFramework
//

#import "Wall.h"

@implementation Wall

-(id)initWithStartPoint:(CGPoint)startPoint endPoint:(CGPoint)endPoint {
    if (self = [super init]) {
        self.startPoint = startPoint;
        self.endPoint = endPoint;
    }

    return self;
}

@end
