//
//  uSDKDeviceManager.h
//  uSDK_iOS_v2
//
//  Created by Zono on 14-1-7.
//  Copyright (c) 2014年 haierubic. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "uSDKConstantInfo.h"
#import "uSDKDevice.h"
#import "uSDKDeviceConfigInfo.h"

@protocol  uSDKDeviceManagerDelegate;


/**
 *   uSDK业务错误码消息类。
 */
@interface uSDKError : NSObject

/**
 *   具体错误码
 */
@property(nonatomic) uSDKErrorConst code;

@end

/**
 *  uSDK设备管理单例类，用于管理uSDK自动发现的局域网内设备和用户关联的远程设备。
 */
@interface uSDKDeviceManager : NSObject {
    uSDKCloudConnectionState _cloudConnectionState;
}

/**
 *  关心的设备类型。用于过滤deviceManager:didAddDevices:回调和deviceManager:didRemoveDevices:回调返回的设备列表，若未设置，则返回所有类型设备
 */
@property (nonatomic, strong) NSArray<NSNumber*> *interestedDeviceTypes;

/**
 *  云连接状态
 */
@property (nonatomic, assign, readonly) uSDKCloudConnectionState cloudConnectionState;

/**
 *  代理，用于接收设备列表变化、绑定、解绑、云平台连接状态消息
 *  注意:
 *  需先设置感兴趣的设备类型，若不设置则默认订阅所有类型设备
 *  见 interestedDeviceTypes 属性
 */
@property (nonatomic, weak) id<uSDKDeviceManagerDelegate> delegate;

/**
 *  所有已发现的设备。这些设备包括uSDK自动发现的wifi网络设备和已与用户关联的设备。如果设备既能本地访问也能远程访问，
 *  uSDK访问设备时会优先本地访问。
 *  设备列表存储形式：[{Key: 家电设备ID, Object: 家电设备实例}, {}...]；
 */
@property (nonatomic, strong ,readonly) NSDictionary<NSString*,uSDKDevice*>* deviceDict;


/**
 *  获取uSDKDeviceManager单例，此单例用于访问自动发现的设备列表和与用户关联的设备列表。
 *
 *  @return 返回uSDKDeviceManager单例
 */
+ (uSDKDeviceManager*)defaultDeviceManager;

/**
 *  获取uSDKDeviceManager单例，此单例用于访问自动发现的设备列表和与用户关联的设备列表。
 *
 *  @return 返回uSDKDeviceManager单例
 */
+ (uSDKDeviceManager*)getSingleInstance DEPRECATED_ATTRIBUTE;

/**
 *  获取当前uSDK管理的设备列表。
 *
 *	@return	当前uSDK管理的设备列表
 */
- (NSArray<uSDKDevice*>*)getDeviceList;

/**
 *  根据类型获取当前uSDK管理的设备列表。
 *
 *  @param deviceType 根据设备类型筛选结果
 *
 *  @return 通过类型筛选后的设备列表
 */
- (NSArray<uSDKDevice*>*)getDeviceList:(uSDKDeviceTypeConst)deviceType;

/**
 *  根据设备ID获取指定设备
 *
 *  @param deviceID 设备ID
 *
 *  @return 根据设备ID得到的设备对象
 */
- (uSDKDevice*)getDeviceWithID:(NSString*)deviceID;

/**
 *   连接云，传入远程设备及云的相关信息。在Internet网络环境下，在有效会话期内，用户可以对设备进行远程操作，接收设备报警、状态、业务等消息。
 *
 *  @param remoteDevices      远程登录的设备列表，指与用户关联的设备，APP需要向云平台获取。获取到的设备基本信息可以通过创建uSDKDeviceInfo对象生成设备实例。
 *  @param token  远程会话token，此会话token是指用户登录云平台后获得的token
 *	@param 	domain  用户主网关域名。此域名由云平台分配，APP需要向云平台获取。
 *	@param 	port    用户主网关端口。此端口由云平台分配，APP需要向云平台获取。
 *  @param success      命令执行成功回调
 *  @param failure      命令执行失败回调，参数为错误原因
 */
- (void)connectToCloudWithDevices:(NSArray<uSDKDeviceInfo*>*)remoteDevices
                            token:(NSString*)token
                    gatewayDomain:(NSString*)domain
                      gatewayPort:(NSInteger)port
                          success:(void(^)()) success
                          failure:(void(^)(NSError *error)) failure;

