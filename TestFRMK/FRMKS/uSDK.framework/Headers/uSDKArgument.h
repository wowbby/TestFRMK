//
//  uSDKArgument.h
//  uSDK
//
//  Created by liugn on 15/12/11.
//  Copyright © 2015年 haier. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  设备参数类
 */
@interface uSDKArgument : NSObject
/**
 *  参数名
 */
@property (nonatomic, copy) NSString* name;
/**
 *  参数值
 */
@property (nonatomic, copy) NSString* value;

@end
