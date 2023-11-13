//
//  Copyright (c) 2018 Agora. All rights reserved.
//

#include "AgoraObjects.h"
#import "AgoraSpatialAudioKitBase.h"

@class AgoraRtcEngineKit;
@class AgoraRtcConnection;

__attribute__((visibility("default"))) @interface AgoraCloudSpatialAudioConfig : NSObject
@property(assign, nonatomic) AgoraRtcEngineKit* _Nullable rtcEngine;
/** The App ID issued to you by Agora. See [How to get the App ID](https://docs.agora.io/en/Agora%20Platform/token#get-an-app-id). Only users in apps with the same App ID can join the same channel and communicate with each other. Use an App ID to create only one AgoraRtcEngineKit instance.  To change your App ID, call [destroy]([AgoraRtcEngineKit destroy]) to `destroy` the current AgoraRtcEngineKit instance, and after `destroy` returns 0, call [sharedEngineWithConfig]([AgoraRtcEngineKit sharedEngineWithConfig:delegate:]) to create an AgoraRtcEngineKit instance with the new App ID.
 */
@property(copy, nonatomic) NSString* _Nullable appId;
/** The region for connection. This advanced feature applies to scenarios that have regional restrictions. <p>For the regions that Agora supports, see AgoraAreaCode. The area codes support bitwise operation. After specifying the region, the SDK connects to the Agora servers within that region.</p>
 */
@property(assign, nonatomic) NSUInteger deployRegion;
@end


__attribute__((visibility("default"))) @interface AgoraLocalSpatialAudioConfig : NSObject
@property(assign, nonatomic) AgoraRtcEngineKit* _Nullable rtcEngine;
@end


NS_ASSUME_NONNULL_BEGIN


__attribute__((visibility("default"))) @interface AgoraLocalSpatialAudioKit : AgoraSpatialAudioKitBase

+ (instancetype _Nonnull)sharedLocalSpatialAudioWithConfig:(AgoraLocalSpatialAudioConfig*)config NS_SWIFT_NAME(sharedLocalSpatialAudio(with:));

- (int)updateRemotePosition:(NSUInteger)uid positionInfo:(AgoraRemoteVoicePositionInfo*)posInfo NS_SWIFT_NAME(updateRemotePosition(_:positionInfo:));

- (int)updateRemotePositionEx:(NSUInteger)uid positionInfo:(AgoraRemoteVoicePositionInfo*)posInfo connection:(AgoraRtcConnection *)connection NS_SWIFT_NAME(updateRemotePositionEx(_:positionInfo:connection:));

- (int)removeRemotePosition:(NSUInteger)uid NS_SWIFT_NAME(removeRemotePosition(_:));

- (int)removeRemotePositionEx:(NSUInteger)uid connection:(AgoraRtcConnection *)connection NS_SWIFT_NAME(removeRemotePositionEx(_:connection:));

- (int)clearRemotePositionsEx:(AgoraRtcConnection *)connection NS_SWIFT_NAME(clearRemotePositionsEx(_:));

- (int)setRemoteAudioAttenuation:(double)attenuation uid:(NSUInteger)uid forceSet:(BOOL)forceSet NS_SWIFT_NAME(setRemoteAudioAttenuation(_:uid:forceSet:));

- (int)updateSelfPositionEx:(simd_float3)position
                axisForward:(simd_float3)axisForward
                axisRight:(simd_float3)axisRight
                axisUp:(simd_float3)axisUp
                connection:(AgoraRtcConnection *)connection NS_SWIFT_NAME(updateSelfPositionEx(_:axisForward:axisRight:axisUp:connection:));

- (int)muteRemoteAudioStream:(NSUInteger)uid mute:(BOOL)mute NS_SWIFT_NAME(muteRemoteAudioStream(_:mute:));

@end

NS_ASSUME_NONNULL_END
