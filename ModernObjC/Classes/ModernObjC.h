//
//  Copyright © Alexey Nazarov. All rights reserved
//

#ifndef ModernObjC_H
#define ModernObjC_H

@interface ModernObjC_dummy : NSObject
@end

//
// Modifiers
//
#if !defined(NEVER)
    #if defined(__has_attribute) && __has_attribute(noreturn)
        ///A few standard library functions, such as abort and exit, cannot return. GCC knows this automatically.
        /// Some programs define their own functions that never return. You can declare them noreturn to tell the compiler this fact.
        /// For example,
        ///
        ///     void fatal () __attribute__ ((noreturn));
        ///
        ///     void
        ///     fatal (/* ... */)
        ///     {
        ///       /* ... */ /* Print error message. */ /* ... */
        ///       exit (1);
        ///     }
        ///
        /// The noreturn keyword tells the compiler to assume that fatal cannot return. It can then optimize without regard to what would happen if fatal ever did return. This makes slightly better code. More importantly, it helps avoid spurious warnings of uninitialized variables.
        ///
        /// The noreturn keyword does not affect the exceptional path when that applies: a noreturn-marked function may still return to the caller by throwing an exception or calling longjmp.
        ///
        /// Do not assume that registers saved by the calling function are restored before calling the noreturn function.
        ///
        /// It does not make sense for a noreturn function to have a return type other than void.
        ///
        #define NEVER __attribute__((noreturn))
    #else
        #define NEVER
    #endif
#endif


#if !defined(WARN_UNUSED_RESULT)
    #if defined(__has_attribute) && __has_attribute(warn_unused_result)
        ///The `warn_unused_result` attribute causes a warning to be emitted if a caller of the function with this attribute does
        ///not use its return value. This is useful for functions where not checking the result is either a security problem or
        ///always a bug, such as realloc.
        ///
        ///    int fn () __attribute__ ((warn_unused_result));
        ///    int foo ()
        ///    {
        ///      if (fn () < 0) return -1;
        ///      fn ();
        ///      return 0;
        ///    }
        ///
        ///    results in warning on line 5.
        #define WARN_UNUSED_RESULT __attribute__((warn_unused_result))
    #else
        #define WARN_UNUSED_RESULT
    #endif
#endif

#if !defined(NO_ESCAPE)
    #if defined(__has_attribute) && __has_attribute(noescape)
        /// `noescape` placed on a function parameter of a pointer type is used to inform the compiler that the pointer
        ///  cannot escape: that is, no reference to the object the pointer points to that is derived from the parameter
        ///  value will survive after the function returns. Users are responsible for making sure parameters annotated with
        ///  noescape do not actually escape. Calling free() on such a parameter does not constitute an escape.
        ///
        /// For example:
        ///
        ///     int *gp;
        ///
        ///     void nonescapingFunc(__attribute__((noescape)) int *p) {
        ///       *p += 100; // OK.
        ///     }
        ///
        ///     void escapingFunc(__attribute__((noescape)) int *p) {
        ///       gp = p; // Not OK.
        ///     }
        /// Additionally, when the parameter is a block pointer <https://clang.llvm.org/docs/BlockLanguageSpec.html>, the same restriction applies to copies of the block. For example:
        ///
        ///     typedef void (^BlockTy)();
        ///     BlockTy g0, g1;
        ///
        ///     void nonescapingFunc(__attribute__((noescape)) BlockTy block) {
        ///       block(); // OK.
        ///     }
        ///
        ///     void escapingFunc(__attribute__((noescape)) BlockTy block) {
        ///       g0 = block; // Not OK.
        ///       g1 = Block_copy(block); // Not OK either.
        ///     }
        #define NO_ESCAPE __attribute__((noescape))
    #else
        #define NO_ESCAPE
    #endif
#endif

#if !defined(CLOSED_ENUM)
    #if defined(__has_attribute) && __has_attribute(enum_extensibility)
        /// Attribute enum_extensibility is used to distinguish between enum definitions that are extensible and those
        /// that are not. The attribute can take either closed or open as an argument. closed indicates a variable of the
        /// enum type takes a value that corresponds to one of the enumerators listed in the enum definition or, when the
        ///  enum is annotated with flag_enum, a value that can be constructed using values corresponding to the enumerators.
        ///  open indicates a variable of the enum type can take any values allowed by the standard and instructs clang to be
        ///  more lenient when issuing warnings.
        ///
        ///     enum __attribute__((enum_extensibility(closed))) ClosedEnum {
        ///       A0, A1
        ///     };
        #define CLOSED_ENUM __attribute__((enum_extensibility(closed)))
    #else
        #define CLOSED_ENUM
    #endif
