//
//  HHAgoraLiveVideoPlayer.m
//  huohuaedu
//
//  Created by lijunjie on 2018/6/23.
//  Copyright © 2018年 wanduoduo. All rights reserved.
//

#import "HHAgoraLiveVideoPlayer.h"
#import <AVFoundation/AVFoundation.h>
#import <CoreFoundation/CoreFoundation.h>
#import <CoreVideo/CoreVideo.h>
#import <AgoraRtcKit/IAgoraMediaPlayer.h>

//#import <CUCoreFoundation/CUCFStringUtil.h>
//#import <CUCoreFoundation/CUCFWeakSelfMacrocDefine.h>
//#import <CUCoreFoundation/CUCFUtils.h>
//#import <AgoraMediaPlayer/AgoraMediaPlayerKit.h>
//#import <CULogger/CULoggerUitilsMacrocDefine.h>
//#import <HHNavigationConfig/HHNavigationConfigManager.h>
//#import <HHLiveSDK/HHLiveEngineManager.h>
//#import <HHLiveSDK/HHLiveLogManager.h>
//#import <HHLiveSDK/HHLiveConstant.h>
//#import <HHLiveSDK/HHLiveAgoraAudioFrameObserver.h>
//#import <CUMediaPlayer/HHVideoPlayerConfig.h>
//#import <CUMediaPlayer/HHVideoPlayerPool.h>

//#include "convert_argb.h"
//#include "scale_argb.h"
//#include "convert_from_argb.h"
//#include "rotate_argb.h"

static NSString *const kAgoraPlayerIdentifierKey = @"agoraLiveVideoPlayer";
static NSString *const kVideoPlayerAgoraModeCode = @"agora_video_player";

@interface HHAgoraLiveVideoPlayer () <AgoraRtcMediaPlayerDelegate>
//<AVPlayerItemOutputPullDelegate, AgoraMediaPlayerDelegate>

@property (nonatomic, strong) dispatch_queue_t queue;

@property (nonatomic, strong) id<AgoraRtcMediaPlayerProtocol> agoraMediaPlayer;

@end

@implementation HHAgoraLiveVideoPlayer

+ (void)load {
//    [HHVideoPlayerConfig addRegisterVideoPlayer:HHLiveEngineAgora videoPlayerClass:[HHAgoraLiveVideoPlayer class]];
}

- (void)dealloc {
    [self removeObserver];
//    [self.delegate destroyVideoPlayer:self.videoId];
}

