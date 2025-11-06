# iOS 26.1 Compatibility Analysis for iosMath

## Executive Summary

This document outlines the changes required to make the `iosMath` library compatible with iOS 26.1. The library currently targets iOS 6.0+ and macOS 10.8+, which are significantly outdated. Several updates are needed to ensure compatibility with modern iOS versions.

---

## 1. Deployment Target Updates

### Current Status
- **Podspec**: iOS 6.0, macOS 10.8
- **Xcode Project**: iOS 8.0/9.0, macOS 10.9
- **Swift Package**: No platform specification

### Required Changes

#### 1.1 Update `iosMath.podspec`
```ruby
# Current:
s.ios.deployment_target = '6.0'
s.osx.deployment_target = '10.8'

# Should be:
s.ios.deployment_target = '17.0'  # Minimum for iOS 26.1 compatibility
s.osx.deployment_target = '14.0'  # Minimum for macOS compatibility
```

#### 1.2 Update Xcode Project Files
- **iosMath.xcodeproj/project.pbxproj**: Update `IPHONEOS_DEPLOYMENT_TARGET` from 8.0/9.0 to 17.0
- **MacOSMath.xcodeproj/project.pbxproj**: Update `MACOSX_DEPLOYMENT_TARGET` from 10.8 to 14.0

#### 1.3 Update Swift Package Manager
```swift
// Package.swift needs platform specification:
platforms: [
    .iOS(.v17),
    .macOS(.v14)
]
```

---

## 2. Deprecated API Usage

### 2.1 macOS Graphics Context API (CRITICAL)

**Location**: `iosMath/render/MTConfig.h:46`

**Issue**: `NSGraphicsContext.currentContext.graphicsPort` is deprecated in macOS 10.14+ and removed in macOS 14.0+

**Current Code**:
```objc
#define MTGraphicsGetCurrentContext() ([[NSGraphicsContext currentContext] graphicsPort])
```

**Required Fix**:
```objc
#if TARGET_OS_IPHONE
#define MTGraphicsGetCurrentContext() UIGraphicsGetCurrentContext()
#else
// macOS 10.14+ requires CGContext from NSGraphicsContext
#define MTGraphicsGetCurrentContext() ([[NSGraphicsContext currentContext] CGContext])
#endif
```

**Impact**: HIGH - This will cause compilation errors on macOS 14.0+

---

### 2.2 iOS Version Checking

**Location**: `iosMath/render/MTMathListDisplay.m:22-40`

**Issue**: Manual version checking using `UIDevice.currentDevice.systemVersion` is outdated. The `isIos6Supported()` function checks for iOS 6.0, which is no longer relevant.

**Current Code**:
```objc
static BOOL isIos6Supported() {
    // Checks for iOS 6.0 support
}
```

**Required Fix**: Remove this function entirely or update to use `@available` checks:
```objc
// Remove isIos6Supported() and use:
if (@available(iOS 6.0, *)) {
    CGRect bounds = CTLineGetBoundsWithOptions(_line, kCTLineBoundsUseGlyphPathBounds);
    // ...
} else {
    [self computeDimensions:font];
}
```

**Impact**: MEDIUM - Code simplification, no functional impact since iOS 6.0+ is always available

---

## 3. Swift Package Manager Configuration

### Current Status
- Swift tools version: 5.2 (outdated)
- No platform specifications
- Incorrect path configuration

### Required Updates

**File**: `Package.swift`

```swift
// swift-tools-version:5.9
import PackageDescription

let package = Package(
    name: "iosMath",
    platforms: [
        .iOS(.v17),
        .macOS(.v14)
    ],
    products: [
        .library(
            name: "iosMath",
            targets: ["iosMath"]),
    ],
    dependencies: [],
    targets: [
        .target(
            name: "iosMath",
            dependencies: [],
            path: "iosMath",
            exclude: ["render/internal"],
            publicHeadersPath: ".",
            cSettings: [
                .headerSearchPath("."),
                .headerSearchPath("render"),
                .headerSearchPath("render/internal"),
                .headerSearchPath("lib")
            ]
        ),
        .testTarget(
            name: "iosMathTests",
            dependencies: ["iosMath"],
            path: "iosMathTests"
        ),
    ]
)
```

**Changes Needed**:
1. Update Swift tools version to 5.9+
2. Add platform specifications
3. Fix path configuration (currently points to root)
4. Add proper header search paths
5. Exclude internal headers from public API

**Impact**: HIGH - Required for SPM integration in modern projects

---

## 4. Xcode Project Modernization

### 4.1 Project Format
- **Current**: Xcode project format version 46
- **Recommended**: Update to latest format (56+)

### 4.2 Build Settings Updates

