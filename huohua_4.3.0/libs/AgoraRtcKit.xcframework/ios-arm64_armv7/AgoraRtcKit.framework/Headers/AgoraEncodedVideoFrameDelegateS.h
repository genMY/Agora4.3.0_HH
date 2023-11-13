//
//  Copyright (c) 2018 Agora. All rights reserved.
//

#import <Foundation/Foundation.h>

@class AgoraEncodedVideoFrameInfoS;

@protocol AgoraEncodedVideoFrameDelegateS <NSObject>
@optional

/**
 * Occurs when  get H264 video data interface before decoding
 */
- (BOOL)onEncodedVideoFrameReceived:(NSData * _Nonnull )videoData length:(size_t)length info:(AgoraEncodedVideoFrameInfoS * _Nonnull)videoFrameInfo NS_SWIFT_NAME(onEncodedVideoFrameReceived(_:length:info:));
@end
