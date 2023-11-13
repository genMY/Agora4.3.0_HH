//
//  AgoraObjectsS.h
//  AgoraRtcEngineKit
//
//  Copyright (c) 2018 Agora. All rights reserved.
//

#import "AgoraObjectsBase.h"

/** Properties of the video canvas object.
 */
__attribute__((visibility("default"))) @interface AgoraRtcVideoCanvasS : AgoraRtcVideoCanvasBase
/**
 * The user id.
 */
@property(copy, nonatomic) NSString* _Nonnull userAccount;
/**
 * The user id of video stream in transcoded stream.
 */
@property(copy, nonatomic) NSString* _Nonnull subviewUserAccount;

@end

/**
 * The statistics of the local video stream.
 */
__attribute__((visibility("default"))) @interface AgoraRtcLocalVideoStatsS : AgoraRtcLocalVideoStatsBase
/**
 * ID of the local user.
 */
@property(copy, nonatomic) NSString* _Nonnull userAccount;
@end

/** Statistics of the remote video stream. */
__attribute__((visibility("default"))) @interface AgoraRtcRemoteVideoStatsS : AgoraRtcRemoteVideoStatsBase
/**
 * ID of the remote user sending the video stream.
 */
@property(copy, nonatomic) NSString* _Nonnull userAccount;

@end

/**
 * The statistics of the remote audio.
 */
__attribute__((visibility("default"))) @interface AgoraRtcRemoteAudioStatsS : AgoraRtcRemoteAudioStatsBase
/**
 * ID of the user sending the audio stream.
 */
@property(copy, nonatomic) NSString* _Nonnull userAccount;
@end

/** Properties of the audio volume information.
 */
__attribute__((visibility("default"))) @interface AgoraRtcAudioVolumeInfoS : AgoraRtcAudioVolumeInfoBase
/** User ID of the speaker.
 */
@property(copy, nonatomic) NSString* _Nonnull userAccount;
@end

/** A class for providing user-specific audio/video transcoding settings.
 */
__attribute__((visibility("default"))) @interface AgoraLiveTranscodingUserS : AgoraLiveTranscodingUserBase
/** User ID.
 */
@property(copy, nonatomic) NSString* _Nonnull userAccount;
@end

/** A class for managing CDN transcoding.
 */
__attribute__((visibility("default"))) @interface AgoraLiveTranscodingS : AgoraLiveTranscodingBase

/** An AgoraLiveTranscodingUser object managing the user layout configuration in the CDN live stream. Agora supports a maximum of 17 transcoding users in a CDN live stream channel. See AgoraLiveTranscodingUser.
 */
@property(copy, nonatomic) NSArray<AgoraLiveTranscodingUserS*>* _Nullable transcodingUsers;

/** Creates a default transcoding object.

 @return Default AgoraLiveTranscoding object.
 */
+ (AgoraLiveTranscodingS* _Nonnull)defaultTranscoding NS_SWIFT_NAME(default());

/** Adds a user displaying the video in CDN live.

 @param user The transcoding user. See AgoraLiveTranscodingUserS.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)addUser:(AgoraLiveTranscodingUserS* _Nonnull)user NS_SWIFT_NAME(add(_:));

/** Removes a user from CDN live.

 @param userAccount The user ID of the user to remove from CDN live.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)removeUser:(NSString* _Nonnull)userAccount NS_SWIFT_NAME(removeUser(_:));

@end

__attribute__((visibility("default"))) @interface AgoraRecorderStreamInfoS : AgoraRecorderStreamInfoBase
/**
 * User account of the user.
 */
@property (copy, nonatomic) NSString* _Nullable userAccount;
@end

__attribute__((visibility("default"))) @interface AgoraAudioSpectrumInfoS : NSObject

/** User ID of the speaker. */
@property(nonatomic, copy) NSString* _Nonnull userAccount;
@property(nonatomic, strong) NSArray<NSNumber *> * _Nullable audioSpectrumData;

@end

__attribute__((visibility("default"))) @interface AgoraEncodedVideoFrameInfoS : AgoraEncodedVideoFrameInfoBase
/**
 * User account of the user.
 */
@property (copy, nonatomic) NSString* _Nullable userAccount;
@end

NS_SWIFT_NAME(AgoraExtensionInfoS) __attribute__((visibility("default"))) @interface AgoraExtensionInfoS : AgoraExtensionInfoBase
/**
 * The id of the remote user on which the extension works.
 *
 * @note remoteUid = 0 means that the extension works on all remote streams.
 */
@property (copy, nonatomic) NSString* _Nonnull remoteUserAccount NS_SWIFT_NAME(remoteUserAccount);
/**
 * User ID.
 */
@property (copy, nonatomic) NSString* _Nonnull localUserAccount NS_SWIFT_NAME(localUserAccount);

@end
