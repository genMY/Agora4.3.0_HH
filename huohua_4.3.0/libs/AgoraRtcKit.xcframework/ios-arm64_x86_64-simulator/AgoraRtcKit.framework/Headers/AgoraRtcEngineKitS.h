//
//  AgoraRtcEngineKit.h
//  AgoraRtcEngineKit
//
//  Copyright (c) 2018 Agora. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AgoraRtcEngineKitBase.h"
#import "AgoraConstants.h"
#import "AgoraObjectsS.h"

/** Agora provides ensured quality of experience (QoE) for worldwide Internet-based voice and video communications through a virtual global network that is especially optimized for real-time web and mobile-to-mobile applications.

 The AgoraRtcEngineKit class is the entry point of the Agora SDK that provides simple APIs for applications to easily start voice and video communication.
 */

@protocol AgoraRtcEngineDelegateS;
@protocol AgoraAudioFrameDelegateS;
@protocol AgoraAudioEncodedFrameDelegate;
@protocol AgoraAudioSpectrumDelegateS;
@protocol AgoraVideoFrameDelegateS;
@protocol AgoraEncodedVideoFrameDelegateS;
@protocol AgoraRtcMediaPlayerDelegate;
@protocol AgoraMediaRecorderDelegate;
@protocol AgoraMediaMetadataDelegateS;
@protocol AgoraMediaMetadataDataSource;
@protocol AgoraDirectCdnStreamingEventDelegate;
@protocol AgoraRtcMediaPlayerCacheManagerProtocol;
@protocol AgoraH265TranscoderProtocolS;

@class AgoraMediaRecorderS;

#pragma mark - AgoraRtcEngineKitS

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
@protocol AgoraRtcEngineKitProtocolS <NSObject>
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
@property(nonatomic, weak) id<AgoraRtcEngineDelegateS> _Nullable delegate;

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
- (int)preloadChannelByToken:(NSString * _Nullable)token
                   channelId:(NSString * _Nonnull)channelId
                 userAccount:(NSString * _Nonnull)userAccount NS_SWIFT_NAME(preloadChannel(byToken:channelId:userAccount:));

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
 * @param userAccount User ID. 
 * @param joinSuccessBlockS Same as \ref AgoraRtcEngineDelegate.rtcEngine:didJoinChannel:withUid:elapsed: didJoinChannel. We recommend you set this parameter as `nil` to use `didJoinChannel`.
 * - If `joinSuccessBlockS` is nil, the SDK triggers the `didJoinChannel` callback.
 * - If you implement both `joinSuccessBlock` and `didJoinChannel`, `joinSuccessBlockS` takes higher priority than `didJoinChannel`.
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
              userAccount:(NSString * _Nonnull)userAccount
              joinSuccess:(void(^ _Nullable)(NSString * _Nonnull channel, NSString * _Nonnull userAccount, NSInteger elapsed))joinSuccessBlockS NS_SWIFT_NAME(joinChannel(byToken:channelId:info:userAccount:joinSuccess:));

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
 * @param userAccount User ID. 
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
              userAccount:(NSString * _Nonnull)userAccount
             mediaOptions:(AgoraRtcChannelMediaOptions * _Nonnull)mediaOptions
              joinSuccess:(void(^ _Nullable)(NSString * _Nonnull channel, NSString * _Nonnull userAccount, NSInteger elapsed))joinSuccessBlock NS_SWIFT_NAME(joinChannel(byToken:channelId:userAccount:mediaOptions:joinSuccess:));

  /** Starts or update to relay media streams across channels.

  After a successful method call, the SDK triggers the [channelMediaRelayStateDidChange]([AgoraRtcEngineDelegate rtcEngine:channelMediaRelayStateDidChange:error:]) callback, and this callback return the state of the media stream relay.

  - If the `channelMediaRelayStateDidChange` callback returns AgoraChannelMediaRelayStateRunning(2) and AgoraChannelMediaRelayStateIdle(0), the SDK starts relaying media streams between the original and the destination channel.
  - If the `channelMediaRelayStateDidChange` callback returns AgoraChannelMediaRelayStateFailure(3), an exception occurs during the media stream relay.

  **Note**

  - Call this method after the [joinChannel]([AgoraRtcEngineKit joinChannelByToken:channelId:info:userAccount:joinSuccess:]) method.
  - This method takes effect only when you are a broadcaster in a Live-broadcast channel.
  - Contact sales-us@agora.io before implementing this function.
  - We do not support string user accounts in this API.

  @param config The configuration of the media stream relay: [AgoraChannelMediaRelayConfiguration](AgoraChannelMediaRelayConfiguration).

  @return - 0: Success.
  - < 0: Failure.
    - -1(ERR_FAILED): A general error occurs (no specified reason).
    - -2(ERR_INVALID_ARGUMENT): The argument is invalid.
    - -5(ERR_REFUSED): The request is rejected.
    - -8(ERR_INVALID_STATE): The current status is invalid, only allowed to be called when the role is the broadcaster.
  */
