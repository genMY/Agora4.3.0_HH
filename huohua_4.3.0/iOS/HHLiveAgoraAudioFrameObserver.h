//
//  HHLiveAgoraAudioFrameObserver.h
//  huohua
//
//  Created by lijunjiie on 2020/06/04.
//  Copyright © 2020 wanduoduo All rights reserved.
//

#import <CoreMedia/CoreMedia.h>

@class AgoraRtcEngineKit;

@interface HHLiveAgoraAudioFrameObserver : NSObject

+ (int)registerAudioFrameObserver:(AgoraRtcEngineKit *)kit;

+ (int)deregisterAudioFrameObserver:(AgoraRtcEngineKit *)kit;

+ (void)resetAudioBuffer;

+ (void)pushAudioFrame:(CMSampleBufferRef)audioFrame;

+ (void)setVolume:(float)volume;

+ (float)getVolume;

@end
