//
//  HHAgoraLiveVideoPlayer.h
//  huohuaedu
//
//  Created by lijunjie on 2018/6/23.
//  Copyright © 2018年 wanduoduo. All rights reserved.
//

#import <Foundation/Foundation.h>
//#import "HHVideoPlayerProtocol.h"
//#import "HHBaseVideoPlayer.h"
#import <AgoraRtcKit/AgoraRtcKit.h>

@interface HHAgoraLiveVideoPlayer : NSString
//<HHVideoPlayerProtocol>
@property (nonatomic, strong) AgoraRtcEngineKit *rtcEngineKit;
@end
