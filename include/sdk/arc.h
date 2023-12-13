#ifndef ARC_H
#define ARC_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void *archiveStartAddr;
    void *FSTStart;
    void *fileStart;
    u32 entryNum;
    char *FSTStringStart;
    u32 FSTLength;
    u32 currDir;
} ARCHandle;

typedef struct {
    ARCHandle *handle;
    u32 startOffset;
    u32 length;
} ARCFileInfo;

BOOL ARCInitHandle(void *arcBinary, ARCHandle *handle);
BOOL ARCOpen(ARCHandle *handle, const char *name, ARCFileInfo *fileInfo);
void *ARCGetStartAddrInMem(ARCFileInfo *fileInfo);
u32 ARCGetStartOffset(ARCFileInfo *fileInfo);
u32 ARCGetLength(ARCFileInfo *fileInfo);
BOOL ARCClose(ARCFileInfo *fileInfo);

#ifdef __cplusplus
}
#endif

#endif
