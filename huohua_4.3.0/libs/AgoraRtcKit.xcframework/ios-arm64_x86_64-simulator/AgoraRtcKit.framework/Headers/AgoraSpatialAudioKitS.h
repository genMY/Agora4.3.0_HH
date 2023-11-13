//
//  Copyright (c) 2018 Agora. All rights reserved.
//


#import "AgoraSpatialAudioKitBase.h"


@class AgoraRtcEngineKitS;
@class AgoraRtcConnectionS;

__attribute__((visibility("default"))) @interface AgoraLocalSpatialAudioConfigS : NSObject

@property(assign, nonatomic) AgoraRtcEngineKitS* _Nullable rtcEngine;

@end


NS_ASSUME_NONNULL_BEGIN


__attribute__((visibility("default"))) @interface AgoraLocalSpatialAudioKitS : AgoraSpatialAudioKitBase

+ (instancetype _Nonnull)sharedLocalSpatialAudioWithConfig:(AgoraLocalSpatialAudioConfigS*)config NS_SWIFT_NAME(sharedLocalSpatialAudio(with:));

- (int)updateRemotePosition:(NSString *)userAccount positionInfo:(AgoraRemoteVoicePositionInfo*)posInfo NS_SWIFT_NAME(updateRemotePosition(_:positionInfo:));

- (int)updateRemotePositionEx:(NSString *)userAccount positionInfo:(AgoraRemoteVoicePositionInfo*)posInfo connection:(AgoraRtcConnectionS *)connection NS_SWIFT_NAME(updateRemotePositionEx(_:positionInfo:connection:));

- (int)removeRemotePosition:(NSString *)userAccount NS_SWIFT_NAME(removeRemotePosition(_:));

- (int)removeRemotePositionEx:(NSString *)userAccount connection:(AgoraRtcConnectionS *)connection NS_SWIFT_NAME(removeRemotePositionEx(_:connection:));

- (int)clearRemotePositionsEx:(AgoraRtcConnectionS *)connection NS_SWIFT_NAME(clearRemotePositionsEx(_:));

- (int)setRemoteAudioAttenuation:(double)attenuation userAccount:(NSString *)userAccount forceSet:(BOOL)forceSet NS_SWIFT_NAME(setRemoteAudioAttenuation(_:userAccount:forceSet:));

- (int)updateSelfPositionEx:(simd_float3)position
                axisForward:(simd_float3)axisForward
                axisRight:(simd_float3)axisRight
                axisUp:(simd_float3)axisUp
                connection:(AgoraRtcConnectionS *)connection NS_SWIFT_NAME(updateSelfPositionEx(_:axisForward:axisRight:axisUp:connection:));

- (int)muteRemoteAudioStream:(NSString *)userAccount mute:(BOOL)mute NS_SWIFT_NAME(muteRemoteAudioStream(_:mute:));

@end

NS_ASSUME_NONNULL_END
