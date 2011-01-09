/*
 *  MW.h
 *
 *  Created by Steve Streza on 1/8/2011.
 *  Copyright 2011 Mustacheware. All rights reserved.
 *
 *	This file contains common includes and defines that should be used 
 *	in all projects as utility functions.
 *
 */

/*
 Defines a series of target macros for conditional compilation. Use these
 instead of the normal macros in case Apple changes them in the future.
 
 MWMacTarget - code that runs on Mac platforms, and not iPhone
 - MWMacLeopardTarget - code that runs on Leopard or higher machines
 - MWMacTigerTarget   - code that runs on Tiger or higher machines
 MWiPhoneTarget - code that runs on the iPhone device and simulator, not on the Mac
 - MWiPhoneDeviceTarget - code that runs on the device, not the simulator
 - MWiPhoneSimulatorTarget - code that runs on the simulator, not the device
 */

#ifdef MAC_OS_X_VERSION_10_0
	#ifdef MAC_OS_X_VERSION_10_5
		#define MWMacLeopardTarget 1
	#elif MAC_OS_X_VERSION_10_4
		#define MWMacTigerTarget 1
	#endif
	#define MWMacTarget 1
#else
	#if TARGET_OS_IPHONE
		#define MWiPhoneDeviceTarget 1
		#define MWiPhoneTarget 1
	#elif TARGET_IPHONE_SIMULATOR
		#define MWiPhoneSimulatorTarget 1
		#define MWiPhoneTarget 1
	#endif
#endif


/*
 Returns a formatted NSString for edge insets.
 
 Availability: iPhone (all)
 */
#ifdef MWiPhoneTarget
#define NSStringFromEdgeInsets(__insets) ([NSString stringWithFormat:@"{left: %i, top: %i, right: %i, bottom: %i}",(int)__insets.left,(int)__insets.top,(int)__insets.right,(int)__insets.bottom])
#endif


/*
 Returns a formatted NSString for objects that are point-like, size-like, or rect-like.
 
 Availability: Mac (all), iPhone (all)
 */
#define NSStringFromPoint(__pt) ([NSString stringWithFormat:@"%ix%i",(int)((__pt).x),(int)((__pt).y)])
#define NSStringFromSize(__size) ([NSString stringWithFormat:@"%ix%i",(int)((__size).width),(int)((__size).height)])
#define NSStringFromRect(__rect) ([NSString stringWithFormat:@"[%@, %@]",NSStringFromPoint(__rect.origin),NSStringFromSize(__rect.size)])


/*
 Defines the methods needed for creating a singleton out of a Cocoa class.
 
 Use MWCocoaSingletonInterface in your .h file, and MWCocoaSingletonImplementation
 in your .m file.
 
 After defining this in your class name, #import this class, and then just call:
	id mySingleton = [__className __sharedObject];
 
 Example:
	__className = MyGizmo
	__sharedObject = sharedGizmo
 
	MyGizmo *gizmo = [MyGizmo sharedGizmo];
	[gizmo doSomething];
 
 Arguments:
	__className: The name of the class, not in a string
	__sharedObject: The name of the method to call to get the object.
 
 Availability: Mac (all), iPhone (all)
 */
#define MWCocoaSingletonInterface(__className, __sharedObject) \
+(__className *)__sharedObject;

#define MWCocoaSingletonImplementation(__className, __sharedObject) \
static __className * __sharedObject = nil; \
+ ( __className * ) __sharedObject {@synchronized(self) {if ( __sharedObject == nil) {[[self alloc]  init];}}return __sharedObject ;} \
+ (id)allocWithZone:(NSZone *)zone{@synchronized(self){if( __sharedObject == nil) { __sharedObject = [super allocWithZone:zone];return __sharedObject ;}}return nil;} \
- (id)copyWithZone:(NSZone *)zone{return self;} \
- (id)retain{return self;} \
- (unsigned)retainCount{return UINT_MAX;} \
- (void)release{} \
- (id)autorelease{return self;}


/*
 Adding NSUInteger and NSInteger for Tiger.
*/

#ifdef MWMacTigerTarget
	#if __LP64__ || NS_BUILD_32_LIKE_64
		typedef long NSInteger;
		typedef unsigned long NSUInteger;
	#else
		typedef int NSInteger;
		typedef unsigned int NSUInteger;
	#endif
#endif

#define CGRectZero CGRectMake(0,0,0,0)