- (void)removeObserver {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

//- (instancetype)initWithPath:(NSString *)path videoId:(int)videoId delegate:(nullable id<HHVideoPlayerDelegate>)delegate {
//    CULog(@"HHAgoraLiveVideoPlayer initWithPath path = %@ self.videoId = %d", path, videoId);
//    self = [self init];
//    if (self) {
//        self.delegate = delegate;
//        self.mediaPath = [path copy];
//        if ([self isRemoteUrl:path]) {
//            self.mediaURL = [NSURL URLWithString:path];
//        } else {
//            self.mediaURL = [NSURL fileURLWithPath:path];
//        }
//        self.videoId = videoId;
//        self.frameCount = 0;
//        self.status = HHVideoPlayerStatusInit;
//        _queue = dispatch_queue_create("com.livevideoengine.www", NULL);
//    }
//    return self;
//}

- (void)load {
//    CULog(@"HHAgoraLiveVideoPlayer load self.videoId = %d", self.videoId);
//    [self loadStatistics:kVideoPlayerAgoraModeCode];
//    self.status = HHVideoPlayerStatusLoad;
//    HHAgoraLiveVideoPlayer *agoraLiveVideoPlayer = (HHAgoraLiveVideoPlayer *)[[HHVideoPlayerPool share] popVideoPlayerWithResuseIdentifier:kAgoraPlayerIdentifierKey];
//    if (agoraLiveVideoPlayer) {
//        _agoraMediaPlayer = agoraLiveVideoPlayer.agoraMediaPlayer;
//        [_agoraMediaPlayer setDelegate:self];
//    } else {
//        BOOL enableVoiceChatMode = YES;
//        if ([[[HHLiveEngineManager share] getLiveEngine] getLiveAudioScenario] != HHLiveAudioScenarioEducation) {
//            enableVoiceChatMode = NO;
//        }
       self.agoraMediaPlayer = [self.rtcEngineKit createMediaPlayerWithDelegate:self];
//    if (_view) [_agoraMediaPlayer setView:_view];
//    if ([HHNavigationConfigManager isDefaultTurnOffWithName:@"AgoraMPKLogUpload"]) {
//        NSString *fileName = [NSString stringWithFormat:@"%u-%@", self.videoId, CUCFDateToStringByFormat([NSDate date], (HHLiveDateFormatDateWithTime))];
//        [_agoraMediaPlayer setLogFile:[[[HHLiveLogManager share] getOrCreateLiveLogCacheDirectory:HHLiveLogTypeAgoraMediaPlayer] stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.log", fileName]]];  要删掉，在RTC sdk会打印日志
    
//    }
//    
//    [[NSNotificationCenter defaultCenter] addObserver:self
//                                             selector:@selector(applicationDidBecomeActive:) name:UIApplicationDidBecomeActiveNotification
//                                               object:nil];
//    [[NSNotificationCenter defaultCenter] addObserver:self
//                                             selector:@selector(applicationWillResignActive:) name:UIApplicationWillResignActiveNotification object:nil];
//    [[NSNotificationCenter defaultCenter] addObserver:self
//                                             selector:@selector(cocosViewIsHidden:) name:@"HHCocosViewIsHidden"
//                                               object:nil];
//    [_agoraMediaPlayer open:self.mediaPath startPos:0];
//    [self showFirstFrame:kVideoPlayerAgoraModeCode];
}

- (void)applicationDidBecomeActive:(NSNotification *)notification {
//    if (self.status == HHVideoPlayerStatusPlaying) {
//        [self mediaPlayerPlay];
//    }
}

- (void)applicationWillResignActive:(NSNotification *)notification {
//    if (self.status == HHVideoPlayerStatusPlaying) {
//        [self mediaPlayerPause];
//    }
}

- (void)cocosViewIsHidden:(NSNotification *)notification {
    NSDictionary *dic = notification.userInfo;
    NSLog(@"HHAgoraLiveVideoPlayer cocosViewIsHidden %d", [dic[@"isShow"] boolValue]);
    if (dic[@"isShow"]) {
        if ([dic[@"isShow"] boolValue]) {
            [self applicationDidBecomeActive:nil];
        } else {
            [self applicationWillResignActive:nil];
        }
    }
}

- (void)play {
//    if (self.status == HHVideoPlayerStatusPlaying) {
//        return;
//    }
//    self.status = HHVideoPlayerStatusPlaying;
//    CULog(@"HHAgoraLiveVideoPlayer play self.videoId = %d", self.videoId);
//    if (_agoraMediaPlayer.state >= AgoraMediaPlayerStateOpenCompleted) {
//        [self mediaPlayerPlay];
//    }
//    [self playStatistics:kVideoPlayerAgoraModeCode];
//}
//
//- (void)pause {
//    if (self.status == HHVideoPlayerStatusPause) {
//        return;
//    }
//    self.status = HHVideoPlayerStatusPause;
//    CULog(@"HHAgoraLiveVideoPlayer pause self.videoId = %d", self.videoId);
//    [self mediaPlayerPause];
//    [self pauseStatistics:kVideoPlayerAgoraModeCode];
}

- (void)unload {
//    CULog(@"HHAgoraLiveVideoPlayer unload self.videoId = %d", self.videoId);
//    [self removeObserver];
//    [self pause];
//    self.status = HHVideoPlayerStatusUnLoad;
//    [self mediaPlayerStop];
//    [_agoraMediaPlayer setView:nil];
//    [[HHVideoPlayerPool share] pushVideoPlayer:self resuseIdentifier:kAgoraPlayerIdentifierKey];
//    [self unloadStatistics:kVideoPlayerAgoraModeCode];
}

- (void)destory {
    [_agoraMediaPlayer setView:nil];
}

- (double)getDuration {
//    return _agoraMediaPlayer.getDuration / 1000.0;
    return 0.01;
}

- (float)getVolume {
//    return [HHLiveAgoraAudioFrameObserver getVolume];
    return  100;
}

- (void)setVolume:(float)volume {
//    [HHLiveAgoraAudioFrameObserver setVolume:volume];
//    [self setVolumeStatistics:kVideoPlayerAgoraModeCode volume:volume];
}

- (void)seek:(double)time {
//    if (time < 0.f) {
//        time = 0.f;
//    }
//    if (time > [self getDuration]) {
//        time = [self getDuration];
//    }
//    CULog(@"HHAgoraLiveVideoPlayer seek self.videoId = %d state", self.videoId);
//    [self mediaPlayerSeekToPosition:time * 1000];
}

- (void)updateVideoFrame:(CVPixelBufferRef)pixelBuffer {
//    if (self.frameCount > 0) return;
//    self.frameCount ++;
//    
//    @weakify(self);
//    CVPixelBufferRetain(pixelBuffer);
//    dispatch_async(_queue, ^{
//        @strongify(self);
//        if (pixelBuffer && self != nil) {
//            [self processVideoYUVPixelBufferToRGBA:pixelBuffer];
//        } else {
//             self.frameCount --;
//        }
//        CVPixelBufferRelease(pixelBuffer);
//    });
}

- (void)processVideoYUVPixelBufferToRGBA:(CVPixelBufferRef)pixelBuffer {
    //表示开始操作数据
    CVPixelBufferLockBaseAddress(pixelBuffer, 0);
    int pixelWidth = (int) CVPixelBufferGetWidth(pixelBuffer);
    int pixelHeight = (int) CVPixelBufferGetHeight(pixelBuffer);
    //Y数据
    unsigned char *y_frame = (unsigned char *)CVPixelBufferGetBaseAddressOfPlane(pixelBuffer, 0);
    //Y stride
    size_t y_stride = CVPixelBufferGetBytesPerRowOfPlane(pixelBuffer, 0);
    //U数据
    unsigned char *u_frame = (unsigned char *)CVPixelBufferGetBaseAddressOfPlane(pixelBuffer, 1);
    //U stride
    size_t u_stride = CVPixelBufferGetBytesPerRowOfPlane(pixelBuffer, 1);
    //V数据
    unsigned char *v_frame = (unsigned char *)CVPixelBufferGetBaseAddressOfPlane(pixelBuffer, 2);
    //V stride
    size_t v_stride = CVPixelBufferGetBytesPerRowOfPlane(pixelBuffer, 2);
    //Unlock
    CVPixelBufferUnlockBaseAddress(pixelBuffer, 0);
    
    int argb_bitsperpixel = 32;//一个像素用几位表示
    int argb_bytesperpixel = argb_bitsperpixel / 8;//一个像素在几个字节的存储空间
    int argb_length = (pixelWidth * pixelHeight * argb_bytesperpixel);
    unsigned char *argb_data = (unsigned char *)malloc(argb_length);
    
//    libyuv::I420ToARGB(y_frame, (int)y_stride,
//                       u_frame, (int)u_stride,
//                       v_frame, (int)v_stride,
//                       argb_data, pixelWidth * 4,
//                       pixelWidth, pixelHeight);
//    
//    uint8 temp;
//    for (int i = 0; i < argb_length / 4; i++) {
//        temp = argb_data[i * 4];//b
//        argb_data[i * 4] = argb_data[i * 4 + 2];//r
//        argb_data[i * 4 + 2] = temp;
//    }
//    
//    dispatch_async(dispatch_get_main_queue(), ^{
//        if (self.videoId >= 0) {
//            [self.delegate updateVideoFrame:self.videoId data:argb_data dataLens:argb_length pixelsWidth:pixelWidth pixelsHight:pixelHeight];
//        }
//        self.frameCount --;
//        free(argb_data);
//    });
}

#pragma mark - AgoraMediaPlayerDelegate
- (void)AgoraRtcMediaPlayer:(id<AgoraRtcMediaPlayerProtocol>)playerKit didChangedToState:(AgoraMediaPlayerState)state reason:(AgoraMediaPlayerReason)reason {
    
//    CULog(@"HHAgoraLiveVideoPlayer AgoraMediaPlayer  didChangedToState state = %ld _status = %ld self.videoId = %d", (long)state, (long)self.status, self.videoId);
//    [self videoPlayerErrorStatistics:kVideoPlayerAgoraModeCode state:state errorCode:error];
//    switch (state) {
//        case AgoraMediaPlayerStateOpenCompleted: {
//            CULog(@"HHAgoraLiveVideoPlayer loadFinishCallBack self.videoId = %d", self.videoId);
//            [self.agoraMediaPlayer adjustVolume:0];
//            [self clearAudioData];
//            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
//                [self.delegate loadFinish:self.videoId];
//                [self loadFinishedStatistics:kVideoPlayerAgoraModeCode];
//            });
//            switch (self.status) {
//                case HHVideoPlayerStatusPlaying: {
//                    [self mediaPlayerPlay];
//                }
//                    break;
//                case HHVideoPlayerStatusPause: {
//                    [self mediaPlayerPause];
//                }
//                    break;
//                case HHVideoPlayerStatusUnLoad: {
//                    [self mediaPlayerStop];
//                }
//                    break;
//                default:
//                    break;
//            }
//        }
//            break;
//        case AgoraMediaPlayerStatePlayBackCompleted: {
//            CULog(@"HHAgoraLiveVideoPlayer playbackFinished self.videoId = %d", self.videoId);
//            [self.delegate playEnd:self.videoId];
//            [self playbackFinishedStatistics:kVideoPlayerAgoraModeCode];
//        }
//            break;
//        case AgoraMediaPlayerStatePlaying: {
//            CULog(@"HHAgoraLiveVideoPlayer HHVideoPlayerStatusPlaying self.videoId = %d", self.videoId);
//        }
//            break;
//        case AgoraMediaPlayerStatePaused: {
//            CULog(@"HHAgoraLiveVideoPlayer HHVideoPlayerStatusPause self.videoId = %d", self.videoId);
//        }
//            break;
//        default:
//            break;
//    }
}


- (void)AgoraRtcMediaPlayer:(id<AgoraRtcMediaPlayerProtocol>)playerKit didChangedToPosition:(NSInteger)positionMs atTimestamp:(NSTimeInterval)timestampMs {
//    [self.delegate timeUpdate:self.videoId time:position / 1000.0];
}

- (void)AgoraRtcMediaPlayer:(id<AgoraRtcMediaPlayerProtocol>)playerKit didOccurEvent:(AgoraMediaPlayerEvent)eventCode elapsedTime:(NSInteger)elapsedTime message:(NSString *)message {
    //    CULog(@"HHAgoraLiveVideoPlayer event=%ld; _status=%ld", (long)event, (long)self.status);
    //    switch (event) {
    //        case AgoraMediaPlayerEventSeekComplete: {
    //            [self clearAudioData];
    //            //需要穿透-没漏写break
    //        }
    //        case AgoraMediaPlayerEventSeekError: {
    //            switch (self.status) {
    //                case HHVideoPlayerStatusPlaying: {
    //                    [self mediaPlayerPlay];
    //                }
    //                    break;
    //                case HHVideoPlayerStatusPause: {
    //                    [self mediaPlayerPause];
    //                }
    //                    break;
    //                case HHVideoPlayerStatusUnLoad: {
    //                    [self mediaPlayerStop];
    //                }
    //                    break;
    //                default:
    //                    break;
    //            }
    //        }
    //        default:
    //            break;
    //    }
}

- (void)AgoraRtcMediaPlayer:(id<AgoraRtcMediaPlayerProtocol>)playerKit didReceiveData:(NSString *)data length:(NSInteger)length {
    
}


//- (void)AgoraMediaPlayer:(AgoraMediaPlayer *_Nonnull)playerKit
//    didReceiveVideoFrame:(CVPixelBufferRef)pixelBuffer {
//    if (!_view) [self updateVideoFrame:pixelBuffer];
//}



#pragma mark MediaPlayer

- (void)mediaPlayerPlay {
    [_agoraMediaPlayer play];
}

- (void)mediaPlayerPause {
    [_agoraMediaPlayer pause];
}

- (void)mediaPlayerStop {
    [_agoraMediaPlayer stop];
}

- (void)mediaPlayerSeekToPosition:(NSInteger)position {
    [_agoraMediaPlayer seekToPosition:position];
}

- (void)clearAudioData {
//    if ([[[HHLiveEngineManager share] getLiveEngine] isSupportLive]) {
//        [HHLiveAgoraAudioFrameObserver resetAudioBuffer];
//    }
}

@end
