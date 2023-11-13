//
//  AgoraRtcEngineKit.h
//  AgoraRtcEngineKit
//
//  Copyright (c) 2018 Agora. All rights reserved.
//

#import "AgoraVideoFrameDelegateBase.h"

@protocol AgoraVideoFrameDelegateS <AgoraVideoFrameDelegateBase>
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
 * @param userAccount ID of the remote user who sends the current video frame.
 * @param channelId Channel name.
 * @param videoFrame A pointer to the video frame: AgoraOutputVideoFrame
 * @return Determines whether to ignore the current video frame if the post-processing fails:
 * - true: Do not ignore.
 * - false: Ignore, in which case this method does not sent the current video frame to the SDK.
 */
- (BOOL)onRenderVideoFrame:(AgoraOutputVideoFrame * _Nonnull)videoFrame userAccount:(NSString* _Nonnull)userAccount channelId:(NSString * _Nonnull)channelId NS_SWIFT_NAME(onRenderVideoFrame(_:userAccount:channelId:));

@end