/**
 *  断开云的连接。
 *
 *  @param token  远程会话token，此会话token是指用户登录云平台后获得的token
 *  @param success      命令执行成功回调
 *  @param failure      命令执行失败回调，参数为错误原因
 */
- (void)disconnectToCloudWithToken:(NSString*)token
                             success:(void(^)()) success
                             failure:(void(^)(NSError *error)) failure;

/**
 *  连接云，传入远程设备及云的相关信息。在Internet网络环境下，在有效会话期内，用户可以对设备进行远程操作，接收设备报警、状态、业务等消息。
 *
 *	@param 	token 远程会话token，此会话token是指用户登录云平台后获得的token。
 *	@param 	remoteDevices   远程设备列表，指与用户关联的设备，APP需要向云平台获取。获取到的设备基本信息可以通过uSDKDevice类的newRemoteDeviceInstance接口生成设备实例传递下来，详情请见uSDKDevice类。
 *	@param 	domain  用户主网关域名。此域名由云平台分配，APP需要向云平台获取。
 *	@param 	port    用户主网关端口。此端口由云平台分配，APP需要向云平台获取。
 *
 *	@return	返回执行结果信息
 */
- (uSDKErrorConst)remoteUserLogin:(NSString*)token withRemoteDevices:(NSArray<uSDKDevice*>*)remoteDevices withAccessGatewayDomain:(NSString*)domain withAccessGatewayPort:(NSInteger)port DEPRECATED_ATTRIBUTE;

/**
 *  登出设备的远程访问。
 *
 *	@return	返回执行结果信息
 */
- (uSDKErrorConst)remoteUserLogout DEPRECATED_ATTRIBUTE;

/**
 *  softap模式获取设备配置信息接口。此接口是在softap配置模式下获取当前模块可连接的 ssid 列表等配置信息，详细请见类uSDKDeviceConfigInfo。
 *  注：此接口已废弃，请使用getSoftapDeviceConfigInfoWithSuccess:failure:接口代替。
 *
 *	@return	返回设备配置类实例 设备配置信息，详细请见类uSDKDeviceConfigInfo
 */
-(uSDKDeviceConfigInfo*)getDeviceConfigInfo DEPRECATED_ATTRIBUTE;

/**
 *  softap模式获取设备配置信息接口。此接口是在softap配置模式下获取当前模块可连接的 ssid 列表等配置信息，详细请见类uSDKDeviceConfigInfo。
 *
 *  @param success 成功回调
 *  @param failure 失败回调
 */
- (void)getSoftapDeviceConfigInfoWithSuccess:(void(^)(uSDKDeviceConfigInfo* deviceConfigInfo)) success failure:(void(^)(NSError *error)) failure;

/**
 *  Softap模式配置设备接口
 *
 *  @param deviceConfigInfo 设备配置信息对象，该对象由getSoftapDeviceConfigInfoWithSuccess:failure:方法获得
 *  @param success          成功回调
 *  @param failure          失败回调
 */
- (void)configDeviceBySoftapWithConfigInfo:(uSDKDeviceConfigInfo*)deviceConfigInfo
                                   success:(void(^)()) success
                                   failure:(void(^)(NSError *error)) failure;


/**
 *  Softap模式配置设备接口(可定义配置是否安全)
 *
 *  @param deviceConfigInfo 设备配置信息对象，该对象由getSoftapDeviceConfigInfoWithSuccess:failure:方法获得
 *  @param security         设备配置是否为安全
 *  @param success          成功回调
 *  @param failure          失败回调
 */
- (void)configDeviceBySoftapWithConfigInfo:(uSDKDeviceConfigInfo*)deviceConfigInfo
                                  security:(BOOL)security
                                   success:(void(^)()) success
                                   failure:(void(^)(NSError *error)) failure;



/**
 *  SmartLink模式配置设备接口
 *
 *  @param ssid      接入点WIFI名称
 *  @param password  接入点WIFI密码
 *  @param success      命令执行成功回调，参数为配置成功的设备
 *  @param failure      命令执行失败回调，参数为错误原因
 */
