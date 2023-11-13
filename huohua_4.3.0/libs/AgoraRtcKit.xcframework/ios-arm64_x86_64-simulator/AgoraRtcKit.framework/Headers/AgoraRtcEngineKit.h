//
//  AgoraRtcEngineKit.h
//  AgoraRtcEngineKit
//
//  Copyright (c) 2018 Agora. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AgoraRtcEngineKitBase.h"
#import "AgoraConstants.h"
#import "AgoraObjects.h"
#import "AgoraRtcMediaPlayerProtocol.h"
#import "AgoraH265TranscoderProtocol.h"
#import "AgoraRtcEngineDelegate.h"
#import "AgoraAudioFrameDelegate.h"
#import "AgoraAudioEncodedFrameDelegate.h"
#import "AgoraRtcAudioSpectrumDelegate.h"
#import "AgoraVideoFrameDelegate.h"
#import "AgoraEncodedVideoFrameDelegate.h"
#import "AgoraRtcMediaPlayerDelegate.h"
#import "AgoraMediaRecorderDelegate.h"
#import "AgoraMediaMetadataDelegate.h"
#import "AgoraMediaMetadataDataSource.h"
#import "AgoraDirectCdnStreamingEventDelegate.h"
#import "AgoraRtcMediaPlayerCacheManagerProtocol.h"
#import "AgoraMediaRecorder.h"

/** Agora provides ensured quality of experience (QoE) for worldwide Internet-based voice and video communications through a virtual global network that is especially optimized for real-time web and mobile-to-mobile applications.

 The AgoraRtcEngineKit class is the entry point of the Agora SDK that provides simple APIs for applications to easily start voice and video communication.
 */

#pragma mark - AgoraRtcEngineKit

/**
 * Provides all methods that can be invoked by your application.
 *
 * Agora provides ensured quality of experience (QoE) for worldwide
 * Internet-based voice and video communications through a virtual global
 * network that is especially optimized for real-time web and mobile-to-mobile
 * applications.
 *
 * `AgoraRtcEngineKit` is the basic interface class of Agora Native SDK. Creating an AgoraRtcEngineKit object and then calling the methods of this object enables the use of Agora Native SDK’s communication functionality.
*/
// __attribute__((visibility("default"))) @interface AgoraRtcEngineKit : NSObject<AgoraRtcEngineBaseProtocol>
@protocol AgoraRtcEngineKitProtocol <NSObject>
@required
#pragma mark Core Methods

/**-----------------------------------------------------------------------------
 * @name Core Methods
 * -----------------------------------------------------------------------------
 */

/**
 * Sets and retrieves the SDK delegate.
 *
 * The SDK uses the delegate to inform the app on engine runtime events. All methods defined in the
 * delegate are optional implementation methods.
 */
@property(nonatomic, weak) id<AgoraRtcEngineDelegate> _Nullable delegate;

/**
 * Preload a channel.
 *
 * This method enables users to preload a channel.
 *
 * A successful call of this method will reduce the time of joining the same channel.
 *
 * Note:
 *  1. The SDK supports preloading up to 20 channels. Once the preloaded channels exceed the limit, the SDK will keep the latest 20 available.
 *  2. Renew the token of the preloaded channel by calling this method with the same 'channelId' and 'uid'.
 *
 * @param token The token generated on your server for authentication.
 * @param channelId The channel name. This parameter signifies the channel in which users engage in
 * real-time audio and video interaction. Under the premise of the same App ID, users who fill in
 * the same channel ID enter the same channel for audio and video interaction. The string length
 * must be less than 64 bytes. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-",
 * ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param uid The user ID. This parameter is used to identify the user in the channel for real-time
 * audio and video interaction. You need to set and manage user IDs yourself, and ensure that each
 * user ID in the same channel is unique. This parameter is a 32-bit unsigned integer. The value
 * range is 1 to 2<h>32</h>-1. If the user ID is not assigned (or set to 0), the SDK assigns a random user
 * ID and returns it in the onJoinChannelSuccess callback. Your application must record and maintain
 * the returned user ID, because the SDK does not do so.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - -7: The IRtcEngine object has not been initialized. You need to initialize the IRtcEngine
 * object before calling this method.
 *   - -102: The channel name is invalid. You need to pass in a valid channel name in channelId to
 * preload the channel again.
 */
- (int)preloadChannelByToken:(NSString * _Nullable)token
                   channelId:(NSString * _Nonnull)channelId
                         uid:(NSUInteger)uid NS_SWIFT_NAME(preloadChannel(byToken:channelId:uid:));

/**
 * Preload a channel.
 *
 * This method enables users to preload a channel.
 *
 * A successful call of this method will reduce the time of joining the same channel.
 *
 * Note:
 *  1. The SDK supports preloading up to 20 channels. Once the preloaded channels exceed the limit, the SDK will keep the latest 20 available.
 *  2. Renew the token of the preloaded channel by calling this method with the same 'channelId' and 'userAccount'.
 *
 * @param token The token generated on your server for authentication.
 * @param channelId The channel name. This parameter signifies the channel in which users engage in
 * real-time audio and video interaction. Under the premise of the same App ID, users who fill in
 * the same channel ID enter the same channel for audio and video interaction. The string length
 * must be less than 64 bytes. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-",
 * ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param userAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that you set this parameter and do not set it as null. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - -2: The parameter is invalid. For example, the userAccount parameter is empty.
 * You need to pass in a valid parameter and preload the channel again.
 *   - -7: The IRtcEngine object has not been initialized. You need to initialize the IRtcEngine
 * object before calling this method.
 *   - -102: The channel name is invalid. You need to pass in a valid channel name in channelId to
 * preload the channel again.
 */
- (int)preloadChannelByTokenWithUserAccount:(NSString * _Nullable)token
                   channelId:(NSString * _Nonnull)channelId
                 userAccount:(NSString * _Nonnull)userAccount NS_SWIFT_NAME(preloadChannelWithUserAccount(byToken:channelId:userAccount:));

/**
 * Joins a channel.
 *
 * Users in the same channel can talk to each other, and multiple users in the
 * same channel can start a group chat. Users with different App IDs cannot
 * call each other even if they join the same channel.
 *
 * You must call the \ref leaveChannel: leaveChannel method to exit the
 * current call before entering another channel. This method call is
 * asynchronous; therefore, you can call this method in the main user interface
 * thread.
 *
 * A successful method call triggers the following callbacks:
 *
 * - The local client: \ref AgoraRtcEngineDelegate.rtcEngine:didJoinChannel:withUid:elapsed: didJoinChannel.
 * - The remote client: \ref AgoraRtcEngineDelegate.rtcEngine:didJoinedOfUid:elapsed: didJoinedOfUid,
 * if the user joining the channel is in the Communication profile, or is a
 * BROADCASTER in the Live Broadcast profile.
 *
 * When the connection between the client and Agora's server is interrupted due
 * to poor network conditions, the SDK tries reconnecting to the server. When
 * the local client successfully rejoins the channel, the SDK triggers the \ref AgoraRtcEngineDelegate.rtcEngine:didRejoinChannel:withUid:elapsed: didRejoinChannel callback on the local client.
 *
 * @note
 * - When joining a channel, the SDK calls
 * `setCategory(AVAudioSessionCategoryPlayAndRecord)` to set `AVAudioSession`
 * to `PlayAndRecord` mode. When `AVAudioSession` is set to `PlayAndRecord`
 * mode, the sound played (for example a ringtone) is interrupted. The app
 * should not set `AVAudioSession` to any other mode.
 * - The SDK uses the iOS's AVAudioSession shared object for audio recording
 * and playback. Using this object may affect the SDK’s audio functions.
 * @param token The token for authentication.
 * - In situations not requiring high security: You can use the temporary token
 * generated at Console. For details, see [Get a temporary token](https://docs.agora.io/en/Agora%20Platform/token?platform=All%20Platforms#get-a-temporary-token).
 * - In situations requiring high security: Set it as the token generated at
 * you server. For details, see [Generate a token](https://docs.agora.io/en/Agora%20Platform/token?platform=All%20Platforms#get-a-token).
 * @param channelId Unique channel name for the AgoraRTC session in the string
 * format. The string length must be less than 64 bytes. Supported character
 * scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param info (Optional) Additional information about the channel. This
 * parameter can be set to `nil` or contain channel related information. Other
 * users in the channel do not receive this message.
 * @param uid User ID. A 32-bit unsigned integer with a value ranging from 1 to
 * (2<sup>32</sup>-1). The `uid` must be unique. If a `uid` is not assigned (or
 * set to 0), the SDK assigns and returns a `uid` in the callback. Your app
 * must record and maintain the returned `uid` since the SDK does not do so.
 * @param joinSuccessBlock Same as \ref AgoraRtcEngineDelegate.rtcEngine:didJoinChannel:withUid:elapsed: didJoinChannel. We recommend you set this parameter as `nil` to use `didJoinChannel`.
 * - If `joinSuccessBlock` is nil, the SDK triggers the `didJoinChannel` callback.
 * - If you implement both `joinSuccessBlock` and `didJoinChannel`, `joinSuccessBlock` takes higher priority than `didJoinChannel`.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *    - -2: #AgoraErrorCodeInvalidArgument
 *    - -3: #AgoraErrorCodeNotReady
 *    - -5: #AgoraErrorCodeRefused
 */
