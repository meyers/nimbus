//
// Copyright 2011 Jeff Verkoeyen
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#ifdef NIMBUS_STATIC_LIBRARY
#import "ASIHTTPRequest/NIHTTPRequest.h"
#import "NimbusNetworkImage/NINetworkImageView.h"
#else
#import "NIHTTPRequest.h"
#import "NINetworkImageView.h"  // For NINetworkImageViewScaleOptions
#endif

/**
 * A threaded network request for an image that chops up and resizes the image before returning
 * to the UI thread.
 *
 *      @ingroup Network-Image-Requests
 */
@interface NIHTTPImageRequest : NIHTTPRequest {
@private
  CGRect _imageCropRect;
  CGSize _imageDisplaySize;

  NINetworkImageViewScaleOptions _scaleOptions;
  CGInterpolationQuality         _interpolationQuality;

  UIViewContentMode _imageContentMode;

  UIImage* _imageCroppedAndSizedForDisplay;
}

#pragma mark Before request is sent to the queue

/**
 * x/y, width/height are in percent coordinates.
 * Valid range is [0..1] for all values.
 *
 * Examples:
 *
 * CGRectZero - Do not crop this image.
 * CGRect(0, 0, 1, 1) - Do not crop this image.
 *
 * The default value is CGRectZero
 */
@property (assign) CGRect imageCropRect;

/**
 * The size of the image to be displayed on the screen. This is the final size that
 * imageCroppedAndSizedForDisplay will be, unless cropImageForDisplay is NO.
 *
 * If this is CGSizeZero, the image will not be resized. It will bereturned at its original size.
 *
 * The default value is CGSizeZero
 */
@property (assign) CGSize imageDisplaySize;

/**
 * Options for modifying the way images are cropped when scaling.
 *
 *      @see NINetworkImageViewScaleOptions
 *
 * The default value is NINetworkImageViewScaleToFitLeavesExcessAndScaleToFillCropsExcess.
 */
@property (assign) NINetworkImageViewScaleOptions scaleOptions;

/**
 * The interpolation quality to use when resizing the image.
 *
 * The default value is kCGInterpolationDefault.
 */
@property (assign) CGInterpolationQuality interpolationQuality;

/**
 * Determines how to resize and crop the image.
 *
 * Supported content modes:
 *
 *  - UIViewContentModeScaleToFill
 *  - UIViewContentModeScaleAspectFill
 *
 * The default value is UIViewContentModeScaleToFill
 */
@property (assign) UIViewContentMode imageContentMode;


/**
 * @name After request completion
 * @{
 *
 * The following methods are provided to aid in subclassing and are not meant to be
 * used externally.
 */
#pragma mark After request completion

/**
 * Upon completion of the request, this is the chopped and sized result image that should be
 * used for display.
 */
@property (retain) UIImage* imageCroppedAndSizedForDisplay;

/**@}*/// End of After request completion

@end


@interface NIHTTPImageRequest (ImageModifications)

/**
 * Take a source image and resize and crop it according to a set of display properties.
 *
 * On devices with retina displays, the resulting image will be returned at the correct
 * resolution for the device.
 *
 * This method is exposed to allow other image operations to generate cropped and resized
 * images as well.
 *
 *      @param src                  The source image.
 *      @param contentMode          The content mode to use when cropping and resizing the image.
 *      @param cropRect             An initial crop rect to apply to the src image.
 *      @param displaySize          The requested display size for the image. The resulting image
 *                                  may or may not match these dimensions depending on the scale
 *                                  options being used.
 *      @param scaleOptions         See the NINetworkImageViewScaleOptions documentation for more
 *                                  details.
 *      @param interpolationQuality The interpolation quality to use when resizing the image.
 *
 *      @returns The resized and cropped image.
 */
+ (UIImage *)imageFromSource: (UIImage *)src
             withContentMode: (UIViewContentMode)contentMode
                    cropRect: (CGRect)cropRect
                 displaySize: (CGSize)displaySize
                scaleOptions: (NINetworkImageViewScaleOptions)scaleOptions
        interpolationQuality: (CGInterpolationQuality)interpolationQuality;

@end

