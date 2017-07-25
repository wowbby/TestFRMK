//
//  uSDKDeviceBase.h
//  uSDKDeviceLocal
//
//  Created by liugn on 2016/10/18.
//  Copyright © 2016年 haier. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "uSDKDeviceInfo.h"
#import "uSDKDeviceControlProtocol.h"
#import "uSDKArgument.h"
#import "uSDKDeviceProtocol.h"
#import "uSDKDeviceAlarm.h"

/**
 *	设备信号强度等级
 */
typedef NS_ENUM(NSInteger,uSDKDeviceSignalStrengthLevel) {
    uSDKDeviceSignalStrengthLevelLow = 0,
    uSDKDeviceSignalStrengthLevelMiddle,
    uSDKDeviceSignalStrengthLevelHigh,
};


@class uSDKSubDevice;

/**
 *  uSDK设备实体类，用于描述设备的基本信息、网络信息和网络状态，缓存当前的运行状态和报警，提供执行设备操作能力，接收属性上报。
 */
@interface uSDKDevice : uSDKDeviceInfo<uSDKDeviceProtocol>{
    @public
    NSMutableDictionary* _attributeDict;
    NSMutableArray* _alarmList;
}

/**
 *  设备代理，用于接收回调消息（设备状态变化、属性变化、报警等）
 */
@property (nonatomic, weak) id<uSDKDeviceDelegate> delegate;

/**
 *   设备属性状态集合。设备属性状态是指每种设备所特有的运行时状态，例如空调的当前环境温度、洗衣机当前剩余的洗涤时间等。每一种设备都有多个功能状态，在这个集合中，可以以属性名称为关键字，找到对应的属性状态；
 */
@property (nonatomic, strong ,readonly) NSDictionary<NSString*,uSDKDeviceAttribute*>* attributeDict;

/**
 *   设备报警信息集合。设备每次报警时，会上报一条或多条报警信息，uSDK会将这些报警信息放入报警列表中。uSDK只保存设备最近一次发生的报警；
 */
@property (nonatomic, strong ,readonly) NSArray<uSDKDeviceAlarm*>* alarmList;

/**
 *  设备的子设备列表
 */
@property (nonatomic, strong , readonly) NSArray<uSDKSubDevice*>* subDeviceList;


-(id<uSDKDeviceControlProtocol>)getDeviceControlAPI;//todo:remove this

- (void)executeOperation:(NSString*)operationName
                    args:(NSArray<uSDKArgument*>*)args
              subDevices:(NSArray<uSDKSubDevice*>*)subDevices
          requestPackage:(uSDKCommandPackage*)reqPkgData
        deviceControlAPI:(id<uSDKDeviceControlProtocol>)deviceControlAPI;//todo:remove this

/**
 *  APP通过解析获取到的远程家电设备json内容得到设备信息，生成远程家电设备对象。
 *
 *	@param 	deviceMac   家电设备Mac地址
 *	@param 	deviceTypeIdentifier 	家电设备类型唯一标识码
 *	@param 	online 	家电设备的网络状态
 *	@param 	smartLinkVersion 	家电设备wifi的软件版本
 *  @param 	smartLinkPlatform 	家电设备wifi的平台信息（用于区分水净化系统及老空调系列模块）
 *
 *	@return	返回家电设备实例
 */
+ (uSDKDevice*)newRemoteDeviceInstance:(NSString*)deviceMac withDeviceTypeIdentifier:(NSString*)deviceTypeIdentifier withOnline:(uSDKDeviceState)online withSmartLinkVersion:(NSString*)smartLinkVersion withSmartLinkPlatform:(NSString*)smartLinkPlatform DEPRECATED_ATTRIBUTE;


/**
 *  连接设备，连接后会收到该设备的相关消息。需要对设备对象设置delegate，才能收到相应设备的消息。注意：调用该方法连接的设备没有就绪状态。
 *
 *  @param success   成功回调
 *  @param failure   失败回调
 */
-(void)connectWithSuccess:(void(^)())success
                  failure:(void(^)(NSError *error)) failure;

