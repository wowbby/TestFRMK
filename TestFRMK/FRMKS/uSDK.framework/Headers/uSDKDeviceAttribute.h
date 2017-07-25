//
//  uSDKDeviceAttribute.h
//  uSDK
//
//  Created by liugn on 15/12/9.
//  Copyright © 2015年 haier. All rights reserved.
//

#import <Foundation/Foundation.h>

@class uSDKDevice;

/**
 *   uSDK设备属性类。
 */
@interface uSDKDeviceAttribute : NSObject{
    
}

@property (nonatomic, weak, readonly) uSDKDevice* device;

/**
 *   设备属性名 属性名称对应于设备ID文档中命令ID集合中的功能识别码；此变量只读，设置无效
 */
@property (nonatomic, copy) NSString* attrName;

/**
 *   设备属性值 对应于设备ID文档中命令ID集合中的属性参数编码；此变量只读，设置无效
 */
@property (nonatomic, copy) NSString* attrValue;

/**
 *  创建并初始化家电设备属性实例。在APP向设备发送操作命令时使用。当APP下发操作命令时，需要将ID文档中的ID操作转换为操作命令对象
 *
 *	@param 	attrName 	家电设备属性名
 *	@param 	attrValue 	家电设备属性值
 *
 *	@return	返回家电设备属性实例
 */
- (id)initWithAttrName:(NSString*)attrName withAttrValue:(NSString*)attrValue;

@end