- (int)startOrUpdateChannelMediaRelay:(AgoraChannelMediaRelayConfiguration * _Nonnull)config NS_SWIFT_NAME(startOrUpdateChannelMediaRelay(_:));

- (int)startLocalVideoTranscoder:(AgoraLocalTranscoderConfigurationS* _Nonnull)config NS_SWIFT_NAME(startLocalVideoTranscoder(_:));

- (int)updateLocalTranscoderConfiguration:(AgoraLocalTranscoderConfigurationS* _Nonnull)config NS_SWIFT_NAME(updateLocalTranscoderConfiguration(_:));

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
                                      delegate:(id<AgoraRtcEngineDelegateS> _Nullable)delegate NS_SWIFT_NAME(sharedEngine(withAppId:delegate:));

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
                                       delegate:(id<AgoraRtcEngineDelegateS> _Nullable)delegate NS_SWIFT_NAME(sharedEngine(with:delegate:));

/** Adjust the playback signal volume of a specified remote user.

 You can call this method as many times as necessary to adjust the playback volume of different remote users, or to repeatedly adjust the playback volume of the same remote user.

 **Note**

 - Call this method after joining a channel.
 - The playback volume here refers to the mixed volume of a specified remote user.
 - This method can only adjust the playback volume of one specified remote user at a time. To adjust the playback volume of different remote users, call the method as many times, once for each remote user.

 @param userAccount The ID of the remote user.
 @param volume The playback volume of the specified remote user. The value ranges from 0 to 100:

 - 0: Mute.
 - 100: Original volume.

 @return - 0: Success.
 - < 0: Failure.
 */
- (int)adjustUserPlaybackSignalVolume:(NSString* _Nonnull)userAccount volume:(int)volume NS_SWIFT_NAME(adjustUserPlaybackSignalVolume(_:volume:));

/**
 * Stops/Resumes receiving the audio stream of a specified user.
 *
 * You can call this method before or after joining a channel.
 * If a user leaves a channel, the settings in this method become invalid.
 * @param userAccount  The ID of the specified user.
 * @param mute Whether to stop receiving the audio stream of the specified user:
 * - `YES`: Stop receiving the audio stream of the specified user.
 * - `NO`: (Default) Resume receiving the audio stream of the specified user.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)muteRemoteAudioStream:(NSString* _Nonnull)userAccount mute:(BOOL)mute NS_SWIFT_NAME(muteRemoteAudioStream(_:mute:));

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
 * @param extensionInfo The information for extension definition see AgoraExtensionInfoS
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
                   extensionInfo:(AgoraExtensionInfoS * __nonnull)extensionInfo
                         enabled:(BOOL)enabled NS_SWIFT_NAME(enableExtension(withVendor:extension:extensionInfo:enabled:));

/**
 * Sets the properties of an extension.
 *
 * @param provider The name of the extension provider, e.g. agora.io.
 * @param extension The name of the extension, e.g. agora.beauty.
 * @param extensionInfo The information for extension. See AgoraExtensionInfoS.
 * @param key The key of the extension.
 * @param value The JSON formatted value of the extension key.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)setExtensionPropertyWithVendor:(NSString * __nonnull)provider
                            extension:(NSString * __nonnull)extension
                        extensionInfo:(AgoraExtensionInfoS * __nonnull)extensionInfo
                                  key:(NSString * __nonnull)key
                                value:(NSString * __nonnull)value NS_SWIFT_NAME(setExtensionPropertyWithVendor(_:extension:extensionInfo:key:value:));

/**
 * Gets the properties of an extension.
 *
 * @param provider The name of the extension provider, e.g. agora.io.
 * @param extension The name of the extension, e.g. agora.beauty.
 * @param extensionInfo The information for extension. See AgoraExtensionInfoS.
 * @param key The key of the extension.
 *
 * @return
 * - JSON formatted string of property's value; return null if failed
 */
