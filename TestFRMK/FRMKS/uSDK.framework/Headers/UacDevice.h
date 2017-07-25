//
//  Device.h
//  uAccountTest
//
//  Created by like on 16/10/11.
//  Copyright © 2016年 haierubic. All rights reserved.
//

#import <Foundation/Foundation.h>
@class UacDeviceAttribute;
@class UacDeviceTypeInfo;
@class UacDeviceModulesInfo;
@class UacDeviceLocation;
@class UacDeviceAddress;
@class UacModulesInfoItem;
@class UacDeviceSafe;


/**
 *  UacDevice 类，包含设备的一些基本信息等
 */
@interface UacDevice : NSObject
/**
 *  设备ID
 */
@property (nonatomic,copy) NSString *id;
/**
 *  设备昵称
 */
@property (nonatomic,copy) NSString *name;
/**
 *  设备属性
 */
@property (nonatomic,strong) UacDeviceAttribute *attrs;
/**
 *  设备类型信息
 */
@property (nonatomic,strong) UacDeviceTypeInfo *typeInfo;
/**
 *  设备模块信息
 */
@property (nonatomic,strong) NSArray<UacDeviceModulesInfo *> *deviceModules;
/**
 *  设备位置
 */
@property (nonatomic,strong) UacDeviceLocation *location;
/**
 *  设备地址
 */
@property (nonatomic,strong) UacDeviceAddress *address;
/**
 *  设备状态
 */
@property (nonatomic,assign) BOOL status;

- (instancetype)initWithId:(NSString *)id withName:(NSString *)name withtypeInfo:(NSString *)typeId;

@end

//------------------

/**
 安全设备类，是设备类的子类，增加key字段
 */
@interface UacDeviceSafe : UacDevice


/**
 调用usdk得到的dev密文
 */
@property (nonatomic,copy) NSString *key;

- (instancetype)initWithId:(NSString *)id Name:(NSString *)name typeInfo:(NSString *)typeId key:(NSString *)key;


@end









//----------------------

/**
 设备属性
 */
@interface UacDeviceAttribute : NSObject
/**
 *  品牌
 */
@property (nonatomic,copy) NSString *brand;
/**
 *  型号
 */
@property (nonatomic,copy) NSString *model;

@end

//----------------------

/**
 设备地址信息
 */
@interface UacDeviceAddress : NSObject
/**
 *  城市代码
 */
@property (nonatomic,strong) NSString *cityCode;
/**
 *  城市名称
 */
@property (nonatomic,strong) NSString *cityName;
/**
 *  城市英文名称
 */
@property (nonatomic,strong) NSString *cityEName;
/**
 *  区
 */
@property (nonatomic,strong) NSString *districtName;
/**
 *  省市
 */
@property (nonatomic,strong) NSString *provinceName;
/**
 *  国家
 */
@property (nonatomic,strong) NSString *countryName;

@end

//----------------------

/**
 设备的经度、纬度信息
 */
@interface UacDeviceLocation : NSObject
/**
 *  经度
 */
@property (nonatomic,strong) NSString *longitude;
/**
 *  纬度
 */
@property (nonatomic,strong) NSString *latitude;

@end

//----------------------

/**
 设备的类别信息
 */
@interface UacDeviceTypeInfo : NSObject
/**
 *  设备大类
 */
@property (nonatomic,strong) NSString *mainType;
/**
 *  设备分类
 */
@property (nonatomic,strong) NSString *deviceType;
/**
 *  设备类型唯一标识码
 */
@property (nonatomic,strong) NSString *typeId;
@end

//----------------------

/**
 设备模块的信息
 */
@interface UacDeviceModulesInfo : NSObject
/**
 *  模块ID
 */
@property (nonatomic,copy) NSString *moduleId;
/**
 *  模块类型
 */
@property (nonatomic,copy) NSString *moduleType;
/**
 *  模块信息列表
 */
@property (nonatomic,strong) NSArray<UacModulesInfoItem *> *moduleInfos;

@end


//----------------------

/**
 模块详细的信息
 */
@interface UacModulesInfoItem : NSObject
/**
 *  模块信息字段
 */
@property (nonatomic,copy) NSString *key;
/**
 *  模块信息值
 */
@property (nonatomic,copy) NSString *value;

@end
//----------------------


