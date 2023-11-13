//
//  AgoraRtcEngineKit.h
//  AgoraRtcEngineKit
//
//  Copyright (c) 2018 Agora. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AgoraAudioFrameDelegateBase.h"

/**
 * The AgoraAudioFrameDelegate protocol enables audio frame callback event notifications to your application.
 */
@protocol AgoraAudioFrameDelegateS <AgoraAudioFrameDelegateBase>
@optional

/**
 * Occurs when the before-mixing playback audio frame is received.
 * @param channelId Unique channel name for the AgoraRTC session in the string
 * format. The string length must be less than 64 bytes. Supported character
 * scopes are:
 * - All lowercase English letters: a to z.
 * - All uppercase English letters: A to Z.
 * - All numeric characters: 0 to 9.
 * - The space character.
 * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
 * @param userAccount ID of the remote user.
 * @param frame A pointer to the audio frame: AgoraAudioFrame.
 * @return
 * - true: The before-mixing playback audio frame is valid and is encoded and sent.
 * - false: The before-mixing playback audio frame is invalid and is not encoded or sent.
 */
- (BOOL)onPlaybackAudioFrameBeforeMixing:(AgoraAudioFrame* _Nonnull)frame channelId:(NSString * _Nonnull)channelId userAccount:(NSString * _Nonnull)userAccount  NS_SWIFT_NAME(onPlaybackAudioFrame(beforeMixing:channelId:userAccount:));

@end