- (int)joinChannelByToken:(NSString * _Nullable)token
                channelId:(NSString * _Nonnull)channelId
                     info:(NSString * _Nullable)info
                      uid:(NSUInteger)uid
              joinSuccess:(void(^ _Nullable)(NSString * _Nonnull channel, NSUInteger uid, NSInteger elapsed))joinSuccessBlock NS_SWIFT_NAME(joinChannel(byToken:channelId:info:uid:joinSuccess:));

/**
 * Joins a channel.
 *
 * Users in the same channel can talk to each other, and multiple users in the
 * same channel can start a group chat. Users with different App IDs cannot
 * call each other even if they join the same channel.
 *
 * You must call the \ref leaveChannel: leaveChannel method to exit the
 * current call before entering another channel. This method call is
 * asynchronous; therefore, you can call this method in the main user interface
 * thread.
 *
 * A successful method call triggers the following callbacks:
 *
 * - The local client: \ref AgoraRtcEngineDelegate.rtcEngine:didJoinChannel:withUid:elapsed: didJoinChannel.
 * - The remote client: \ref AgoraRtcEngineDelegate.rtcEngine:didJoinedOfUid:elapsed: didJoinedOfUid,
 * if the user joining the channel is in the Communication profile, or is a
 * BROADCASTER in the Live Broadcast profile.
 *
 * When the connection between the client and Agora's server is interrupted due
 * to poor network conditions, the SDK tries reconnecting to the server. When
 * the local client successfully rejoins the channel, the SDK triggers the \ref AgoraRtcEngineDelegate.rtcEngine:didRejoinChannel:withUid:elapsed: didRejoinChannel callback on the local client.
 *
 * @note
 * - When joining a channel, the SDK calls
 * `setCategory(AVAudioSessionCategoryPlayAndRecord)` to set `AVAudioSession`
 * to `PlayAndRecord` mode. When `AVAudioSession` is set to `PlayAndRecord`
 * mode, the sound played (for example a ringtone) is interrupted. The app
 * should not set `AVAudioSession` to any other mode.
 * - The SDK uses the iOS's AVAudioSession shared object for audio recording
 * and playback. Using this object may affect the SDK’s audio functions.
 * @param token The token for authentication.
 * - In situations not requiring high security: You can use the temporary token
 * generated at Console. For details, see [Get a temporary token](https://docs.agora.io/en/Agora%20Platform/token?platform=All%20Platforms#get-a-temporary-token).
 * - In situations requiring high security: Set it as the token generated at
 * you server. For details, see [Generate a token](https://docs.agora.io/en/Agora%20Platform/token?platform=All%20Platforms#get-a-token).
 * @param channelId Unique channel name for the AgoraRTC session in the string
 * format. The string length must be less than 64 bytes. Supported character
 * scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param uid User ID. A 32-bit unsigned integer with a value ranging from 1 to
 * (2<sup>32</sup>-1). The `uid` must be unique. If a `uid` is not assigned (or
 * set to 0), the SDK assigns and returns a `uid` in the callback. Your app
 * must record and maintain the returned `uid` since the SDK does not do so.
 * @param mediaOptions AgoraRtcChannelMediaOptions Object.
 * @param joinSuccessBlock Same as \ref AgoraRtcEngineDelegate.rtcEngine:didJoinChannel:withUid:elapsed: didJoinChannel. We recommend you set this parameter as `nil` to use `didJoinChannel`.
 * - If `joinSuccessBlock` is nil, the SDK triggers the `didJoinChannel` callback.
 * - If you implement both `joinSuccessBlock` and `didJoinChannel`, `joinSuccessBlock` takes higher priority than `didJoinChannel`.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *    - -2: #AgoraErrorCodeInvalidArgument
 *    - -3: #AgoraErrorCodeNotReady
 *    - -5: #AgoraErrorCodeRefused
 */
- (int)joinChannelByToken:(NSString * _Nullable)token
                channelId:(NSString * _Nonnull)channelId
                      uid:(NSUInteger)uid
             mediaOptions:(AgoraRtcChannelMediaOptions * _Nonnull)mediaOptions
              joinSuccess:(void(^ _Nullable)(NSString * _Nonnull channel, NSUInteger uid, NSInteger elapsed))joinSuccessBlock NS_SWIFT_NAME(joinChannel(byToken:channelId:uid:mediaOptions:joinSuccess:));

  /** Starts or update to relay media streams across channels.

  After a successful method call, the SDK triggers the [channelMediaRelayStateDidChange]([AgoraRtcEngineDelegate rtcEngine:channelMediaRelayStateDidChange:error:]) callback, and this callback return the state of the media stream relay.

  - If the `channelMediaRelayStateDidChange` callback returns AgoraChannelMediaRelayStateRunning(2) and AgoraChannelMediaRelayStateIdle(0), the SDK starts relaying media streams between the original and the destination channel.
  - If the `channelMediaRelayStateDidChange` callback returns AgoraChannelMediaRelayStateFailure(3), an exception occurs during the media stream relay.

  **Note**

  - Call this method after the [joinChannel]([AgoraRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) method.
  - This method takes effect only when you are a broadcaster in a Live-broadcast channel.
  - Contact sales-us@agora.io before implementing this function.
  - We do not support string user accounts in this API.

  @since v4.2.0
  @param config The configuration of the media stream relay: [AgoraChannelMediaRelayConfiguration](AgoraChannelMediaRelayConfiguration).

  @return - 0: Success.
  - < 0: Failure.
    - -1(ERR_FAILED): A general error occurs (no specified reason).
    - -2(ERR_INVALID_ARGUMENT): The argument is invalid.
    - -5(ERR_REFUSED): The request is rejected.
    - -8(ERR_INVALID_STATE): The current status is invalid, only allowed to be called when the role is the broadcaster.
  */
- (int)startOrUpdateChannelMediaRelay:(AgoraChannelMediaRelayConfiguration * _Nonnull)config NS_SWIFT_NAME(startOrUpdateChannelMediaRelay(_:));

- (int)startLocalVideoTranscoder:(AgoraLocalTranscoderConfiguration* _Nonnull)config NS_SWIFT_NAME(startLocalVideoTranscoder(_:));

- (int)updateLocalTranscoderConfiguration:(AgoraLocalTranscoderConfiguration* _Nonnull)config NS_SWIFT_NAME(updateLocalTranscoderConfiguration(_:));

/**
 * Initializes the Agora SDK service.
 *
 * After the initialization, the service is set to enable audio by default.
 * @note Ensure that you call this method before calling any other API.
 * @warning Only users with the same App ID can call each other.
 * @warning One AgoraRtcEngineKit can use only one App ID. If you need to
 * change the App ID, call \ref destroy to release the current instance
 * first, and then call this method to create a new instance.
 @param appId    [App ID](https://docs.agora.io/en/Agora%20Platform/terms?platform=All%20Platforms#a-nameappidaapp-id) of
 your Agora project.
 @param delegate AgoraRtcEngineDelegate.
 @return An AgoraRtcEngineKit object.
 */
+ (instancetype _Nonnull)sharedEngineWithAppId:(NSString * _Nonnull)appId
                                      delegate:(id<AgoraRtcEngineDelegate> _Nullable)delegate NS_SWIFT_NAME(sharedEngine(withAppId:delegate:));

/** Creates an AgoraRtcEngineKit instance.

  Unless otherwise specified, all the methods provided by the AgoraRtcEngineKit instance are executed asynchronously. Agora recommends calling these methods in the same thread.

  @note
  - You must create the AgoraRtcEngineKit instance before calling any other method.
  - You can create an AgoraRtcEngineKit instance either by calling this method or by calling \ref AgoraRtcEngineKit.sharedEngineWithAppId:delegate: sharedEngineWithAppId. The difference between `sharedEngineWithAppId` and this method is that this method enables you to specify the connection area.
  - The SDK supports creating only one AgoraRtcEngineKit instance for an app for now.

  @param config    Configurations for the AgoraRtcEngineKit instance. For details, see AgoraRtcEngineConfig.
  @param delegate AgoraRtcEngineDelegate.

  @return - The AgoraRtcEngineKit instance, if this method call succeeds.
 - The error code, if this method call fails.

  - `-1`(`AgoraErrorCodeFailed`): A general error occurs (no specified reason).
  - `-2`(`AgoraErrorCodeInvalidArgument`): No `AgoraRtcEngineDelegate` object is specified.
  - `-7`(`AgoraErrorCodeNotInitialized`): The SDK is not initialized.
  - `-101`(`AgoraErrorCodeInvalidAppId`): The App ID is invalid.
  */
+ (instancetype _Nonnull)sharedEngineWithConfig:(AgoraRtcEngineConfig * _Nonnull)config
                                       delegate:(id<AgoraRtcEngineDelegate> _Nullable)delegate NS_SWIFT_NAME(sharedEngine(with:delegate:));

