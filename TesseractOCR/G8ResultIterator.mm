//
//  G8ResultIterator.m
//  TesseractOCR
//
//  Created by Nickolas Pohilets on 26.11.16.
//  Copyright © 2016 Daniele Galiotto - www.g8production.com. All rights reserved.
//

#import "G8ResultIterator.h"
#import "G8ResultIterator-Private.h"

@implementation G8ResultIterator
{
    tesseract::ResultIterator *_it;
    float _rowHeight;
    float _descender;
    float _ascender;
}

- (instancetype)initWithIterator:(tesseract::ResultIterator*)it {
    if ((self = [super init])) {
        _it = it;
        [self resetAttributes];
    }
    return self;
}

- (void)dealloc {
    delete _it;
}

- (void)restartPage {
    [self resetAttributes];
    _it->Begin();
}

- (void)restartParagraph {
    [self resetAttributes];
    _it->RestartParagraph();
}

- (void)restartRow {
    [self resetAttributes];
    _it->RestartRow();
}

- (bool)moveNext:(G8PageIteratorLevel)level {
    [self resetAttributes];
    return _it->Next((tesseract::PageIteratorLevel)level);
}

- (NSComparisonResult)compare:(G8ResultIterator*)other {
    int r = _it->Cmp(*other->_it);
    if (r < 0)
        return NSOrderedAscending;
    if (r > 0)
        return NSOrderedDescending;
    return NSOrderedSame;
}

- (CGRect)boundingBox:(G8PageIteratorLevel)level {
    int x1, y1, x2, y2;
    _it->BoundingBox((tesseract::PageIteratorLevel)level, &x1, &y1, &x2, &y2);
    return CGRectMake(x1, y1, x2 - x1, y2 - y1);
}

- (BOOL)getBaseline:(G8PageIteratorLevel)level from:(CGPoint*)from to:(CGPoint*)to {
    int x1, y1, x2, y2;
    BOOL ok = _it->Baseline((tesseract::PageIteratorLevel)level, &x1, &y1, &x2, &y2);
    if (from) {
        from->x = x1;
        from->y = y1;
    }
    if (to) {
        to->x = x2;
        to->y = y2;
    }
    return ok;
}

- (CGFloat)xHeight {
    if (isnan(_rowHeight)) {
        [self getRowAttributes];
    }
    return _rowHeight - _ascender + _descender;
}

- (CGFloat)rowHeight {
    if (isnan(_rowHeight)) {
        [self getRowAttributes];
    }
    return _rowHeight;
}

- (CGFloat)descender {
    if (isnan(_descender)) {
        [self getRowAttributes];
    }
    return _descender;
}

- (CGFloat)ascender {
    if (isnan(_ascender)) {
        [self getRowAttributes];
    }
    return _ascender;
}

- (void)getRowAttributes {
    _it->RowAttributes(&_rowHeight, &_descender, &_ascender);
}

- (void)resetAttributes {
    _rowHeight = NAN;
    _descender = NAN;
    _ascender = NAN;
}

@end