- (NSString * _Nullable)getExtensionPropertyWithVendor:(NSString * __nonnull)provider
                                             extension:(NSString * __nonnull)extension
                                         extensionInfo:(AgoraExtensionInfoS * __nonnull)extensionInfo
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
 * @param local The local video view and settings. See #AgoraRtcVideoCanvasBase.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)setupLocalVideo:(AgoraRtcVideoCanvasBase * _Nullable)local NS_SWIFT_NAME(setupLocalVideo(_:));

/** Binds the remote user to the video display window, that is, sets the view for the user of the specified userAccount.

 Usually, the application should specify the userAccount of the remote video in the method call before the user enters a channel. If the remote userAccount is unknown to the application, set it later when the application receives the [userJoinedBlock]([AgoraRtcEngineKit userJoinedBlock:]) event.
 If the Video Recording function is enabled, the Video Recording Service joins the channel as a dumb client, which means other clients will also receive the [didJoinedOfUid]([AgoraRtcEngineDelegate rtcEngine:didJoinedOfUid:elapsed:]) event. Your application should not bind it with the view, because it does not send any video stream. If your application cannot recognize the dumb client, bind it with the view when the [firstRemoteVideoDecodedOfUid]([AgoraRtcEngineDelegate rtcEngine:firstRemoteVideoDecodedOfUid:size:elapsed:]) event is triggered. To unbind the user with the view, set the view to null. After the user has left the channel, the SDK unbinds the remote user.

 @param remote AgoraRtcVideoCanvas

 @return * 0: Success.
* <0: Failure.
 */
- (int)setupRemoteVideo:(AgoraRtcVideoCanvasS * _Nonnull)remote NS_SWIFT_NAME(setupRemoteVideo(_:));

/** Configures the remote video display mode. The application can call this method multiple times to change the display mode.

 @param userAccount The userAccount of the user whose video streams are received.
 @param mode AgoraVideoRenderMode
 @param mirror AgoraVideoMirrorMode

 @return * 0: Success.
* <0: Failure.
 */
- (int)setRemoteRenderMode:(NSString* _Nonnull)userAccount
                      mode:(AgoraVideoRenderMode)mode
                    mirror:(AgoraVideoMirrorMode)mirror NS_SWIFT_NAME(setRemoteRenderMode(_:mode:mirror:));

/**
 * Stops or resumes receiving the video stream of a specified user.
 *
 * You can call this method before or after joining a channel.
 * If a user leaves a channel, the settings in this method become invalid.
 *
 * @param userAccount The user account of the specified remote user.
 * @param mute Whether to stop receiving the video stream of the specified user:
 * - `YES`: Stop receiving the video stream of the specified user.
 * - `NO`: (Default) Resume receiving the video stream of the specified user.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)muteRemoteVideoStream:(NSString* _Nonnull)userAccount
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
 @param userAccount The userAccount of the remote user.
 @param pan The sound position of the remote user. The value ranges from -1.0 to 1.0:

 * 0.0: (default) the remote sound comes from the front.
 * -1.0: the remote sound comes from the left.
 * 1.0: the remote sound comes from the right.

 @param gain Gain of the remote user. The value ranges from 0.0 to 100.0. The default value is 100.0 (the original gain of the remote user). The smaller the value, the less the gain.

 @return * 0: Success.
* < 0: Failure.
 */
