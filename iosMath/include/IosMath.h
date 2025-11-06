//
//  IosMath.h
//  iosMath
//
//  Created by MARIO ANDHIKA on 8/28/15.
//  Copyright (C) 2015 MathChat
//   
//  This software may be modified and distributed under the terms of the
//  MIT license. See the LICENSE file for details.
//

//! Project version number for iosMath.
FOUNDATION_EXPORT double iosMathVersionNumber;

//! Project version string for iosMath.
FOUNDATION_EXPORT const unsigned char iosMathVersionString[];

// Main public API - Math rendering view
#import <IosMath/MTMathUILabel.h>

// Core math data structures
#import <IosMath/MTMathList.h>
#import <IosMath/MTMathListBuilder.h>
#import <IosMath/MTMathListDisplay.h>

// Font management
#import <IosMath/MTFont.h>
#import <IosMath/MTFontManager.h>

// Advanced APIs for programmatic math list creation
#import <IosMath/MTMathAtomFactory.h>
#import <IosMath/MTMathListIndex.h>
