//
//  Copyright (c) 2018 Agora. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AgoraEnumerates.h"
#import "AgoraObjects.h"
#import <simd/simd.h>


NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default"))) @interface AgoraRemoteVoicePositionInfo : NSObject
@property(assign, nonatomic) simd_float3 position;
@property(assign, nonatomic) simd_float3 forward;
@end


__attribute__((visibility("default"))) @interface AgoraSpatialAudioZone : NSObject
//the zone id
@property(assign, nonatomic) NSInteger zoneSetId;
//zone center point
@property(nonatomic) simd_float3 position;
//forward direction 
@property(nonatomic) simd_float3 forward;
//right direction
@property(nonatomic) simd_float3 right;
//up direction
@property(nonatomic) simd_float3 up;
//the forward side length of the zone
@property(assign, nonatomic) float forwardLength;
//tehe right side length of the zone
@property(assign, nonatomic) float rightLength;
//the up side length of the zone
@property(assign, nonatomic) float upLength;
//the audio attenuation of zone
@property(assign, nonatomic) float audioAttenuation;
@end


__attribute__((visibility("default"))) @interface AgoraSpatialAudioKitBase : NSObject

+ (void)destroy NS_SWIFT_NAME(destroy());

- (int)setMaxAudioRecvCount:(NSUInteger)maxCount NS_SWIFT_NAME(setMaxAudioRecvCount(_:));

- (int)setAudioRecvRange:(float)range NS_SWIFT_NAME(setAudioRecvRange(_:));

- (int)setDistanceUnit:(float)unit NS_SWIFT_NAME(setDistanceUnit(_:));

- (int)updatePlayerPositionInfo:(NSInteger)playerId positionInfo:(AgoraRemoteVoicePositionInfo* _Nonnull)positionInfo NS_SWIFT_NAME(updatePlayerPositionInfo(_:positionInfo:));

- (int)updateSelfPosition:(simd_float3)position axisForward:(simd_float3)axisForward axisRight:(simd_float3)axisRight axisUp:(simd_float3)axisUp NS_SWIFT_NAME(updateSelfPosition(_:axisForward:axisRight:axisUp:));

- (int)updateSelfTransform:(simd_float4x4)transform NS_SWIFT_NAME(updateSelfTransform(_:));

- (int)muteLocalAudioStream:(BOOL)mute NS_SWIFT_NAME(muteLocalAudioStream(_:));

- (int)muteAllRemoteAudioStreams:(BOOL)mute NS_SWIFT_NAME(muteAllRemoteAudioStreams(_:));

- (int)setZones:(NSArray<AgoraSpatialAudioZone*> * _Nullable)zones NS_SWIFT_NAME(setZones(_:));

- (int)setPlayerAttenuation:(double)attenuation playerId:(NSUInteger)playerId forceSet:(BOOL)forceSet NS_SWIFT_NAME(setPlayerAttenuation(_:playerId:forceSet:));

- (int)clearRemotePositions NS_SWIFT_NAME(clearRemotePositions());

@end

NS_ASSUME_NONNULL_END