- (int)setRemoteVoicePosition:(NSString* _Nonnull)userAccount pan:(double)pan gain:(double)gain NS_SWIFT_NAME(setRemoteVoicePosition(_:pan:gain:));

/** Sets spatial audio parameters of a remote user.

 When the local user calls this method to set the spatial audio parameters  of a remote user, the sound difference between the left and right channels allows the local user to track the real-time position of the remote user, creating a real sense of spatial.

**Note:**

- For the best effect, we recommend using the following audio output devices:
  - (iOS) A stereo headset.
  - (macOS) A stereo loudspeaker.
 @param userAccount The userAccount of the remote user.
 @param params The spatial audio parameters of the remote user.

 @return * 0: Success.
* < 0: Failure.
 */
- (int)setRemoteUserSpatialAudioParams:(NSString* _Nonnull)userAccount
                                  params:(AgoraSpatialAudioParams* _Nonnull)params NS_SWIFT_NAME(setRemoteUserSpatialAudioParams(_:params:));

#pragma mark Echo Test
/**-----------------------------------------------------------------------------
 * @name Echo Test
 * -----------------------------------------------------------------------------
 */

/** Launches an audio call test to determine whether the audio devices (for example, headset and speaker) and the network connection are working properly.

 In the test, the user first speaks, and the recording is played back in 10 seconds. If the user can hear the recording in 10 seconds, it indicates that the audio devices and network connection work properly.

 @note  After calling this method, always call stopEchoTest to end the test, otherwise the application will not be able to run the next echo test, nor can it call the `joinChannelByToken` method to start a new call.

 @param successBlock Callback on successfully starting the echo test. See JoinSuccessBlockS in `joinChannelByToken` for a description of the callback parameters.

 @return * 0: Success.
* <0: Failure.
 For example, AgoraErrorCodeRefused(-5)：Failed to launch the echo test.
 */
- (int)startEchoTest:(void(^ _Nullable)(NSString * _Nonnull channel, NSString* _Nonnull userAccount, NSInteger elapsed))successBlock NS_SWIFT_NAME(startEchoTest(_:));

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
                  successBlock:(void(^ _Nullable)(NSString * _Nonnull channel, NSString* _Nonnull userAccount, NSInteger elapsed))successBlock NS_SWIFT_NAME(startEchoTest(withInterval:successBlock:));

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
 * @param userAccount The userAccount of the remote user sending the video stream.
 * @param streamType The video stream type: #AgoraVideoStreamType.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)setRemoteVideoStream:(NSString* _Nonnull)userAccount
                       type:(AgoraVideoStreamType)streamType NS_SWIFT_NAME(setRemoteVideoStream(_:type:));

/**
   * Sets the remote video subscription options
   *
   *
   * @param userAccount The userAccount of the remote user sending the video stream.
   * @param options Sets the video subscription options.
   * @return
   * - 0: Success.
   * - < 0: Failure.
   */
- (int)setRemoteVideoSubscriptionOptions:(NSString* _Nonnull)userAccount
                                 options:(AgoraVideoSubscriptionOptions* _Nonnull)options NS_SWIFT_NAME(setRemoteVideoSubscriptionOptions(_:options:));

#pragma mark Subscribe Blocklist / Allowlist

