//
//  AgoraH265TranscoderProtocol.h
//  AgoraH265TranscoderProtocol
//
//  Copyright (c) 2022 Agora. All rights reserved.
//

#import "AgoraH265TranscoderBaseProtocol.h"

@protocol AgoraH265TranscoderDelegate;

@protocol AgoraH265TranscoderProtocolS <AgoraH265TranscoderBaseProtocol>

/**
 * Enable transcoding for a channel.
 * @param token The token for authentication.
 * @param channel The unique channel name for the AgoraRTC session in the string format.
 * @param userAccount  User ID.
 * @return
 * -  0: Success.
 * - <0: Failure.
 */
- (NSInteger)enableTranscodeWithToken:(NSString* _Nonnull)token 
                      channel:(NSString* _Nonnull)channel 
                userAccount:(NSString* _Nonnull)userAccount NS_SWIFT_NAME(enableTranscode(token:channel:userAccount:));

/**
 * Query the transcoded channel of a channel.
 * @param token The token for authentication.
 * @param channel The unique channel name for the AgoraRTC session in the string format.
 * @param userAccount  User ID.
 * @return
 * -  0: Success.
 * - <0: Failure.
 */
- (NSInteger)queryChannelWithToken:(NSString* _Nonnull)token 
                           channel:(NSString* _Nonnull)channel 
                       userAccount:(NSString* _Nonnull)userAccount NS_SWIFT_NAME(queryChannel(token:channel:userAccount:));

/**
 * Trigger channel transcoding.
 * @param token The token for authentication.
 * @param channel The unique channel name for the AgoraRTC session in the string format.
 * @param userAccount  User ID.
 * @return
 * -  0: Success.
 * - <0: Failure.
 */
- (NSInteger)triggerTranscodeWithToken:(NSString* _Nonnull)token 
                               channel:(NSString* _Nonnull)channel 
                           userAccount:(NSString* _Nonnull)userAccount NS_SWIFT_NAME(triggerTranscode(token:channel:userAccount:));
                                   
@end