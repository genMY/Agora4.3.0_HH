//
//  HHAgoraAdapter.m
//  HHLiveSDK
//
//  Created by lijunjie on 2020/9/9.
//  Copyright © 2020 lijunjie. All rights reserved.
//

#import "HHAgoraAdapter.h"
#import <HHLiveSDK/HHLiveStats.h>
#import <HHLiveSDK/HHLiveEngineType.h>
#import <HHLiveSDK/HHLiveEngineManager.h>
#import <HHLiveSDK/HHLiveWhiteListManager.h>
#import <HHLiveSDK/HHLiveConstant.h>
#import <HHLiveSDK/HHLiveLogManager.h>
#import <HHLiveSDK/HHLiveVideoProfile.h>
#import "HHAgoraVideoRender.h"
#import "HHLiveAgoraAudioFrameObserver.h"
#import "HHAgoraAudioDumpManager.h"
#import <sys/utsname.h>

@import AgoraRtcKit;
@import CUCoreFoundation;
@import ESLogger;
@import HHNavigationConfig;

@interface HHAgoraAdapter () <AgoraRtcEngineDelegate>

@property (nonatomic, strong) AgoraRtcEngineKit *rtcEngine;

@property (nonatomic, assign) BOOL isDump;

@property (nonatomic, assign) HHLiveAudioScenario audioScenario;

@property (nonatomic, assign) BOOL isLeave;

@end

@implementation HHAgoraAdapter

+ (void)load {
    [HHLiveEngineManager addRegisterWithLiveType:HHLiveEngineAgora liveClass:[HHAgoraAdapter class]];
}

- (instancetype)init:(NSDictionary *)config {
    if (self = [self init]) {
        self.rtcConfig = [HHRTCConfig getRTCConfig:config];
        if (self.rtcConfig && (!CUCFStringIsNull(self.rtcConfig.appId)) && (!CUCFStringIsNull(self.rtcConfig.channelName))) {
            self.isLeave = NO;
            [HHAgoraAudioDumpManager deleteAgoraAudioDumpCacheDirectory];
            self.rtcEngine = [AgoraRtcEngineKit sharedEngineWithAppId:self.rtcConfig.appId
               delegate:self];
            [self.rtcEngine setLogFile:[[[HHLiveLogManager share] getOrCreateLiveLogCacheDirectory:HHLiveLogTypeAgora] stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.log", self.rtcConfig.classroomInfo]]]; //设置日志文件路径
            [self.rtcEngine setLogFileSize:2048];//单个日志文件大小2048KB=2M
            [self.rtcEngine setParameters:@"{\"che.audio.keep.audiosession\":true}"];//通话断开的时候会恢复到进入之前的category
            if ([HHNavigationConfigManager isDefaultTurnOffWithName:@"agoraForceUnifiedCommunication"]) {
                [self.rtcEngine setParameters:@"{\"rtc.force_unified_communication_mode\": true}"];//手动打开通信模式下的优化模式
            }
            if ([HHNavigationConfigManager isDefaultTurnOffWithName:@"agoraFecMethod"]) {
                [self.rtcEngine setParameters:@"{\"che.video.fecMethod\":2}"];
            }
            [self.rtcEngine setParameters:@"{\"che.video.inactive_enable_encoding_and_decoding\":true}"];
            [self.rtcEngine setParameters:@"{\"che.audio.restartWhenInterrupted\":true}"];
            if (self.rtcConfig.rtcParameter) {
                [self.rtcConfig.rtcParameter enumerateObjectsUsingBlock:^(NSString *rtcParameter, NSUInteger idx, BOOL * _Nonnull stop) {
                    [self.rtcEngine setParameters:rtcParameter];
                }];
            }
            
            AgoraChannelProfile agoraChannelProfile = (AgoraChannelProfile)self.rtcConfig.channelProfile;
            [_rtcEngine setChannelProfile:agoraChannelProfile];//设置房间模式
            if (agoraChannelProfile == AgoraChannelProfileLiveBroadcasting) {
                [self.rtcEngine setClientRole:(AgoraClientRole)self.rtcConfig.clientRole]; //设置直播场景里的用户角色
            }
            [self.rtcEngine enableVideo];//开启视频
            HHLiveVideoProfile *liveVideoProfile = [[HHLiveVideoProfile alloc] initWithVideoProfile:self.rtcConfig.videoProfile];
            AgoraVideoEncoderConfiguration *videoEncoderConfiguration = [[AgoraVideoEncoderConfiguration alloc] initWithWidth:liveVideoProfile.width height:liveVideoProfile.height frameRate:liveVideoProfile.frameRate bitrate:liveVideoProfile.bitrate orientationMode:AgoraVideoOutputOrientationModeFixedLandscape];
            [self.rtcEngine setVideoEncoderConfiguration:videoEncoderConfiguration];
            [self.rtcEngine setAudioProfile:AgoraAudioProfileDefault
                               scenario:[self getAgoraAudioScenario]];//设置音频模
            if ([HHNavigationConfigManager isDefaultTurnOffWithName:@"AgoraRecordingVolume"] && self.rtcConfig.recordingVolume) {
                [self setAudioRecordingVolume:[self.rtcConfig.recordingVolume unsignedIntValue]];
            }
            [self.rtcEngine enableAudioVolumeIndication:self.rtcConfig.volumeInterval smooth:3 report_vad:NO];//设置音量大小回调，500毫秒，平滑系数默认3
            [self.rtcEngine enableWebSdkInteroperability:YES];//设置web互通
            [self.rtcEngine enableDualStreamMode:self.rtcConfig.enableDualStream];
            if (self.rtcConfig.enableDualStream) {
                HHLiveVideoProfile *smallVideoProfile = [[HHLiveVideoProfile alloc] initWithVideoProfile:self.rtcConfig.smallVideoProfile];
                NSString *key = @"che.video.lowBitRateStreamParameter";
                NSString *value = [NSString stringWithFormat:@"{\"width\":%d,\"height\":%d,\"frameRate\":%d,\"bitRate\":%d}", smallVideoProfile.width, smallVideoProfile.height, smallVideoProfile.frameRate, smallVideoProfile.bitrate];
                NSString *options = [NSString stringWithFormat:@"{\"%@\": %@}", key, value];
                [self.rtcEngine setParameters:options];
            }
            [self.rtcEngine setRemoteDefaultVideoStreamType:AgoraVideoStreamTypeLow];
            [self.rtcEngine setDefaultMuteAllRemoteAudioStreams:YES];
            [self.rtcEngine setDefaultMuteAllRemoteVideoStreams:YES];
        }
    }
    return self;
}

- (instancetype)init {
    if (self = [super init]) {
        AgoraLastmileProbeConfig *config = [[AgoraLastmileProbeConfig alloc] init];
        [self.rtcEngine startLastmileProbeTest:config];
    }
    return self;
}

- (int)joinChannel {
    __block int code = -1;
    if (self.rtcConfig && self.rtcEngine) {
        //设置原始音频数据处理声音格式
        [self.rtcEngine setPlaybackAudioFrameParametersWithSampleRate:48000 channel:2 mode:AgoraAudioRawFrameOperationModeReadWrite samplesPerCall:1920];
        NSString *appToken = nil;
        if (!CUCFStringIsNull(self.rtcConfig.appToken)) {
            if ([HHNavigationConfigManager isDefaultTurnOnWithName:@"AgoraAppToken"]) {
                appToken = self.rtcConfig.appToken;
                [ESItsServer info:nil modCode:HHLiveEngineItsServerModeCode funcCode:@"agoraAppToken" ext:nil];
            }
        }
        code = [self.rtcEngine joinChannelByToken:appToken channelId:self.rtcConfig.channelName info:nil uid:self.rtcConfig.uid.longLongValue joinSuccess:nil];
        if (code == 0) {
            [HHLiveAgoraAudioFrameObserver registerAudioFrameObserver:self.rtcEngine];
        }
    }
    return code;
}

- (void)destroyRtcEngine {
    if (self.rtcEngine) {
        [self leave];
        [HHLiveAgoraAudioFrameObserver deregisterAudioFrameObserver:_rtcEngine];
        //该方法需要在子线程中操作
        //该方法为同步调用。 App 不得在 SDK 生成的回调中调用该方法，不然 SDK 只能等候该回调返回才能重新获取相应的对象资源造成死锁。
        [AgoraRtcEngineKit destroy];
        self.rtcEngine = nil;
        self.isDump = NO;
    }
}

- (HHLiveEngineType)getLiveType {
    return HHLiveEngineTypeAgora;
}

/// 离开房间
- (int)leave {
    int res = -1;
    if (self.rtcEngine && (!self.isLeave)) {
        res = [self.rtcEngine leaveChannel:nil];
        [self.rtcEngine setLocalVideoRenderer:nil];
        self.isLeave = YES;
        [HHLiveLogManager leaveStatistics:HHLiveEngineItsServerModeCode];
    }
    return res;
}

/// 开启关闭本地音频
/// @param isMute YES 关闭本地用户音频，NO 打开本地用户音频
- (int)muteLocalAudio:(BOOL)isMute {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine muteLocalAudioStream:isMute];
        [HHLiveLogManager muteLocalStreamStatistics:HHLiveEngineItsServerModeCode isMute:isMute isAudioStream:YES];
    }
    return res;
}

