//
//  uSDKDeviceConfigInfo.h
//  uSDK_iOS_v2
//
//  Created by Zono on 14-1-7.
//  Copyright (c) 2014年 haierubic. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "uSDKConstantInfo.h"

@class uSDKDeviceConfigInfoAp;

/**
 *	@brief  功能描述：<br>
 *      uSDK设备配置信息类，用于描述设备的配置信息。设备配置信息包括设备的一些基本信息、要连接的路由ssid和密码以及当前能够搜索到的路由列表。<br>
 *      当获取设备的配置信息时，配置信息以类实例方式返回。当设置设备的配置信息时，要设置的配置信息以类实例方式传给uSDK。
 */
@interface uSDKDeviceConfigInfo : NSObject {
    @public
    NSString* _roomname;
    @private
    NSString* _ip;
}

/**
 *      设备大类分类信息；
 */
@property (nonatomic, assign,readonly) uSDKDeviceTypeConst type;

/**
 *      设备mac；
 */
@property (nonatomic, strong,readonly) NSString* mac;

/**
 *      设备搜索到的wifi列表；
 */
@property (nonatomic, strong,readonly) NSArray<uSDKDeviceConfigInfoAp*>* aplist;

/**
 *      配置需要连接的SSID；
 */
@property (nonatomic, strong) NSString* apSsid;

/**
 *      配置需要连接SSID对应的密码；
 */
@property (nonatomic, strong) NSString* apPassword;

/**
 *      主网关域名
 */
@property (nonatomic, strong) NSString* mainGatewayDomain;

/**
 *      主网关端口
 */
@property (nonatomic, assign) NSInteger mainGatewayPort;

/**
 *      配置设备所连接的主网关域名；
 */
@property (nonatomic, strong) NSString* accessGatewayDomain;

/**
 *      配置设备所连接的接入网关端口；
 */
@property (nonatomic, assign) NSInteger accessGatewayPort;

/**
 *      e++协议版本号；
 */
@property (nonatomic, strong,readonly) NSString* eProtocolVer;

/**
 *      设备Identifier标识码【此变量已废弃，值无效】
 */
@property (nonatomic, strong,readonly) NSString* typeIdentifier;

/**
 *      【准备废弃】连接设备使用的密码【此变量已废弃，值无效】
 */
@property (nonatomic, strong) NSString* devicePassword;

/**
 *      网关地址【此变量已废弃，值无效】
 */
@property (nonatomic, strong) NSString* gateway;


- (id)initWithType:(uSDKDeviceTypeConst) type
               mac:(NSString*)mac
                ip:(NSString*)ip
    typeIdentifier:(NSString*)typeIdentifier
      eProtocolVer:(NSString*)eProtocolVer
          roomname:(NSString*)roomname;

@end


/**
 *	@brief	功能描述：<br>
 *      uSDK设备配置信息中的AP信息类，用于描 述路由信息，包括ap加密方式、ap信号强度、ap的ssid名称。<br>
 *      当获取设备softap配置信息时，在设备返回的当前能够搜索到的ap列表中，存放的就是AP信息类实例。
 */
@interface uSDKDeviceConfigInfoAp : NSObject

/**
 *      wifi热点的SSID；此变量只读，设置无效
 */
@property (nonatomic, strong) NSString* ssid;

/**
 *      wifi热点的信号强度 范围是0～100；此变量只读，设置无效
 */
@property (nonatomic, assign) int power;

/**
 *      wifi加密方式；此变量只读，设置无效
 */
@property (nonatomic, assign) uSDKApEncryptionTypeConst encrytionType;


@end