/**
 *  连接设备同时自动查询设备的所有属性，连接后会收到该设备的相关消息。需要对设备对象设置delegate，才能收到相应设备的消息。注意：调用该方法连接的设备有就绪状态。
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

/**
 *   此函数可执行设备组命令和设备单命令。每一种设备都有自己特定的命令集，详细的命令集描述请参看对应的设备ID文档。 设备单命令指命令名称和参数，例如洗衣机的启动、空调的设置温度等。如果单命令执行成功，uSDK更新设备的当前状态。 设备组命令需要严格遵守设备ID文档中的组命令格式，每条组命令都通过组命令名称来标识。如果组命令执行成功，设备状态的变化会随后通过消息通知方式通知APP。
 *
 *	@param 	cmdList 要执行的设备操作列表，列表不能为null或空，设备操作列表中存放单个或一组命令。如果执行的是单命令，此列表中只存放一条命令；如果执行的是组命令，此列表中存放的是一组命令。
 *	@param 	cmdsn   命令sn 操作命令序号，由UI生成。如果传值为0，表示APP不关心操作命令的执行顺序；如果传值为正整数，表示APP需要把操作命令与执行结果对应起来。
 *	@param 	groupCmdName    组命令名称  组命令名称。如果执行的是组命令，组命令名称请查询对应的设备ID文档。如果要执行的是单命令，没有组命令名称，此参数应传入null或""。
 *
 *	@return	设备操作的执行结果
 */
- (uSDKErrorConst)execDeviceOperation:(NSMutableArray*)cmdList withCmdSN:(int)cmdsn withGroupCmdName:(NSString*)groupCmdName DEPRECATED_ATTRIBUTE;

/**
 *   此函数可执行设备组命令和设备单命令，接口超时时间为5秒。每一种设备都有自己特定的命令集，详细的命令集描述请参看对应的设备ID文档。 设备单命令指命令名称和参数，例如洗衣机的启动、空调的设置温度等。如果单命令执行成功，uSDK更新设备的当前状态。 设备组命令需要严格遵守设备ID文档中的组命令格式，每条组命令都通过组命令名称来标识。如果组命令执行成功，设备状态的变化会随后通过消息通知方式通知APP。
 *      注意：此方法不可用于发送单命令
 *
 *	@param 	cmdList 要执行的设备操作列表，列表不能为null或空，设备操作列表中存放单个或一组命令。如果执行的是单命令，此列表中只存放一条命令；如果执行的是组命令，此列表中存放的是一组命令。
 *	@param 	cmdsn   命令sn 操作命令序号，由UI生成。如果传值为0，表示APP不关心操作命令的执行顺序；如果传值为正整数，表示APP需要把操作命令与执行结果对应起来。
 *	@param 	groupName    组命令名称  组命令名称。如果执行的是组命令，组命令名称请查询对应的设备ID文档。如果要执行的是单命令，没有组命令名称，此参数应传入0。
 *
 *	@return	设备操作的执行结果
 */
- (uSDKErrorInfo*)execDeviceOperation:(NSMutableArray*)cmdList withCmdSN:(int)cmdsn withGroupName:(int)groupName DEPRECATED_ATTRIBUTE;

/**
 *  写入设备属性值,回调中只返回是否成功,如果写入成功，设备对应的属性值会在设备属性变化上报中更新。注：此方法可用于发送单命令.
 *
 *  @param name    属性名
 *  @param value   属性值
 *  @param subDevices    子机对象数组
 *  @param timeoutInterval 超时时间（12-120秒）
 *  @param success 成功
 *  @param failure 失败
 */
-(void)writeAttributeWithName:(NSString*)name
                        value:(NSString*)value
                   subDevices:(NSArray<uSDKSubDevice*>*)subDevices
              timeoutInterval:(NSTimeInterval)timeoutInterval
                      success:(void(^)()) success
                      failure:(void(^)(NSError *error)) failure;

/**
 *  执行设备命令操作，可自定义超时时间。每一种设备都有自己特定的命令集，详细的命令集描述请参看对应的设备ID文档。
 *
 *  @param operationName   要执行的设备操作命令
 *  @param args            要执行的设备操作命令参数列表
 *  @param subDevices      子机对象数组
 *  @param timeoutInterval 超时时间（12-120秒）
 *  @param success         命令执行成功回调
 *  @param failure         命令执行失败回调
 */
