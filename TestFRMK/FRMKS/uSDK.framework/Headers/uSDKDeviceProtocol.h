//
//  uSDKDeviceProtocol.h
//  uSDKDeviceLocal
//
//  Created by liugn on 2016/10/14.
//  Copyright © 2016年 haier. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "uSDKDeviceInfo.h"
#import "uSDKArgument.h"

#define DEVICE_OPER_TIME_OUT_INTERVAL 15.0

/**
 *  uSDK设备协议
 */
@protocol uSDKDeviceProtocol <NSObject>

/**
 *  连接设备，连接后会收到该设备的相关消息。需要对设备对象设置delegate，才能收到相应设备的消息。
 *
 *  @param success   成功回调
 *  @param failure   失败回调
 */
-(void)connectWithSuccess:(void(^)())success
                  failure:(void(^)(NSError *error)) failure;

/**
 *  连接设备同时自动查询设备的所有属性，连接后会收到该设备的相关消息。需要对设备对象设置delegate，才能收到相应设备的消息。
 *
 *  @param success 成功回调
 *  @param failure 失败回调
 */
-(void)connectNeedPropertiesWithSuccess:(void(^)())success
                                failure:(void(^)(NSError *error)) failure;

/**
 *  断开设备连接
 *
 *  @param success   成功回调
 *  @param failure   失败回调
 */
-(void)disconnectWithSuccess:(void(^)())success
                     failure:(void(^)(NSError *error)) failure;

/**
 *  根据属性名读取设备的属性值，属性值会在回调函数中返回，并更新设备对应的属性值。
 *
 *  @param name    属性名
 *  @param success 成功，返回属性值
 *  @param failure 失败
 */
-(void)readAttributeWithName:(NSString*)name
                     success:(void(^)(NSString *value)) success
                     failure:(void(^)(NSError *error)) failure;

/**
 *  根据属性名读取设备的属性值，属性值会在回调函数中返回，并更新设备对应的属性值。
 *
 *  @param name    属性名
 *  @param timeoutInterval 超时时间（12-120秒）
 *  @param success 成功，返回属性值
 *  @param failure 失败
 */
-(void)readAttributeWithName:(NSString*)name
             timeoutInterval:(NSTimeInterval)timeoutInterval
                     success:(void(^)(NSString *value)) success
                     failure:(void(^)(NSError *error)) failure;

/**
 *  写入设备属性值,回调中只返回是否成功,如果写入成功，设备对应的属性值会在设备属性变化上报中更新。注：此方法可用于发送单命令.
 *
 *  @param name    属性名
 *  @param value   属性值
 *  @param success 成功
 *  @param failure 失败
 */
-(void)writeAttributeWithName:(NSString*)name
                        value:(NSString*)value
                      success:(void(^)()) success
                      failure:(void(^)(NSError *error)) failure;

/**
 *  写入设备属性值,回调中只返回是否成功,如果写入成功，设备对应的属性值会在设备属性变化上报中更新。注：此方法可用于发送单命令.
 *
 *  @param name    属性名
 *  @param value   属性值
 *  @param timeoutInterval 超时时间（12-120秒）
 *  @param success 成功
 *  @param failure 失败
 */
-(void)writeAttributeWithName:(NSString*)name
                        value:(NSString*)value
              timeoutInterval:(NSTimeInterval)timeoutInterval
                      success:(void(^)()) success
                      failure:(void(^)(NSError *error)) failure;

/**
 *  执行设备命令操作。每一种设备都有自己特定的命令集，详细的命令集描述请参看对应的设备ID文档。
 *
 *  @param operationName   要执行的设备操作命令
 *  @param args            要执行的设备操作命令列表
 *  @param success         命令执行成功回调
 *  @param failure         命令执行失败回调
 */
- (void)executeOperation:(NSString*)operationName
                    args:(NSArray<uSDKArgument*>*)args
                 success:(void(^)()) success
                 failure:(void(^)(NSError *error)) failure;
/**
 *  执行设备命令操作，可自定义超时时间。每一种设备都有自己特定的命令集，详细的命令集描述请参看对应的设备ID文档。
 *
 *  @param operationName   要执行的设备操作命令
 *  @param args            要执行的设备操作命令列表
 *  @param timeoutInterval 超时时间（12-120秒）
 *  @param success         命令执行成功回调
 *  @param failure         命令执行失败回调
 */
- (void)executeOperation:(NSString*)operationName
                    args:(NSArray<uSDKArgument*>*)args
         timeoutInterval:(NSTimeInterval)timeoutInterval
                 success:(void(^)()) success
                 failure:(void(^)(NSError *error)) failure;

@end
