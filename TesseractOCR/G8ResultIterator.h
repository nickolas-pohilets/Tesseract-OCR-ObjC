//
//  G8ResultIterator.h
//  TesseractOCR
//
//  Created by Nickolas Pohilets on 26.11.16.
//  Copyright © 2016 Daniele Galiotto - www.g8production.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "G8Constants.h"

@interface G8ResultIterator : NSObject

- (void)restartPage;
- (void)restartParagraph;
- (void)restartRow;

- (BOOL)isEmpty:(G8PageIteratorLevel)level;
- (BOOL)moveNext:(G8PageIteratorLevel)level;

- (NSComparisonResult)compare:(G8ResultIterator*)other;

- (CGRect)boundingBox:(G8PageIteratorLevel)level;
- (BOOL)getBaseline:(G8PageIteratorLevel)level from:(CGPoint*)from to:(CGPoint*)to;

// -- Row attributes ------

@property(nonatomic, readonly) CGFloat xHeight;
@property(nonatomic, readonly) CGFloat rowHeight;
@property(nonatomic, readonly) CGFloat descender;
@property(nonatomic, readonly) CGFloat ascender;

- (NSString*)text:(G8PageIteratorLevel)level;

@end