/** Adjust the playback signal volume of a specified remote user.

 You can call this method as many times as necessary to adjust the playback volume of different remote users, or to repeatedly adjust the playback volume of the same remote user.

 **Note**

 - Call this method after joining a channel.
 - The playback volume here refers to the mixed volume of a specified remote user.
 - This method can only adjust the playback volume of one specified remote user at a time. To adjust the playback volume of different remote users, call the method as many times, once for each remote user.

 @param uid The ID of the remote user.
 @param volume The playback volume of the specified remote user. The value ranges from 0 to 100:

 - 0: Mute.
 - 100: Original volume.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)adjustUserPlaybackSignalVolume:(NSUInteger)uid volume:(int)volume NS_SWIFT_NAME(adjustUserPlaybackSignalVolume(_:volume:));

/**
 * Stops/Resumes receiving the audio stream of a specified user.
 *
 * You can call this method before or after joining a channel.
 * If a user leaves a channel, the settings in this method become invalid.
 * @param uid  The ID of the specified user.
 * @param mute Whether to stop receiving the audio stream of the specified user:
 * - `YES`: Stop receiving the audio stream of the specified user.
 * - `NO`: (Default) Resume receiving the audio stream of the specified user.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)muteRemoteAudioStream:(NSUInteger)uid mute:(BOOL)mute NS_SWIFT_NAME(muteRemoteAudioStream(_:mute:));

/**
 * Enable/Disable an extension.
 * By calling this function, you can dynamically enable/disable the extension without changing the pipeline.
 * For example, enabling/disabling Extension_A means the data will be adapted/bypassed by Extension_A.
 *
 * NOTE: For compatibility reasons, if you haven't call registerExtensionWithVendor,
 * enableExtension will automatically register the specified extension.
 * We suggest you call registerExtensionWithVendor explicitly.
 *
 * @param provider The name of the extension provider, e.g. agora.io.
 * @param extension The name of the extension, e.g. agora.beauty.
 * @param extensionInfo The information for extension definition see AgoraExtensionInfo
 * @param enabled Whether to enable the extension:
 * - true: (Default) Enable the extension.
 * - false: Disable the extension.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)enableExtensionWithVendor:(NSString * __nonnull)provider
                       extension:(NSString * __nonnull)extension
                   extensionInfo:(AgoraExtensionInfo * __nonnull)extensionInfo
                         enabled:(BOOL)enabled NS_SWIFT_NAME(enableExtension(withVendor:extension:extensionInfo:enabled:));

/**
 * Sets the properties of an extension.
 *
 * @param provider The name of the extension provider, e.g. agora.io.
 * @param extension The name of the extension, e.g. agora.beauty.
 * @param extensionInfo The information for extension. See AgoraExtensionInfo.
 * @param key The key of the extension.
 * @param value The JSON formatted value of the extension key.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)setExtensionPropertyWithVendor:(NSString * __nonnull)provider
                            extension:(NSString * __nonnull)extension
                        extensionInfo:(AgoraExtensionInfo * __nonnull)extensionInfo
                                  key:(NSString * __nonnull)key
                                value:(NSString * __nonnull)value NS_SWIFT_NAME(setExtensionPropertyWithVendor(_:extension:extensionInfo:key:value:));

/**
 * Gets the properties of an extension.
 *
 * @param provider The name of the extension provider, e.g. agora.io.
 * @param extension The name of the extension, e.g. agora.beauty.
 * @param extensionInfo The information for extension. See AgoraExtensionInfo.
 * @param key The key of the extension.
 *
 * @return
 * - JSON formatted string of property's value; return null if failed
 */
- (NSString * _Nullable)getExtensionPropertyWithVendor:(NSString * __nonnull)provider
                                             extension:(NSString * __nonnull)extension
                                         extensionInfo:(AgoraExtensionInfo * __nonnull)extensionInfo
                                                   key:(NSString * __nonnull)key NS_SWIFT_NAME(getExtensionProperty(withVendor:extension:extensionInfo:key:));

#pragma mark Core Video

/**
 * This method initializes the video view of the local stream on the local
 * device.
 *
 * It affects only the video view that the local user sees, not the published
 * local video stream.
 *
 * Call this method to bind the local video stream to a video view and to set
 * the rendering and mirror modes of the video view. To unbind the `view`, set
 * the `view` in #AgoraRtcVideoCanvas to `nil`.
 *
 * @note
 * Call this method before joining a channel.
 * @param local The local video view and settings. See #AgoraRtcVideoCanvas.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)setupLocalVideo:(AgoraRtcVideoCanvas * _Nullable)local NS_SWIFT_NAME(setupLocalVideo(_:));

/** Binds the remote user to the video display window, that is, sets the view for the user of the specified uid.

 Usually, the application should specify the uid of the remote video in the method call before the user enters a channel. If the remote uid is unknown to the application, set it later when the application receives the [userJoinedBlock]([AgoraRtcEngineKit userJoinedBlock:]) event.
 If the Video Recording function is enabled, the Video Recording Service joins the channel as a dumb client, which means other clients will also receive the [didJoinedOfUid]([AgoraRtcEngineDelegate rtcEngine:didJoinedOfUid:elapsed:]) event. Your application should not bind it with the view, because it does not send any video stream. If your application cannot recognize the dumb client, bind it with the view when the [firstRemoteVideoDecodedOfUid]([AgoraRtcEngineDelegate rtcEngine:firstRemoteVideoDecodedOfUid:size:elapsed:]) event is triggered. To unbind the user with the view, set the view to null. After the user has left the channel, the SDK unbinds the remote user.

 @param remote AgoraRtcVideoCanvas

 @return * 0: Success.
* <0: Failure.
 */
- (int)setupRemoteVideo:(AgoraRtcVideoCanvas * _Nonnull)remote NS_SWIFT_NAME(setupRemoteVideo(_:));

/** Configures the remote video display mode. The application can call this method multiple times to change the display mode.

 @param uid  User id of the user whose video streams are received.
 @param mode AgoraVideoRenderMode
 @param mirror AgoraVideoMirrorMode

 @return * 0: Success.
* <0: Failure.
 */
- (int)setRemoteRenderMode:(NSUInteger)uid
                      mode:(AgoraVideoRenderMode)mode
                    mirror:(AgoraVideoMirrorMode)mirror NS_SWIFT_NAME(setRemoteRenderMode(_:mode:mirror:));

/**
 * Stops or resumes receiving the video stream of a specified user.
 *
 * You can call this method before or after joining a channel.
 * If a user leaves a channel, the settings in this method become invalid.
 *
 * @param uid ID of the specified remote user.
 * @param mute Whether to stop receiving the video stream of the specified user:
 * - `YES`: Stop receiving the video stream of the specified user.
 * - `NO`: (Default) Resume receiving the video stream of the specified user.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)muteRemoteVideoStream:(NSUInteger)uid
                        mute:(BOOL)mute NS_SWIFT_NAME(muteRemoteVideoStream(_:mute:));

#pragma mark Sound Position Indication
/** Sets the sound position and gain of a remote user.

 When the local user calls this method to set the sound position of a remote user, the sound difference between the left and right channels allows the local user to track the real-time position of the remote user, creating a real sense of space. This method applies to massively multiplayer online games, such as Battle Royale games.

**Note:**

- Ensure that you call this method after joining a channel. For this method to work, enable stereo panning for remote users by calling [enableSoundPositionIndication]([AgoraRtcEngineKit enableSoundPositionIndication:]) before joining a channel.
This method requires hardware support.
- For the best effect, we recommend using the following audio output devices:
  - (iOS) A stereo headset.
  - (macOS) A stereo loudspeaker.
 @param uid The ID of the remote user.
 @param pan The sound position of the remote user. The value ranges from -1.0 to 1.0:

 * 0.0: (default) the remote sound comes from the front.
 * -1.0: the remote sound comes from the left.
 * 1.0: the remote sound comes from the right.

 @param gain Gain of the remote user. The value ranges from 0.0 to 100.0. The default value is 100.0 (the original gain of the remote user). The smaller the value, the less the gain.

 @return * 0: Success.
* < 0: Failure.
 */
- (int)setRemoteVoicePosition:(NSUInteger)uid pan:(double)pan gain:(double)gain NS_SWIFT_NAME(setRemoteVoicePosition(_:pan:gain:));

/** Sets spatial audio parameters of a remote user.

 When the local user calls this method to set the spatial audio parameters  of a remote user, the sound difference between the left and right channels allows the local user to track the real-time position of the remote user, creating a real sense of spatial.

**Note:**

- For the best effect, we recommend using the following audio output devices:
  - (iOS) A stereo headset.
  - (macOS) A stereo loudspeaker.
 @param uid The ID of the remote user.
 @param params The spatial audio parameters of the remote user.

 @return * 0: Success.
* < 0: Failure.
 */
- (int)setRemoteUserSpatialAudioParams:(NSUInteger)uid
                                  params:(AgoraSpatialAudioParams* _Nonnull)params NS_SWIFT_NAME(setRemoteUserSpatialAudioParams(_:params:));

#pragma mark Echo Test
/**-----------------------------------------------------------------------------
 * @name Echo Test
 * -----------------------------------------------------------------------------
 */

/** Launches an audio call test to determine whether the audio devices (for example, headset and speaker) and the network connection are working properly.

 In the test, the user first speaks, and the recording is played back in 10 seconds. If the user can hear the recording in 10 seconds, it indicates that the audio devices and network connection work properly.

 @note  After calling this method, always call stopEchoTest to end the test, otherwise the application will not be able to run the next echo test, nor can it call the `joinChannelByToken` method to start a new call.

 @param successBlock Callback on successfully starting the echo test. See JoinSuccessBlock in `joinChannelByToken` for a description of the callback parameters.

 @return * 0: Success.
* <0: Failure.
 For example, AgoraErrorCodeRefused(-5)：Failed to launch the echo test.
 */
- (int)startEchoTest:(void(^ _Nullable)(NSString * _Nonnull channel, NSUInteger uid, NSInteger elapsed))successBlock NS_SWIFT_NAME(startEchoTest(_:));

