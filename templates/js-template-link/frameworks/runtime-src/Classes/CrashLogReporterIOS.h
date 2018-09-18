
#import <Foundation/Foundation.h>

@interface CrashLogReporterIOS : NSObject

+ (void)setCrashLogReporterUrl:(NSString *)url;
+ (void)setLogFilePrefix:(NSString *)prefix;

+ (NSString *)getLogFile;
+ (void)resetLogFile;
+ (void)reopenLogFile;
+ (void)clearLogFile;

@end

