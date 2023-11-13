//
//  AgoraRtcEngineKit.h
//  AgoraRtcEngineKit
//
//  Copyright (c) 2018 Agora. All rights reserved.
//

#import "AgoraVideoFrameDelegateBase.h"

@protocol AgoraVideoFrameDelegate <AgoraVideoFrameDelegateBase>
@optional

/**
 * Occurs each time the SDK receives a video frame sent by the remote user.
 *
 * After you successfully register the video frame observer, the SDK triggers this callback each time a
 * video frame is received. In this callback, you can get the video data sent by the remote user. You
 * can then post-process the data according to your scenarios.
 *
 * After post-processing, you can send the processed data back to the SDK by setting the `videoFrame`
 * parameter in this callback.
 *
 * @param uid ID of the remote user who sends the current video frame.
 * @param channelId Channel name.
 * @param videoFrame A pointer to the video frame: AgoraOutputVideoFrame
 * @return Determines whether to ignore the current video frame if the post-processing fails:
 * - true: Do not ignore.
 * - false: Ignore, in which case this method does not sent the current video frame to the SDK.
 */
- (BOOL)onRenderVideoFrame:(AgoraOutputVideoFrame * _Nonnull)videoFrame uid:(NSUInteger)uid channelId:(NSString * _Nonnull)channelId NS_SWIFT_NAME(onRenderVideoFrame(_:uid:channelId:));

/* Unavailable Delegate Methods */
#if TARGET_OS_IPHONE
- (BOOL)onCaptureVideoFrame:(AgoraOutputVideoFrame * _Nonnull)videoFrame NS_SWIFT_NAME(onCapture(_:)) __attribute__((availability(ios,deprecated=7_0,message="Use onCaptureVideoFrame:sourceType: instead.")));
- (BOOL)onSecondaryCameraCaptureVideoFrame:(AgoraOutputVideoFrame * _Nonnull)videoFrame NS_SWIFT_NAME(onSecondaryCameraCapture(_:)) __attribute__((availability(ios,deprecated=7_0,message="Use onCaptureVideoFrame:sourceType: instead.")));
- (BOOL)onScreenCaptureVideoFrame:(AgoraOutputVideoFrame * _Nonnull)videoFrame NS_SWIFT_NAME(onScreenCapture(_:)) __attribute__((availability(ios,deprecated=7_0,message="Use onCaptureVideoFrame:sourceType: instead.")));
- (BOOL)onSecondaryScreenCaptureVideoFrame:(AgoraOutputVideoFrame * _Nonnull)videoFrame NS_SWIFT_NAME(onSecondaryScreenCapture(_:)) __attribute__((availability(ios,deprecated=7_0,message="Use onCaptureVideoFrame:sourceType: instead.")));
- (BOOL)onPreEncodeVideoFrame:(AgoraOutputVideoFrame * _Nonnull)videoFrame NS_SWIFT_NAME(onPreEncode(_:)) __attribute__((availability(ios,deprecated=7_0,message="Use onPreEncodeVideoFrame:sourceType: instead.")));
- (BOOL)onPreEncodeScreenVideoFrame:(AgoraOutputVideoFrame * _Nonnull)videoFrame NS_SWIFT_NAME(onPreEncodeScreenVideoFrame(_:)) __attribute__((availability(ios,deprecated=7_0,message="Use onPreEncodeVideoFrame:sourceType: instead.")));
#endif

#if (!(TARGET_OS_IPHONE) && (TARGET_OS_MAC))
- (BOOL)onCaptureVideoFrame:(AgoraOutputVideoFrame * _Nonnull)videoFrame NS_SWIFT_NAME(onCapture(_:)) __attribute__((availability(macos,deprecated=10_9,message="Use onCaptureVideoFrame:sourceType: instead.")));
- (BOOL)onSecondaryCameraCaptureVideoFrame:(AgoraOutputVideoFrame * _Nonnull)videoFrame NS_SWIFT_NAME(onSecondaryCameraCapture(_:)) __attribute__((availability(macos,deprecated=10_9,message="Use onCaptureVideoFrame:sourceType: instead.")));
- (BOOL)onScreenCaptureVideoFrame:(AgoraOutputVideoFrame * _Nonnull)videoFrame NS_SWIFT_NAME(onScreenCapture(_:)) __attribute__((availability(macos,deprecated=10_9,message="Use onCaptureVideoFrame:sourceType: instead.")));
- (BOOL)onSecondaryScreenCaptureVideoFrame:(AgoraOutputVideoFrame * _Nonnull)videoFrame NS_SWIFT_NAME(onSecondaryScreenCapture(_:)) __attribute__((availability(macos,deprecated=10_9,message="Use onCaptureVideoFrame:sourceType: instead.")));
- (BOOL)onPreEncodeVideoFrame:(AgoraOutputVideoFrame * _Nonnull)videoFrame NS_SWIFT_NAME(onPreEncode(_:)) __attribute__((availability(macos,deprecated=10_9,message="Use onPreEncodeVideoFrame:sourceType: instead.")));
- (BOOL)onPreEncodeScreenVideoFrame:(AgoraOutputVideoFrame * _Nonnull)videoFrame NS_SWIFT_NAME(onPreEncodeScreenVideoFrame(_:)) __attribute__((availability(macos,deprecated=10_9,message="Use onPreEncodeVideoFrame:sourceType: instead.")));
#endif

@end
