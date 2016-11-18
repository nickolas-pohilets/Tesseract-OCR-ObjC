//
//  G8Image.h
//  Tesseract OCR iOS
//
//  Created by Nickolas Pohilets on 17.11.16.
//  Copyright © 2016 Daniele Galiotto - www.g8production.com. All rights reserved.
//

#include "TargetConditionals.h"

#if !TARGET_OS_OSX
#import <UIKit/UIKit.h>
#define G8Image UIImage
#define G8Color UIColor
#else
#import <AppKit/AppKit.h>
#define G8Image NSImage
#define G8Color NSColor
#endif
