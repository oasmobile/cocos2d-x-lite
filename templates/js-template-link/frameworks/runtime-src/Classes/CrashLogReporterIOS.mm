
#include "CrashLogReporter.h"
#include "CrashLogReporterIOS.h"

#include "platform/CCFileUtils.h"

using namespace cocos2d;


static NSString *server_url = @"http://log-en-dol.oasmobile.com/crash_log/index.php";
static NSString *log_file_prefix = @"ios";
static NSString *log_file = @"dol.log";


@implementation CrashLogReporterIOS

+ (void)setCrashLogReporterUrl:(NSString *)url
{
    if (!url || [url isEqualToString:@""]) return ;
    server_url = url;
}


+ (void)setLogFilePrefix:(NSString *)prefix
{
    if (!prefix || [prefix isEqualToString:@""]) return ;
    log_file_prefix = prefix;
}


+ (NSString *)getLogFile
{
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    NSString *nsWritablePath = [NSString stringWithUTF8String: writablePath.c_str()];
    NSString *logFile = [NSString stringWithFormat:@"%@%@", nsWritablePath, log_file];
    return logFile;
}


+ (void)resetLogFile
{
    [self clearLogFile];
    [self reopenLogFile];
}


+ (void)reopenLogFile
{
    NSString *logFilePath = [self getLogFile];
    freopen([logFilePath cStringUsingEncoding:NSASCIIStringEncoding], "a+", stdout);
}


+ (void)clearLogFile
{
    NSString *logFilePath = [self getLogFile];
    NSError *error;
    if ([[NSFileManager defaultManager] isDeletableFileAtPath:logFilePath]) {
        BOOL success = [[NSFileManager defaultManager] removeItemAtPath:logFilePath error:&error];
        if (!success) {
            NSLog(@"Error removing log file at path: %@", error.localizedDescription);
        }
    }
}

@end


static void DoUploadLog()
{
    NSDate * date = [NSDate date];
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"yyyy_MM_dd_HH_mm_ss"];
    NSString *localDateString = [dateFormatter stringFromDate:date];
    NSTimeInterval intervalSince1970 = [date timeIntervalSince1970];
    
    NSString *log_file_name = [NSString stringWithFormat:@"%@_%@_%f.log", log_file_prefix, localDateString, intervalSince1970];
    
    NSURL *url = [NSURL URLWithString:server_url];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url];
    
    [request setHTTPMethod:@"POST"];
    
    // Header
    NSString *lineEnd = @"\r\n";
    NSString *twoHyphens = @"--";
    NSString *boundary = @"*****";
    
    [request setValue:@"Keep-Alive" forHTTPHeaderField:@"Connection"];
    [request setValue:@"multipart/form-data" forHTTPHeaderField:@"ENCTYPE"];
    NSString *contentType = [NSString stringWithFormat:@"multipart/form-data; boundary=%@", boundary];
    [request setValue:contentType forHTTPHeaderField:@"Content-Type"];
    [request setValue:@"gzip" forHTTPHeaderField:@"Accept-Encoding"];
    
    [request setValue:log_file_name forHTTPHeaderField:@"uploaded_file"];
    
    
    // Body
    NSMutableData *body = [NSMutableData data];
    
    [body appendData:[[NSString stringWithFormat:@"%@%@%@", twoHyphens, boundary, lineEnd] dataUsingEncoding:NSUTF8StringEncoding]];
    NSString *contentDisposition = [NSString stringWithFormat:@"Content-Disposition: form-data; name=\"uploaded_file\";filename=\"%@\"%@", log_file_name, lineEnd];
    [body appendData:[contentDisposition dataUsingEncoding:NSUTF8StringEncoding]];
    [body appendData:[lineEnd dataUsingEncoding:NSUTF8StringEncoding]];
    
    
    // Data
    NSString *logFile = [CrashLogReporterIOS getLogFile];
    
    if ([[NSFileManager defaultManager] fileExistsAtPath:logFile])
    {
        NSString *logContents = [[NSString alloc] initWithContentsOfFile:logFile encoding:NSUTF8StringEncoding error:NULL];
        [body appendData:[logContents dataUsingEncoding:NSUTF8StringEncoding]];
    }
    
    
    // Final Boundary
    [body appendData:[[NSString stringWithFormat:@"%@%@%@%@%@", lineEnd, twoHyphens, boundary, twoHyphens, lineEnd] dataUsingEncoding:NSUTF8StringEncoding]];
    
    
    // Set the body
    [request setHTTPBody:body];
    
    
    // Send
    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse *response, NSData *data, NSError *error) {
        
        NSInteger responseCode = [(NSHTTPURLResponse *)response statusCode];
        
        if (!error && responseCode == 200)
        {
            NSLog(@"CRASH_LOG_REPORTER Upload Success");
            [CrashLogReporterIOS resetLogFile];
        }
        else
        {
            NSLog(@"CRASH_LOG_REPORTER Upload Fail");
        }
    }];
    
    
    /*
    NSURLConnection *connection = [NSURLConnection connectionWithRequest:request delegate:nil];
    [connection start];//*/
    
    /*
     NSData *returnData = [NSURLConnection sendSynchronousRequest:request returningResponse:nil error:nil];
     NSString *returnString = [[NSString alloc] initWithData:returnData encoding:NSUTF8StringEncoding];
     NSLog(@"result %@", returnString);//*/
}


void CrashLogReporter::UploadLog()
{
    DoUploadLog();
}