- (void)executeOperation:(NSString*)operationName
                    args:(NSArray<uSDKArgument*>*)args
              subDevices:(NSArray<uSDKSubDevice*>*)subDevices
         timeoutInterval:(NSTimeInterval)timeoutInterval
                 success:(void(^)()) success
                 failure:(void(^)(NSError *error)) failure;


/**
 *  配置模块主网关域名和端口，默认超时时间为5秒。国内主网关：gw.haier.net 端口：56808  海外主网关：gw.haieriot.net 端口：56808
 *
 *  @param domain  主网关域名
 *  @param port    端口号
 *  @param success 命令执行成功回调
 *  @param failure 命令执行失败回调
 */
- (void)setDeviceGatewayWithDomain:(NSString *)domain
                              port:(NSInteger)port
                           success:(void(^)()) success
                           failure:(void(^)(NSError *error)) failure;

/**
 *  获取设备绑定信息
 *
 *  @param token 登录后云平台分配的token
 *  @param success 成功回调
 *  @param failure 失败回调
 */
- (void)getDeviceBindInfoWithToken:(NSString *)token
                           success:(void(^)(NSString *info)) success
                           failure:(void(^)(NSError *error)) failure;

/**
 *  获取设备绑定信息--同步方法
 *
 *  @param token 登录后云平台分配的token
 *  @param error 错误信息
 *  @return 设备绑定信息
 */
- (NSString *)getDeviceBindInfoWithToken:(NSString *)token error:(NSError**)error;

/**
 *  获取设备信号强度信息
 *
 *  @param token 登录后云平台分配的token
 *  @param success 成功回调
 *  @param failure 失败回调
 */
- (void)getSignalStrengthWithToken:(NSString *)token
                           success:(void(^)(uSDKDeviceSignalStrengthLevel signalStrengthLevel,NSInteger signalStrengthValue)) success
                           failure:(void(^)(NSError *error)) failure;

@end



/**
 *  uSDKDevice对象代理协议，用于接收回调消息（设备状态变化、属性变化、报警等）
 */
@protocol uSDKDeviceDelegate <NSObject>

@optional

/**
 *  设备基本信息变化（netType和ip）
 *
 *  @param device   信息变化的设备
 */
-(void)deviceDidUpdateBaseInfo:(uSDKDevice*)device;

/**
 *  设备在线状态变化
 *
 *  @param device   状态变化的设备
 *  @param state    变化后的状态
 *  @param error  离线原因
 */
-(void)device:(uSDKDevice*)device didUpdateState:(uSDKDeviceState)state error:(NSError*)error;

/**
 *  设备属性状态变化
 *
 *  @param device     设备对象
 *  @param attributes 属性发生变化的集合
 */
-(void)device:(uSDKDevice*)device didUpdateVlaueForAttributes:(NSArray<uSDKDeviceAttribute*>*)attributes ;

/**
 *  设备报警列表
 *
 *  @param device 发生报警的设备对象
 *  @param alarms 报警信息列表，列表中数据类型为uSDKDeviceAlarm
 */
-(void)device:(uSDKDevice*)device didReceiveAlarms:(NSArray<uSDKDeviceAlarm*>*)alarms ;

/**
 *  子机设备列表变化
 *
 *  @param device           主机设备
 *  @param subDevices       新增的子机设备列表
 */
-(void)device:(uSDKDevice*)device didAddSubDevices:(NSArray<uSDKSubDevice*>*)subDevices;

@end


/**
 *    子设备类，包含子设备特有属性，能查看父设备，执行命令
 */
@interface uSDKSubDevice : uSDKDevice{
    NSString* _subId;
    NSInteger _subType;
    __weak uSDKDevice* _parentDevice;
}

/**
 *	@brief	功能描述：<br>
 *      复杂类设备子机号；此变量只读，设置无效
 */
@property (nonatomic, strong,readonly) NSString* subId;

/**
 *	@brief	功能描述：<br>
 *      一拖多设备子机类型；此变量只读，设置无效 <br>
 *      0：所有子设备，包括室内机和室外机；1：室内机；2：室外机；-1：未知
 */
@property (nonatomic, assign,readonly) NSInteger subType;

/**
 *	@brief	功能描述：<br>
 *      子设备所属父设备
 */
@property (nonatomic, weak,readonly) uSDKDevice* parentDevice;

-(instancetype)initWithID:(NSString*)subId parentDevice:(uSDKDevice*)parentDevice;

@end
