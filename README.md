# ModernObjC

[![CI Status](https://img.shields.io/travis/nzrsky/ModernObjC.svg?style=flat)](https://app.travis-ci.com/nzrsky//ModernObjC)
[![Version](https://img.shields.io/cocoapods/v/ModernObjC.svg?style=flat)](https://cocoapods.org/pods/ModernObjC)
[![License](https://img.shields.io/cocoapods/l/ModernObjC.svg?style=flat)](https://cocoapods.org/pods/ModernObjC)
[![Platform](https://img.shields.io/cocoapods/p/ModernObjC.svg?style=flat)](https://cocoapods.org/pods/ModernObjC)

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
