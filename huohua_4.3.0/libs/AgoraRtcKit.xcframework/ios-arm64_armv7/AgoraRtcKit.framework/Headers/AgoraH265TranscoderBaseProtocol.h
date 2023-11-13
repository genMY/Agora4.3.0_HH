//
//  AgoraH265TranscoderProtocol.h
//  AgoraH265TranscoderProtocol
//
//  Copyright (c) 2022 Agora. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol AgoraH265TranscoderDelegate;

@protocol AgoraH265TranscoderBaseProtocol <NSObject>
                                   
/**
 * Register a AgoraH265TranscoderDelegate object.
 * @param delegate AgoraH265TranscoderDelegate.
 * @return
 * -  0: Success.
 * - <0: Failure.
 */
- (NSInteger)registerTranscoderDelegate:(id<AgoraH265TranscoderDelegate>_Nullable)delegate NS_SWIFT_NAME(registerTranscoderDelegate(_:));

/**
 * Unregister a AgoraH265TranscoderDelegate object.
 * @param delegate AgoraH265TranscoderDelegate.
 * @return
 * -  0: Success.
 * - <0: Failure.
 */
- (NSInteger)unregisterTranscoderDelegate:(id<AgoraH265TranscoderDelegate>_Nullable)delegate NS_SWIFT_NAME(unregisterTranscoderDelegate(_:));

@end