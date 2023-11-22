//
//  HHLiveAgoraAudioFrameObserver.mm
//  huohua
//
//  Created by lijunjiie on 2020/06/04.
//  Copyright © 2020 wanduoduo All rights reserved.
//

#import <Foundation/Foundation.h>
#import "HHLiveAgoraAudioFrameObserver.h"
#import <AgoraRtcKit/AgoraRtcEngineKit.h>
#import <AgoraRtcKit/IAgoraRtcEngine.h>
#import <AgoraRtcKit/IAgoraMediaEngine.h>
#import <string.h>
#import "LiveAudioCircularBuffer.h"
#import "live_scoped_ptr.h"
#import <mutex>

using namespace LiveRTC;

static scoped_ptr<LiveAudioCircularBuffer<char>> playoutBuf(new LiveAudioCircularBuffer<char>(2048,true));
static NSObject *threadLockPlay = [[NSObject alloc] init];

class LiveAgoraAudioFrameObserver : public agora::media::IAudioFrameObserver {
    
    public:
    std::atomic<float>  playOutSignalValue_{1.0f};
    
    void setPlayoutSignalVolume(float volume){
        @synchronized (threadLockPlay) {
            playOutSignalValue_ = volume;
        }
    }
    
    float getPlayoutSignalVolume() {
        @synchronized (threadLockPlay) {
            return playOutSignalValue_;
        }
    }

    void pushData(char *data,int length){
        @synchronized (threadLockPlay) {
            playoutBuf->Push(data, length);
        }
    }
    
    virtual bool onRecordAudioFrame(AudioFrame& audioFrame) {
        return true;
    }
    
    virtual bool onPlaybackAudioFrame(AudioFrame& audioFrame) {
    @synchronized (threadLockPlay) {
//        int bytes = audioFrame.samples * audioFrame.channels * audioFrame.bytesPerSample;
//        if (playoutBuf->mAvailSamples < bytes) {
//            return true;
//        }
//        //计算重采样钱的数据大小 重采样的采样率 * SDK回调时间 * 声道数 * 字节数
//        char *data = (char *)malloc(bytes);//--------------------------------
//        playoutBuf->Pop(data, bytes);
//        int16_t *p16 = (int16_t *)data;
//        int16_t *audioBuf = (int16_t *)audioFrame.buffer;
//        for (int i = 0; i < bytes / 2; ++i) {
//            audioBuf[i] += (p16[i] * playOutSignalValue_);
//            //audio overflow
//            if (audioBuf[i] > 32767) {
//                audioBuf[i] = 32767;
//            } else if (audioBuf[i] < -32768) {
//                audioBuf[i] = -32768;
//            }
//        }
//        free(data);
    }
        return true;
    }
    
    virtual bool onMixedAudioFrame(AudioFrame& audioFrame) {
        return false;
    }
    
    virtual bool onPlaybackAudioFrameBeforeMixing(unsigned int uid, AudioFrame& audioFrame) {
        return false;
    }
    
private:
    
};

@implementation HHLiveAgoraAudioFrameObserver

//static LiveAgoraAudioFrameObserver s_audioFrameObserver;

+ (void)resetAudioBuffer {
    @synchronized (self) {
        playoutBuf.reset(new LiveAudioCircularBuffer<char>(2048,true));
    }
}

+ (void)pushAudioFrame:(CMSampleBufferRef)audioFrame {
    //pushExternalAudioBuffer
    CMBlockBufferRef audioBuffer  = CMSampleBufferGetDataBuffer(audioFrame);
    OSStatus err;
    size_t lengthAtOffSet;
    size_t totalBytes;
    char *samples;
    err = CMBlockBufferGetDataPointer(audioBuffer, 0, &lengthAtOffSet, &totalBytes, &samples);
    if (totalBytes == 0) {
        return;
    }
//    s_audioFrameObserver.pushData(samples, (int)totalBytes);
}
//
//+ (void)setVolume:(float)volume {
////    s_audioFrameObserver.setPlayoutSignalVolume(volume);
//}
//
//+ (float)getVolume {
////    return s_audioFrameObserver.getPlayoutSignalVolume();
//}

//+ (int)registerAudioFrameObserver:(AgoraRtcEngineKit *)kit {
//    if (!kit) {
//        return -1;
//    }
//    
//    agora::rtc::IRtcEngine* rtc_engine = (agora::rtc::IRtcEngine*)kit.getNativeHandle;
//    agora::util::AutoPtr<agora::media::IMediaEngine> mediaEngine;
//    mediaEngine.queryInterface(rtc_engine, agora::AGORA_IID_MEDIA_ENGINE);
//    if (mediaEngine)
//    {
//        mediaEngine->registerAudioFrameObserver(&s_audioFrameObserver);
//    }
//    return 0;
//}

//+ (int)deregisterAudioFrameObserver:(AgoraRtcEngineKit *)kit {
//    if (!kit) {
//        return -1;
//    }
//    
//    agora::rtc::IRtcEngine* rtc_engine = (agora::rtc::IRtcEngine*)kit.getNativeHandle;
//    agora::util::AutoPtr<agora::media::IMediaEngine> mediaEngine;
//    mediaEngine.queryInterface(rtc_engine, agora::AGORA_IID_MEDIA_ENGINE);
//    if (mediaEngine)
//    {
//        mediaEngine->registerAudioFrameObserver(NULL);
//    }
//    return 0;
//}

@end
