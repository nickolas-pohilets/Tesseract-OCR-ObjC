//
//  G8ResultIterator.h
//  TesseractOCR
//
//  Created by Nickolas Pohilets on 26.11.16.
//  Copyright © 2016 Daniele Galiotto - www.g8production.com. All rights reserved.
//

#import "G8ResultIterator.h"
#import "resultiterator.h"

@interface G8ResultIterator()

- (instancetype)initWithIterator:(tesseract::ResultIterator*)it;

@end