/// 开启关闭本地视频
/// @param isMute YES 关闭本地用户视频，NO 打开本地用户视频
- (int)muteLocalVideo:(BOOL)isMute {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine muteLocalVideoStream:isMute];
        [HHLiveLogManager muteLocalStreamStatistics:HHLiveEngineItsServerModeCode isMute:isMute isAudioStream:NO];
    }
    return res;
}

/// 开启关闭远端视频
/// @param uid 用户id
/// @param isMute YES 关闭远端用户视频 ，NO 打开远端用户视频
- (int)muteRemoteVideo:(NSString *)uid isMute:(BOOL)isMute {
    int res = -1;
    if (self.rtcEngine && [self muteVideo:uid isMuted:isMute]) {
        res = [self.rtcEngine muteRemoteVideoStream:uid.longLongValue mute:isMute];
    }
    return res;
}

/// 开启关闭远端音频
/// @param uid 用户id
/// @param isMute YES 关闭远端用户音频 ，NO 打开远端用户音频
- (int)muteRemoteAudio:(NSString *)uid isMute:(BOOL)isMute {
    int res = -1;
    if (self.rtcEngine && [self muteAudio:uid isMuted:isMute]) {
        res = [self.rtcEngine muteRemoteAudioStream:uid.longLongValue mute:isMute];
    }
    return res;
}

/// 打开关闭扬声器
/// @param enableSpeaker YSE 打开扬声器播放，NO 关闭扬声器播放
- (int)setEnableSpeakerphone:(BOOL)enableSpeaker {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine setEnableSpeakerphone:enableSpeaker];
        [HHLiveLogManager setEnableSpeakerphoneStatistics:HHLiveEngineItsServerModeCode enableSpeaker:enableSpeaker];
    }
    return res;
}

/// 设置录制音量
/// @param volume 0-100
- (int)setAudioRecordingVolume:(unsigned int)volume {
    int res = -1;
    if (self.rtcEngine) {
        [super setAudioRecordingVolume:volume];
        volume = [self dealWithVolume:volume multiple:3];
        res = [self.rtcEngine adjustRecordingSignalVolume:volume];
    }
    return res;
}