/** Starts an audio call test.

  This method starts an audio call test to determine whether the audio devices (for example, headset and speaker) and the network connection are working properly.
  In the audio call test, you record your voice. If the recording plays back within the set time interval, the audio devices and the network connection are working properly.

  @note
  - Call this method before joining a channel.
  - After calling this method, call the stopEchoTest method to end the test. Otherwise, the app cannot run the next echo test, or join a channel.
  - In the live interactive streaming profile, only a host can call this method.

  @param interval The time interval (s) between when you speak and when the recording plays back.
  @param successBlock The SDK triggers the `successBlock` callback if this method call is successful.

  @return * 0: Success.
  * < 0: Failure.
*/
- (int)startEchoTestWithInterval:(NSInteger)interval
                  successBlock:(void(^ _Nullable)(NSString * _Nonnull channel, NSUInteger uid, NSInteger elapsed))successBlock NS_SWIFT_NAME(startEchoTest(withInterval:successBlock:));

#pragma mark Dual Video Mode
/**
 * Sets the remote video stream type.
 *
 * If the remote user has enabled the dual-stream mode, by default the SDK
 * receives the high-stream video. Call this method to switch to the low-stream
 * video.
 *
 * @note
 * This method applies to scenarios where the remote user has enabled the
 * dual-stream mode by \ref enableDualStreamMode: enableDualStreamMode
 * before joining the channel.
 *
 * @param uid ID of the remote user sending the video stream.
 * @param streamType The video stream type: #AgoraVideoStreamType.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)setRemoteVideoStream:(NSUInteger)uid
                       type:(AgoraVideoStreamType)streamType NS_SWIFT_NAME(setRemoteVideoStream(_:type:));

/**
   * Sets the remote video subscription options
   *
   *
   * @param uid ID of the remote user sending the video stream.
   * @param options Sets the video subscription options.
   * @return
   * - 0: Success.
   * - < 0: Failure.
   */
- (int)setRemoteVideoSubscriptionOptions:(NSUInteger)uid
                                 options:(AgoraVideoSubscriptionOptions* _Nonnull)options NS_SWIFT_NAME(setRemoteVideoSubscriptionOptions(_:options:));

#pragma mark Subscribe Blocklist / Allowlist

/**
 * Sets the blocklist of subscribe remote stream audio.
 *
 * @param blocklist The uid list of users who do not subscribe to audio.
 *
 * @note
 * If uid is in blacklist, the remote user's audio will not be subscribed,
 * even if muteRemoteAudioStream(uid, false) and muteAllRemoteAudioStreams(false) are operated.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)setSubscribeAudioBlocklist:(NSArray <NSNumber *> *_Nonnull)blocklist NS_SWIFT_NAME(setSubscribeAudioBlocklist(_:));

/**
 * Sets the allowlist of subscribe remote stream audio.
 *
 * @param allowlist The uid list of users who do subscribe to audio.
 *
 * @note
 * If uid is in allowlist, the remote user's audio will be subscribed,
 * even if muteRemoteAudioStream(uid, true) and muteAllRemoteAudioStreams(true) are operated.
 *
 * If a user is in the blocklist and allowlist at the same time, the user will not subscribe to audio.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)setSubscribeAudioAllowlist:(NSArray <NSNumber *> *_Nonnull)allowlist NS_SWIFT_NAME(setSubscribeAudioAllowlist(_:));

/**
 * Sets the blocklist of subscribe remote stream video.
 *
 * @param blocklist The uid list of users who do not subscribe to video.
 *
 * @note
 * If uid is in blocklist, the remote user's video will not be subscribed,
 * even if muteRemoteVideoStream(uid, false) and muteAllRemoteVideoStreams(false) are operated.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)setSubscribeVideoBlocklist:(NSArray <NSNumber *> *_Nonnull)blocklist NS_SWIFT_NAME(setSubscribeVideoBlocklist(_:));

/**
 * Sets the allowlist of subscribe remote stream video.
 *
 * @param allowlist The uid list of users who do subscribe to video.
 *
 * @note
 * If uid is in allowlist, the remote user's video will be subscribed,
 * even if muteRemoteVideoStream(uid, true) and muteAllRemoteVideoStreams(true) are operated.
 *
 * If a user is in the blocklist and allowlist at the same time, the user will not subscribe to video.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)setSubscribeVideoAllowlist:(NSArray <NSNumber *> *_Nonnull)allowlist NS_SWIFT_NAME(setSubscribeVideoAllowlist(_:));

#pragma mark Stream Fallback

/** Sets high priority user list and related remote subscribe stream fallback option.

  This method sets the high priority user list and disables/enables the vips' remote subscribe stream fallback option according to the network conditions in NASA2.

 If you use the option as AgoraStreamFallbackOptionAudioOnly = 2, the AutVos will automatically switch the video from a high-stream to a low-stream, or disable the video when the downlink network conditions cannot support both audio and video to guarantee the quality of the audio. The AutVos monitors the network quality and re-enables the video stream when the network conditions improve.
 Once the subscribed stream falls back to audio only, or the audio stream switches back to the video stream, the [didRemoteSubscribeFallbackToAudioOnly]([AgoraRtcEngineDelegate  rtcEngine:didRemoteSubscribeFallbackToAudioOnly:byUid:]) callback will be triggered.

 @param option AgoraStreamFallbackOptions
 @return * 0: Success.
* <0: Failure.
 */
- (int)setHighPriorityUserList:(NSArray <NSNumber *> *_Nullable)uidList
                        option:(AgoraStreamFallbackOptions)option;

#pragma mark External Media Source

/**
 * Pushes the encoded external video frame to Agora SDK.
 *
 * @note
 * Ensure that you have configured encoded video source before calling this method.
 *
 * @param frame The encoded external video data, which must be the direct buffer.
 * @param info The encoded external video frame info: AgoraEncodedVideoFrameInfo.
 *
 * @return
 * - 0: Success, which means that the encoded external video frame is pushed successfully.
 * - < 0: Failure, which means that the encoded external video frame fails to be pushed.
 */
- (int)pushExternalEncodedVideoFrame:(NSData* _Nonnull)frame
                                info:(AgoraEncodedVideoFrameInfo * _Nonnull)info NS_SWIFT_NAME(pushExternalEncodedVideoFrame(_:info:));

/**
 * Pushes the encoded external video frame to specified connection in Agora SDK.
 *
 * @note
 * Ensure that you have configured encoded video source before calling this method.
 *
 * @param frame The encoded external video data, which must be the direct buffer.
 * @param info The encoded external video frame info: AgoraEncodedVideoFrameInfo.
 * @param videoTrackId The id of the video track.
 *
 * @return
 * - 0: Success, which means that the encoded external video frame is pushed successfully.
 * - < 0: Failure, which means that the encoded external video frame fails to be pushed.
 */
- (int)pushExternalEncodedVideoFrame:(NSData* _Nonnull)frame
                                  info:(AgoraEncodedVideoFrameInfo * _Nonnull)info
                            videoTrackId:(NSUInteger)videoTrackId NS_SWIFT_NAME(pushExternalEncodedVideoFrame(_:info:videoTrackId:));


#pragma mark Audio spectrum monitor   
/**
 * Registers an audio spectrum delegate.
 *
 * You need to register the following callbacks
 * according to your scenario:
 * - "onAudioSpectrumComputed": Occurs when the SDK receives the audio data and at set intervals.
 *
 * @param delegate AgoraAudioSpectrumDelegate
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)registerAudioSpectrumDelegate:(id<AgoraAudioSpectrumDelegate> _Nullable )delegate NS_SWIFT_NAME(registerAudioSpectrumDelegate(_:));

  /**
   * Releases the audio spectrum delegate.
   *
   * @param delegate AgoraAudioSpectrumDelegate
   * @return
   * - 0: Success.
   * - < 0: Failure.
   */
- (int)unregisterAudioSpectrumDelegate:(id<AgoraAudioSpectrumDelegate> _Nullable)delegate NS_SWIFT_NAME(unregisterAudioSpectrumDelegate(_:));

#pragma mark Stream Publish

/**
 * New publish stream interface, just publish mix stream
 * @param url  The CDN streaming URL in the RTMP format. The maximum length of this parameter is 1024 bytes. The RTMP URL address must not contain special characters, such as Chinese language characters.
 * @param transcoding Sets the CDN live audio/video transcoding settings. See AgoraLiveTranscoding.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *   - #ERR_INVALID_ARGUMENT (2): The RTMP URL address is NULL or has a string length of 0.
 *   - #ERR_NOT_INITIALIZED (7): You have not initialized the RTC engine when publishing the stream.
 *   - #ERR_ALREADY_IN_USE (19): This streaming URL is already in use. Use a new streaming URL for CDN streaming.
 */
- (int)startRtmpStreamWithTranscoding:(NSString* _Nonnull)url transcoding:(AgoraLiveTranscoding* _Nullable)transcoding NS_SWIFT_NAME(startRtmpStream(withTranscoding:transcoding:));

/** Sets the video layout and audio settings for CDN live. (CDN live only.)

 The SDK triggers the [rtcEngineTranscodingUpdated]([AgoraRtcEngineDelegate rtcEngineTranscodingUpdated:]) callback when you call the `setLiveTranscoding` method to update the transcoding setting.

 **Note**

 - This method applies to live-broadcast profile only.
 - Ensure that you enable the RTMP Converter service before using this function. See [Prerequisites](https://docs.agora.io/en/Interactive%20Broadcast/cdn_streaming_apple?platform=iOS#prerequisites).
 - If you call the `setLiveTranscoding` method to update the transcoding setting for the first time, the SDK does not trigger the `rtcEngineTranscodingUpdated` callback.


 @param transcoding Sets the CDN live audio/video transcoding settings. See AgoraLiveTranscoding.

 @return = 0: Success.
 *       < 0: Failure.
 */
