//
//
//  Copyright (c) 2018 Agora. All rights reserved.
//
#import <Foundation/Foundation.h>

/** The definition of AgoraMediaMetadataDelegate.
@note  Implement the callback in this protocol in the critical thread. We recommend avoiding any time-consuming operation in the critical thread.
*/
@protocol AgoraMediaMetadataDelegateS <NSObject>
@required

/** Occurs when the local user receives the metadata.
 @param data The received metadata.
 @param userAccount The user account of the user who sends the metadata.
 @param timestamp The NTP timestamp (ms) when the metadata is sent.
 @note If the receiver is audience, the receiver cannot get the NTP timestamp (ms) from `timestamp`.
 */
- (void)receiveMetadata:(NSData * _Nonnull)data fromUserAccount:(NSString * _Nonnull)userAccount atTimestamp:(NSTimeInterval)timestamp NS_SWIFT_NAME(receiveMetadata(_:fromUserAccount:atTimestamp:));

@end
