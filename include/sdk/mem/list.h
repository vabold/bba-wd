#ifndef MEM_LIST_H
#define MEM_LIST_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMLink {
    void *prevObject;
    void *nextObject;
} MEMLink;

typedef struct MEMList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} MEMList;

void MEMInitList(MEMList *list, u16 offset);
void MEMAppendListObject(MEMList *list, void *object);
void MEMRemoveListObject(MEMList *list, void *object);
void *MEMGetNextListObject(MEMList *list, void *object);

#ifdef __cplusplus
}
#endif

#endif