/// 获取录制音量,是setAudioRecordingVolume设置的volume值
- (int)getAudioRecordingVolume {
    return [super getAudioRecordingVolume];
}

/// 设置远端用户音量
/// @param uid 用户id
/// @param volume 0-100
- (int)setAudioPlaybackVolume:(NSString *)uid volume:(unsigned int)volume {
    int res = -1;
    if (self.rtcEngine) {
        [super setAudioPlaybackVolume:uid volume:volume];
        volume = [self dealWithVolume:volume multiple:3];
        NSString *key = @"che.audio.playout.uid.volume";
        NSString *value = [NSString stringWithFormat:@"{\"channel\":\"%@\",\"uid\":%lld,\"volume\":%d}", self.rtcConfig.channelName, uid.longLongValue, volume];
        NSString *options = [NSString stringWithFormat:@"{\"%@\": %@}", key, value];
        res = [self.rtcEngine setParameters:options];
    }
    return res;
}

/// 获取远端用户音量,是setAudioPlaybackVolume设置的volume值
/// @param uid 用户id
- (int)getAudioPlaybackVolume:(NSString *)uid {
    return [super getAudioPlaybackVolume:uid];
}

/// 设置远端所有用户音量
/// @param volume 0-100
- (int)setAudioAllPlaybackVolume:(unsigned int)volume {
    int res = -1;
    if (self.rtcEngine) {
        [super setAudioAllPlaybackVolume:volume];
        volume = [self dealWithVolume:volume multiple:3];
        res = [self.rtcEngine adjustPlaybackSignalVolume:volume];
    }
    return res;
}

/// 获取远端所有用户音量，是setAudioAllPlaybackVolume方法设置的volume值
- (int)getAudioAllPlaybackVolume {
    return [super getAudioAllPlaybackVolume];
}

/// 启用说话者音量提示
/// @param interval 指定音量提示的时间间隔(ms)
- (int)enableAudioVolumeIndication:(unsigned int)interval {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine enableAudioVolumeIndication:interval smooth:3 report_vad:NO];
    }
    return res;
}

- (int)setupLocalVideo:(NSString *)uid
             container:(UIView *)container
            renderMode:(int)renderMode {
    int res = -1;
    if (self.rtcEngine) {
        AgoraRtcVideoCanvas *canvas = [[AgoraRtcVideoCanvas alloc] init];
        canvas.uid = uid.longLongValue;
        canvas.view = container;
        canvas.renderMode = (AgoraVideoRenderMode)renderMode;
        res = [self.rtcEngine setupLocalVideo:canvas];
        [HHLiveLogManager setupVideoViewStatistics:HHLiveEngineItsServerModeCode uid:uid container:container renderMode:renderMode isLocalVideo:YES];
    }
    return res;
}

- (int)setupRemoteVideo:(NSString *)uid
              container:(UIView *)container
             renderMode:(int)renderMode {
    int res = -1;
    if (self.rtcEngine) {
        AgoraRtcVideoCanvas *canvas = [[AgoraRtcVideoCanvas alloc] init];
        canvas.uid = uid.longLongValue;
        canvas.view = container;
        canvas.renderMode = (AgoraVideoRenderMode)renderMode;
        res = [self.rtcEngine setupRemoteVideo:canvas];
        [HHLiveLogManager setupVideoViewStatistics:HHLiveEngineItsServerModeCode uid:uid container:container renderMode:renderMode isLocalVideo:NO];
    }
    return res;
}

#pragma mark - Other
/// 特殊配置
/// @param options 配置选项字符串
- (int)setParameters:(NSString * _Nonnull)options {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine setParameters:options];
        [HHLiveLogManager setParametersStatistics:HHLiveEngineItsServerModeCode options:options];
    }
    return res;
}

/// 获取版本号
- (NSString *)getVersion {
    return [AgoraRtcEngineKit getSdkVersion];
}

/// 启用或关闭音频模块。（模块默认为开启状态）
/// @param enabled YES：启用，NO：关闭
- (int)enableAudio:(BOOL)enabled {
    int res = -1;
    if (self.rtcEngine) {
        if (enabled) {
            res = [self.rtcEngine enableAudio];
        } else {
            res = [self.rtcEngine disableAudio];
        }
        [HHLiveLogManager enableStreamStatistics:HHLiveEngineItsServerModeCode enabled:enabled isAudioStream:YES];
    }
    return res;
}

/// 启用或关闭视频模块。（模块默认为开启状态）
/// @param enabled YES：启用，NO：关闭
- (int)enableVideo:(BOOL)enabled {
    int res = -1;
    if (self.rtcEngine) {
        if (enabled) {
            res = [self.rtcEngine enableVideo];
        } else {
            res = [self.rtcEngine disableVideo];
        }
        [HHLiveLogManager enableStreamStatistics:HHLiveEngineItsServerModeCode enabled:enabled isAudioStream:NO];
    }
    return res;
}

/// 开启本地视频预览
/// @note 该方法用于在进入频道前启动本地视频预览。本地预览默认开启镜像功能/// 启用了本地视频预览后，如果调用 -leaveChannel 退出频道，本地预览依然处于启动状态，如需要关闭本地预览，需要调用 -stopPreview。
- (int)startPreview {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine startPreview];
        [HHLiveLogManager startPreviewStatistics:HHLiveEngineItsServerModeCode];
    }
    return res;
}

/// 停止本地视频预览
- (int)stopPreview {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine stopPreview];
        [HHLiveLogManager stopPreviewStatistics:HHLiveEngineItsServerModeCode];
    }
    return res;
}

/// 开关本地音频采集
- (int)enableLocalAudio:(BOOL)enabled {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine enableLocalAudio:enabled];
        [HHLiveLogManager enableLocalStreamStatistics:HHLiveEngineItsServerModeCode enabled:enabled isAudioStream:YES];
    }
    return res;
}

