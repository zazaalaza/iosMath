//
//  MTMathListDisplay+Internal.h
//  iosMath
//
//  Created by Kostub Deshmukh on 6/21/16.
//
//  This software may be modified and distributed under the terms of the
//  MIT license. See the LICENSE file for details.
//

#import "MTMathListDisplay.h"

@interface MTDisplay ()

@property (nonatomic) CGFloat ascent;
@property (nonatomic) CGFloat descent;
@property (nonatomic) CGFloat width;
@property (nonatomic) NSRange range;
@property (nonatomic) BOOL hasScript;

@end

// The Downshift protocol allows an MTDisplay to be shifted down by a given amount.
@protocol DownShift <NSObject>

@property (nonatomic) CGFloat shiftDown;

@end

@interface MTMathListDisplay ()

- (instancetype _Nonnull )init NS_UNAVAILABLE;

- (instancetype _Nonnull ) initWithDisplays:(NSArray<MTDisplay*>*_Nonnull) displays range:(NSRange) range NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readwrite) MTLinePosition type;
@property (nonatomic, readwrite) NSUInteger index;

@end

@interface MTCTLineDisplay ()

- (instancetype _Nonnull )initWithString:(NSAttributedString*_Nonnull) attrString position:(CGPoint)position range:(NSRange) range font:(MTFont*_Nonnull) font atoms:(NSArray<MTMathAtom*>*_Nonnull) atoms NS_DESIGNATED_INITIALIZER;

- (instancetype _Nonnull )init NS_UNAVAILABLE;

@end

@interface MTFractionDisplay ()

- (instancetype _Nonnull )initWithNumerator:(MTMathListDisplay*_Nonnull) numerator denominator:(MTMathListDisplay*_Nonnull) denominator position:(CGPoint) position range:(NSRange) range NS_DESIGNATED_INITIALIZER;

- (instancetype _Nonnull )init NS_UNAVAILABLE;

@property (nonatomic) CGFloat numeratorUp;
@property (nonatomic) CGFloat denominatorDown;
@property (nonatomic) CGFloat linePosition;
@property (nonatomic) CGFloat lineThickness;

@end

@interface MTRadicalDisplay ()

- (instancetype _Nonnull )initWitRadicand:(MTMathListDisplay*_Nonnull) radicand glpyh:(MTDisplay*_Nonnull) glyph position:(CGPoint) position range:(NSRange) range NS_DESIGNATED_INITIALIZER;

- (void) setDegree:(MTMathListDisplay *_Nonnull)degree fontMetrics:(MTFontMathTable*_Nonnull) fontMetrics;

@property (nonatomic) CGFloat topKern;
@property (nonatomic) CGFloat lineThickness;

@end

// Rendering of an large glyph as an MTDisplay
@interface MTGlyphDisplay() <DownShift>

- (instancetype _Nonnull )initWithGlpyh:(CGGlyph) glyph range:(NSRange) range font:(MTFont*_Nonnull) font NS_DESIGNATED_INITIALIZER;

@end

// Rendering of a constructed glyph as an MTDisplay
@interface MTGlyphConstructionDisplay : MTDisplay<DownShift>

- (instancetype _Nonnull ) init NS_UNAVAILABLE;
- (instancetype _Nonnull ) initWithGlyphs:(NSArray<NSNumber*>*_Nonnull) glyphs offsets:(NSArray<NSNumber*>*_Nonnull) offsets font:(MTFont*_Nonnull) font NS_DESIGNATED_INITIALIZER;

@end

@interface MTLargeOpLimitsDisplay ()

- (instancetype _Nonnull ) initWithNucleus:(MTDisplay*_Nonnull) nucleus upperLimit:(MTMathListDisplay*_Nonnull) upperLimit lowerLimit:(MTMathListDisplay*_Nonnull) lowerLimit limitShift:(CGFloat) limitShift extraPadding:(CGFloat) extraPadding NS_DESIGNATED_INITIALIZER;

- (instancetype _Nonnull )init NS_UNAVAILABLE;

@property (nonatomic) CGFloat upperLimitGap;
@property (nonatomic) CGFloat lowerLimitGap;

@end

@interface MTLineDisplay ()

- (instancetype _Nonnull )initWithInner:(MTMathListDisplay*_Nonnull) inner position:(CGPoint) position range:(NSRange) range NS_DESIGNATED_INITIALIZER;

// How much the line should be moved up.
@property (nonatomic) CGFloat lineShiftUp;
@property (nonatomic) CGFloat lineThickness;

@end

@interface MTAccentDisplay ()

- (instancetype _Nonnull )initWithAccent:(MTGlyphDisplay*_Nonnull) glyph accentee:(MTMathListDisplay*_Nonnull) accentee range:(NSRange) range NS_DESIGNATED_INITIALIZER;

@end


@interface MTInnerDisplay ()

- (instancetype _Nonnull ) initWithInner:(MTMathListDisplay*_Nonnull) inner leftDelimiter:(MTDisplay*_Nonnull) leftDelimiter rightDelimiter:(MTDisplay*_Nullable) rightDelimiter atIndex:(NSUInteger) index NS_DESIGNATED_INITIALIZER;

@property (nonatomic) MTMathListDisplay* _Nonnull inner;

@property (nonatomic, nullable) MTDisplay* leftDelimiter;
@property (nonatomic, nullable) MTDisplay* rightDelimiter;

@property (nonatomic) NSUInteger index;

@end