- (int)updateRtmpTranscoding:(AgoraLiveTranscoding* _Nullable)transcoding NS_SWIFT_NAME(updateRtmpTranscoding(_:));


#pragma mark String UID
/** Registers a user account.
 *
 * Once registered, the user account can be used to identify the local user when the user joins the channel.
 * After the user successfully registers a user account, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onLocalUserRegistered "onLocalUserRegistered" callback on the local client,
 * reporting the user ID and user account of the local user.
 *
 * To join a channel with a user account, you can choose either of the following:
 *
 * Call the [registerLocalUserAccount]([AgoraRtcEngineKit registerLocalUserAccount:appId:]) method to create a user account, and then the [joinChannelByUserAccount]([AgoraRtcEngineKit joinChannelByUserAccount:token:channelId:joinSuccess:]) method to join the channel.
 * Call the [joinChannelByUserAccount]([AgoraRtcEngineKit joinChannelByUserAccount:token:channelId:joinSuccess:]) method to join the channel.

 *
 * The difference between the two is that for the former, the time elapsed between calling the \ref agora::rtc::IRtcEngine::joinChannelWithUserAccount "joinChannelWithUserAccount" method
 * and joining the channel is shorter than the latter.
 *
 * @note
 * - Ensure that you set the `userAccount` parameter. Otherwise, this method does not take effect.
 * - Ensure that the value of the `userAccount` parameter is unique in the channel.
 * - To ensure smooth communication, use the same parameter type to identify the user. For example, if a user joins the channel with a user ID, then ensure all the other users use the user ID too. The same applies to the user account. If a user joins the channel with the Agora Web SDK, ensure that the uid of the user is set to the same parameter type.
 *
 * @param userAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that you set this parameter and do not set it as null. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param appId The App ID of your project.

 * @return
 * - 0: Success.
 * - < 0: Failure.
     */
- (int)registerLocalUserAccount:(NSString* _Nonnull)userAccount appId:(NSString* _Nonnull)appId  NS_SWIFT_NAME(registerLocalUserAccount(_:appId:));

/** Joins the channel with a user account.
 *
 * After the user successfully joins the channel, the SDK triggers the following callbacks:
 *
 * - The local client: \ref agora::rtc::IRtcEngineEventHandler::onLocalUserRegistered "onLocalUserRegistered" and \ref agora::rtc::IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess" .
 * The remote client: \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" and \ref agora::rtc::IRtcEngineEventHandler::onUserInfoUpdated "onUserInfoUpdated" , if the user joining the channel is in the `COMMUNICATION` profile, or is a host in the `LIVE_BROADCASTING` profile.
 *
 * @note To ensure smooth communication, use the same parameter type to identify the user. For example, if a user joins the channel with a user ID, then ensure all the other users use the user ID too. The same applies to the user account.
 * If a user joins the channel with the Agora Web SDK, ensure that the uid of the user is set to the same parameter type.
 *
 * @param token The token generated at your server:
 * - For low-security requirements: You can use the temporary token generated at Console. For details, see [Get a temporary toke](https://docs.agora.io/en/Voice/token?platform=All%20Platforms#get-a-temporary-token).
 * - For high-security requirements: Set it as the token generated at your server. For details, see [Get a token](https://docs.agora.io/en/Voice/token?platform=All%20Platforms#get-a-token).
 * @param channelId The channel name. The maximum length of this parameter is 64 bytes. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param userAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that you set this parameter and do not set it as null. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param joinSuccessBlock callback block
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *  - #ERR_INVALID_ARGUMENT (-2)
 *  - #ERR_NOT_READY (-3)
 *  - #ERR_REFUSED (-5)
 */
- (int)joinChannelByToken:(NSString * _Nullable)token
                channelId:(NSString * _Nonnull)channelId
              userAccount:(NSString * _Nonnull)userAccount
              joinSuccess:(void(^ _Nullable)(NSString * _Nonnull channel, NSUInteger uid, NSInteger elapsed))joinSuccessBlock NS_SWIFT_NAME(joinChannel(byToken:channelId:userAccount:joinSuccess:));

/** Joins the channel with a user account.
 *
 * After the user successfully joins the channel, the SDK triggers the following callbacks:
 *
 * - The local client: \ref agora::rtc::IRtcEngineEventHandler::onLocalUserRegistered "onLocalUserRegistered" and \ref agora::rtc::IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess" .
 * The remote client: \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" and \ref agora::rtc::IRtcEngineEventHandler::onUserInfoUpdated "onUserInfoUpdated" , if the user joining the channel is in the `COMMUNICATION` profile, or is a host in the `LIVE_BROADCASTING` profile.
 *
 * @note To ensure smooth communication, use the same parameter type to identify the user. For example, if a user joins the channel with a user ID, then ensure all the other users use the user ID too. The same applies to the user account.
 * If a user joins the channel with the Agora Web SDK, ensure that the uid of the user is set to the same parameter type.
 *
 * @param token The token generated at your server:
 * - For low-security requirements: You can use the temporary token generated at Console. For details, see [Get a temporary toke](https://docs.agora.io/en/Voice/token?platform=All%20Platforms#get-a-temporary-token).
 * - For high-security requirements: Set it as the token generated at your server. For details, see [Get a token](https://docs.agora.io/en/Voice/token?platform=All%20Platforms#get-a-token).
 * @param channelId The channel name. The maximum length of this parameter is 64 bytes. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param userAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that you set this parameter and do not set it as null. Supported character scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param mediaOptions  The channel media options: \ref agora::rtc::ChannelMediaOptions::ChannelMediaOptions "ChannelMediaOptions"
 * @param joinSuccessBlock callback block
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 *  - #ERR_INVALID_ARGUMENT (-2)
 *  - #ERR_NOT_READY (-3)
 *  - #ERR_REFUSED (-5)
 */
- (int)joinChannelByToken:(NSString * _Nullable)token
                channelId:(NSString * _Nonnull)channelId
              userAccount:(NSString * _Nonnull)userAccount
             mediaOptions:(AgoraRtcChannelMediaOptions * _Nonnull)mediaOptions
              joinSuccess:(void(^ _Nullable)(NSString * _Nonnull channel, NSUInteger uid, NSInteger elapsed))joinSuccessBlock NS_SWIFT_NAME(joinChannel(byToken:channelId:userAccount:mediaOptions:joinSuccess:));

/** Gets the user information by passing in the user account.

 * After a remote user joins the channel, the SDK gets the user ID and user account of the remote user, caches them in a mapping table object (`AgoraUserInfo`), and triggers the [didUpdatedUserInfo]([AgoraRtcEngineDelegate rtcEngine:didUpdatedUserInfo:withUid:]) callback on the local client.

 * After receiving the [didUpdatedUserInfo]([AgoraRtcEngineDelegate rtcEngine:didUpdatedUserInfo:withUid:]) callback, you can call this method to get the user ID of the remote user from the `userInfo` object by passing in the user account.

 * @param userAccount The user account of the user. Ensure that you set this parameter.
 * @param error The pointer to [AgoraErrorCode](AgoraErrorCode). It can be set as nil.
 * @return An [AgoraUserInfo](AgoraUserInfo) object that contains the user account and user ID of the user.
 */
- (AgoraUserInfo* _Nullable)getUserInfoByUserAccount:(NSString* _Nonnull)userAccount withError:(AgoraErrorCode* _Nullable)error NS_SWIFT_NAME(getUserInfo(byUserAccount:withError:));

/** Gets the user information by passing in the user ID.

 * After a user joins the channel, the SDK gets the user ID and user account of the remote user, caches them in a mapping table object (`AgoraUserInfo`), and triggers the [didUpdatedUserInfo]([AgoraRtcEngineDelegate rtcEngine:didUpdatedUserInfo:withUid:]) callback on the local client.

 * After receiving the [didUpdatedUserInfo]([AgoraRtcEngineDelegate rtcEngine:didUpdatedUserInfo:withUid:]) callback, you can call this method to get the user account of the user from the `userInfo` object by passing in the user ID.

 * @param uid The user ID of the user. Ensure that you set this parameter.
 * @param error The pointer to [AgoraErrorCode](AgoraErrorCode). It can be set as nil.
 * @return An [AgoraUserInfo](AgoraUserInfo) object that contains the user account and user ID of the user.
 */
- (AgoraUserInfo* _Nullable)getUserInfoByUid:(NSUInteger)uid withError:(AgoraErrorCode* _Nullable)error NS_SWIFT_NAME(getUserInfo(byUid:withError:));

#pragma mark Custom Audio PCM Frame
/**
  * @brief register & unregister the player audio observer
  *
  * @param delegate observer object, pass nil to unregister
  * @return int <= 0 On behalf of an error, the value corresponds to one of PLAYER_ERROR
  */
- (BOOL)setAudioFrameDelegate:(id<AgoraAudioFrameDelegate> _Nullable)delegate NS_SWIFT_NAME(setAudioFrameDelegate(_:));