- (void)configDeviceBySmartLinkWithSSID:(NSString*)ssid
                               password:(NSString*)password
                                success:(void(^)(uSDKDevice *device)) success
                                failure:(void(^)(NSError *error)) failure;//存在正在配置中的情况
/**
 *  SmartLink模式配置设备接口(自定义超时时间)
 *
 *  @param ssid      接入点WIFI名称
 *  @param password  接入点WIFI密码
 *  @param timeoutInterval 超时时间（单位是秒，范围为12秒-120秒）
 *  @param success      命令执行成功回调，参数为配置成功的设备
 *  @param failure      命令执行失败回调，参数为错误原因
 */
- (void)configDeviceBySmartLinkWithSSID:(NSString*)ssid
                               password:(NSString*)password
                        timeoutInterval:(NSTimeInterval)timeoutInterval
                                success:(void(^)(uSDKDevice *device)) success
                                failure:(void(^)(NSError *error)) failure;//存在正在配置中的情况

/**
 *   SmartLink模式配置设备接口（可指定deviceID）
 *
 *  @param ssid      接入点WIFI名称
 *  @param password  接入点WIFI密码
 *  @param deviceID  设备ID，目前均为设备MAC地址（MAC为无分隔符的字符串）
 *  @param success      命令执行成功回调，参数为配置成功的设备
 *  @param failure      命令执行失败回调，参数为错误原因
 */
- (void)configDeviceBySmartLinkWithSSID:(NSString*)ssid
                               password:(NSString*)password
                               deviceID:(NSString*)deviceID
                                success:(void(^)(uSDKDevice *device)) success
                                failure:(void(^)(NSError *error)) failure;

/**
 *  SmartLink模式配置设备接口(自定义超时时间和可指定deviceID)
 *
 *  @param ssid      接入点WIFI名称
 *  @param password  接入点WIFI密码
 *  @param timeoutInterval 超时时间（单位是秒，范围为12秒-120秒）
 *  @param deviceID  设备ID，目前均为设备MAC地址（MAC为无分隔符的字符串）
 *  @param success      命令执行成功回调，参数为配置成功的设备
 *  @param failure      命令执行失败回调，参数为错误原因
 */
- (void)configDeviceBySmartLinkWithSSID:(NSString*)ssid
                               password:(NSString*)password
                               deviceID:(NSString*)deviceID
                        timeoutInterval:(NSTimeInterval)timeoutInterval
                                success:(void(^)(uSDKDevice *device)) success
                                failure:(void(^)(NSError *error)) failure;


/**
 *  SmartLink模式配置设备接口(自定义超时时间和可指定deviceID和是否为安全配置)
 *
 *  @param ssid      接入点WIFI名称
 *  @param password  接入点WIFI密码
 *  @param deviceID  设备ID，目前均为设备MAC地址（MAC为无分隔符的字符串）
 *  @param timeoutInterval 超时时间（单位是秒，范围为12秒-120秒）
 *  @param security  配置是否为安全配置
 *  @param success      命令执行成功回调，参数为配置成功的设备
 *  @param failure      命令执行失败回调，参数为错误原因
 */
- (void)configDeviceBySmartLinkWithSSID:(NSString*)ssid
                               password:(NSString*)password
                               deviceID:(NSString*)deviceID
                        timeoutInterval:(NSTimeInterval)timeoutInterval
                               security:(BOOL)security
                                success:(void(^)(uSDKDevice *device)) success
                                failure:(void(^)(NSError *error)) failure;



/**
 *  获取Smartlink配置错误信息。
 *
 *  @param success 成功
 *  @param failure 失败
 */
-(void)getSmartLinkConfigErrorInfoWithSuccess:(void(^)(NSError *errorInfo)) success
                                      failure:(void(^)(NSError *error)) failure;

/**
 *  停止smartLink配置。
 *
 *  @param success 成功回调
 *  @param failure 失败回调
 */
- (void)stopSmartLinkConfig:(void(^)()) success
                    failure:(void(^)(NSError *error)) failure;

/**
 *  停止smartconfig配置。
 *
 *	@return	返回函数的执行结果
 */
-(uSDKErrorConst)stopDeviceConfig DEPRECATED_ATTRIBUTE;

