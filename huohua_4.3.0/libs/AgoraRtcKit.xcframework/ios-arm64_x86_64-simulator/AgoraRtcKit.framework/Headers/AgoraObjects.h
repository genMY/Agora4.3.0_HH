//
//  AgoraObjects.h
//  AgoraRtcEngineKit
//
//  Copyright (c) 2018 Agora. All rights reserved.
//

#import "AgoraObjectsBase.h"

/** Properties of the video canvas object.
 */
__attribute__((visibility("default"))) @interface AgoraRtcVideoCanvas : AgoraRtcVideoCanvasBase
/**
 * The user id of local video.
 */
@property(assign, nonatomic) NSUInteger uid;

/**
  * The uid of video stream composing the video stream from transcoder which will be drawn on this video canvas. 
  */
@property(assign, nonatomic) NSUInteger subviewUid;
@end

/**
 * The statistics of the local video stream.
 */
__attribute__((visibility("default"))) @interface AgoraRtcLocalVideoStats : AgoraRtcLocalVideoStatsBase
/**
 * ID of the local user.
 */
@property(assign, nonatomic) NSUInteger uid;
@end

/** Statistics of the remote video stream. */
__attribute__((visibility("default"))) @interface AgoraRtcRemoteVideoStats : AgoraRtcRemoteVideoStatsBase
/**
 * ID of the remote user sending the video stream.
 */
@property(assign, nonatomic) NSUInteger uid;

@end

/**
 * The statistics of the remote audio.
 */
__attribute__((visibility("default"))) @interface AgoraRtcRemoteAudioStats : AgoraRtcRemoteAudioStatsBase
/**
 * ID of the user sending the audio stream.
 */
@property(assign, nonatomic) NSUInteger uid;
@end

/** Properties of the audio volume information.
 */
__attribute__((visibility("default"))) @interface AgoraRtcAudioVolumeInfo : AgoraRtcAudioVolumeInfoBase
/** User ID of the speaker.
 */
@property(assign, nonatomic) NSUInteger uid;
@end

/** A class for providing user-specific audio/video transcoding settings.
 */
__attribute__((visibility("default"))) @interface AgoraLiveTranscodingUser : AgoraLiveTranscodingUserBase
/** User ID.
 */
@property(assign, nonatomic) NSUInteger uid;
@end

/** A class for managing CDN transcoding.
 */
__attribute__((visibility("default"))) @interface AgoraLiveTranscoding : AgoraLiveTranscodingBase

/** An AgoraLiveTranscodingUser object managing the user layout configuration in the CDN live stream. Agora supports a maximum of 17 transcoding users in a CDN live stream channel. See AgoraLiveTranscodingUser.
 */
@property(copy, nonatomic) NSArray<AgoraLiveTranscodingUser*>* _Nullable transcodingUsers;

/** Creates a default transcoding object.

 @return Default AgoraLiveTranscoding object.
 */
+ (AgoraLiveTranscoding* _Nonnull)defaultTranscoding NS_SWIFT_NAME(default());

/** Adds a user displaying the video in CDN live.

 @param user The transcoding user. See AgoraLiveTranscodingUser.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)addUser:(AgoraLiveTranscodingUser* _Nonnull)user NS_SWIFT_NAME(add(_:));

/** Removes a user from CDN live.

 @param uid The user ID of the user to remove from CDN live.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)removeUser:(NSUInteger)uid NS_SWIFT_NAME(removeUser(_:));

@end

__attribute__((visibility("default"))) @interface AgoraRecorderStreamInfo : AgoraRecorderStreamInfoBase
/* User ID. A 32-bit unsigned integer with a value ranging from 1 to
 * (2<sup>32</sup>-1). The `uid` must be unique and not set to 0 . Your app
 * must record and maintain the returned `uid` since the SDK does not do so.
 */
@property (nonatomic, nonatomic) NSUInteger uid;
@end

__attribute__((visibility("default"))) @interface AgoraAudioSpectrumInfo : NSObject

/** User ID of the speaker. */
@property(nonatomic, assign) NSInteger uid;
@property(nonatomic, strong) NSArray<NSNumber *> * _Nullable audioSpectrumData;

@end

__attribute__((visibility("default"))) @interface AgoraEncodedVideoFrameInfo : AgoraEncodedVideoFrameInfoBase
/**
 * ID of the user.
 */
@property (assign, nonatomic) NSInteger uid;
@end

NS_SWIFT_NAME(AgoraExtensionInfo) __attribute__((visibility("default"))) @interface AgoraExtensionInfo : AgoraExtensionInfoBase
/**
 * The id of the remote user on which the extension works.
 *
 * @note remoteUid = 0 means that the extension works on all remote streams.
 */
@property (assign, nonatomic) NSUInteger remoteUid NS_SWIFT_NAME(remoteUid);
/**
 * User ID: A 32-bit unsigned integer ranging from 1 to (2^32-1). It must be unique.
 */
@property (assign, nonatomic) NSUInteger localUid NS_SWIFT_NAME(localUid);

@end
/**
 * Video layout info.
 */
__attribute__((visibility("default"))) @interface AgoraVideoLayout: NSObject
/**
 * Channel Id from which this video stream come from.
 */
@property(copy, nonatomic) NSString* _Nonnull channelId NS_SWIFT_NAME(channelId);
/**
 * User id of video stream.
 */
@property (assign, nonatomic) NSUInteger uid NS_SWIFT_NAME(uid);
/**
 * User account of video stream.
 */
@property(copy, nonatomic) NSString* _Nullable strUid NS_SWIFT_NAME(strUid);
/**
 * video state  of video stream on a transcoded video stream canvas.
 * 0 for normal video , 1 for placeholder image showed , 2 for black image.
 */
@property (assign, nonatomic) NSUInteger videoState NS_SWIFT_NAME(videoState);
/**
 * x coordinate of video stream on a transcoded video stream canvas.
 */
@property (assign, nonatomic) NSUInteger x NS_SWIFT_NAME(x);
/**
 * y coordinate of video stream on a transcoded video stream canvas.
 */
@property (assign, nonatomic) NSUInteger y NS_SWIFT_NAME(y);
/**
 * width of video stream on a transcoded video stream canvas.
 */
@property (assign, nonatomic) NSUInteger width NS_SWIFT_NAME(width);
/**
 * height of video stream on a transcoded video stream canvas.
 */
@property (assign, nonatomic) NSUInteger height NS_SWIFT_NAME(height);
@end
/** 
 *  The definition of AgoraVideoLayoutInfo.
 */
__attribute__((visibility("default"))) @interface AgoraVideoLayoutInfo: NSObject
/**
 * width of transcoded video stream.
 */ 
@property (assign, nonatomic) NSUInteger width NS_SWIFT_NAME(width);
/**
 * height of transcoded video stream.
 */ 
@property (assign, nonatomic) NSUInteger height NS_SWIFT_NAME(height);
/**
 * count of video layout info in transcoded video stream.
 */ 
@property (assign, nonatomic) NSUInteger layoutCount NS_SWIFT_NAME(layoutCount);
/**
 * video layout info in transcoded video stream.
 */
@property(copy, nonatomic) NSArray<AgoraVideoLayout *> *_Nullable layoutList NS_SWIFT_NAME(layoutList);
@end