#pragma mark Custom Video Frame
/**
 * Registers & unregister video frame observer object.
 *
 * @note
 * - Ensure that you call this method before joining the channel.
 *
 * @param delegate An object to the video frame observer: id<AgoraVideoFrameDelegate>.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (BOOL)setVideoFrameDelegate:(id<AgoraVideoFrameDelegate> _Nullable)delegate NS_SWIFT_NAME(setVideoFrameDelegate(_:));

#pragma mark Encoded Video Frame
/**
 * Obtain H264 video data before decoding.
 *
 * @note
 * - Ensure that you call this method before joining the channel.
 *
 * @param delegate An object to the video frame observer: id<AgoraEncodedVideoFrameDelegate>.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (BOOL)setEncodedVideoFrameDelegate:(id<AgoraEncodedVideoFrameDelegate> _Nullable)delegate NS_SWIFT_NAME(setEncodedVideoFrameDelegate(_:));

#pragma mark Custom Media Metadata
/** Sets the delegate of the metadata.

 You need to implement the AgoraMediaMetadataDelegate protocol and specify the type of metadata in this method.

 **Note**

 - Call this method before the `joinChannelByToken` method.
 - This method applies to the live interactive streaming channel profile only.

 @param metadataDelegate The AgoraMediaMetadataDelegate protocol.
 @param type The metadata type. See \ref AgoraMetadataType. Currently, the SDK supports video metadata only.
 @return
 - YES: Success.
 - NO: Failure.
 */
- (BOOL)setMediaMetadataDelegate:(id<AgoraMediaMetadataDelegate> _Nullable)metadataDelegate withType:(AgoraMetadataType)type NS_SWIFT_NAME(setMediaMetadataDelegate(_:with:));

#pragma mark Channel Transcoder

/** Get the H265Transcoder instance
 * @return id<AgoraH265TranscoderProtocol>
 * 
*/
- (id<AgoraH265TranscoderProtocol>_Nullable)getH265Transcoder NS_SWIFT_NAME (getH265Transcoder());

- (NSInteger)takeSnapshot:(NSInteger)uid filePath:(NSString* _Nonnull)filePath NS_SWIFT_NAME(takeSnapshot(_:filePath:));

/** Bind local user and a remote user as an audio&video sync group. The remote user is defined by cid and uid.
  There’s a usage limit that local user must be a video stream sender. On the receiver side, media streams from same sync group will be time-synced

 @param channelId The channel id
 @param uid The user ID of the remote user to be bound with (local user)

 @return
 - 0: Success.
 - < 0: Failure.
 */
- (int)setAVSyncSource:(NSString* _Nonnull)channelId uid:(NSUInteger)uid NS_SWIFT_NAME(setAVSyncSource(_:uid:));

/**
 * Creates a media recorder object and return its pointer.
 *
 * @param info The AgoraRecorderStreamInfo object. It contains the user ID and the channel name.
 * @return
 * - The pointer to \ref "AgoraMediaRecorder",
 *   if the method call succeeds.
 * - The empty pointer NULL, if the method call fails.
 */
- (AgoraMediaRecorder * _Nullable)createMediaRecorder:(AgoraRecorderStreamInfo * _Nonnull)info NS_SWIFT_NAME(createMediaRecorder(withInfo:));

/**
 * Destroy a media recorder source instance.
 *
 * @param mediaRecorder AgoraMediaRecorder pointer
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)destroyMediaRecorder:(AgoraMediaRecorder * _Nullable)mediaRecorder;

@optional
#pragma mark Deprecated Methods

/**
 * @deprecated
 * To set whether to receive remote audio streams by default, call \ref muteAllRemoteAudioStreams: muteAllRemoteAudioStreams before calling `joinChannelByToken`.
 *
 * Determines whether to receive all remote audio streams by default.
 *
 * @param mute Whether to receive remote audio streams by default:
 * - `YES`: Do not receive any remote audio stream by default.
 * - `NO`: (Default) Receive remote audio streams by default.
 *
 * @return
 * - 0: Success.
 * - <0: Failure.
 */
- (int)setDefaultMuteAllRemoteAudioStreams:(BOOL)mute NS_SWIFT_NAME(setDefaultMuteAllRemoteAudioStreams(_:)) __deprecated;

/**
 * @deprecated
 * To set whether to receive remote audio streams by default, call \ref muteAllRemoteAudioStreams: muteAllRemoteAudioStreams before calling `joinChannelByToken`.
 *
 * Determines whether to receive all remote audio streams by default.
 *
 * @param mute Whether to receive remote audio streams by default:
 * - `YES`: Do not receive any remote audio stream by default.
 * - `NO`: (Default) Receive remote audio streams by default.
 *
 * @return
 * - 0: Success.
 * - <0: Failure.
 */
- (int)setDefaultMuteAllRemoteAudioStreams:(BOOL)mute NS_SWIFT_NAME(setDefaultMuteAllRemoteAudioStreams(_:)) __deprecated;

/**
 * @deprecated
 * To set whether to receive remote video streams by default, call \ref muteAllRemoteVideoStreams: muteAllRemoteVideoStreams before calling `joinChannelByToken`.
 *
 * Determines whether to receive all remote video streams by default.
 *
 * @param mute Whether to receive remote video streams by default:
 * - `YES`: Do not receive any remote video stream by default.
 * - `NO`: (Default) Receive remote video streams by default.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)setDefaultMuteAllRemoteVideoStreams:(BOOL)mute NS_SWIFT_NAME(setDefaultMuteAllRemoteVideoStreams(_:)) __deprecated;

/**
 * @deprecated
 */
- (int)setLocalVideoMirrorMode:(AgoraVideoMirrorMode)mode NS_SWIFT_NAME(setLocalVideoMirrorMode(_:)) __deprecated;

/**
 * @deprecated Web SDK interoperability is by default enabled.
 *
 * @param enabled Whether interoperability with the Agora Web SDK is enabled:
 * - YES: Enabled.
 * - NO: Disabled.
 * @return
 * - 0: Success.
 * - <0: Failure.
 */
- (int)enableWebSdkInteroperability:(BOOL)enabled NS_SWIFT_NAME(enableWebSdkInteroperability(_:)) __deprecated;

/** The user who is talking and the speaker’s volume.
 @deprecated From v1.1

 By default it is disabled. If needed, use the [enableAudioVolumeIndication]([AgoraRtcEngineKit enableAudioVolumeIndication:smooth:]) method to configure it.

 @param audioVolumeIndicationBlock callback block, which contains the following
    speakers The speakers (array). Each speaker ():
     - uid: User ID of the speaker.
     - volume：Volume of the speaker, between 0 (lowest volume) to 255 (highest volume).
    totalVolume Total volume after audio mixing between 0 (lowest volume) to 255 (highest volume).
 */
- (void)audioVolumeIndicationBlock:(void(^ _Nullable)(NSArray * _Nonnull speakers, NSInteger totalVolume))audioVolumeIndicationBlock NS_SWIFT_NAME(audioVolumeIndicationBlock(_:)) __deprecated_msg("use delegate instead.");

/** The first local video frame is displayed on the screen.
 @deprecated From v1.1

 @param firstLocalVideoFrameBlock callback block, which contains the following
  width   Width (pixels) of the video stream.
  height  Height (pixels) of the video stream.
  elapsed Time elapsed (ms) from a user joining the channel until this callback is triggered.
 */
- (void)firstLocalVideoFrameBlock:(void(^ _Nullable)(NSInteger width, NSInteger height, NSInteger elapsed))firstLocalVideoFrameBlock NS_SWIFT_NAME(firstLocalVideoFrameBlock(_:)) __deprecated_msg("use delegate instead.");

/** Occurs when the first remote video frame is received and decoded.

 @deprecated This callback is deprecated.

 @param firstRemoteVideoDecodedBlock callback block, which contains the following
  uid     User ID of the user whose video streams are received.
  width   Width (pixels) of the video stream.
  height  Height (pixels) of the video stream.
  elapsed Time elapsed (ms) from the user joining the channel until this callback is triggered.
 */
- (void)firstRemoteVideoDecodedBlock:(void(^ _Nullable)(NSUInteger uid, NSInteger width, NSInteger height, NSInteger elapsed))firstRemoteVideoDecodedBlock NS_SWIFT_NAME(firstRemoteVideoDecodedBlock(_:)) __deprecated_msg("use delegate instead.");

/** The first remote video frame is received and decoded.
 @deprecated From v1.1

 @param firstRemoteVideoFrameBlock callback block, which contains the following
  uid     User ID of the user whose video streams are received.
  width   Width (pixels) of the video stream.
  height  Height (pixels) of the video stream.
  elapsed Time elapsed (ms) from the user joining the channel until this callback is triggered.
 */
- (void)firstRemoteVideoFrameBlock:(void(^ _Nullable)(NSUInteger uid, NSInteger width, NSInteger height, NSInteger elapsed))firstRemoteVideoFrameBlock NS_SWIFT_NAME(firstRemoteVideoFrameBlock(_:)) __deprecated_msg("use delegate instead.");

/** A user has successfully joined the channel.
 @deprecated From v1.1

 If there are other users in the channel when this user joins, the SDK also reports to the application on the existing users who are already in the channel.

 @param userJoinedBlock callback block, which contains the following:
   uid     User ID. If the uid is specified in the `joinChannelByToken` method, it returns the specified ID; if not, it returns an ID that is automatically assigned by the Agora server.
   elapsed Time elapsed (ms) from calling joinChannelByToken until this callback is triggered.
 */
- (void)userJoinedBlock:(void(^ _Nullable)(NSUInteger uid, NSInteger elapsed))userJoinedBlock NS_SWIFT_NAME(userJoinedBlock(_:)) __deprecated_msg("use delegate instead.");

/** A user has left the call or gone offline.
 @deprecated From v1.1

 The SDK reads the timeout data to determine if a user has left the channel (or has gone offline). If no data package is received from the user in 15 seconds, the SDK assumes the user is offline. Sometimes a weak network connection may lead to false detections; therefore, Agora recommends using signaling for reliable offline detection.

 @param userOfflineBlock callback block, which contains the following:
  uid User ID.
 */
