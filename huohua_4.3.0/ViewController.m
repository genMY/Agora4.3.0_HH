//
//  ViewController.m
//  huohua_4.3.0
//
//  Created by yangmoumou on 2023/11/9.
//

#import "ViewController.h"
#import <AgoraRtcKit/AgoraRtcKit.h>
#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonDigest.h>
#import <CommonCrypto/CommonHMAC.h>
#import <Security/Security.h>



@interface ViewController ()<AgoraRtcEngineDelegate,AgoraVideoFrameDelegate,AgoraRtcMediaPlayerDelegate,AgoraEncodedVideoFrameDelegate>
@property (nonatomic, strong) AgoraRtcEngineKit *rtcEngineKit;

@property (nonatomic) NSInteger userId;
@property (weak, nonatomic) IBOutlet UIView *mediaPlayerView;

@property (nonatomic,strong) id<AgoraRtcMediaPlayerProtocol> mediaPlayerProtocol;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    AgoraRtcEngineConfig *config = [[AgoraRtcEngineConfig alloc] init];
    config.appId = @"aab8b8f5a8cd4469a63042fcfafe7063";
    
    self.rtcEngineKit = [AgoraRtcEngineKit sharedEngineWithConfig:config  delegate:self];
    
    AgoraRtcChannelMediaOptions *channelMediaOptions = [[AgoraRtcChannelMediaOptions alloc] init];
    channelMediaOptions.channelProfile = AgoraChannelProfileLiveBroadcasting;
    channelMediaOptions.clientRoleType = AgoraClientRoleBroadcaster;
    channelMediaOptions.publishMicrophoneTrack = true;
    
//    [self.rtcEngineKit setParameters:@"{\"rtc.api_treat_stringuid_as_intuid\":true}"];
    
    [self.rtcEngineKit enableVideo];
   
    self.mediaPlayerProtocol = [self.rtcEngineKit createMediaPlayerWithDelegate:self];
    
    [self.mediaPlayerProtocol open:[[NSBundle mainBundle]pathForResource:@"504938FA8E56E079EAFA078D0087EEFE" ofType:@"MP4"] startPos:0.0];
//    [self.mediaPlayerProtocol setView:self.mediaPlayerView];

    
    AgoraRtcVideoCanvas *canvas = [[AgoraRtcVideoCanvas alloc] init];
    canvas.view = self.mediaPlayerView;
    canvas.sourceType = AgoraVideoSourceTypeMediaPlayer;
    canvas.renderMode = AgoraVideoRenderModeHidden;
    canvas.mediaPlayerId = self.mediaPlayerProtocol.getMediaPlayerId;
    
    [self.rtcEngineKit setupLocalVideo:canvas];

    [self.rtcEngineKit setEncodedVideoFrameDelegate:self];
    [self.rtcEngineKit startPreview:(AgoraVideoSourceTypeMediaPlayer)];
   
//   int code =  [self.rtcEngineKit joinChannelByToken:nil channelId:@"12121212" userAccount:@"123456" mediaOptions:channelMediaOptions joinSuccess:nil];
    [self.rtcEngineKit joinChannelByToken:nil channelId:@"12121212" uid:222333 mediaOptions:channelMediaOptions joinSuccess:nil];
    
    [self.rtcEngineKit setVideoFrameDelegate:self];
    
}


- (IBAction)getUserInfo:(UIButton *)sender {
//    AgoraErrorCode errorcode;
////    AgoraUserInfo *userInfo = [self.rtcEngineKit getUserInfoByUid:123456 withError:&errorcode];
//    AgoraUserInfo *userInfo = [self.rtcEngineKit getUserInfoByUserAccount:@"123456" withError:&errorcode];
//    NSLog(@"error---- %ld ----- %ld ------- %@",errorcode,userInfo.uid,userInfo.userAccount);

//    [self.mediaPlayerProtocol play];
    
    [self.mediaPlayerProtocol seekToPosition:810000];
    
 
    NSInteger videoTime =   [self.mediaPlayerProtocol getDuration];
    NSLog(@"-------video TIme  --- %ld",videoTime);
    
}
- (void)AgoraRtcMediaPlayer:(id<AgoraRtcMediaPlayerProtocol>)playerKit didChangedToState:(AgoraMediaPlayerState)state error:(AgoraMediaPlayerError)error {
    if (state== AgoraMediaPlayerStateOpenCompleted) {
//        [self.mediaPlayerProtocol play];
    }
    NSLog(@"didChangedToState---------- %ld",state);
}



- (void)AgoraRtcMediaPlayer:(id<AgoraRtcMediaPlayerProtocol>)playerKit didChangedToPosition:(NSInteger)position {
    NSLog(@"playerKit----- %ld----------",position);
}
- (void)rtcEngine:(AgoraRtcEngineKit *)engine didOccurError:(AgoraErrorCode)errorCode {
    
}


- (void)rtcEngine:(AgoraRtcEngineKit *)engine didJoinedOfUid:(NSUInteger)uid elapsed:(NSInteger)elapsed {
    NSLog(@"didJoinedOfUid---- %ld ",uid);
    
}

- (void)rtcEngine:(AgoraRtcEngineKit *)engine didUserInfoUpdatedWithUserId:(NSUInteger)uid userInfo:(AgoraUserInfo *)userInfo {
    NSLog(@"didUserInfoUpdatedWithUserId---- %ld ----- %ld ------- %@",uid,userInfo.uid,userInfo.userAccount);
}


- (BOOL)onCaptureVideoFrame:(AgoraOutputVideoFrame *)videoFrame sourceType:(AgoraVideoSourceType)sourceType {
    
    
    return true;
}

- (BOOL)onRenderVideoFrame:(AgoraOutputVideoFrame *)videoFrame uid:(NSUInteger)uid channelId:(NSString *)channelId {
    
    return true;
}

- (BOOL)onPreEncodeVideoFrame:(AgoraOutputVideoFrame *)videoFrame sourceType:(AgoraVideoSourceType)sourceType {
    return true;
}

- (AgoraVideoFormat)getVideoFormatPreference{
    return AgoraVideoFormatCVPixelNV12;
}

- (BOOL)getRotationApplied {
    return true;
}

- (BOOL)getMirrorApplied{
    return true;
}

- (AgoraVideoFrameProcessMode)getVideoFrameProcessMode{
    return AgoraVideoFrameProcessModeReadWrite;
}

- (void)rtcEngine:(AgoraRtcEngineKit *)engine networkQuality:(NSUInteger)uid txQuality:(AgoraNetworkQuality)txQuality rxQuality:(AgoraNetworkQuality)rxQuality {
    NSLog(@"networkQuality--- uid %ld-----txQ -- %ld -----rx  %ld",uid,txQuality,rxQuality);
}

- (void)rtcEngine:(AgoraRtcEngineKit *)engine didAudioRouteChanged:(AgoraAudioOutputRouting)routing {
    NSLog(@"wsssss");
}

@end