/// 开关本地视频采集
- (int)enableLocalVideo:(BOOL)enabled {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine enableLocalVideo:enabled];
        [HHLiveLogManager enableLocalStreamStatistics:HHLiveEngineItsServerModeCode enabled:enabled isAudioStream:NO];
    }
    return res;
}

/// 本地自定义视频渲染器
/// @param videoRenderer 自定义的视频渲染器
/// @note 默认不开启自定义视频渲染功能，如要使用请在初始化 Engine 前调用 +setExternalVideoRender 进行设置。
/// 本地渲染还需要调用 -startPreview 开启预览才会输出数据。
- (void)setLocalVideoRenderer:(nullable id<HHLiveVideoSinkProtocol>)videoRenderer {
    if (self.rtcEngine && !self.rtcConfig.isRtcCanvas) {
        HHAgoraVideoRender *agoraVideoRenderer = [[HHAgoraVideoRender alloc] init];
        agoraVideoRenderer.videoRenderer = videoRenderer;
        [self.rtcEngine setLocalVideoRenderer:agoraVideoRenderer];
    }
}

/// 远端自定义视频渲染器
/// @param videoRenderer 自定义的视频渲染器
/// @param userId 远端用户的 uid
/// @note 默认不开启自定义视频渲染功能，如要使用请在初始化 Engine 前调用 +setExternalVideoRender 进行设置。
- (void)setRemoteVideoRenderer:(nullable id<HHLiveVideoSinkProtocol>)videoRenderer forUserId:(NSString *)userId {
    if (self.rtcEngine && !self.rtcConfig.isRtcCanvas) {
        HHAgoraVideoRender *agoraVideoRenderer = [[HHAgoraVideoRender alloc] init];
        agoraVideoRenderer.videoRenderer = videoRenderer;
        [self.rtcEngine setRemoteVideoRenderer:agoraVideoRenderer forUserId:userId.longLongValue];
    }
}

/// 设置音频编码配置
/// @param profile 音频质量
/// @param scenario 音频应用场景
/// @note 进入频道前调用有效。
- (int)setAudioProfile:(HHLiveAudioProfile)profile scenario:(HHLiveAudioScenario)scenario {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine setAudioProfile:(AgoraAudioProfile)profile scenario:(AgoraAudioScenario)scenario];
        self.audioScenario = scenario;
    }
    return res;
}

/// 打开web互通
/// @param enabled YES互通，NO不互通
- (int)enableWebSdkInteroperability:(BOOL)enabled {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine enableWebSdkInteroperability:enabled];
    }
    return res;
}

///开关视频双流模式
/// @param enabled YES: 双流模式，NO: 单流模式（默认）
/// @note 使用该方法设置单流（默认）或者双流模式。发送端开启双流模式后，接收端可以选择接收大流还是小流。 其中，大流指高分辨率、高码率的视频流，小流指低分辨率、低码率的视频流。
- (int)enableDualStreamMode:(BOOL)enabled {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine enableDualStreamMode:enabled];
        [HHLiveLogManager enableDualStreamModeStatistics:HHLiveEngineItsServerModeCode enabled:enabled];
    }
    return res;
}

/// 设置订阅的视频流类型
/// @param uid 用户 ID
/// @param streamType 设置视频流大小
/// @note 如果发送端选择发送视频双流（大流或小流），接收端可以选择接收大流还是小流。其中大流可以理解为高分辨率高码率的视频流，小流则是低分辨率低码率的视频流。该方法可以根据视频窗口的大小动态调整对应视频流的大小，以节约带宽和计算资源。
- (int)setRemoteVideoStream:(NSString *)uid type:(HHLiveVideoStreamType)streamType {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine setRemoteVideoStream:uid.longLongValue type:(AgoraVideoStreamType)streamType];
        [HHLiveLogManager setRemoteVideoStreamStatistics:HHLiveEngineItsServerModeCode uid:uid type:streamType];
    }
    return res;
}

/// 设置默认订阅的视频流类型
/// @param streamType 设置默认接收的视频流类型
/// @note 该方法设置远端视频默认为大流或小流。
- (int)setRemoteDefaultVideoStreamType:(HHLiveVideoStreamType)streamType {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine setRemoteDefaultVideoStreamType:(AgoraVideoStreamType)streamType];
    }
    return res;
}

/// 设置是否默认接收音频流
/// @param mute 默认是否接收音频流
/// @note 该方法在加入频道前后都可调用。如果加入频道后调用该方法，会收不到后面加入频道的用户的音频流。
- (int)setDefaultMuteAllRemoteAudioStreams:(BOOL)mute {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine setDefaultMuteAllRemoteAudioStreams:mute];
        [HHLiveLogManager setDefaultMuteAllRemoteStreamsStatistics:HHLiveEngineItsServerModeCode mute:mute isAudioStream:YES];
    }
    return res;
}

/// 设置是否默认接收视频流
/// @param mute 默认是否接收视频流
/// @note 该方法在加入频道前后都可调用。如果加入频道后调用该方法，会收不到后面加入频道的用户的视频流。
- (int)setDefaultMuteAllRemoteVideoStreams:(BOOL)mute {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine setDefaultMuteAllRemoteVideoStreams:mute];
        [HHLiveLogManager setDefaultMuteAllRemoteStreamsStatistics:HHLiveEngineItsServerModeCode mute:mute isAudioStream:NO];
    }
    return res;
}

- (int)setRemoteUserPriority:(NSString *)uid userPriority:(NSInteger)userPriority {
    int res = -1;
    if (self.rtcEngine) {
        AgoraUserPriority agoraUserPriority = AgoraUserPriorityNormal;
        if (userPriority == 1) {
            agoraUserPriority = AgoraUserPriorityHigh;
        }
        res = [self.rtcEngine setRemoteUserPriority:uid.longLongValue type:agoraUserPriority];
        [HHLiveLogManager setRemoteUserPriorityStatistics:HHLiveEngineItsServerModeCode uid:uid userPriority:userPriority];
    }
    return res;
}

