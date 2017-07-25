//
//  uAccount.h
//  uAccountTest
//
//  Created by like on 16/9/29.
//  Copyright © 2016年 haierubic. All rights reserved.
//

#import <Foundation/Foundation.h>
@class RespCommonModel;
@class UacUserBase;
@class UacDevice;

#define UACCOUNT_VERSION @"1.1.01"
#define UACCOUNT_BUILD_DATE @"2017021717"


/**
 uAccount管理类，通过这个类来调用所有的接口
 */
@interface uAccount : NSObject

/**
 *  获取uAccount单例对象
 *
 *  @return 返回uAccount对象
 */
+ (uAccount *)defaultUAccount;
/**
 *  设置uAccount基础信息
 *
 *  @param baseUrl 基本URL，不能为空，  开发者环境为：https://developer.haier.net:6503   生产环境为 https://uhome.haier.net:6503
 *  @param appId   云平台分配的appid，不能为空
 *  @param appKey  云平台分配的appkey，不能为空
 */
- (void)startWithBaseUrl:(NSString *)baseUrl
                   appId:(NSString *)appId
                  appKey:(NSString *)appKey;


/**
 *  登录 此方法为异步方法，不会阻塞线程，执行结果会在回调函数中以参数形式返回，不需要登录可以访问。
 *
 *  @param loginId     登录账户，不能为空，可以填写手机号、邮箱或者loginName，格式需要符合要求，详见接口文档
 *  @param password    登录密码，不能为空
 *  @param deviceToken 非必填项，可填 @“” 或 nil
 *  @param success     成功的回调
 *  @param failure     失败的回调
 *  @param httpError   网络异常的回调
 */
- (void)loginWithLoginId:(NSString *)loginId
                password:(NSString *)password
             deviceToken:(NSString *)deviceToken
                 success:(void(^)(NSString *result))success
                 failure:(void(^)(RespCommonModel *failure))failure
               httpError:(void(^)(RespCommonModel *httpError))httpError;

/**
 *  申请激活码（注册前） 此方法为异步方法，不会阻塞线程，执行结果会在回调函数中以参数形式返回，不需要登录可以访问。
 *
 *  @param mobile    申请激活码的手机号 ，手机号的格式需要符合要求，详见接口文档
 *  @param success   成功的回调
 *  @param failure   失败的回调
 *  @param httpError 网络异常的回调
 */
- (void)applyActivationCodeWithMobile:(NSString *)mobile
                              success:(void(^)(RespCommonModel *success))success
                              failure:(void(^)(RespCommonModel *failure))failure
                            httpError:(void(^)(RespCommonModel *httpError))httpError;

/**
 *  使用激活码注册并登录 此方法为异步方法，不会阻塞线程，执行结果会在回调函数中以参数形式返回，不需要登录可以访问。
 *
 *  @param password       您将要注册账号的密码， 长度为6~20位，不允许使用@#￥%&*等特殊字符
 *  @param activationcode 短信收到的激活码
 *  @param success        成功的回调，返回唯一的userID
 *  @param failure        失败的回调
 *  @param httpError      网络异常的回调
 */
- (void)registerAndloginWithPassword:(NSString *)password
                      activationcode:(NSString *)activationcode
                             success:(void(^)(NSString *result))success
                             failure:(void(^)(RespCommonModel *failure))failure
                           httpError:(void(^)(RespCommonModel *httpError))httpError;


/**
 *  修改密码 此方法为同步方法，会阻塞线程，登录后访问。
 *
 *  @return 返回固定的H5的URL地址
 */
- (NSString *)modifyPassword;


/**
 *  获取设备列表 此方法为异步方法，不会阻塞线程，执行结果会在回调函数中以参数形式返回，登录后访问。
 *
 *  @param mainType  设备大类  可以为nil，如果输入，则只返回符合指定大类的设备
 *  @param typeId    设备类型唯一识别码 可以为nil ，如果输入，则只返回符合指定设备类型唯一识别码的设备，覆盖设备大类过滤条件
 *  @param success   成功的回调
 *  @param failure   失败的回调
 *  @param httpError 网络错误的回调
 */
- (void)getDeviceListWithMainType:(NSString *)mainType
                           typeId:(NSString *)typeId
                          success:(void(^)(NSArray<UacDevice *> *failedIds))success
                          failure:(void(^)(RespCommonModel *failure))failure
                        httpError:(void(^)(RespCommonModel *httpError))httpError;


/**
 *  绑定设备 此方法为异步方法，不会阻塞线程，执行结果会在回调函数中以参数形式返回，登录后访问。
 *
 *  @param deviceId  设备唯一id
 *  @param name      设备名字
 *  @param typeId    设备类型唯一识别码
 *  @param success   成功的回调，返回绑定不成功设备id列表
 *  @param failure   失败的回调
 *  @param httpError 网络异常的回调
 */
