//
//  vsPlugin.h
//
//  VS Plugin
//  Copyright (c) 2013 Aumentia. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <CoreVideo/CoreVideo.h>
#import <CoreMedia/CoreMedia.h>
#import "ROI.h"
#import "_vs_versions.h"

#ifndef _vsPlugin
#define _vsPlugin

typedef enum
{
    search_image,
    search_QRcodes,
    search_all
}search_mode;


/**
 *  Optional protocol Called when an Image is recognised within a pool.
 */
@protocol imageMatchedProtocol <NSObject>

@optional

/**
 *  Called when an Image is recognised within a pool.
 *  @param uId Matched Image unique Id.
 */
-(void)imageMatchedResult:(NSInteger)uId ;

@end


/**
 *  Optional callback: Called when a single QR / bar code is recognised.
 *  The supported standarts are:
 
 - UPC-A
 - UPC-E
 - EAN-8
 - EAN-13
 - Code 39
 - Code 93
 - Code 128
 - ITF
 - Codabar
 - RSS-14 (all variants)
 - QR Code
 - Data Matrix
 - Aztec ('beta' quality)
 - PDF 417 ('alpha' quality)
 
 */
@protocol QRMatchedProtocol <NSObject>

@optional
/**
 *  Called when a single QR / bar code is recognised.
 *
 *  @param res Code read string.
 */
-(void)singleQRMatchedResult:(NSString*)res ;

/**
 *  Called when multiple QR / bar codes are recognised.
 *
 *  @param codes Array of found ROIs. Each ROI has a CGRect defining the crop rectangle and the QR string response.
 */
-(void)multipleQRMatchedResult:(NSArray*)codes ;

@end


/**
 * <b>Visual Search Plugin:</b><br>
 * This plugin analyses the input video feed frames looking for matches within the images
 * pools previously inserted. When there is a positive match, the image information will
 * be returned.<br>
 * This plugin support both simultaneously QR, bar code and regular images recongnition.
 *
 */

__attribute__((__visibility__("default"))) @interface vsPlugin : UIViewController
{
    
}

/** @name Add Images */

/**
 * @brief Add image to the system. The system will generate an automatic unique id.
 *
 * @param image The image to be added to the system.
 *
 * @return Image unique identifier, -1 if image is not added to the system ( does not have enough features ).
 */
- (NSInteger) insertImage:(UIImage*)image vs_AVAILABLE(vs_V_0_1_1);

/**
 * @brief Add image to the system directly from URL. The system will generate an automatic unique id.
 *
 * @param imageUrl URL that holds the image to be added to the system.
 *
 * @return Image unique identifier, -1 if image is not added to the system ( does not have enough features or has not been downloaded properly).
 */
- (NSInteger) insertImageFromURL:(NSURL*)imageUrl vs_AVAILABLE(vs_V_0_1_1);

/**
 * @brief Add image to the system. The user specifies the image unique id.
 *
 * @param image The image to be added to the system.
 *
 * @param uId The image identifier defined by the user. Must be unique.
 *
 *  @return YES if the image has been successfully inserted, NO otherwise ( does not have enough features or the id is not unique).
 */
- (BOOL) insertImage:(UIImage*)image withId:(NSInteger)uId vs_AVAILABLE(vs_V_0_1_1);

/**
 * @brief Add image to the system directly from URL. The user specifies the image unique id.
 *
 * @param imageUrl Url that holds the image to be added to the system.
 *
 * @param uId The image identifier defined by the user. Must be unique.
 *
 * @return YES if the image has been successfully inserted, NO otherwise ( does not have enough features,
 * has not been downloaded properly or the id is not unique).
 */
- (BOOL) insertImageFromURL:(NSURL*)imageUrl withId:(NSInteger)uId vs_AVAILABLE(vs_V_0_1_1);



/** @name Remove Images */

/**
 *  @brief Delete image from the system.
 *
 *  @param uId Image unique id.
 *
 *  @return YES if the image has been properly deleted, NO otherwise.
 */
- (BOOL) deleteImage:(NSInteger)uId vs_AVAILABLE(vs_V_0_1_1);

/**
 *  @brief Remove all the image from the system.
 *
 *  @return YES if all images properly deleted, NO otherwise.
 *
 */
- (BOOL) deleteAllImages vs_AVAILABLE(vs_V_0_1_1);



/** @name Process Images / Frames */

/**
 *  @brief Process an UIImage and look for positive matches against any image added to the system or read QR / bar codes.
 *
 *  @param image Input image to be analysed.
 *
 *  @param saveImageToPhotoAlbum Save Image to the device photo album after resize and crop. Set to YES this flag in order to check out the frame is being sent to the recognition process.
 */
- (void) processUIImage:(UIImage* )image saveImageToPhotoAlbum:(BOOL)saveImageToPhotoAlbum vs_AVAILABLE(vs_V_0_1_1);

/**
 *  @brief Process an image buffer and look for positive matches against any image added to the system or read QR / bar codes.
 *  Camera output settings should be either <b>kCVPixelFormatType_420YpCbCr8BiPlanarFullRange</b> or <b>kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange</b>
 *
 *  @param imageBuffer Image buffer input to be analysed.
 *
 *  @param saveImageToPhotoAlbum Save Image to the device photo album after resize and crop. Set to YES this flag in order to check out the frame is being sent to the recognition process.
 */