/**
 * Sets the blocklist of subscribe remote stream audio.
 *
 * @param blocklist The userAccount list of users who do not subscribe to audio.
 *
 * @note
 * If userAccount is in blacklist, the remote user's audio will not be subscribed,
 * even if muteRemoteAudioStream(userAccount, false) and muteAllRemoteAudioStreams(false) are operated.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)setSubscribeAudioBlocklist:(NSArray <NSString*> *_Nonnull)blocklist NS_SWIFT_NAME(setSubscribeAudioBlocklist(_:));

/**
 * Sets the allowlist of subscribe remote stream audio.
 *
 * @param allowlist The userAccount list of users who do subscribe to audio.
 *
 * @note
 * If userAccount is in allowlist, the remote user's audio will be subscribed,
 * even if muteRemoteAudioStream(userAccount, true) and muteAllRemoteAudioStreams(true) are operated.
 *
 * If a user is in the blocklist and allowlist at the same time, the user will not subscribe to audio.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)setSubscribeAudioAllowlist:(NSArray <NSString*> *_Nonnull)allowlist NS_SWIFT_NAME(setSubscribeAudioAllowlist(_:));

/**
 * Sets the blocklist of subscribe remote stream video.
 *
 * @param blocklist The userAccount list of users who do not subscribe to video.
 *
 * @note
 * If userAccount is in blocklist, the remote user's video will not be subscribed,
 * even if muteRemoteVideoStream(userAccount, false) and muteAllRemoteVideoStreams(false) are operated.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)setSubscribeVideoBlocklist:(NSArray <NSString*> *_Nonnull)blocklist NS_SWIFT_NAME(setSubscribeVideoBlocklist(_:));

/**
 * Sets the allowlist of subscribe remote stream video.
 *
 * @param allowlist The userAccount list of users who do subscribe to video.
 *
 * @note
 * If userAccount is in allowlist, the remote user's video will be subscribed,
 * even if muteRemoteVideoStream(userAccount, true) and muteAllRemoteVideoStreams(true) are operated.
 *
 * If a user is in the blocklist and allowlist at the same time, the user will not subscribe to video.
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)setSubscribeVideoAllowlist:(NSArray <NSString*> *_Nonnull)allowlist NS_SWIFT_NAME(setSubscribeVideoAllowlist(_:));

#pragma mark Stream Fallback

/** Sets high priority user list and related remote subscribe stream fallback option.

  This method sets the high priority user list and disables/enables the vips' remote subscribe stream fallback option according to the network conditions in NASA2.

 If you use the option as AgoraStreamFallbackOptionAudioOnly = 2, the AutVos will automatically switch the video from a high-stream to a low-stream, or disable the video when the downlink network conditions cannot support both audio and video to guarantee the quality of the audio. The AutVos monitors the network quality and re-enables the video stream when the network conditions improve.
 Once the subscribed stream falls back to audio only, or the audio stream switches back to the video stream, the [didRemoteSubscribeFallbackToAudioOnly]([AgoraRtcEngineDelegate  rtcEngine:didRemoteSubscribeFallbackToAudioOnly:byUid:]) callback will be triggered.

 @param option AgoraStreamFallbackOptions
 @return * 0: Success.
* <0: Failure.
 */
- (int)setHighPriorityUserList:(NSArray <NSString *> *_Nullable)userAccountList
                        option:(AgoraStreamFallbackOptions)option;

#pragma mark External Media Source

/**
 * Pushes the external video frame.
 *
 * This method pushes the video frame using the AgoraVideoFrame class and
 * passes it to the Agora SDK with the `format` parameter in AgoraVideoFormat.
 *
 * Call \ref setExternalVideoSource:useTexture:pushMode: setExternalVideoSource
 * and set the `pushMode` parameter as `YES` before calling this method.
 * @note
 * In the Communication profile, this method does not support pushing textured
 * video frames.
 * @param frame Video frame containing the SDK's encoded video data to be
 * pushed: #AgoraVideoFrame.
 * @param videoTrackId The id of the video track.
 * @return
 * - `YES`: Success.
 * - `NO`: Failure.
 */
- (BOOL)pushExternalVideoFrame:(AgoraVideoFrame * _Nonnull)frame videoTrackId:(NSUInteger)videoTrackId NS_SWIFT_NAME(pushExternalVideoFrame(_:videoTrackId:));