**Required Changes**:
1. **CLANG_CXX_LANGUAGE_STANDARD**: Update from `gnu++0x` to `gnu++17` or `c++17`
2. **GCC_C_LANGUAGE_STANDARD**: Update from `gnu99` to `gnu11` or `c11`
3. **CLANG_ENABLE_MODULES**: Already enabled ✓
4. **CLANG_WARN_DEPRECATED_OBJC_IMPLEMENTATIONS**: Already enabled ✓

### 4.3 Framework Linking
- Current: Explicit framework linking (old style)
- Modern: Use `@import` statements (already partially done)

---

## 5. CoreText API Compatibility

### Status: ✅ GOOD
The library uses CoreText APIs that are stable and well-supported:
- `CTLineCreateWithAttributedString` - Available since iOS 3.2
- `CTLineGetTypographicBounds` - Available since iOS 3.2
- `CTLineGetBoundsWithOptions` - Available since iOS 6.0
- `CTLineDraw` - Available since iOS 3.2
- `CTLineGetGlyphRuns` - Available since iOS 3.2
- `CTRunGetGlyphCount` - Available since iOS 3.2
- `CTRunGetGlyphs` - Available since iOS 3.2

**No changes required** - All CoreText APIs used are stable and forward-compatible.

---

## 6. UIKit/AppKit Compatibility

### Status: ✅ GOOD
The library uses platform abstraction macros (`MTView`, `MTColor`, etc.) which are well-designed for cross-platform compatibility.

**No changes required** - The abstraction layer handles platform differences correctly.

---

## 7. Module System and Headers

### Current Issues
1. Public headers are not properly organized for module imports
2. Internal headers may leak into public API

### Required Changes

**File**: `iosMath/IosMath.h`
- Ensure all public headers are properly exposed
- Verify module map generation

**Impact**: MEDIUM - Affects import statements in consuming projects

---

## 8. Testing Requirements

### 8.1 Update Test Targets
- Update deployment targets for test targets to match main target
- Ensure test frameworks are compatible with iOS 26.1

### 8.2 CI/CD Updates
- Update `.travis.yml` or migrate to GitHub Actions
- Add iOS 26.1 simulator testing

---

## 9. Documentation Updates

### Required Updates
1. **README.md**: Update minimum iOS version requirements
2. **CHANGELOG.md**: Document breaking changes for iOS 26.1 compatibility
3. Update installation instructions for new deployment targets

---

## 10. Priority Action Items

### Critical (Must Fix)
1. ✅ Update deployment targets in all configuration files
2. ✅ Fix macOS `graphicsPort` deprecation
3. ✅ Update Swift Package Manager configuration

### High Priority
4. ✅ Update Xcode project build settings
5. ✅ Modernize Swift tools version
6. ✅ Fix SPM path configuration

### Medium Priority
7. Remove/update iOS version checking code
8. Update project format version
9. Update documentation

### Low Priority
10. Clean up deprecated build settings
11. Update CI/CD configuration

---

## 11. Migration Checklist

- [ ] Update `iosMath.podspec` deployment targets
- [ ] Update `Package.swift` with platforms and correct paths
- [ ] Fix `MTConfig.h` graphicsPort deprecation
- [ ] Update `iosMath.xcodeproj` deployment targets
- [ ] Update `MacOSMath.xcodeproj` deployment targets
- [ ] Remove/update `isIos6Supported()` function
- [ ] Update Swift tools version to 5.9+
- [ ] Test compilation on Xcode with iOS 26.1 SDK
- [ ] Test on iOS 26.1 simulator
- [ ] Test on macOS 14.0+ if applicable
- [ ] Update README.md with new requirements
- [ ] Update CHANGELOG.md
- [ ] Verify SPM integration works
- [ ] Verify CocoaPods integration works
- [ ] Run test suite

---

## 12. Estimated Impact

### Breaking Changes
- **Deployment target increase**: Projects using iosMath must target iOS 17.0+ (from iOS 6.0+)
- **macOS compatibility**: Requires macOS 14.0+ (from macOS 10.8+)

### Non-Breaking Changes
- Internal API modernization
- Build system updates
- Documentation improvements

---

## 13. Testing Strategy

1. **Unit Tests**: Run existing test suite on iOS 26.1 simulator
2. **Integration Tests**: Test library integration in sample app
3. **Performance Tests**: Verify no performance regressions
4. **Compatibility Tests**: Test on various iOS versions (17.0, 18.0, 26.1)

---

## 14. References

- [Apple iOS 26 Release Notes](https://developer.apple.com/ios/)
- [NSGraphicsContext Deprecation](https://developer.apple.com/documentation/appkit/nsgraphicscontext/1529857-graphicsport)
- [Swift Package Manager Documentation](https://swift.org/package-manager/)

---

## Notes

- iOS 26.1 is a future version; this analysis is based on typical iOS upgrade patterns
- Some APIs may have additional deprecations in iOS 26.1 that are not yet documented
- Regular testing on beta versions of iOS 26.1 is recommended
- Consider maintaining a compatibility branch for older iOS versions if needed

