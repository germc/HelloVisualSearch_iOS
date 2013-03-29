//
//  Roi.h
//
//  VS Plugin
//  Copyright (c) 2013 Aumentia. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 *  Region of interest.
 *  A maximum of 4 can be defined.
 *  The engine will look for QR / bar codes in the defined areas.
 */
@interface Roi : NSObject


/**
 *  @brief: Initialise a Region of Interest.
 *
 *  @param rect Frame that defines the ROI.
 */
-(id)initWithRect:(CGRect)rect;


/**
 * Frame that defines the ROI.
 */
@property (assign, nonatomic) CGRect roiRect;

/**
 * String read from the QR / bar code.
 */
@property (strong, readonly) NSString* qrString;

@end