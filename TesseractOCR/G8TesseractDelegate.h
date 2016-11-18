//
//  G8TesseractDelegate.h
//  Tesseract OCR iOS
//
//  Created by Nikolay Volosatov on 25.12.14.
//  Copyright (c) 2014 Daniele Galiotto - www.g8production.com. All rights reserved.
//

#ifndef Tesseract_OCR_iOS_G8TesseractDelegate_h
#define Tesseract_OCR_iOS_G8TesseractDelegate_h

#import "G8Image.h"

@class G8Tesseract;

/**
 *  `G8TesseractDelegate` provides delegate methods for Tesseract recognition.
 */
@protocol G8TesseractDelegate <NSObject>

@optional

/**
 *  An optional method to be called periodically during recognition so
 *  the recognition's progress can be observed.
 *
 *  @param tesseract The `G8Tesseract` object performing the recognition.
 */
- (void)progressImageRecognitionForTesseract:(G8Tesseract *)tesseract;

/**
 *  An optional method to be called periodically during recognition so
 *  the user can choose whether or not to cancel recognition.
 *
 *  @param tesseract The `G8Tesseract` object performing the recognition.
 *
 *  @return Whether or not to cancel the recognition in progress.
 */
- (BOOL)shouldCancelImageRecognitionForTesseract:(G8Tesseract *)tesseract;

/**
 *  An optional method to provide image preprocessing. To perform default
 *  Tesseract preprocessing return `nil` in this method.
 *
 *  @param tesseract   The `G8Tesseract` object performing the recognition.
 *  @param sourceImage The source `UIImage` to perform preprocessing.
 *
 *  @return Preprocessed `UIImage` or nil to perform default preprocessing.
 */
- (G8Image *)preprocessedImageForTesseract:(G8Tesseract *)tesseract sourceImage:(G8Image *)sourceImage;

@end

#endif
