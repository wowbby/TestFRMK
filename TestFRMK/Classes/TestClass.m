//
//  TestClass.m
//  Pods
//
//  Created by 郑振兴 on 2017/7/25.
//
//

#import "TestClass.h"
#import <UMMobClick/MobClick.h>
#import <uSDK/uSDKDeviceManager.h>
@implementation TestClass
+(void)testFunc{
    
    [MobClick startWithConfigure:nil];
    [uSDKDeviceManager defaultDeviceManager];
}
@end
