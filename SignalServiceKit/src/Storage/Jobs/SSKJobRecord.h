//
//  Copyright (c) 2019 Open Whisper Systems. All rights reserved.
//

#import "TSYapDatabaseObject.h"

NS_ASSUME_NONNULL_BEGIN

extern NSErrorDomain const SSKJobRecordErrorDomain;

typedef NS_ERROR_ENUM(SSKJobRecordErrorDomain, JobRecordError){
    JobRecordError_AssertionError = 100,
    JobRecordError_IllegalStateTransition,
};

typedef NS_ENUM(NSUInteger, SSKJobRecordStatus) {
    SSKJobRecordStatus_Unknown,
    SSKJobRecordStatus_Ready,
    SSKJobRecordStatus_Running,
    SSKJobRecordStatus_PermanentlyFailed,
    SSKJobRecordStatus_Obsolete
};

#pragma mark -

@interface SSKJobRecord : TSYapDatabaseObject

@property (nonatomic) NSUInteger failureCount;
@property (nonatomic) NSString *label;

- (instancetype)initWithLabel:(NSString *)label NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithUniqueId:(NSString *_Nullable)uniqueId NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

// --- CODE GENERATION MARKER

// This snippet is generated by /Scripts/sds_codegen/sds_generate.py. Do not manually edit it, instead run
// `sds_codegen.sh`.

// clang-format off

- (instancetype)initWithUniqueId:(NSString *)uniqueId
                    failureCount:(NSUInteger)failureCount
                           label:(NSString *)label
                          sortId:(unsigned long long)sortId
                          status:(SSKJobRecordStatus)status
NS_SWIFT_NAME(init(uniqueId:failureCount:label:sortId:status:));

// clang-format on

// --- CODE GENERATION MARKER

@property (readonly, nonatomic) SSKJobRecordStatus status;

// GRDB TODO: Replace sortId column with autoincremented id column
@property (nonatomic, readonly) UInt64 sortId;

- (BOOL)saveAsStartedWithTransaction:(YapDatabaseReadWriteTransaction *)transaction
                               error:(NSError **)outError NS_SWIFT_NAME(saveAsStarted(transaction:));

- (void)saveAsPermanentlyFailedWithTransaction:(YapDatabaseReadWriteTransaction *)transaction
    NS_SWIFT_NAME(saveAsPermanentlyFailed(transaction:));

- (void)saveAsObsoleteWithTransaction:(YapDatabaseReadWriteTransaction *)transaction
    NS_SWIFT_NAME(saveAsObsolete(transaction:));

- (BOOL)saveRunningAsReadyWithTransaction:(YapDatabaseReadWriteTransaction *)transaction
                                    error:(NSError **)outError NS_SWIFT_NAME(saveRunningAsReady(transaction:));

- (BOOL)addFailureWithWithTransaction:(YapDatabaseReadWriteTransaction *)transaction
                                error:(NSError **)outError NS_SWIFT_NAME(addFailure(transaction:));

@end

NS_ASSUME_NONNULL_END