- (void)userOfflineBlock:(void(^ _Nullable)(NSUInteger uid))userOfflineBlock NS_SWIFT_NAME(userOfflineBlock(_:)) __deprecated_msg("use delegate instead.");

/** A user's audio stream has muted/unmuted.
 @deprecated From v1.1

 @param userMuteAudioBlock callback block, which contains the following:
   uid   User ID.
   muted
     - YES: Muted.
     - NO: Unmuted.
*/
- (void)userMuteAudioBlock:(void(^ _Nullable)(NSUInteger uid, BOOL muted))userMuteAudioBlock NS_SWIFT_NAME(userMuteAudioBlock(_:)) __deprecated_msg("use delegate instead.");

/** Occurs when a remote user pauses or resumes sending the video stream.

  @deprecated This callback is deprecated. Use [remoteVideoStateChangedOfUid](remoteVideoStateChangedOfUid:state:reason:elapsed:)
   instead.

  @note This callback is invalid when the number of users or broadacasters in a
  channel exceeds 20.

 @param userMuteVideoBlock callback block, which contains the following:
   userId ID of the remote user.
   muted
  - YES: The remote user has paused sending the video stream.
  - NO: The remote user has resumed sending the video stream.
 */
- (void)userMuteVideoBlock:(void(^ _Nullable)(NSUInteger uid, BOOL muted))userMuteVideoBlock NS_SWIFT_NAME(userMuteVideoBlock(_:)) __deprecated_msg("use delegate instead.");

/** The SDK updates the application about the statistics of the uploading local video streams once every two seconds.
 @deprecated From v1.1

 @param localVideoStatBlock callback block, which contains the following:
  sentBytes  Total bytes sent since last count.
  sentFrames Total frames sent since last count.
 */
- (void)localVideoStatBlock:(void(^ _Nullable)(NSInteger sentBitrate, NSInteger sentFrameRate))localVideoStatBlock NS_SWIFT_NAME(localVideoStatBlock(_:)) __deprecated_msg("use delegate instead.");

/** The SDK updates the application about the statistics of receiving remote video streams once every two seconds.
 @deprecated From v1.1

 @param remoteVideoStatBlock callback block, which contains the following:
  uid           User ID that specifies whose video streams are received.
  rameCount     Total frames received since last count.
  delay         Time delay (ms)
  receivedBytes Total bytes received since last count.
  */
- (void)remoteVideoStatBlock:(void(^ _Nullable)(NSUInteger uid, NSInteger delay, NSInteger receivedBitrate, NSInteger receivedFrameRate))remoteVideoStatBlock NS_SWIFT_NAME(remoteVideoStatBlock(_:)) __deprecated_msg("use delegate instead.");

/** The camera is turned on and ready to capture the video.
 @deprecated From v1.1
 */
- (void)cameraReadyBlock:(void(^ _Nullable)(void))cameraReadyBlock NS_SWIFT_NAME(cameraReadyBlock(_:)) __deprecated_msg("use delegate instead.");

/** The SDK has lost network connection with the server.
 @deprecated From v1.1
 */
- (void)connectionLostBlock:(void(^ _Nullable)(void))connectionLostBlock NS_SWIFT_NAME(connectionLostBlock(_:)) __deprecated_msg("use delegate instead.");

/** A user has rejoined the channel with the reported channel ID and user ID.
 @deprecated From v1.1

 When the local machine loses connection with the server because of network problems, the SDK automatically attempts to reconnect, and then triggers this callback method upon reconnection.

 @param rejoinChannelSuccessBlock callback block, which contains the following:
  channel Channel name.
  uid     User ID.
  elapsed Time delay (ns) in rejoining the channel.
 */
- (void)rejoinChannelSuccessBlock:(void(^ _Nullable)(NSString * _Nonnull channel, NSUInteger uid, NSInteger elapsed))rejoinChannelSuccessBlock NS_SWIFT_NAME(rejoinChannelSuccessBlock(_:)) __deprecated_msg("use delegate instead.");

/** The RtcEngine runtime statistics reported once every two seconds.
 @deprecated From v1.1

 @param rtcStatsBlock callback block, which contains the following:
  stat AgoraChannelStats
 */
- (void)rtcStatsBlock:(void(^ _Nullable)(AgoraChannelStats * _Nonnull stat))rtcStatsBlock NS_SWIFT_NAME(rtcStatsBlock(_:)) __deprecated_msg("use delegate instead.");

/** The audio quality of the current call reported once every two seconds.
 @deprecated From v1.1

 @param audioQualityBlock callback block, which contains the following:
  uid     User ID of the speaker
  quality AgoraNetworkQuality
  delay   Time delay (ms)
  lost    The packet loss rate (%)
 */
- (void)audioQualityBlock:(void(^ _Nullable)(NSUInteger uid, AgoraNetworkQuality quality, NSUInteger delay, NSUInteger lost))audioQualityBlock NS_SWIFT_NAME(audioQualityBlock(_:)) __deprecated_msg("use delegate instead.");

/** The network quality of the specified user in a communication or live broadcast channel reported once every two seconds.
 @deprecated From v1.1

 @param networkQualityBlock callback block, which contains the following:
  uid       User ID. The network quality of the user with this UID will be reported. If uid is 0, the local network quality is reported.
  txQuality The transmission quality of the user: AgoraNetworkQuality
  rxQuality The receiving quality of the user: AgoraNetworkQuality
 */
- (void)networkQualityBlock:(void(^ _Nullable)(NSUInteger uid, AgoraNetworkQuality txQuality, AgoraNetworkQuality rxQuality))networkQualityBlock NS_SWIFT_NAME(networkQualityBlock(_:)) __deprecated_msg("use delegate instead.");

/** The network quality of the local user reported once after you have called [startLastmileProbeTest]([AgoraRtcEngineKit startLastmileProbeTest]).
 @deprecated From v1.1

 @param lastmileQualityBlock callback block, which contains the following:
  quality Quality of the last mile network: AgoraNetworkQuality
 */
- (void)lastmileQualityBlock:(void(^ _Nullable)(AgoraNetworkQuality quality))lastmileQualityBlock NS_SWIFT_NAME(lastmileQualityBlock(_:)) __deprecated_msg("use delegate instead.");

/** The media engine event.
 @deprecated From v1.1.
 */
- (void)mediaEngineEventBlock:(void(^ _Nullable)(NSInteger code))mediaEngineEventBlock NS_SWIFT_NAME(mediaEngineEventBlock(_:)) __deprecated_msg("use delegate instead.");

/** Disables the audio function in the channel.

 Replaced with the disableAudio method from v2.3.

 @deprecated  Replaced with the disableAudio method from v2.3.

 @return * 0: Success.
* <0: Failure.
 */
- (int)pauseAudio __deprecated_msg("use disableAudio instead.");

/** Enables the audio function in the channel.

 Replaced with the enableAudio method from v2.3.

 @deprecated Replaced with the enableAudio method from v2.3.

 @return * 0: Success.
* <0: Failure.
 */
- (int)resumeAudio __deprecated_msg("use enableAudio instead.");

/** Initializes the The AgoraRtcEngineKit object.

 Replaced with [sharedEngineWithAppId]([AgoraRtcEngineKit sharedEngineWithAppId:delegate:]).

 @deprecated  Replaced with sharedEngineWithAppId.
 */
+ (instancetype _Nonnull)sharedEngineWithAppId:(NSString * _Nonnull)AppId
                                         error:(void(^ _Nullable)(AgoraErrorCode errorCode))errorBlock NS_SWIFT_NAME(sharedEngine(withAppId:error:)) __deprecated_msg("use sharedEngineWithAppId:delegate: instead.");

/** Sets the high-quality audio parameters.
 @deprecated

 Replaced with [setAudioProfile](setAudioProfile:scenario:).
 */
- (int)setHighQualityAudioParametersWithFullband:(BOOL)fullband
                                          stereo:(BOOL)stereo
                                     fullBitrate:(BOOL)fullBitrate NS_SWIFT_NAME(setHighQualityAudioParametersWithFullband(_:stereo:fullBitrate:)) __deprecated_msg("use setAudioProfile:scenario: instead.");

/** Sets the video encoding profile.
 @deprecated From v2.3

 Each profile includes a set of parameters, such as the resolution, frame rate, and bitrate. When the camera does not support the specified resolution, the SDK chooses a suitable camera resolution, while the encoder resolution is the one specified by [setVideoProfile](setVideoProfile:swapWidthAndHeight:).

 @note * Always set the video profile after calling the enableVideo method.
 * Always set the video profile before calling the `joinChannelByToken` or startPreview method.

 @param profile            Enumeration definition about the video resolution, fps, and maximum kbit/s. See AgoraVideoProfile.
 @param swapWidthAndHeight The width and height of the output video is consistent with that of the video profile you set. This parameter sets whether to swap the width and height of the stream:

 * YES: Swap the width and height. After that the video will be in the portrait mode, that is, width < height.
 * NO: (Default) Do not swap the width and height, and the video remains in the landscape mode, that is, width > height.

 @return * 0: Success.
* <0: Failure.
 */
- (int)setVideoProfile:(AgoraVideoProfile)profile
    swapWidthAndHeight:(BOOL)swapWidthAndHeight NS_SWIFT_NAME(setVideoProfile(_:swapWidthAndHeight:)) __deprecated_msg("use setVideoEncoderConfiguration: instead.");

