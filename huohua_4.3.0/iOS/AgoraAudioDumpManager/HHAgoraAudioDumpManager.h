//
//  HHAgoraAudioDumpManager.h
//  HHLiveSDK
//
//  Created by changjingjing on 2020/10/20.
//  Copyright © 2020 changjingjing. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface HHAgoraAudioDumpManager : NSObject

+ (void)startUploadAudioDump:(NSString *)audioDumpDirectory progress:(void (^)(float percent))progress completion:(void (^)(NSError *error))completion;

+ (NSString *)getOrCreateAgoraAudioDumpCacheDirectory:(NSString *)subDirectory;

+ (void)deleteAgoraAudioDumpCacheDirectory;

@end