/**
 * Pushes the encoded external video frame to Agora SDK.
 *
 * @note
 * Ensure that you have configured encoded video source before calling this method.
 *
 * @param frame The encoded external video data, which must be the direct buffer.
 * @param info The encoded external video frame info: AgoraEncodedVideoFrameInfoS.
 *
 * @return
 * - 0: Success, which means that the encoded external video frame is pushed successfully.
 * - < 0: Failure, which means that the encoded external video frame fails to be pushed.
 */
- (int)pushExternalEncodedVideoFrame:(NSData* _Nonnull)frame
                                info:(AgoraEncodedVideoFrameInfoS * _Nonnull)info NS_SWIFT_NAME(pushExternalEncodedVideoFrame(_:info:));

/**
 * Pushes the encoded external video frame to specified connection in Agora SDK.
 *
 * @note
 * Ensure that you have configured encoded video source before calling this method.
 *
 * @param frame The encoded external video data, which must be the direct buffer.
 * @param info The encoded external video frame info: AgoraEncodedVideoFrameInfoS.
 * @param videoTrackId The id of the video track.
 *
 * @return
 * - 0: Success, which means that the encoded external video frame is pushed successfully.
 * - < 0: Failure, which means that the encoded external video frame fails to be pushed.
 */
- (int)pushExternalEncodedVideoFrame:(NSData* _Nonnull)frame
                                  info:(AgoraEncodedVideoFrameInfoS * _Nonnull)info
                            videoTrackId:(NSUInteger)videoTrackId NS_SWIFT_NAME(pushExternalEncodedVideoFrame(_:info:videoTrackId:));


#pragma mark Audio spectrum monitor   
/**
 * Registers an audio spectrum delegate.
 *
 * You need to register the following callbacks
 * according to your scenario:
 * - "onAudioSpectrumComputed": Occurs when the SDK receives the audio data and at set intervals.
 *
 * @param delegate AgoraAudioSpectrumDelegateS
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)registerAudioSpectrumDelegate:(id<AgoraAudioSpectrumDelegateS> _Nullable )delegate NS_SWIFT_NAME(registerAudioSpectrumDelegate(_:));

  /**
   * Releases the audio spectrum delegate.
   *
   * @param delegate AgoraAudioSpectrumDelegateS
   * @return
   * - 0: Success.
   * - < 0: Failure.
   */
- (int)unregisterAudioSpectrumDelegate:(id<AgoraAudioSpectrumDelegateS> _Nullable)delegate NS_SWIFT_NAME(unregisterAudioSpectrumDelegate(_:));

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
- (int)startRtmpStreamWithTranscoding:(NSString* _Nonnull)url transcoding:(AgoraLiveTranscodingS* _Nullable)transcoding NS_SWIFT_NAME(startRtmpStream(withTranscoding:transcoding:));

/** Sets the video layout and audio settings for CDN live. (CDN live only.)

 The SDK triggers the [rtcEngineTranscodingUpdated]([AgoraRtcEngineDelegateS rtcEngineTranscodingUpdated:]) callback when you call the `setLiveTranscoding` method to update the transcoding setting.

 **Note**

 - This method applies to live-broadcast profile only.
 - Ensure that you enable the RTMP Converter service before using this function. See [Prerequisites](https://docs.agora.io/en/Interactive%20Broadcast/cdn_streaming_apple?platform=iOS#prerequisites).
 - If you call the `setLiveTranscoding` method to update the transcoding setting for the first time, the SDK does not trigger the `rtcEngineTranscodingUpdated` callback.


 @param transcoding Sets the CDN live audio/video transcoding settings. See AgoraLiveTranscoding.

 @return = 0: Success.
 *       < 0: Failure.
 */
- (int)updateRtmpTranscoding:(AgoraLiveTranscodingS* _Nullable)transcoding NS_SWIFT_NAME(updateRtmpTranscoding(_:));

#pragma mark Custom Audio PCM Frame
/**
  * @brief register & unregister the player audio observer
  *
  * @param delegate observer object, pass nil to unregister
  * @return int <= 0 On behalf of an error, the value corresponds to one of PLAYER_ERROR
  */