#endif

#if !defined(OVERLOADABLE)
    #if defined(__has_attribute) && __has_attribute(overloadable)
        /// Clang provides support for C++ function overloading in C. Function overloading in C is introduced using the overloadable attribute. For example, one might provide several overloaded versions of a tgsin function that invokes the appropriate standard function computing the sine of a value with float, double, or long double precision:
        ///
        ///     #include <math.h>
        ///     float __attribute__((overloadable)) tgsin(float x) { return sinf(x); }
        ///     double __attribute__((overloadable)) tgsin(double x) { return sin(x); }
        ///     long double __attribute__((overloadable)) tgsin(long double x) { return sinl(x); }
        #define OVERLOADABLE __attribute__((overloadable))
    #else
        #define OVERLOADABLE
    #endif
#endif

#if !defined(BOXABLE)
    #if defined(__has_attribute) && __has_attribute(objc_boxable)
        /// Structs and unions marked with the objc_boxable attribute can be used with the Objective-C boxed expression syntax, @(...).
        /// Usage: __attribute__((objc_boxable)). This attribute can only be placed on a declaration of a trivially-copyable struct or union:
        ///
        ///     struct __attribute__((objc_boxable)) some_struct {
        ///       int i;
        ///     };
        ///     union __attribute__((objc_boxable)) some_union {
        ///       int i;
        ///       float f;
        ///     };
        ///     typedef struct __attribute__((objc_boxable)) _some_struct some_struct;
        ///     ...
        ///     some_struct ss;
        ///     NSValue *boxed = @(ss);
        #define BOXABLE __attribute__((objc_boxable))
    #else
        #define BOXABLE
    #endif
#endif

//
// Vars & Lets
//
#if !defined(let)
    /// Example:
    ///     let x = foo();
    #define let  __auto_type const
#endif

#if !defined(var)
    /// Example:
    ///     var x = foo(); x = 0;
    #define var  __auto_type
#endif

#if !defined(force_nonnul)
    /// Example:
    ///     let x = force_nonnul(foo());
    #define force_nonnul(_obj) \
        ({ \
            NSCAssert(_obj, @"Expected `%@` not to be nil.", @#_obj); \
            (typeof({ __auto_type result_ = (_obj); result_; }))(_obj); \
        })
#endif

#if !defined(optional_as)
    /// Example:
    ///     let x = optional_as(foo(), NSString).length;
    #define optional_as(obj_, cls_) \
        (([obj_ isKindOfClass: cls_.class]) ? (cls_ *)(obj_) : nil)
#endif

//
// Typed copy
//
@interface NSString (TypedCopying)
- (NSString *)copy WARN_UNUSED_RESULT;
- (NSMutableString *)mutableCopy WARN_UNUSED_RESULT;
@end

@interface NSAttributedString (TypedCopying)
- (NSAttributedString *)copy WARN_UNUSED_RESULT;
- (NSMutableAttributedString *)mutableCopy WARN_UNUSED_RESULT;
@end

@interface NSArray<__covariant ObjectType> (TypedCopying)
- (NSArray<ObjectType> *)copy WARN_UNUSED_RESULT;
- (NSMutableArray<ObjectType> *)mutableCopy WARN_UNUSED_RESULT;
@end

@interface NSSet<__covariant ObjectType> (TypedCopying)
- (NSSet<ObjectType> *)copy WARN_UNUSED_RESULT;
- (NSMutableSet<ObjectType> *)mutableCopy WARN_UNUSED_RESULT;
@end

@interface NSDictionary<__covariant KeyType, __covariant ObjectType> (TypedCopying)
- (NSDictionary<KeyType, ObjectType> *)copy WARN_UNUSED_RESULT;
- (NSMutableDictionary<KeyType, ObjectType> *)mutableCopy WARN_UNUSED_RESULT;
@end

//
// Typed for in
//
#if !defined(foreach)
    /// Example:
    ///     foreach(item, array) { ... item type is known here ... }
    #define foreach(_obj, _col) \
        for (typeof((_col).private_enumeratedType)(_obj) in (_col))

    // Private extensions for type inference
    @interface NSArray<__covariant ObjectType> (TypedForeach)
    @property (nonatomic, strong, readonly) ObjectType private_enumeratedType;
    @end
    @interface NSDictionary<__covariant KeyType, __covariant ObjectType> (TypedForeach)
    @property (nonatomic, strong, readonly) KeyType private_enumeratedType;
    @end
#endif

#endif /* ModernObjC_H */