/**
 * Sets the audio parameters and application scenarios.
 * @deprecated This method is deprecated. You can use the
 * \ref AgoraRtcEngineKit.setAudioProfile: setAudioProfile
 * method instead.
 *
 * @note
 * - Call this method before calling `joinChannelByToken`.
 * - In scenarios requiring high-quality audio, we recommend setting `profile`
 * as `AgoraAudioProfileMusicHighQuality`(4) and `scenario` as
 * `AgoraAudioScenarioGameStreaming`(3).
 * @param profile  Sets the sample rate, bitrate, encoding mode, and the number of channels. See #AgoraAudioProfile.
 * @param scenario Sets the audio application scenarios. See #AgoraAudioScenario.
 *
 * @return
 * - 0: Success.
 * - <0: Failure.
 */
- (int)setAudioProfile:(AgoraAudioProfile)profile scenario:(AgoraAudioScenario)scenario NS_SWIFT_NAME(setAudioProfile(_:scenario:)) __deprecated_msg("use setAudioProfile: instead.");

/** Gets the device type; such as a recording, playback, or video capture device.
 @note  This method applies to macOS only, not to iOS.

 @param type AgoraMediaDeviceType
 @return When called successfully, it returns the device ID of the device. Otherwise, it returns nil.
 */
- (NSString * _Nullable)getDeviceId:(AgoraMediaDeviceType)type NS_SWIFT_NAME(getDeviceId(_:)) __deprecated_msg("use getDeviceInfo: instead.");

/**
 * Sets the external audio source.
 *
 * @note
 * Ensure that you call this method before joining the channel.
 *
 * @deprecated This method is deprecated. Use createCustomAudioTrack:(AgoraAudioTrackType)trackType config:(AgoraAudioTrackConfig* _Nonnull)config instead.
 *
 * @param enabled Determines whether to enable the external audio source:
 * - true: Enable the external audio source.
 * - false: (default) Disable the external audio source.
 * @param sampleRate The Sample rate (Hz) of the external audio source, which can set be as
 * 8000, 16000, 32000, 44100, or 48000.
 * @param channels The number of channels of the external audio source, which can be set as 1 or 2:
 * - 1: Mono.
 * - 2: Stereo.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)setExternalAudioSource:(BOOL)enabled
                   sampleRate:(NSInteger)sampleRate
                     channels:(NSInteger)channels NS_SWIFT_NAME(setExternalAudioSource(_:sampleRate:channels:)) __deprecated_msg("use createCustomAudioTrack:config: instead.");

/**
 * Sets the external audio source.
 *
 * @note
 * Ensure that you call this method before joining the channel.
 *
 * @deprecated This method is deprecated. Use createCustomAudioTrack:(AgoraAudioTrackType)trackType config:(AgoraAudioTrackConfig* _Nonnull)config instead.
 *
 * @param enabled Determines whether to enable the external audio source:
 * - true: Enable the external audio source.
 * - false: (default) Disable the external audio source.
 * @param sampleRate The Sample rate (Hz) of the external audio source, which can set be as
 * 8000, 16000, 32000, 44100, or 48000.
 * @param channels The number of channels of the external audio source, which can be set as 1 or 2:
 * - 1: Mono.
 * - 2: Stereo.
 * @param localPlayback Enable/Disables the local playback of external audio track:
 * - true: Enable local playback
 * - false: (Default) Do not enable local playback
 * @param publish Determines whether to publish the external audio track:
 * - true: (Default) Publish the external audio track.
 * - false: Don`t publish the external audio track.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)setExternalAudioSource:(BOOL)enabled
                   sampleRate:(NSInteger)sampleRate
                     channels:(NSInteger)channels
                localPlayback:(BOOL)localPlayback
                      publish:(BOOL)publish NS_SWIFT_NAME(setExternalAudioSource(_:sampleRate:channels:localPlayback:publish:)) __deprecated_msg("use createCustomAudioTrack:config: instead.");

#if (!(TARGET_OS_IPHONE) && (TARGET_OS_MAC))
/** Sets the speakerphone volume.

 @note  This method applies to macOS only, not to iOS.

 @param volume 0 (lowest volume) to 255 (highest volume).

 @return * 0: Success.
* <0: Failure.
 */
- (int)setSpeakerphoneVolume:(NSUInteger)volume NS_SWIFT_NAME(setSpeakerphoneVolume(_:)) __deprecated_msg("use setDeviceVolume:volume: instead.");

- (int)startScreenCapture:(NSUInteger)windowId
          withCaptureFreq:(NSInteger)captureFreq
                  bitRate:(NSInteger)bitRate
                  andRect:(CGRect)rect NS_SWIFT_NAME(startScreenCapture(_:withCaptureFreq:bitRate:andRect:)) __deprecated_msg("use startScreenCaptureByWindowId:regionRect:captureParams: instead.");
#endif

/** Returns the Media Engine version.
 @deprecated From v2.3

 @return string, Media engine version
 */
+ (NSString * _Nonnull)getMediaEngineVersion NS_SWIFT_NAME(getMediaEngineVersion()) __deprecated;

/** Sets the built-in encryption mode.
 @deprecated

 The Agora Native SDK supports built-in encryption. Call this API to set the encryption mode.
 All users in the same channel must use the same encryption mode and password. Refer to information related to the encryption algorithm on the differences between encryption modes.
 Call [setEncryptionSecret](setEncryptionSecret:) to enable the built-in encryption function before calling this API.

 @note  Do not use this function together with CDN.

 @param encryptionMode Sets the encryption mode.
 - "sm4-128-ecb": 128-bit SM4 encryption, ECB mode.

 @return * 0: Success.
* <0: Failure.
 */
- (int)setEncryptionMode:(NSString * _Nullable)encryptionMode NS_SWIFT_NAME(setEncryptionMode(_:)) __deprecated_msg("use enableEncryption: instead.");

/** Enables built-in encryption.
 @deprecated

 Use this method to specify an encryption password to enable built-in encryption before joining a channel.
 All users in a channel must set the same encryption password.
 The encryption password is automatically cleared once a user has left the channel.
 If the encryption password is not specified or set to empty, the encryption function will be disabled.

 @note  Do not use this function together with CDN.

 @param secret Encryption password
 @return * 0: Success.
* <0: Failure.
 */
- (int)setEncryptionSecret:(NSString * _Nullable)secret NS_SWIFT_NAME(setEncryptionSecret(_:)) __deprecated_msg("use enableEncryption: instead.");

/** Sets the video encoding profile manually.
 @deprecated From v2.3

 @param size      Size of the video that you want to set. The highest value is 1280 x 720.
 @param frameRate Frame rate of the video that you want to set. The highest value is 30. You can set it to 5, 10, 15, 24, 30, and so on.
 @param bitrate   Bitrate of the video that you want to set. You need to manually work out the frame rate according to the width, height, and frame rate. With the same width and height, the bitrate varies with the change of the frame rate:

 * If the frame rate is 5 fps, divide the recommended bitrate by 2.
 * If the frame rate is 15 fps, use the recommended bitrate.
 * If the frame rate is 30 fps, multiply the recommended bitrate by 1.5.
 * Calculate your bitrate with the ratio if you choose other frame rates.

 For example, the resolution is 320 x 240 and the frame rate is 15 fps, hence, the bitrate is 200:

 * If the frame rate is 5 fps, the bitrate is 100.
 * If the frame rate is 30 fps, the bitrate is 300.
 * If the bitrate you set is beyond the proper range, the SDK will automatically adjust it to a value within the range.
 */
- (int)setVideoResolution:(CGSize)size andFrameRate:(NSInteger)frameRate bitrate:(NSInteger)bitrate NS_SWIFT_NAME(setVideoResolution(_:andFrameRate:bitrate:)) __deprecated_msg("use setVideoEncoderConfiguration: instead.");

/** A user has left the channel.
 @deprecated From v1.1

 This callback also provides call session statistics, including the duration of the call and the transmitting and receiving bytes.

 @param leaveChannelBlock callback block, which contains the following:
  stat AgoraChannelStats
 */
- (void)leaveChannelBlock:(void(^ _Nullable)(AgoraChannelStats * _Nonnull stat))leaveChannelBlock NS_SWIFT_NAME(leaveChannelBlock(_:)) __deprecated_msg("use delegate instead.");

/**
 * @deprecated
 */
- (int)setLocalRenderMode:(NSUInteger)uid
                     mode:(AgoraVideoRenderMode)mode NS_SWIFT_NAME(setLocalRenderMode(_:mode:)) __deprecated;

/**
 * Enable or disable the external audio source local playback.
 *
 * * @param enable Determines whether to enable the external audio source local playback:
 * - true: Enable the external audio source local playback.
 * - false: (default) Disable the external audio source local playback.
 * @return int
 * -  0: Success.
 * - <0: Failure.
 */
- (int)enableExternalAudioSourceLocalPlayback:(BOOL)enable NS_SWIFT_NAME(enableExternalAudioSourceLocalPlayback(_:)) __deprecated;;

- (int)startMultipleVideoStreams:(VIEW_CLASS * _Nonnull)view screen:(VIEW_CLASS * _Nonnull)screenView remotes:(NSArray * _Nullable)remoteViews NS_SWIFT_NAME(startMultipleVideoStreams(_:screen:remotes:)) __deprecated;;

@end

__attribute__((visibility("default"))) @interface AgoraRtcEngineKit : NSObject<AgoraRtcEngineBaseProtocol, AgoraRtcEngineKitProtocol>
#pragma mark Core Methods

@property(nonatomic, weak) id<AgoraRtcEngineDelegate> _Nullable delegate;
@end