# ModernObjC

[![Build Status](https://app.travis-ci.com/nzrsky/ModernObjC.svg?branch=master)](https://app.travis-ci.com/nzrsky/ModernObjC)
[![codecov.io](https://codecov.io/github/nzrsky/ModernObjC/coverage.svg?branch=master)](https://codecov.io/github/nzrsky/ModernObjC?branch=master)
[![CocoaPods Compatible](https://img.shields.io/cocoapods/v/ModernObjC.svg)](https://cocoapods.org/pods/ModernObjC)
[![Carthage compatible](https://img.shields.io/badge/Carthage-compatible-4BC51D.svg?style=flat)](https://github.com/Carthage/Carthage)
[![Platform](https://img.shields.io/cocoapods/p/ModernObjC.svg?style=flat)](http://cocoadocs.org/docsets/ModernObjC)
[![Twitter](https://img.shields.io/badge/twitter-@nzrsky-blue.svg?style=flat)](http://twitter.com/nzrsky)

It adds lets, vars and typed copy/foreach functions for ObjC collections

## Example

To run the example project, clone the repo, and run `pod install` from the Example directory first.

```objective-c
	// Objective-C without types
	NSDictionary *notes = [document fetchNotes];
	printf("%d", [notes[@"default"] words]);

	// Before:
	NSDictionary<NSString*, NSArray<Note*>*> *notes = [document fetchNotes];
	printf("%d", notes[@"default"]);

	NSDictionary<NSString*, NSArray<Note*>*> *notes = [document fetchNotes];
	printf("%d", notes[@"default"]);
```

## Requirements

## Installation

ModernObjC is available through [CocoaPods](https://cocoapods.org). To install
it, simply add the following line to your Podfile:

```ruby
pod 'ModernObjC'
```

## Author

Alexey Nazarov, alexx.nazaroff@gmail.com

## License

ModernObjC is available under the MIT license. 
See the LICENSE file for more info.
