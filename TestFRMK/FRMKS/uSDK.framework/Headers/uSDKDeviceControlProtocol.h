//
//  uSDKDeviceControlProtocol.h
//  uSDKDeviceLocal
//
//  Created by liugn on 2016/9/28.
//  Copyright © 2016年 haier. All rights reserved.
//

#import <Foundation/Foundation.h>

@class uSDKMutableDevice,PMDeviceAttrReadReq,PMDeviceAttrReadResp,PMDeviceAttrWriteReq,PMDeviceAttrWriteResp,PMDeviceOperReq,PMDeviceOperResp,uSDKCommandPackage,uSDKRequestDataInfo;

//对内暴露的设备对象接口
@protocol uSDKDeviceControlProtocol <NSObject>

@optional

-(void)connectWithDevice:(uSDKMutableDevice*)device error:(NSError **) error;

-(void)disconnectWithDevice:(uSDKMutableDevice*)device error:(NSError **) error;

-(PMDeviceAttrReadResp*)readAttrWithReqModel:(PMDeviceAttrReadReq*)reqModel sendData:(uSDKRequestDataInfo*)sendData timeoutInterval:(double)timeoutInterval ;

-(PMDeviceAttrWriteResp*)writeAttrWithReqModel:(PMDeviceAttrWriteReq*)reqModel sendData:(uSDKRequestDataInfo*)sendData timeoutInterval:(double)timeoutInterval ;

-(PMDeviceOperResp*)operateDeviceWithReqModel:(PMDeviceOperReq*)reqModel sendData:(uSDKRequestDataInfo*)sendData timeoutInterval:(double)timeoutInterval ;

-(void)sendMsg2ServerWithData:(uSDKCommandPackage*)package ;

@end