- (void)processYUVFrame:(CVImageBufferRef)imageBuffer saveImageToPhotoAlbum:(BOOL)saveImageToPhotoAlbum vs_AVAILABLE(vs_V_0_1_1);

/**
 *  @brief Process an image buffer and look for positive matches against any image added to the system or read QR / bar codes.
 *  Camera output settings should be <b>kCVPixelFormatType_32BGRA</b>
 *
 *  @param imageBuffer Image buffer input to be analysed.
 *
 *  @param saveImageToPhotoAlbum Save Image to the device photo album after resize and crop. Set to YES this flag in order to check out the frame is being sent to the recognition process.
 */
- (void)processRGBFrame:(CVImageBufferRef)imageBuffer saveImageToPhotoAlbum:(BOOL)saveImageToPhotoAlbum vs_AVAILABLE(vs_V_0_1_1);



/** @name Init and Config Params */

/**
 * @brief Init the visual search plugin
 *
 * @param key License Key
 *
 * @param isDebug Activate debug logs.
 */
- (id)initWithKey:(NSString *)key setDebug:(BOOL)isDebug vs_AVAILABLE(vs_V_0_1_1);

/**
 *  @brief Set the engine search mode: look for regular images, look for QR / bar codes or look for all.
 *
 *  @param smode Search_image (Look for regular images)<br>  Search_QRcodes (Look for QR / bar code)<br> Search_all (Both image and QR / bar code matching. (default option)).
 */
- (void) setSearchMode:(search_mode)smode vs_AVAILABLE(vs_V_0_1_1);

/**
 *  @brief The images added to the system receive a punctuation between 0 and 10 indicating
 *  how "rich" is the image (amounf of good features for matching). The more close to 10, easier
 *  is to match the image and more difficult is to get a false positive.
 *  Setting this param, the user decides the minimum quality of his pool of images.
 *
 *  @param score Puntuation between (0-10) 0 almost any image will be inserted, 10 only the most feature-rich images will be inserted.
 *  <b>default threshold value is 5</b>
 */
- (void) setMatchingThreshold:(NSInteger)score vs_AVAILABLE(vs_V_0_1_1);

/**
 * @brief   Get image punctuation, meaning the image quality.
 *
 * @param   image Input image to be analyzed.
 *
 * @return  Quality score.
 */
- (NSInteger)getImageScore:(UIImage*)image vs_AVAILABLE(vs_V_0_1_1);



/** @name QR / BAR Codes */

/**
 *  @brief Add a target rect or region of interest to look for QR / bar codes.
 *  If you define several rects, you will be able to read several QR / bar codes a time.
 *
 *  @param frame the target region of interest.
 *
 *  @return YES if target rect successfully defined, NO other wise (rect does not fit in the image or it overlaps other already defined rect).
 */
- (BOOL) addQRRect:(Roi*)frame vs_AVAILABLE(vs_V_0_1_1);

/**
 *  @brief Remove al target rects.
 *
 */
- (void) clearAllQRRects vs_AVAILABLE(vs_V_0_1_1);


/** @name Motion Filter */

/**
 *  @brief Enable Motion Detection filter: the engine will not search if the device is moving. This option makes it more difficult to get false positives.
 *
 */
- (void)initMotionDetection vs_AVAILABLE(vs_V_0_1_1);

/**
 *  @brief Disable Motion Detection filter.
 *
 */
- (void)removeMotionDetection vs_AVAILABLE(vs_V_0_1_1);



/** @name Properties */

/**
 *  @brief Crop rect: The system will crop the input image / frame and perform the search over that cropped area.
 *  <b>Default (0 ,0 ,0 ,0) No cropping.</b>
 */
@property (assign, nonatomic) CGRect ImageCropRect vs_AVAILABLE(vs_V_0_1_1);

/**
 *  @brief Frame Size: The input frame & added images height or width (max(w,h)) will be resized to this value. Higher sizes will improve the macthing and low the speed.
 *  <b>Default 250px.</b>
 */
@property (assign, nonatomic) NSInteger frameSize vs_AVAILABLE(vs_V_0_1_1);

/**
 *  @brief Minimum amount of features accepted to insert an image in the system.<br>
 *  The higher it is the most feature-rich images will be required to be inserted.<br>
 *  This value is related with the threshold: the higher the most restrictive the threshold will be.<br>
 *  <b>Default value is 50.</b>
 */
@property (assign, nonatomic, setter = setMinFeatures:, getter = getMinFeatures) NSInteger MinFeatures vs_AVAILABLE(vs_V_0_1_1);

/**
 *  @brief Maximum amount of features accepted to match an image.<br>
 *  When an image / frame is going to be matched against the images already inserted in the system, the engine
 *  extract the best features and compares them with the ones of the images in the system.
 *  The higher it is the most features will be accepted in the matching process.<br>
 *  The higher it is the better will be the matching quality but the matching speed will be reduced.<br>
 *  <b>Default value is 50.</b>
 */
@property (assign, nonatomic, setter = setMaxFeatures:, getter = getMaxFeatures) NSInteger MaxFeatures vs_AVAILABLE(vs_V_0_1_1);

/**
 *  @brief Protocol delegate.
 */
@property (weak, nonatomic) id <imageMatchedProtocol> imageDelegate vs_AVAILABLE(vs_V_0_1_1);

/**
 *  @brief Protocol delegate.
 */
@property (weak, nonatomic) id <QRMatchedProtocol> QRDelegate vs_AVAILABLE(vs_V_0_1_1);


@end

#endif