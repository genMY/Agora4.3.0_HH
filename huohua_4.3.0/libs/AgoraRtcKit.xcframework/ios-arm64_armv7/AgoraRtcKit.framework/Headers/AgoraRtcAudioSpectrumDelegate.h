//
//  Copyright (c) 2020 Agora. All rights reserved.
//

#import "AgoraRtcAudioSpectrumDelegateBase.h"

@protocol AgoraAudioSpectrumDelegate <AgoraAudioSpectrumDelegateBase>
@optional
/**
 * Reports the audio spectrum of remote user.
 *
 * This callback reports the IDs and audio spectrum data of the loudest speakers at the moment
 * in the channel.
 *
 * You can set the time interval of this callback using  "enableAudioSpectrumMonitor".
 *
 * @param AudioSpectrumInfo The pointer to AudioSpectrumInfo, which is an array containing
 * the user ID and audio spectrum data for each speaker.
 * - This array contains the following members:
 *   - `uid`, which is the UID of each remote speaker
 *   - `audioSpectrumData`, which reports the audio spectrum of each remote speaker.
 *   - `spectrumDataLength`, the length of audio spectrum data.
 * - true: Processed.
 * - false: Not processed.
 */
- (BOOL)onRemoteAudioSpectrum:(NSArray<AgoraAudioSpectrumInfo *> * _Nullable)AudioSpectrumInfo NS_SWIFT_NAME(onRemoteAudioSpectrum(_:));


@end