/**
 *	@brief	功能描述：<br>
 *      smartconfig设备配置信息接口。<br>
 *
 *      注意：<br>
 *      每种类型的家电设备，进入配置模式的方法，需查看各设备的使用说明。 APP向设备发送配置信息之后，设备配置成功后会连接到配置的路由上。如果APP订阅了设备列表通知消息，会得知该设备上线。设备平均上线时间为20秒左右。
 *
 *
 *	@param 	ssid        配置模块连接的路由器的ssid
 *	@param 	password 	配置模块连接的路由器的密码【传入nil时，等同于@""，都是无密码的情况】
 *	@param 	error       如果返回值（uSDKDevice对象）是nil，在uSDKError对象里的code字段，描述了发生了什么错误。如果你没有兴趣可能发生的错误，传入nil。
 *
 *	@return	返回配置成功的设备
 */
- (uSDKDevice*)setDeviceSmartConfigV2Info:(NSString*)ssid withPassword:(NSString*)password error:(uSDKError**)error DEPRECATED_ATTRIBUTE;

/**
 *	@brief	功能描述：<br>
 *      smartconfig设备配置信息接口。<br>
 *
 *      注意：<br>
 *      每种类型的家电设备，进入配置模式的方法，需查看各设备的使用说明。 APP向设备发送配置信息之后，设备配置成功后会连接到配置的路由上。如果APP订阅了设备列表通知消息，会得知该设备上线。设备平均上线时间为20秒左右。
 *	@param 	ssid        配置模块连接的路由器的ssid
 *	@param 	password 	配置模块连接的路由器的密码【传入nil时，等同于@""，都是无密码的情况】
 *  @param  time        超时时间
 *	@param 	error       如果返回值（uSDKDevice对象）是nil，在uSDKError对象里的code字段，描述了发生了什么错误。如果你没有兴趣可能发生的错误，传入nil。
 *
 *	@return	返回配置成功的设备
 */
- (uSDKDevice*)setDeviceSmartConfigV2Info:(NSString*)ssid withPassword:(NSString*)password withTimeout:(NSTimeInterval)time error:(uSDKError**)error DEPRECATED_ATTRIBUTE;


/**
 *	@brief	功能描述：<br>
 *      smartconfig设备配置信息接口。<br>
 *
 *      注意：<br>
 *      每种类型的家电设备，进入配置模式的方法，需查看各设备的使用说明。 APP向设备发送配置信息之后，设备配置成功后会连接到配置的路由上。如果APP订阅了设备列表通知消息，会得知该设备上线。设备平均上线时间为20秒左右。
 *
 *	@param 	ssid        配置模块连接的路由器的ssid
 *	@param 	password 	配置模块连接的路由器的密码【传入nil时，等同于@""，都是无密码的情况】
 *  @param  deviceMac   配置模块的mac MAC地址格式为：0007A88A4D4D，不区分大小写
 *	@param 	error       如果返回值（uSDKDevice对象）是nil，在uSDKError对象里的code字段，描述了发生了什么错误。如果你没有兴趣可能发生的错误，传入nil。
 *
 *	@return	返回配置成功的设备
 */
- (uSDKDevice*)setDeviceSmartConfigV2Info:(NSString*)ssid withPassword:(NSString*)password withDeviceMac:(NSString*)deviceMac error:(uSDKError**)error DEPRECATED_ATTRIBUTE;

/**
 *	@brief	功能描述：<br>
 *      smartconfig设备配置信息接口。<br>
 *      注意：<br>
 *      每种类型的家电设备，进入配置模式的方法，需查看各设备的使用说明。 APP向设备发送配置信息之后，设备配置成功后会连接到配置的路由上。如果APP订阅了设备列表通知消息，会得知该设备上线。设备平均上线时间为20秒左右。
 *
 *	@param 	ssid        配置模块连接的路由器的ssid
 *	@param 	password 	配置模块连接的路由器的密码【传入nil时，等同于@""，都是无密码的情况】
 *  @param  deviceMac   配置模块的mac MAC地址格式为：0007A88A4D4D，不区分大小写
 *  @param  time        超时时间
 *	@param 	error       如果返回值（uSDKDevice对象）是nil，在uSDKError对象里的code字段，描述了发生了什么错误。如果你没有兴趣可能发生的错误，传入nil。
 *
 *	@return	返回配置成功的设备
 */