#pragma mark - 网络质量探测
/// 开始通话前网络质量探测
/// @param config 网络探测配置
- (int)startLastmileProbeTest:(NSString *)config {
    int res = -1;
    if (self.rtcEngine) {
        HHLiveLastmileProbeConfig *probeConfig = [self getLastmileProbeConfig:config];
        AgoraLastmileProbeConfig *agoraProbeConfig = [[AgoraLastmileProbeConfig alloc] init];
        agoraProbeConfig.probeUplink = probeConfig.probeUplink;
        agoraProbeConfig.probeDownlink = probeConfig.probeDownlink;
        agoraProbeConfig.expectedUplinkBitrate = probeConfig.expectedUplinkBitrate;
        agoraProbeConfig.expectedDownlinkBitrate = probeConfig.expectedDownlinkBitrate;
        res = [self.rtcEngine startLastmileProbeTest:agoraProbeConfig];
    }
    return res;
}

/// 停止通话前网络质量探测
- (int)stopLastmileProbeTest {
    int res = -1;
    if (self.rtcEngine) {
        [self.rtcEngine stopLastmileProbeTest];
    }
    return res;
}

#pragma mark - HHLiveAudioPlayerProtocol
/// 设置音频播放音量
/// @param soundId 音频id
/// @param volume 音量 0.0-100.0
- (int)setVolumeOfAudio:(int)soundId
             withVolume:(double)volume {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine setVolumeOfEffect:soundId withVolume:volume];
    }
    return res;
}

/// 获取音频播放音量
/// @param soundId 音频id
- (double)getAudioPlayoutVolume:(int)soundId {
    return -1.0;
}

// 设置音效音量
- (int)setAudiosVolume:(double)volume {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine setEffectsVolume:volume];
    }
    return res;
}

/// 播放音频了文件
/// @param soundId 音频id
/// @param filePath 文件路径
/// @param loopCount 循环次数 0：一次 1：两次 -1：无限循环，直到调用stop
/// @param gain 设置音效的音量。取值范围为 [0.0,100.0]。默认值为 100.0。取值越小，则音效的音量越低
- (int)playAudio:(int)soundId
        filePath:(NSString * _Nullable)filePath
       loopCount:(int)loopCount
            gain:(double)gain {
    return [self playAudio:soundId filePath:filePath loopCount:loopCount gain:gain publish:NO];
}

/// 播放音频了文件
/// @param soundId 音频id
/// @param filePath 文件路径
/// @param loopCount 循环次数 0：一次 1：两次 -1：无限循环，直到调用stop
/// @param gain 设置音效的音量。取值范围为 [0.0,100.0]。默认值为 100.0。取值越小，则音效的音量越低
/// @param publish 是否将音效传到远端，YES 则远端也能听到音效，NO 仅为本地播放。
- (int)playAudio:(int)soundId
        filePath:(NSString * _Nullable)filePath
       loopCount:(int)loopCount
            gain:(double)gain
         publish:(BOOL)publish {
    int res = -1;
    if (self.rtcEngine) {
        int currentPos = [self.rtcEngine getEffectCurrentPosition:soundId];
        if (currentPos < 0) {
            currentPos = 0;
        }
        res = [self.rtcEngine playEffect:soundId filePath:filePath loopCount:loopCount pitch:1.0 pan:0 gain:gain publish:publish startPos:currentPos];
    }
    return res;
}

/// 停止音频播放
/// @param soundId 音频id
- (int)stopAudio:(int)soundId {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine stopEffect:soundId];
    }
    return res;
}

/// 停止所有音频播放
- (int)stopAllAudios {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine stopAllEffects];
    }
    return res;
}

/// 预加载音频
/// @param soundId 音频id
/// @param filePath 文件路径
- (int)preloadAudio:(int)soundId
            filePath:(NSString * _Nullable)filePath {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine preloadEffect:soundId filePath:filePath];
    }
    return res;
}

/// 卸载预加载的音频
/// @param soundId 音频id
- (int)unloadAudio:(int)soundId {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine unloadEffect:soundId];
    }
    return res;
}

/// 暂停音频播放
/// @param soundId 音频id
- (int)pauseAudio:(int)soundId {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine pauseEffect:soundId];
    }
    return res;
}

/// 暂停所有音频播放
- (int)pauseAllAudios {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine pauseAllEffects];
    }
    return res;
}

/// 恢复音频播放
/// @param soundId 音频id
- (int)resumeAudio:(int)soundId {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine resumeEffect:soundId];
    }
    return res;
}

/// 恢复所有音频播放
- (int)resumeAllAudios {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine resumeAllEffects];
    }
    return res;
}

/// 获取音频播放进度 返回值单位ms
/// @param soundId 音频id
- (int)getAudioCurrentPosition:(int)soundId {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine getEffectCurrentPosition:soundId];
    }
    return res;
}

/// 设置音频播放进度
/// @param soundId 音频id
/// @param pos 进度值单位ms
- (int)setAudioPosition:(int)soundId
                    pos:(NSInteger)pos {
    int res = -1;
    if (self.rtcEngine) {
        res = [self.rtcEngine setEffectPosition:soundId pos:pos];
    }
    return res;
}

