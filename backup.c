#include <CoreServices/CoreServices.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

char watchDir[256];
char backupRoot[256];

/* Create timestamp */
void get_timestamp(char *buf) {
    time_t now = time(NULL);
    strftime(buf, 50, "%Y-%m-%d_%H-%M-%S", localtime(&now));
}

/* FSEvents callback */
void eventCallback(
    ConstFSEventStreamRef streamRef,
    void *clientCallBackInfo,
    size_t numEvents,
    void *eventPaths,
    const FSEventStreamEventFlags eventFlags[],
    const FSEventStreamEventId eventIds[]
) {
    char timestamp[50];
    get_timestamp(timestamp);

    char backupDir[512];
    snprintf(backupDir, sizeof(backupDir), "%s/%s", backupRoot, timestamp);

    /* Create backup directory */
    char mkdirCmd[600];
    snprintf(mkdirCmd, sizeof(mkdirCmd), "mkdir -p \"%s\"", backupDir);
    system(mkdirCmd);

    /* Run rsync */
    char rsyncCmd[800];
    snprintf(rsyncCmd, sizeof(rsyncCmd),
             "rsync -a --delete \"%s/\" \"%s/\"",
             watchDir, backupDir);
    system(rsyncCmd);

    /* Log */
    char logCmd[800];
    snprintf(logCmd, sizeof(logCmd),
             "echo \"Backup triggered at %s\" >> \"%s/backup.log\"",
             timestamp, backupRoot);
    system(logCmd);

    printf("Backup completed at %s\n", timestamp);
}

int main() {
    printf("Enter directory to monitor: ");
    scanf("%255s", watchDir);

    printf("Enter backup root directory: ");
    scanf("%255s", backupRoot);

    /* Create backup root if not exists */
    char cmd[600];
    snprintf(cmd, sizeof(cmd), "mkdir -p \"%s\"", backupRoot);
    system(cmd);

    CFStringRef path = CFStringCreateWithCString(
        NULL, watchDir, kCFStringEncodingUTF8);

    CFArrayRef pathsToWatch = CFArrayCreate(
        NULL, (const void **)&path, 1, NULL);

    FSEventStreamRef stream = FSEventStreamCreate(
        NULL,
        &eventCallback,
        NULL,
        pathsToWatch,
        kFSEventStreamEventIdSinceNow,
        1.0,
        kFSEventStreamCreateFlagFileEvents
    );

    FSEventStreamScheduleWithRunLoop(
        stream, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);

    FSEventStreamStart(stream);

    printf("\nMonitoring directory (macOS FSEvents)…\n");
    CFRunLoopRun();

    return 0;
}
