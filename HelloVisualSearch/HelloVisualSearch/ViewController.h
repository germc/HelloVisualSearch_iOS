//
//  ViewController.h
//  HelloVisualSearch
//
//  Copyright (c) 2013 Aumentia. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <VS/vsPlugin.h>
#import "CaptureSessionManager.h"

@interface ViewController : UIViewController<imageMatchedProtocol, QRMatchedProtocol, CameraCaptureDelegate>

@end
