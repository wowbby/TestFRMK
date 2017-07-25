//
//  RespCommonModel.h
//  uAccountTest
//
//  Created by like on 16/10/9.
//  Copyright © 2016年 haierubic. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  公共错误码，包含了错误码以及错误的具体情况描述
 */
@interface RespCommonModel : NSObject
/**
 *  错误码
 */
@property (nonatomic,copy) NSString *retCode;
/**
 *  错误描述，根据具体情况描述
 */
@property (nonatomic,copy) NSString *retInfo;


- (instancetype)initWithRetCode:(NSString*)retCode retInfo:(NSString*)retInfo;

@end
