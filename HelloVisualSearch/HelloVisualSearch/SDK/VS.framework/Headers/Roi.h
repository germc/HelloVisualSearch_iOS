//
//  Roi.h
//  ARBarReader
//
//  Copyright (c) 2012 VPS. All rights reserved.
//  Version 0.1
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface Roi : NSObject

@property (assign, nonatomic) CGRect roiRect;
@property (strong, nonatomic) NSString* qrString;

-(id)initWithRect:(CGRect)rect;

@end
