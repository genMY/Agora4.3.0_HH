//
//  Copyright (c) 2020 Agora. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AgoraObjects.h"

@protocol AgoraAudioSpectrumDelegateBase <NSObject>
@optional
/**
 * Reports the audio spectrum of audio recording.
 *
 * This callback reports the audio spectrum data of the audio recording at the moment
 * in the channel.
 *
 * You can set the time interval of this callback using "enableAudioSpectrumMonitor".
 *
 * @param audioSpectrumData The audio spectrum data of audio recording.
 * - true: Processed.
 * - false: Not processed.
 */
- (BOOL)onLocalAudioSpectrum:(NSArray<NSNumber *> * _Nullable)audioSpectrumData NS_SWIFT_NAME(onLocalAudioSpectrum(_:));

@end