- (uSDKDevice*)setDeviceSmartConfigV2Info:(NSString*)ssid withPassword:(NSString*)password withDeviceMac:(NSString*)deviceMac withTimeout:(NSTimeInterval)time error:(uSDKError**)error DEPRECATED_ATTRIBUTE;

/**
 *	@brief	功能描述：<br>
 *      设置设备配置信息接口。uSDK支持两种设备配置模式：smartlink和softap。<br>
 *      当设备处于softap模式下，设备以热点模式存在，热点名称以“U_”或“haier_”开头，接口超时时间为5秒。 当设备处于smartlink模式下，设备不以热点存在，但接收udp广播的配置信息，接口立即返回。<br>
 *
 *      注意：<br>
 *      每种类型的家电设备，进入配置模式的方法，需查看各设备的使用说明。 APP向设备发送配置信息之后，设备配置成功后会连接到配置的路由上。如果APP订阅了设备列表通知消息，会得知该设备上线。设备平均上线时间为20秒左右。
 *
 *	@param 	deviceConfigMode 	配置模式，支持两种配置模式：smartlink和softap，请见uSDKDeviceConfigModeConst。
 *	@param 	waitingConfirm 	是否等待确认，值为false表示不等待模块配置确认立即返回；值为true表示等待模块配置确认后才返回，此时接口超时时间为1分钟。
 *	@param 	deviceConfigInfo 	配置信息，不能为null。如果是smartlink模式，只需填入要配置的路由ssid和密码
 *
 *	@return	返回配置结果信息
 */
- (uSDKErrorConst)setDeviceConfigInfo:(uSDKDeviceConfigModeConst)deviceConfigMode watitingConfirm:(BOOL)waitingConfirm deviceConfigInfo:(uSDKDeviceConfigInfo*)deviceConfigInfo DEPRECATED_ATTRIBUTE;

/**
 *  通过极路由配置设备接口(自定义超时时间和可指定deviceID)
 *
 *  @param deviceID  设备ID，目前均为设备MAC地址（MAC为无分隔符的字符串）
 *  @param timeoutInterval 超时时间（单位是秒，范围为12秒-120秒）
 *  @param success      命令执行成功回调，参数为配置成功的设备
 *  @param failure      命令执行失败回调，参数为错误原因
 */
- (void)configDeviceByHiRouterWithDeviceID:(NSString*)deviceID
                           timeoutInterval:(NSTimeInterval)timeoutInterval
                                   success:(void(^)(uSDKDevice *device)) success
                                   failure:(void(^)(NSError *error)) failure;

@end


/**
 *  uSDKDeviceManager对象的代理协议，包括设备增加、删除、绑定、解绑及云连接状态消息。
 */
@protocol uSDKDeviceManagerDelegate <NSObject>

@optional

/**
 *  发现设备消息（该消息为实时消息）
 *
 *  @param deviceManager 设备管理器对象
 *  @param devices       新增的设备数组
 */
-(void)deviceManager:(uSDKDeviceManager*)deviceManager didAddDevices:(NSArray<uSDKDevice*>*)devices;

/**
 *  删除设备消息（该消息为实时消息）
 *
 *  @param deviceManager 设备管理器对象
 *  @param devices       删除的设备数组
 */
-(void)deviceManager:(uSDKDeviceManager*)deviceManager didRemoveDevices:(NSArray<uSDKDevice*>*)devices;

/**
 *  设备绑定
 *
 *  @param deviceManager 设备管理器对象
 *  @param deviceID   绑定设备的ID
 */
-(void)deviceManager:(uSDKDeviceManager*)deviceManager didBindDevice:(NSString*)deviceID;

/**
 *  设备解绑定
 *
 *  @param deviceManager 设备管理器对象
 *  @param deviceID   解绑定设备的ID
 */
-(void)deviceManager:(uSDKDeviceManager*)deviceManager didUnbindDevice:(NSString*)deviceID;

/**
 *  云连接状态更新
 *
 *  @param deviceManager 设备管理器对象
 *  @param state         云平台连接状态
 *  @param offlineReason 离线原因
 */
-(void)deviceManager:(uSDKDeviceManager*)deviceManager didUpdateCloudState:(uSDKCloudConnectionState)state error:(NSError*)offlineReason;

@end

