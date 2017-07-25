//
//  uSDKDeviceAlarm.h
//  uSDK
//
//  Created by liugn on 15/12/9.
//  Copyright © 2015年 haier. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "uSDKDeviceAttribute.h"

/**
 *   uSDK设备报警信息类，用于描述设备的报警消息。
 */
@interface uSDKDeviceAlarm : NSObject{
    NSString *_alarmTimestamp;
}

/**
 *  报警名称
 */
@property (nonatomic, copy, readonly) NSString* name;

/**
 *  报警描述
 */
@property (nonatomic, copy, readonly) NSString* value;

/**
 *   六位码协议的报警信息  报警消息中存储的是报警消息ID，即设备ID文档中报警ID集合的报警属性。每种设备都有各自的报警ID集合，APP需要通过设备ID文档自行匹配对应的报警描述。
 */
@property (nonatomic, copy) NSString* alarmMessage;

/**
 *   六位码协议的报警时间   时间格式为yyyy-MM-dd HH:mm:ss.SSS，即年-月-日 时:分:秒.毫秒（其中小时为24小时制），例如2013-01-05 23:37:27.323
 */
@property (nonatomic, copy) NSString* alarmTimestamp;

/**
 *  根据name和value初始化
 *
 *  @param name  属性名
 *  @param value 属性值
 *
 *  @return 返回初始化的属性对象
 */
-(instancetype)initWithName:(NSString*)name vlaue:(NSString*) value;

@end