/// 获取音频文件总时长
/// @param filePath 文件路径
- (float)getAudioDuration:(NSString *)filePath {
    int res = -1;
    if (self.rtcEngine) {
        if (CUCFStringIsNull(filePath)) {
            return res;
        }
        NSURL *url = nil;
        if ([filePath hasPrefix:@"http"]) {
            url = [NSURL URLWithString:filePath];
        } else {//播放本机录制的文件
            url = [NSURL fileURLWithPath:filePath];
        }
        if (!url) {
            return -2.0;
        }
        NSDictionary *dic = @{
            AVURLAssetPreferPreciseDurationAndTimingKey:@(YES)
        };
        AVURLAsset* audioAsset = [AVURLAsset URLAssetWithURL:url options:dic];
        CMTime audioDuration = audioAsset.duration;
        double audioDurationSeconds = CMTimeGetSeconds(audioDuration);
        res = audioDurationSeconds * 1000;
    }
    return res;
}

- (void)rtcEngineDidAudioEffectFinish:(AgoraRtcEngineKit * _Nonnull)engine soundId:(NSInteger)soundId {
    [self audioEffectFinishOfSoundId:soundId];
    [self.delegate liveEngineDidAudioEffectFinishOfSoundId:soundId];
}

#pragma mark - AgoraRtcEngineDelegate
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didJoinChannel:(NSString * _Nonnull)channel withUid:(NSUInteger)uid elapsed:(NSInteger) elapsed {
    [self.delegate liveEngineDidJoinChannel:channel withUid:@(uid).stringValue];
    [self didJoinedOfUid:@(uid).stringValue];
}

- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didRejoinChannel:(NSString * _Nonnull)channel withUid:(NSUInteger)uid elapsed:(NSInteger) elapsed {
    [self.delegate liveEngineDidRejoinChannel:channel withUid:@(uid).stringValue];
    [HHLiveLogManager didRejoinChannelStatistics:HHLiveEngineItsServerModeCode uid:@(uid).stringValue];
}

- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didLeaveChannelWithStats:(AgoraChannelStats * _Nonnull)stats {
    [self.delegate liveEngineDidLeaveChannel];
    [HHLiveLogManager didOfflineStatistics:HHLiveEngineItsServerModeCode uid:self.rtcConfig.uid isLocal:YES];
}

- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didJoinedOfUid:(NSUInteger)uid elapsed:(NSInteger)elapsed {
    [self didJoinedOfUid:@(uid).stringValue];
    [self.delegate liveEngineDidJoinedOfUid:@(uid).stringValue];
}

- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didOfflineOfUid:(NSUInteger)uid reason:(AgoraUserOfflineReason)reason {
    [self didOfflineOfUid:@(uid).stringValue];
    [self.delegate liveEngineDidOfflineOfUid:@(uid).stringValue];
}

- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didAudioMuted:(BOOL)muted byUid:(NSUInteger)uid {
    [self.delegate liveEngineDidAudioMuted:muted byUid:@(uid).stringValue];
    [HHLiveLogManager didMutedStreamStatistics:HHLiveEngineItsServerModeCode muted:muted byUid:@(uid).stringValue isAudioStream:YES];
}

- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didVideoMuted:(BOOL)muted byUid:(NSUInteger)uid {
    [self.delegate liveEngineDidVideoMuted:muted byUid:@(uid).stringValue];
    [HHLiveLogManager didMutedStreamStatistics:HHLiveEngineItsServerModeCode muted:muted byUid:@(uid).stringValue isAudioStream:NO];
}

- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didLocalVideoEnabled:(BOOL)enabled byUid:(NSUInteger)uid {
    [self.delegate liveEngineDidLocalVideoEnabled:enabled byUid:@(uid).stringValue];
    [HHLiveLogManager didLocalVideoEnabledStatistics:HHLiveEngineItsServerModeCode enabled:enabled byUid:@(uid).stringValue];
}

- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine networkQuality:(NSUInteger)uid txQuality:(AgoraNetworkQuality)txQuality rxQuality:(AgoraNetworkQuality)rxQuality {
    if (uid == 0) {
        uid = self.rtcConfig.uid.intValue;
    }
    [self.delegate liveEngineNetworkQuality:@(uid).stringValue txQuality:(HHLiveNetworkQuality)txQuality rxQuality:(HHLiveNetworkQuality)rxQuality];
}

//音量提示回调getAudioLevel
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine reportAudioVolumeIndicationOfSpeakers:(NSArray*)speakers totalVolume:(NSInteger)totalVolume {
    for (AgoraRtcAudioVolumeInfo *info in speakers) {
        unsigned int uid = (unsigned int)info.uid;
        if (uid == 0) {
            uid = self.rtcConfig.uid.intValue;
        }
        [self.delegate liveEngineReportAudioVolumeIndicationOfUid:@(uid).stringValue volume:(float)info.volume totalVolume:(float)totalVolume];
    }
}

- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine reportRtcStats:(AgoraChannelStats * _Nonnull)stats {
    HHLiveChannelStats *liveChannelStats = [HHLiveChannelStats channelStatsWithDuration:stats.duration txBytes:stats.txBytes rxBytes:stats.rxBytes txKBitRate:stats.txKBitrate rxKBitRate:stats.rxKBitrate txAudioKBitRate:stats.txAudioKBitrate rxAudioKBitRate:stats.rxAudioKBitrate txVideoKBitRate:stats.txVideoKBitrate rxVideoKBitRate:stats.rxVideoKBitrate lastmileDelay:stats.lastmileDelay txLostRate:stats.txPacketLossRate rxLostRate:stats.rxPacketLossRate userCount:stats.userCount cpuAppUsage:stats.cpuAppUsage cpuTotalUsage:stats.cpuTotalUsage gatewayRtt:stats.gatewayRtt];
    [self.delegate liveEngineReportRtcStats:liveChannelStats];
}

- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine localVideoStats:(AgoraRtcLocalVideoStats*)stats {
    HHLiveLocalVideoStats *localVideoStats = [HHLiveLocalVideoStats localVideoStatsWithSentBitrate:stats.sentBitrate sentFrameRate:stats.sentFrameRate encoderOutputFrameRate:stats.encoderOutputFrameRate rendererOutputFrameRate:stats.rendererOutputFrameRate];
    [self.delegate liveEngineLocalVideoStats:localVideoStats];
    [self localVideoStats:localVideoStats];
}

- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine remoteVideoStats:(AgoraRtcRemoteVideoStats*)stats {
    HHLiveRemoteVideoStats *remoteVideoStats = [HHLiveRemoteVideoStats remoteVideoStatsWithUid:@(stats.uid).stringValue width:stats.width height:stats.height videoKBitRate:stats.receivedBitrate videoFrozenRate:stats.frozenRate videoLostRate:stats.packetLossRate videoFps:stats.decoderOutputFrameRate videoQuality:INVALID_VAlUE rendererOutputFrameRate:stats.rendererOutputFrameRate rxStreamType:stats.rxStreamType totalFrozenTime:stats.totalFrozenTime];
    [self.delegate liveEngineRemoteVideoStats:remoteVideoStats];
    [self remoteVideoStats:remoteVideoStats];
}

// 通话中远端音频流的统计信息回调
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine remoteAudioStats:(AgoraRtcRemoteAudioStats *)stats {
    HHLiveRemoteAudioStats *remoteAudioStats = [HHLiveRemoteAudioStats remoteAudioStatsWithUid:@(stats.uid).stringValue audioKBitRate:stats.receivedBitrate audioFrozenRate:stats.frozenRate audioLostRate:stats.audioLossRate audioDelay:stats.networkTransportDelay audioQuality:stats.quality jitterBufferDelay:stats.jitterBufferDelay totalFrozenTime:stats.totalFrozenTime mosValue:stats.mosValue];
    [self.delegate liveEngineRemoteAudioStats:remoteAudioStats];
}

// 通话中远端音频流传输的统计信息回调
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine audioTransportStatsOfUid:(NSUInteger)uid delay:(NSUInteger)delay lost:(NSUInteger)lost rxKBitRate:(NSUInteger)rxKBitRate {
    [self.delegate liveEngineAudioTransportStatsOfUid:@(uid).stringValue delay:delay lost:lost rxKBitRate:rxKBitRate];
}

// 通话中远端视频流传输的统计信息回调
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine videoTransportStatsOfUid:(NSUInteger)uid delay:(NSUInteger)delay lost:(NSUInteger)lost rxKBitRate:(NSUInteger)rxKBitRate {
    [self.delegate liveEngineVideoTransportStatsOfUid:@(uid).stringValue delay:delay lost:lost rxKBitRate:rxKBitRate];
}

/// 通话前网络上下行 last mile 质量报告回调
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine lastmileQuality:(AgoraNetworkQuality)quality {
    [self.delegate liveEngineLastmileQuality:(HHLiveNetworkQuality)quality];
}

/// 通话前网络质量探测报告回调
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine lastmileProbeTestResult:(AgoraLastmileProbeResult *)result {
    HHLiveLastmileProbeResult *probeResult = [HHLiveLastmileProbeResult lastmileProbeResultWithState:(HHLiveLastmileProbeResultState)result.state rtt:result.rtt uplinkReportPacketLossRate:result.uplinkReport.packetLossRate uplinkReportJitter:result.uplinkReport.jitter uplinkReportAvailableBandWidth:result.uplinkReport.availableBandwidth downlinkReportPacketLossRate:result.downlinkReport.packetLossRate downlinkReportJitter:result.downlinkReport.jitter downlinkReportAvailableBandWidth:result.downlinkReport.availableBandwidth];
    [self.delegate liveEngineLastmileProbeTestResult:probeResult];
}

// 该回调在网络连接状态发生改变的时候触发，并告知用户当前的网络连接状态，和引起网络状态改变的原因。
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine connectionChangedToState:(AgoraConnectionStateType)state reason:(AgoraConnectionChangedReason)reason {
    if (self.isAppActive && (state == AgoraConnectionStateReconnecting || state == AgoraConnectionStateFailed)) {
        NSMutableDictionary *statisticsDict = [NSMutableDictionary dictionary];
        statisticsDict[@"state"] = @(state);
        statisticsDict[@"reason"] = @(reason);
        [ESItsServer info:nil modCode:HHLiveEngineItsServerModeCode funcCode:@"connectionChanged" ext:[statisticsDict copy]];
    }
}

// 本地网络连接类型发生改变时，SDK 会触发该回调，并在回调中明确当前的网络连接类型。可以通过该回调获取正在使用的网络类型；当连接终端时，该回调能辨别引起中断的原因是网络切换还是网络条件不好。
- (void)rtcEngine:(AgoraRtcEngineKit *)engine networkTypeChangedToType:(AgoraNetworkType)type {
    if (self.isAppActive && type != AgoraNetworkTypeWIFI) {
        [ESItsServer info:nil modCode:HHLiveEngineItsServerModeCode funcCode:@"networkTypeChanged" ext:@{@"type":@(type)}];
    }
}

// 网络连接中断，无论之前加入频道是否连接成功，只要 10 秒内和服务器无法建立连接都会触发。
- (void)rtcEngineConnectionDidLost:(AgoraRtcEngineKit *)engine {
    if (self.isAppActive) {
        [self.delegate liveEngineConnectionDidLost];
        [HHLiveLogManager didConnectionLostStatistics:HHLiveEngineItsServerModeCode];
    }
}

- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine tokenPrivilegeWillExpire:(NSString *)token {
    if (self.isAppActive) {
        NSMutableDictionary *statisticsDict = [NSMutableDictionary dictionary];
        statisticsDict[@"appToken"] = token;
        [ESItsServer info:nil modCode:HHLiveEngineItsServerModeCode funcCode:@"tokenWillExpire" ext:[statisticsDict copy]];
    }
}

- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didOccurError:(AgoraErrorCode)errorCode {
    if (self.isAppActive && errorCode != AgoraErrorCodeNoError) {
        [self.delegate liveEngineDidOccurError:(NSInteger)errorCode errMsg:nil extInfo:nil];
        [HHLiveLogManager didOccurErrorStatistics:HHLiveEngineItsServerModeCode errorCode:(NSInteger)errorCode errMsg:nil extInfo:nil];
    }
}

- (void)rtcEngine:(AgoraRtcEngineKit* _Nonnull)engine didOccurWarning:(AgoraWarningCode)warningCode {
    if (self.isAppActive) {
        [self.delegate liveEngineDidOccurWarning:(NSInteger)warningCode errMsg:nil extInfo:nil];
    }
}

// 本地视频设备状态
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine localVideoStateChange:(AgoraLocalVideoStreamState)state error:(AgoraLocalVideoStreamError)error {
    if (self.isAppActive) {
        [self.delegate liveEngineLocalVideoStateChange:(HHLiveLocalVideoStreamState)state error:(HHLiveLocalVideoStreamError)error];
        if ((error != AgoraLocalVideoStreamErrorOK) && (error != AgoraLocalVideoStreamErrorCaptureInBackGround) && (error != AgoraLocalVideoStreamErrorCaptureMultipleForegroundApps)) {
            [HHLiveLogManager localVideoStateChangeStatistics:state streamError:error];
        }
    }
}

// 本地音频设备状态
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine localAudioStateChange:(AgoraAudioLocalState)state error:(AgoraAudioLocalError)error {
    if (self.isAppActive) {
        [self.delegate liveEngineLocalAudioStateChange:(HHLiveLocalAudioState)state error:(HHLiveLocalAudioError)error];
        [HHLiveLogManager localAudioStateChangeStatistics:(HHLiveLocalAudioState)state error:(HHLiveLocalAudioError)error];
    }
}

// 远端视频状态发生改变回调。
- (void)rtcEngine:(AgoraRtcEngineKit *)engine remoteVideoStateChangedOfUid:(NSUInteger)uid state:(AgoraVideoRemoteState)state reason:(AgoraVideoRemoteStateReason)reason elapsed:(NSInteger)elapsed {
    if (self.isAppActive) {
        [self.delegate liveEngineRemoteVideoStateChangedOfUid:@(uid).stringValue state:(HHLiveRemoteStreamState)state reason:(HHLiveRemoteStreamReason)reason];
        [HHLiveLogManager remoteStreamStateChangedStatistics:HHLiveEngineItsServerModeCode uid:@(uid).stringValue state:state reason:reason isAudioStream:NO];
    }
}

// 远端音频状态发生改变回调。
- (void)rtcEngine:(AgoraRtcEngineKit *)engine remoteAudioStateChangedOfUid:(NSUInteger)uid state:(AgoraAudioRemoteState)state reason:(AgoraAudioRemoteStateReason)reason elapsed:(NSInteger)elapsed {
    if (self.isAppActive) {
        [self.delegate liveEngineRemoteAudioStateChangedOfUid:@(uid).stringValue state:(HHLiveRemoteStreamState)state reason:(HHLiveRemoteStreamReason)reason];
        [HHLiveLogManager remoteStreamStateChangedStatistics:HHLiveEngineItsServerModeCode uid:@(uid).stringValue state:state reason:reason isAudioStream:YES];
    }
}

#pragma mark - audioDump
- (BOOL)audioDumpStart {
    int res = 1;
    if (self.rtcEngine) {
        NSString *path = [HHAgoraAudioDumpManager getOrCreateAgoraAudioDumpCacheDirectory:self.rtcConfig.classroomInfo];
        res = [_rtcEngine setParameters:[NSString stringWithFormat:@"{\"che.audio.start_debug_recording\": \"%@\"}", path]];
    }
    _isDump = (res == 0);
    return _isDump;
}

- (NSString *)audioDumpStop {
    int res = 1;
    if (self.rtcEngine && _isDump) {
        res = [_rtcEngine setParameters:@"{\"che.audio.stop_debug_recording\": true}"];
    }
    _isDump = NO;
    if (res == 0) {
        NSString *dir = [HHAgoraAudioDumpManager getOrCreateAgoraAudioDumpCacheDirectory:self.rtcConfig.classroomInfo];
        if (!CUCFDirectoryIsExist(dir)) {
            dir = nil;
        }
        return dir;
    }
    return nil;
}

#pragma mark - private
- (AgoraAudioScenario)getAgoraAudioScenario {
    AgoraAudioScenario res = AgoraAudioScenarioEducation;
    struct utsname systemInfo;
    uname(&systemInfo);
    NSString *machine = [NSString stringWithCString:systemInfo.machine encoding:NSUTF8StringEncoding];
    if ([[machine lowercaseString] isEqualToString:@"ipad7,1"] ||
        [[machine lowercaseString] isEqualToString:@"ipad7,2"]) {//判断是iPad7,1和iPad7,2特定设置，因为这两个设备没有硬件回声消除
        res = AgoraAudioScenarioMeeting;
    }
    if ([HHLiveWhiteListManager getWhiteListResult:HHLiveAgoraWhiteListGS] || [HHNavigationConfigManager isDefaultTurnOffWithName:HHLiveAgoraWhiteListGS]) {
        res = AgoraAudioScenarioMeeting;
        [ESItsServer info:nil modCode:HHLiveEngineItsServerModeCode funcCode:@"agoraWhiteListGS" ext:nil];
    }
    self.audioScenario = (HHLiveAudioScenario)res;
    return res;
}

- (HHLiveAudioScenario)getLiveAudioScenario {
    return self.audioScenario;
}

@end
