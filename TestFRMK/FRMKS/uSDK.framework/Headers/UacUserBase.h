//
//  UserBase.h
//  uAccountTest
//
//  Created by like on 16/10/10.
//  Copyright © 2016年 haierubic. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 用户基本信息，包括ID，用户名，邮箱手机等信息
 */
@interface UacUserBase : NSObject
/**
 *  用户ID,由系统生成
 */
@property (nonatomic,copy) NSString *id;
/**
 *  登录名
 */
@property (nonatomic,copy) NSString *loginName;
/**
 *  邮箱
 */
@property (nonatomic,copy) NSString *email;
/**
 *  手机号
 */
@property (nonatomic,copy) NSString *mobile;
/**
 *  状态值，0：已激活，1：已注册
 */
@property (nonatomic,assign) NSInteger status;


- (instancetype)initWithId:(NSString *)id withEmail:(NSString *)email withLoginName:(NSString *)loginName withMobile:(NSString *)mobile withStatus:(NSInteger)status;
@end
