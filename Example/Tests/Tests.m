@import XCTest;
@import ModernObjC;

// OVERLOADABLE works, no warnings
void foo(int x) OVERLOADABLE {}
void foo(long x) OVERLOADABLE {}

typedef int(^SomeBlock)(int x);
SomeBlock tmpBlock;

typedef struct BOXABLE {
    int x; int y;
} some_boxable_struct;

typedef struct {
    int x; int y;
} some_nonboxable_struct;

typedef NS_CLOSED_ENUM(int, SomeClosedEnum) {
    SomeClosedEnumA = 0, SomeClosedEnumB = 1
};

typedef NS_ENUM(int, SomeEnum) {
    SomeEnumA = 0, SomeEnumB = 1
};

@interface ModernObjCTests: XCTestCase
@end

@implementation ModernObjCTests

// NEVER works, you will see warning here
- (void)unusedFunc NEVER {}

// WARN_UNUSED_RESULT,
- (BOOL)unusedResult WARN_UNUSED_RESULT {
    return YES;
}

- (void)textBoxable {
    // some_nonboxable_struct ssunbox;
    // NSValue *boxed1 = @(ssunbox); error

    some_boxable_struct ssbox;
    NSValue *boxed = @(ssbox);

    XCTAssert(boxed, "Pass");
}

- (void)textEnum {
    SomeClosedEnum closed;
    closed = 2;

    SomeEnum open;
    open = 2;
}

- (void)storeBlock:(SomeBlock)block {
    tmpBlock = block;
}

- (void)storeNoEscapeBlock:(SomeBlock NO_ESCAPE)block {
    tmpBlock = block;
}

- (void)textEscape {
    let foo = (int)time(NULL);
    [self storeBlock:^(int x){ return foo; }];
    [self storeNoEscapeBlock:^(int x){ return foo; }];
}

- (void)testWarnUnusedResult {
    // Should be warning here
    [self unusedResult];
}

- (void)testVarLet {
    let x = @"foo";
    XCTAssert(x.length == 3, "Pass");
    // x = @"bar"; error

    var y = @"foo";
    XCTAssert(y.length == 3, "Pass");
    y = @"b";
    XCTAssert(y.length == 1, "Pass");
}

- (void)testForeach {
    let list = (NSArray<NSString*> *)@[@"foo", @"bar"];
    foreach(str, list) {
        XCTAssert(str.length > 0, "Pass");
    }
}

- (void)testOptionalAs {
    let a = (NSString *)nil;
    let b = @"foo";
    XCTAssert(optional_as(a, NSString).length == 0, "Pass");
    XCTAssert(optional_as(b, NSString).length == 3, "Pass");
}

- (NSString * _Nullable)nullableString {
    return @"foo";
}

- (void)readNonnullString:(NSString * _Nonnull)str { /* ... */ }

- (void)testForceNonnull {
    [self readNonnullString:force_nonnul(self.nullableString)];
    [self readNonnullString:self.nullableString];
    XCTAssert(force_nonnul(self.nullableString).length == 3, "Pass");
}

- (void)testCopy {
    let array = (NSArray<NSString*> *)@[@"foo", @"bar"];
    let dict = (NSDictionary<NSString*, NSString*> *)@{@"foo":@"baz", @"bar": @"fix"};
    let set = (NSSet<NSString*> *)[[NSSet alloc] initWithArray: array];

    let strCopy = @"foo".copy;
    XCTAssert(strCopy.length == 3, "Pass");
    XCTAssert(optional_as(strCopy, NSString), "Pass");

    let strMutCopy = @"foo".mutableCopy;
    [strMutCopy appendString:@"bar"];
    XCTAssert(strMutCopy.length == 6, "Pass");
    XCTAssert(optional_as(strMutCopy, NSMutableString), "Pass");

    let astrCopy = [[NSAttributedString alloc] initWithString:@"fox"].copy;
    XCTAssert(astrCopy.length == 3, "Pass");
    XCTAssert(optional_as(astrCopy, NSAttributedString), "Pass");

    let astrMutCopy = [[NSAttributedString alloc] initWithString:@"fix"].mutableCopy;
    XCTAssert(astrMutCopy.length == 3, "Pass");
    XCTAssert(optional_as(astrMutCopy, NSMutableAttributedString), "Pass");

    let arrCopy = array.copy;
    XCTAssert(arrCopy[0].length == 3, "Pass");
    XCTAssert(optional_as(arrCopy, NSArray), "Pass");

    let arrMutCopy = array.mutableCopy;
    [arrMutCopy addObject:@"bar"];
    XCTAssert(arrMutCopy[0].length == 3, "Pass");
    XCTAssert(optional_as(arrMutCopy, NSMutableArray), "Pass");

    let setCopy = set.copy;
    XCTAssert(setCopy.anyObject.length > 0, "Pass");
    XCTAssert(optional_as(setCopy, NSSet), "Pass");

    let setMutCopy = set.mutableCopy;
    [setMutCopy addObject:@"bar"];
    XCTAssert(setMutCopy.anyObject.length > 0, "Pass");
    XCTAssert(optional_as(setMutCopy, NSMutableSet), "Pass");

    let dictCopy = dict.copy;
    XCTAssert(dictCopy[@"foo"].length > 0, "Pass");
    XCTAssert(optional_as(dictCopy, NSDictionary), "Pass");

    let dictMutCopy = dict.mutableCopy;
    [dictMutCopy setObject:@"bar" forKey:@"baz"];
    XCTAssert(dictMutCopy[@"bar"].length > 0, "Pass");
    XCTAssert(optional_as(dictMutCopy, NSMutableDictionary), "Pass");
}

@end
