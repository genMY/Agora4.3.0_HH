//
//  HHAgoraAudioDumpManager.h
//  HHLiveSDK
//
//  Created by changjingjing on 2020/10/20.
//  Copyright © 2020 changjingjing. All rights reserved.
//

#import "HHAgoraAudioDumpManager.h"
//#import <HHLiveSDK/HHLiveConstant.h>

//@import CUCoreFoundation;
//@import HHAppConfig;
//@import SSZipArchive;
//@import HHCDNUploader;

@implementation HHAgoraAudioDumpManager

+ (void)startUploadAudioDump:(NSString *)audioDumpDirectory progress:(void (^)(float percent))progress completion:(void (^)(NSError *error))completion {
//    if (!CUCFDirectoryIsExist(audioDumpDirectory)) {
//        completion([NSError errorWithDomain:@"dump 文件不存在" code:1 userInfo:nil]);
//    }
//    NSString *file = [HHAgoraAudioDumpManager zipAudioDumpFilePath];
//    BOOL res = [SSZipArchive createZipFileAtPath:file withContentsOfDirectory:audioDumpDirectory keepParentDirectory:YES];
//    if (!res) {
//        if (completion) {
//            completion([NSError errorWithDomain:@"压缩失败" code:1 userInfo:nil]);
//        }
//        [HHAgoraAudioDumpManager deleteAgoraAudioDumpCacheDirectory];
//    }
//    NSString *fileName = [audioDumpDirectory lastPathComponent];
//    NSArray *fileStrings = [fileName componentsSeparatedByString:@"-"];
//    if (fileStrings.count == 0) return;
//    NSString *classroomCode = fileStrings.firstObject;
//    NSString *key = [NSString stringWithFormat:@"%@/agora-log/%@/%@%@.zip", [[[[HHAppConfigManager share] getCommonEnvironmentConfig] getEnvironment] lowercaseString], classroomCode, fileName, [NSString stringWithFormat:@"%@", CUCFDateToStringByFormat([NSDate date], (HHLiveDateFormatDateWithTime))]];
//    HHUploadRequest *request = [[HHUploadRequest alloc] initWithFilePath:file fileName:nil key:key type:HHUploadResourceTypeZip channel:nil keyInfix:nil navigationConfigName:@"useOssRTCLog" isDefaultTurnOn:NO];
//    [[HHUploadManager share] startUploadTask:nil uploadRequest:request progressBlock:^(CGFloat percent) {
//        if (progress) {
//            progress(percent);
//        }
//    } successBlock:^(HHUploadResponse * _Nullable response) {
//        if (completion) {
//            completion(nil);
//        }
//        [HHAgoraAudioDumpManager deleteAgoraAudioDumpCacheDirectory];
//    } failBlock:^(NSError * _Nullable error, NSString * _Nullable taskId) {
//        if (completion) {
//            completion([NSError errorWithDomain:@"上传失败" code:1 userInfo:nil]);
//        }
//        [HHAgoraAudioDumpManager deleteAgoraAudioDumpCacheDirectory];
//    }];
}

+ (NSString *)getOrCreateAgoraAudioDumpCacheDirectory:(NSString *)subDirectory {
//    if (!subDirectory) {
//        subDirectory = @"agora-audio-dump";
//    }
//    NSString *res = [[HHAgoraAudioDumpManager getAudioDumpCacheDirectory] stringByAppendingPathComponent:subDirectory];
//    if (!CUCFDirectoryIsExist(res)) {
//        CUCFFileDirectoryCreate(res);
//        CUCFAppAddSkipBackupAttributeToItemAtPath(res);
//    }
//    return res;
    return  NULL;
}

+ (void)deleteAgoraAudioDumpCacheDirectory {
//    NSString *path = [HHAgoraAudioDumpManager getAudioDumpCacheDirectory];
//    if (CUCFDirectoryIsExist(path)) {
//        CUCFFileDeleteDirectory(path);
//    }
//    path = [HHAgoraAudioDumpManager zipAudioDumpFilePath];
//    if (CUCFFileIsExist(path)) {
//        CUCFFileDeletePath(path);
//    }
}

+ (NSString *)zipAudioDumpFilePath {
    NSString *path = [NSTemporaryDirectory() stringByAppendingPathComponent:@"9c41e464-7cfa-4b1a-bb2b-871094a8005c.zip"];
    return path;
}

+ (NSString *)getAudioDumpCacheDirectory {
    return [NSTemporaryDirectory() stringByAppendingPathComponent:@"agora-audio-dump"];
}

@end
