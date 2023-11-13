//
//  AgoraRtcEngineKit.h
//  AgoraRtcEngineKit
//
//  Copyright (c) 2018 Agora. All rights reserved.
//

#import "AgoraMediaRecorderBase.h"

@protocol AgoraMediaRecorderDelegateS;

@protocol AgoraMediaRecorderProtocolS <NSObject>
@required

/**
 * Registers the AgoraMediaRecorderDelegate delegate.
 *
 * @since v4.0.0
 *
 * @note Call this method before the startRecording method.
 *
 * @param delegate The callbacks for recording audio and video streams. See AgoraMediaRecorderDelegate 
 *
 * @return
 * - 0(ERR_OK): Success.
 * - < 0: Failure:
 */
- (int)setMediaRecorderDelegate:(id<AgoraMediaRecorderDelegateS> _Nullable)delegate;

@end

__attribute__((visibility("default"))) @interface AgoraMediaRecorderS : NSObject<AgoraMediaRecorderBaseProtocol, AgoraMediaRecorderProtocolS>
@end