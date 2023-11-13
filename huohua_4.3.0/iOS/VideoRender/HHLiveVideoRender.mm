//
//  HHLiveVideoRender.m
//  HHLiveSDK_Example
//
//  Created by changjingjing on 2020/10/21.
//  Copyright © 2020 changjingjing. All rights reserved.
//

#import "HHLiveVideoRender.h"
#import <CUCoreFoundation/CUCFWeakSelfMacrocDefine.h>
#import <CUCoreFoundation/CUCFStringUtilMacrocDefine.h>
#include "HHLibYUV/scale_argb.h"
#import "HHLiveEngineManager.h"

@interface HHLiveVideoRender ()

@property (nonatomic, copy) NSString *uid;

@property (nonatomic, strong) dispatch_queue_t renderQueue;

@end

@implementation HHLiveVideoRender

- (instancetype)initWithUid:(NSString *)uid {
    if (self = [self init]) {
        _uid = uid;
    }
    return self;
}

- (instancetype)init {
    if (self = [super init]) {
        _renderQueue = dispatch_queue_create("liveVideoRender.huohua.cn", DISPATCH_QUEUE_SERIAL);
        
    }
    return self;
}

- (BOOL)shouldInitialize {
    return YES;
}

- (void)shouldStart {
    
}

- (void)shouldStop {
    
}

- (void)shouldDispose {
    [self resetFrameCount];
}

- (HHLiveVideoBufferType)bufferType {
    return HHLiveVideoBufferTypePixelBuffer;
}

- (HHLiveVideoPixelFormat)pixelFormat {
    return HHLiveVideoPixelFormatBGRA;
}

- (void)renderPixelBuffer:(CVPixelBufferRef)pixelBuffer rotation:(HHLiveVideoRotation)rotation {
    [self renderPixelBuffer:pixelBuffer rotation:rotation uid:self.uid];
}

- (void)renderRawData:(void *)rawData size:(CGSize)size rotation:(HHLiveVideoRotation)rotation {
    
}

static NSUInteger frameCount = 0;
- (void)renderPixelBuffer:(CVPixelBufferRef)pixelBuffer rotation:(HHLiveVideoRotation)rotation uid:(NSString *)uid {
    if (frameCount > 0) return;
    frameCount ++;
    
    CVBufferRetain(pixelBuffer);
    @weakify(self);
    dispatch_async(_renderQueue, ^{
        @strongify(self);
        [self processPixelBuffer:pixelBuffer rotation:rotation uid:uid];
        CVBufferRelease(pixelBuffer);
    });
}

- (void)processPixelBuffer:(CVPixelBufferRef)pixelBuffer rotation:(HHLiveVideoRotation)rotation uid:(NSString *)uid {
    CVPixelBufferLockBaseAddress(pixelBuffer, 0);
    int width = (int)CVPixelBufferGetWidth(pixelBuffer);
    int height = (int)CVPixelBufferGetHeight(pixelBuffer);
    unsigned char *bgra_data = (unsigned char *)CVPixelBufferGetBaseAddressOfPlane(pixelBuffer, 0);
    int bgra_stride_bgra = (int)CVPixelBufferGetBytesPerRowOfPlane(pixelBuffer, 0);
    if ( bgra_stride_bgra != width * 4) {
        width = bgra_stride_bgra / 4;
    }
    int bgra_length = bgra_stride_bgra * height;
    CVPixelBufferUnlockBaseAddress(pixelBuffer, 0);

    BOOL isScale = NO;
    if (CUCFStringIsNull(uid) || [uid isEqualToString:@"0"]) {
        uid = [[HHLiveEngineManager share] getLiveEngine].rtcConfig.uid;
    }

    CGSize tSize = [[[HHLiveEngineManager share] getLiveEngine] getTextureSize:uid];
    if (width != tSize.width && height != tSize.height) {
        isScale = YES;
        int width_src = width;
        int height_src = height;
        width = (width > tSize.width ? width : tSize.width);
        height = (height > tSize.height ? height : tSize.height);
        int argb_stride_argb_src = bgra_stride_bgra;
        bgra_stride_bgra = width * 4;
        bgra_length = (width * height * 4);
        uint8* argb_data_dst = (uint8* )calloc(bgra_length, sizeof(uint8));
        libyuv::ARGBScale(bgra_data, argb_stride_argb_src, width_src, height_src, argb_data_dst, bgra_stride_bgra, width, height, libyuv::kFilterNone);
        bgra_data = argb_data_dst;
    }
    
    int finalRotation = [self convertRotation:rotation];
    if ((finalRotation % 360) == 180) { // agora需要这样处理，zego应该不需要，等测试zego时，需要注意这块开发
        uint8 temp[4];
        for (int i = 0; i <= (bgra_length / 8); i++) {
            temp[0] = bgra_data[4 * i];
            temp[1] = bgra_data[4 * i + 1];
            temp[2] = bgra_data[4 * i + 2];
            temp[3] = bgra_data[4 * i + 3];
            bgra_data[4 * i] = bgra_data[bgra_length - 4 * i - 2] ;
            bgra_data[4 * i + 1] = bgra_data[bgra_length - 4 * i - 3];
            bgra_data[4 * i + 2] = bgra_data[bgra_length - 4 * i - 4];
            bgra_data[4 * i + 3] = bgra_data[bgra_length - 4 * i -1];
            bgra_data[bgra_length - 4 * i - 4] = temp[2];
            bgra_data[bgra_length - 4 * i - 3] = temp[1];
            bgra_data[bgra_length - 4 * i - 2] = temp[0];
            bgra_data[bgra_length - 4 * i - 1] = temp[3];
        }
    } else {
        [self convertData:bgra_data length:bgra_length];
    }

    if (!isScale) {
        CVBufferRetain(pixelBuffer);
    }

    dispatch_async(dispatch_get_main_queue(), ^{
        [[[HHLiveEngineManager share] getLiveEngine] notificationWithUid:uid rgbaBuffer:bgra_data rgbaStride:bgra_stride_bgra dataLen:bgra_length width:width height:height];
        if (!isScale) {
            CVBufferRelease(pixelBuffer);
        } else {
            free(bgra_data);
        }
        if (frameCount > 0) {
            frameCount --;
        }
    });
}

- (void)convertData:(unsigned char *)data length:(int)length {
    uint8 temp;
    for (int i = 0; i < length / 4; i++) {
        temp = data[i * 4];//b
        data[i * 4] = data[i * 4 + 2];//r
        data[i * 4 + 2] = temp;
    }
}

- (void)resetFrameCount {
    frameCount = 0;
}

- (int)convertRotation:(HHLiveVideoRotation)rotation {
    int finalRotation;
    switch (rotation) {
        case HHLiveVideoRotation90: {
            finalRotation = 90;
        }
            break;
        case HHLiveVideoRotation180: {
            finalRotation = 180;
        }
            break;
        case HHLiveVideoRotation270: {
            finalRotation = 270;
        }
            break;
        default: {
            finalRotation = 0;
        }
            break;
    }
    return finalRotation;
}

@end