- (BOOL)setAudioFrameDelegate:(id<AgoraAudioFrameDelegateS> _Nullable)delegate NS_SWIFT_NAME(setAudioFrameDelegate(_:));

#pragma mark Custom Video Frame
/**
 * Registers & unregister video frame observer object.
 *
 * @note
 * - Ensure that you call this method before joining the channel.
 *
 * @param delegate An object to the video frame observer: id<AgoraVideoFrameDelegateS>.
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (BOOL)setVideoFrameDelegate:(id<AgoraVideoFrameDelegateS> _Nullable)delegate NS_SWIFT_NAME(setVideoFrameDelegate(_:));

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
- (BOOL)setEncodedVideoFrameDelegate:(id<AgoraEncodedVideoFrameDelegateS> _Nullable)delegate NS_SWIFT_NAME(setEncodedVideoFrameDelegate(_:));

#pragma mark Custom Media Metadata
/** Sets the delegate of the metadata.

 You need to implement the AgoraMediaMetadataDelegateS protocol and specify the type of metadata in this method.

 **Note**

 - Call this method before the `joinChannelByToken` method.
 - This method applies to the live interactive streaming channel profile only.

 @param metadataDelegate The AgoraMediaMetadataDelegateS protocol.
 @param type The metadata type. See \ref AgoraMetadataType. Currently, the SDK supports video metadata only.
 @return
 - YES: Success.
 - NO: Failure.
 */
- (BOOL)setMediaMetadataDelegate:(id<AgoraMediaMetadataDelegateS> _Nullable)metadataDelegate withType:(AgoraMetadataType)type NS_SWIFT_NAME(setMediaMetadataDelegate(_:with:));

#pragma mark Channel Transcoder

/** Get the H265Transcoder instance
 * @return id<AgoraH265TranscoderProtocolS>
 * 
*/
- (id<AgoraH265TranscoderProtocolS>_Nullable)getH265Transcoder NS_SWIFT_NAME (getH265Transcoder());

- (NSInteger)takeSnapshot:(NSString* _Nonnull)userAccount filePath:(NSString* _Nonnull)filePath NS_SWIFT_NAME(takeSnapshot(_:filePath:));

/** Bind local user and a remote user as an audio&video sync group. The remote user is defined by cid and userAccount.
  There’s a usage limit that local user must be a video stream sender. On the receiver side, media streams from same sync group will be time-synced

 @param channelId The channel id
 @param userAccount The user account of the remote user to be bound with (local user)

 @return
 - 0: Success.
 - < 0: Failure.
 */
- (int)setAVSyncSource:(NSString* _Nonnull)channelId userAccount:(NSString* _Nonnull)userAccount NS_SWIFT_NAME(setAVSyncSource(_:userAccount:));

/**
 * Creates a media recorder object and return its pointer.
 *
 * @param info The AgoraRecorderStreamInfoS object. It contains the user account and the channel name.
 * @return
 * - The pointer to \ref "AgoraMediaRecorderS",
 *   if the method call succeeds.
 * - The empty pointer NULL, if the method call fails.
 */
- (AgoraMediaRecorderS * _Nullable)createMediaRecorder:(AgoraRecorderStreamInfoS * _Nonnull)info NS_SWIFT_NAME(createMediaRecorder(withInfo:));

/**
 * Destroy a media recorder source instance.
 *
 * @param mediaRecorder AgoraMediaRecorderS pointer
 *
 * @return
 * - 0: Success.
 * - < 0: Failure.
 */
- (int)destroyMediaRecorder:(AgoraMediaRecorderS * _Nullable)mediaRecorder;

@end


__attribute__((visibility("default"))) @interface AgoraRtcEngineKitS : NSObject<AgoraRtcEngineBaseProtocol, AgoraRtcEngineKitProtocolS>
@property(nonatomic, weak) id<AgoraRtcEngineDelegateS> _Nullable delegate;

- (int)prepareUserAccount:(NSString* _Nonnull)userAccount uid:(NSUInteger)uid;
@end