- (void)bindDevicesWithDevicesId:(NSString *)deviceId
                      deviceName:(NSString *)name
                          typeId:(NSString *)typeId
                         success:(void(^)(NSArray<NSString *> *failedIds))success
                         failure:(void(^)(RespCommonModel *failure))failure
                       httpError:(void(^)(RespCommonModel *httpError))httpError;

/**
 *  解绑设备 此方法为异步方法，不会阻塞线程，执行结果会在回调函数中以参数形式返回，登录后访问。
 *
 *  @param deviceId  设备唯一ID
 *  @param success   成功的回调
 *  @param failure   失败的回调
 *  @param httpError 网络异常的回调
 */
- (void)unbindDevicesWithDeviceId:(NSString *)deviceId
                          success:(void(^)(RespCommonModel *success))success
                          failure:(void(^)(RespCommonModel *failure))failure
                        httpError:(void(^)(RespCommonModel *httpError))httpError;

/**
 *  退出 此方法为异步方法，不会阻塞线程，执行结果会在回调函数中以参数形式返回，登录后访问。
 *
 *  @param success   成功的回调
 *  @param failure   失败的回调
 *  @param httpError 网络异常的回调
 */
- (void)logoutWithSuccess:(void(^)(RespCommonModel *success))success
                  failure:(void(^)(RespCommonModel *failure))failure
                httpError:(void(^)(RespCommonModel *httpError))httpError;


/**
 *  获取登录用户基础信息 此方法为异步方法，不会阻塞线程，执行结果会在回调函数中以参数形式返回，登录后访问。
 *
 *  @param success   成功的回调
 *  @param failure   失败的回调
 *  @param httpError 网络异常的回调
 */
- (void)getUserBaseInfoSuccess:(void(^)(UacUserBase *success))success
                       failure:(void(^)(RespCommonModel *failure))failure
                     httpError:(void(^)(RespCommonModel *httpError))httpError;


/**
 *  修改设备昵称 此方法为异步方法，不会阻塞线程，执行结果会在回调函数中以参数形式返回，登录后访问。
 *
 *  @param deviceId  设备唯一ID，不能为空
 *  @param name      设备的新昵称，不能为空
 *  @param success   成功的回调
 *  @param failure   失败的回调
 *  @param httpError 网络异常的回调
 */
- (void)updateNicknameWithDeviceId:(NSString *)deviceId
                           newName:(NSString *)name
                           success:(void(^)(RespCommonModel *success))success
                           failure:(void(^)(RespCommonModel *failure))failure
                         httpError:(void(^)(RespCommonModel *httpError))httpError;


/**
 *  申请绑定手机号的验证码 此方法为异步方法，不会阻塞线程，执行结果会在回调函数中以参数形式返回，登录后访问。
 *
 *  @param email     电子邮箱，需要符合邮箱格式，详见接口文档
 *  @param mobile    想要绑定的手机号，需要符合手机的格式，详见接口文档
 *  @param success   成功的回调
 *  @param failure   失败的回调
 *  @param httpError 网络异常的回调
 */
- (void)applyBindMobileCodeWithEmail:(NSString *)email
                              mobile:(NSString *)mobile
                             success:(void(^)(RespCommonModel *success))success
                             failure:(void(^)(RespCommonModel *failure))failure
                           httpError:(void(^)(RespCommonModel *httpError))httpError;


/**
 *  用验证码绑定手机号 此方法为异步方法，不会阻塞线程，执行结果会在回调函数中以参数形式返回，登录后访问。
 *
 *  @param activationcode 短信收到的验证码
 *  @param success        成功的回调
 *  @param failure        失败的回调
 *  @param httpError      网络异常的回调
 */
- (void)bindMobileWithActivationcode:(NSString *)activationcode
                             success:(void(^)(RespCommonModel *success))success
                             failure:(void(^)(RespCommonModel *failure))failure
                           httpError:(void(^)(RespCommonModel *httpError))httpError;


/**
 *  找回密码 此方法为同步方法，会阻塞线程，不需要登录可以访问。
 *
 *  @return 返回固定的H5的URL
 */
- (NSString *)findPassword;

/**
 *  用户登录后，获取AccessToken
 *
 *  @return 返回AccessToken
 */
- (NSString *)getAccessToken;


/**
 *  自定义请求接口，此接口适用于openapi二期文档中的接口，默认都是POST请求，请求头部分已经内部处理完成，这里只需传入URL地址和请求体即可。返回的数据是JSON数据，需要自行解析。**注意** 该接口不能用于 用户登录 和 退出功能，该接口登录后访问。
 *
 *  @param detailedURL URL地址，**注意**：输入的是整个URL的后半部分， 如： 获取设备列表接口 对应的地址为  /openapi/v2/device/queryList
 *  @param httpBody    请求体，如果没有  可以为 nil 或 @{}
 *  @param result      服务器返回的JSON数据
 *  @param failure     失败的回调
 */
- (void)sendCustomRequestWithURL:(NSString *)detailedURL
                        httpBody:(NSDictionary *)httpBody
                          result:(void(^)(NSData *data))result
                         failure:(void(^)(RespCommonModel *failure))failure;

@end
